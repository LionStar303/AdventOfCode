import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Day03 {

    private static int result1 = 0;
    private static int result2 = 0;
    private static String input;

    public static void main(String[] args) {
        
        System.out.println("...starte...");

        String folderPath = "2024\\day_03\\";
        String demoPath = folderPath + "demo-input.txt";
        String path = folderPath + "input.txt";
        readInput(new File(path));

        // Part 1
        Pattern doPattern = Pattern.compile("do\\(\\)|don't\\(\\)");
        Matcher doMatcher = doPattern.matcher(input);
        String clearedInput = "";

        int start = 0;
        while(doMatcher.find()) {
            if(start < 0 && doMatcher.group().equals(new String("do()"))) start = doMatcher.start();
            else if(start >= 0 && doMatcher.group().equals(new String("don't()"))) {
                System.out.println(start + " - " + doMatcher.start());
                clearedInput += input.substring(start, doMatcher.start());
                start = -1;
            }
        }

        Pattern mulPattern = Pattern.compile("mul\\(\\d+,\\d+\\)");
        Matcher mulMatcher = mulPattern.matcher(clearedInput);

        while(mulMatcher.find()) {
            String cmd = mulMatcher.group();
            cmd = cmd.substring(4,cmd.length()-1);
            String[] ab = cmd.split(",");
            result1 += Integer.parseInt(ab[0]) * Integer.parseInt(ab[1]);
        }

        System.out.println("result of part 1: " + result1);

        // Part 2
        
        System.out.println("result of part 2: " + result2);
        System.out.println("...success...");
    }
    
    private static void readInput(File file) {
        try {
            input = "";
            Scanner myReader = new Scanner(file);
            while(myReader.hasNextLine()) input += (myReader.nextLine());
            myReader.close();
        } catch (Exception e) {
            e.printStackTrace();;
        }
    }
}
