package days;
import java.io.File;
import java.util.Scanner;

public class Day11 {

    private static final int ITERATIONS1 = 25;
    private static final int ITERATIONS2 = 75;
    private static int result1 = 0;
    private static int result2 = 0;
    private static String[] input;

    public static void main(String[] args) {
        
        System.out.println("...starte...");

        String folderPath = "2024\\input\\";
        String path = folderPath + "input11.txt";
        readInput(new File(path));
        long time = System.currentTimeMillis();

        // Part 1
        for(String stone : input) result1 += getStones(stone, ITERATIONS1);
        time = System.currentTimeMillis() - time;
        System.out.println("result of part 1: " + result1 + " in " + time + "ms");

        // Part 2
        for(String stone : input) {
            result2 += getStones(stone, ITERATIONS2);
            System.out.println(result2);
        }
        System.out.println("result of part 2: " + result2);
        System.out.println("...success...");
    }

    private static int getStones(String stone, int i) {
        if(i == 0) return 1;
        // rule 1: replace 0 by 1
        if(Long.parseLong(stone) == 0) return getStones("1", i-1);
        // rule 2: split any stone with even number of digits
        if(stone.length() % 2 == 0) return getStones(stone.substring(0, stone.length() / 2), i-1) + getStones(String.valueOf(Long.parseLong(stone.substring(stone.length() / 2))), i-1);
        // rule 3: multiply by 2024
        return getStones(String.valueOf(Long.parseLong(stone) * 2024), i-1);

    }
    
    private static void readInput(File file) {
        try {
            Scanner myReader = new Scanner(file);
            while(myReader.hasNextLine()) input = myReader.nextLine().split(" ");
            myReader.close();
        } catch (Exception e) {
            e.printStackTrace();;
        }
    }
}
