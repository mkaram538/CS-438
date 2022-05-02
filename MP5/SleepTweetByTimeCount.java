import java.io.IOException;
import java.util.StringTokenizer;
import java.text.SimpleDateFormat;
import java.text.ParseException;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class SleepTweetByTimeCount {

    public static class TokenizerMapper
            extends Mapper<Object, Text, Text, IntWritable>{

        private final static IntWritable one = new IntWritable(1);
        private Text word = new Text();
        private Text hourText = new Text();
        private Text timeLabel = new Text("T");
        private Text textLabel = new Text("W");
        private Text sleepWord = new Text("sleep");

        public void map(Object key, Text value, Context context
        ) throws IOException, InterruptedException {
            StringTokenizer itr = new StringTokenizer(value.toString());

            // First checks if line is empty
            if (itr.hasMoreTokens()) {
                // Then checks what the line begins with
                word.set(itr.nextToken());
                // If T, then it is a time line and the hour of the tweet is grabbed
                if (word.equals(timeLabel)) {
                    // If it does continues through the rest of the line
                    while (itr.hasMoreTokens()) {
                        String time = itr.nextToken();
                        String test = time;
                        java.text.SimpleDateFormat format = new java.text.SimpleDateFormat("HH:mm:ss");
                        // Tries to parse the token as a time, if it can, finds the hour substring then stores
                        // the value in a Text variable so that if sleep is in the text it can be accessed
                        try{
                            format.parse(test);
                            String hour = time.substring(0, time.indexOf(":"));
                            hourText.set(hour);
                        }
                        catch(ParseException e) {
                        }
                    }
                // If W, then the line is checked for an instance of "sleep"
                } else if (word.equals(textLabel)) {
                    boolean contains = false;
                    // Iterates through the tokens for the line to determine if "sleep" is present
                    while (itr.hasMoreTokens()) {
                        word.set(itr.nextToken());
                        if (word.equals(sleepWord)) {
                            contains = true;
                        }
                    }
                    // If so, maps the hour of the tweet to the value of one
                    if (contains) {
                        context.write(hourText, one);
                    }
                }
            }

        }
    }

    public static class IntSumReducer
            extends Reducer<Text,IntWritable,Text,IntWritable> {
        private IntWritable result = new IntWritable();

        public void reduce(Text key, Iterable<IntWritable> values,
                           Context context
        ) throws IOException, InterruptedException {
            int sum = 0;
            for (IntWritable val : values) {
                sum += val.get();
            }
            result.set(sum);
            context.write(key, result);
        }
    }

    public static void main(String[] args) throws Exception {
        Configuration conf = new Configuration();
        Job job = Job.getInstance(conf, "sleep tweet count");
        job.setJarByClass(SleepTweetByTimeCount.class);
        job.setMapperClass(TokenizerMapper.class);
        job.setCombinerClass(IntSumReducer.class);
        job.setReducerClass(IntSumReducer.class);
        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(IntWritable.class);
        FileInputFormat.addInputPath(job, new Path(args[0]));
        FileOutputFormat.setOutputPath(job, new Path(args[1]));
        System.exit(job.waitForCompletion(true) ? 0 : 1);
    }
}