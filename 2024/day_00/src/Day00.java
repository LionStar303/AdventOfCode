import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;

public class Day00 {

    private static int result1 = 0;
    private static int result2 = 0;
    private static ArrayList<String> input;

    public static void main(String[] args) {
        
        System.out.println("...starte...");

        String folderPath = "2024\\day_00\\";
        String demoPath = folderPath + "demo-input.txt";
        String path = folderPath + "input.txt";
        readInput(new File(demoPath));

        // Part 1

        System.out.println("result of part 1: " + result1);

        // Part 2
        
        System.out.println("result of part 2: " + result2);
        System.out.println("...success...");
    }
    
    private static void readInput(File file) {
        try {
            Scanner myReader = new Scanner(file);
            while(myReader.hasNextLine()) input.add(myReader.nextLine());
            myReader.close();
        } catch (Exception e) {
            e.printStackTrace();;
        }
    }
}
