import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;

public class Day02 {

    private static int result1 = 0;
    private static int result2 = 0;
    private static ArrayList<String> input;

    public static void main(String[] args) {
        
        System.out.println("...starte...");

        String demoPath = "2024\\day_02\\" + "demo-input.txt";
        String path = "2024\\day_02\\" + "testinput.txt";
        readInput(new File(path));

        // Part 1

        for(String line : input) {
            String[] numArray = line.split(" ");
            ArrayList<Integer> nums = new ArrayList<Integer>();
            for(String s : numArray) {
                nums.add(Integer.parseInt(s));
            }
            if(isSafe(nums)) result1++;
        }

        System.out.println("result of part 1: " + result1);

        // Part 2
        
        for(String line : input) {
            String[] numArray = line.split(" ");
            ArrayList<Integer> nums = new ArrayList<Integer>();
            for(String s : numArray) {
                nums.add(Integer.parseInt(s));
            }
            if(isSafe2(nums)) result2++;
        }
        
        System.out.println("result of part 2: " + result2);
        System.out.println("...success...");
    }
    
    private static boolean isSafe(ArrayList<Integer> nums) {
        boolean inc = (nums.get(1) - nums.get(0)) > 0;
        for(int i = 1; i < nums.size(); i++) {
            if(((nums.get(i) - nums.get(i-1)) > 0) != inc) {
                return false;
            }
            if((Math.abs(nums.get(i) - nums.get(i-1)) < 1) || (Math.abs(nums.get(i) - nums.get(i-1)) > 3)) {
                return false;
            }
        }
        return true;
    }

    private static boolean isSafe2(ArrayList<Integer> nums) {
        boolean inc = (nums.get(1) - nums.get(0)) > 0;
        for(int i = 1; i < nums.size(); i++) {
            if(((nums.get(i) - nums.get(i-1)) > 0) != inc) {
                ArrayList<Integer> nums2 = new ArrayList<Integer>(nums);
                nums2.remove(0);
                if(isSafe(nums2)) {
                    return true;
                }
                nums.remove(i);
                return isSafe(nums);
            }
            if((Math.abs(nums.get(i) - nums.get(i-1)) < 1) || (Math.abs(nums.get(i) - nums.get(i-1)) > 3)) {
                ArrayList<Integer> nums2 = new ArrayList<Integer>(nums);
                nums2.remove(0);
                if(isSafe(nums2)) {
                    return true;
                }
                nums.remove(i);
                return isSafe(nums);
            }
        }
        return true;
    }

    private static void readInput(File file) {
        try {
            input = new ArrayList<String>();
            Scanner myReader = new Scanner(file);
            while(myReader.hasNextLine()) {
                input.add(myReader.nextLine());
            }
            myReader.close();
        } catch (Exception e) {
            e.printStackTrace();;
        }
    }
}
