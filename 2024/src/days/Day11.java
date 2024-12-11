package days;
import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;

public class Day11 {

    private static final int ITERATIONS = 25;
    private static int result1 = 0;
    private static int result2 = 0;
    private static String[] input;
    private static ArrayList<String> line = new ArrayList<>();

    public static void main(String[] args) {
        
        System.out.println("...starte...");

        String folderPath = "2024\\input\\";
        String path = folderPath + "input11.txt";
        readInput(new File(path));
        for(String stone : input) line.add(stone);

        // Part 1
        for(int i = 0; i < ITERATIONS; i++) {
            int length = line.size();
            for(int j = 0; j < length; j++) {
                String stone = line.get(j);
                // rule 1: replace 0 by 1
                if(Long.parseLong(stone) == 0) {
                    line.set(j, "1");
                    continue;
                }
                // rule 2: split any stone with even number of digits
                if(stone.length() % 2 == 0) {
                    String stone1 = stone.substring(0, stone.length() / 2);
                    // alle führenden nullen von Stone 2 entfernen
                    String stone2 = String.valueOf(Long.parseLong(stone.substring(stone.length() / 2)));
                    line.set(j, stone1);
                    line.add(j+1, stone2);
                    length++; j++;// stone2 überspringen
                    continue;
                }
                // rule 3: multiply by 2024
                line.set(j, String.valueOf(Long.parseLong(stone) * 2024));  
            }
            System.out.println(i);
        }
        result1 = line.size();
        System.out.println("result of part 1: " + result1);

        // Part 2
        
        System.out.println("result of part 2: " + result2);
        System.out.println("...success...");
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
