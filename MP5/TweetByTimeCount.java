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

public class TweetByTimeCount {

    public static class TokenizerMapper
            extends Mapper<Object, Text, Text, IntWritable>{

        private final static IntWritable one = new IntWritable(1);
        private Text word = new Text();
        private Text timeStamp = new Text("T");

        public void map(Object key, Text value, Context context
        ) throws IOException, InterruptedException {
            StringTokenizer itr = new StringTokenizer(value.toString());

            // First checks if the line begins with "T" which is the label of the time line
            if (itr.hasMoreTokens()) {
                word.set(itr.nextToken());
                if (word.equals(timeStamp)) {
                    // If it does continues through the rest of the line
                    while (itr.hasMoreTokens()) {
                        String time = itr.nextToken();
                        String test = time;
                        java.text.SimpleDateFormat format = new java.text.SimpleDateFormat("HH:mm:ss");
                        // Tries to parse the token as a time, if it can finds the hour substring then maps
                        // the hour to a value of one
                        try{
                            format.parse(test);
                            String hour = time.substring(0, time.indexOf(":"));
                            word.set(hour);
                            context.write(word, one);
                        }
                        catch(ParseException e) {
                        }
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
        Job job = Job.getInstance(conf, "tweet count");
        job.setJarByClass(TweetByTimeCount.class);
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