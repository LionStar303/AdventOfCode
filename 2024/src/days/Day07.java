package days;
import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class Day07 {

    private static long result1 = 0;
    private static long result2 = 0;
    private static ArrayList<long[]> input = new ArrayList<>();

    @SuppressWarnings("unused")
    public static void main(String[] args) {
        
        System.out.println("...starte...");

        String folderPath = "2024\\input\\";
        String demoPath = folderPath + "demo-input.txt";
        String path = folderPath + "input07.txt";
        readInput(new File(path));

        // Part 1
        long time = System.currentTimeMillis();
        for(long[] nums : input) {
            for(int count = 0; count < Math.pow(2, nums.length-1); count++) {
                final int localCount = count;
                long res = nums[1];
                for(int i = 2; i < nums.length; i++) {
                    if((int)(localCount / Math.pow(2,i-2)) % 2 == 0) res *= nums[i];
                    else res += nums[i];
                }
                if(res > nums[0]) continue;
                if(res == nums[0]) { result1 += nums[0]; break; }
            }
        }
        time = System.currentTimeMillis() - time;
        System.out.println("result of part 1: " + result1 + "  " + time + "ms");

        // Part 2
        time = System.currentTimeMillis();
        try {
            ExecutorService es = Executors.newFixedThreadPool(Runtime.getRuntime().availableProcessors());
            List<Future<?>> futures = new ArrayList<>();
            
            for(long[] nums : input) {
                futures.add(es.submit(() -> {
                    for(int count = 0; count < Math.pow(3, nums.length-1); count++) {
                        long res = nums[1];
                        for(int i = 2; i < nums.length; i++) {
                            if((int)(count / Math.pow(3,i-2)) % 3 == 0) res *= nums[i];
                            else if((int)(count / Math.pow(3,i-2)) % 3 == 1) res += nums[i];
                            else res = Long.parseLong(String.valueOf(res) + String.valueOf(nums[i]));
                        }
                        if(res > nums[0]) continue;
                        if(res == nums[0]) {
                            synchronized(Day07.class) { result2 += nums[0]; }
                            break;
                        }
                    }
                }));
            }
            
            // Wait for all tasks to finish
            for (Future<?> future : futures) {
                future.get(); // Wait for completion
            }
    
            es.shutdown(); // Shutdown the executor
        } catch (Exception e) {
            // TODO: handle exception
        } 
        time = System.currentTimeMillis() - time;
        System.out.println("result of part 2: " + result2 + "  " + time + "ms");
        System.out.println("...success...");
    }
    
    private static void readInput(File file) {
        try {
            Scanner myReader = new Scanner(file);
            while(myReader.hasNextLine()) {
                String line[] = myReader.nextLine().split("(:)* ");
                long nums[] = new long[line.length];
                for(int i = 0; i < line.length; i++) nums[i] = Long.parseLong(line[i]);
                input.add(nums);
            }
            myReader.close();
        } catch (Exception e) {
            e.printStackTrace();;
        }
    }
}
