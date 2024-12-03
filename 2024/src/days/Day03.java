package days;
import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import utils.Mul;

public class Day03 {

    private static int result1 = 0;
    private static int result2 = 0;
    private static String input;

    public static void main(String[] args) {
        
        System.out.println("...starte...");

        String folderPath = "2024\\input\\";
        String demoPath = folderPath + "demoInput.txt";
        String path = folderPath + "input03.txt";
        readInput(new File(path));
        
        String regex = "do\\(\\)|don't\\(\\)|mul\\(\\d+,\\d+\\)";
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(input);
        ArrayList<Mul> muls = new ArrayList<Mul>();
        boolean valid = true;

        while(matcher.find()) {
            switch (matcher.group()) {
                case "do()":
                    valid = true;
                    break;
                case "don't()":
                    valid = false;
                    break;
                default:
                    // 01234...n
                    // mul(1,2)
                    String[] ab = matcher.group().substring(4, matcher.group().length()-1).split(",");
                    muls.add(new Mul(Integer.parseInt(ab[0]), Integer.parseInt(ab[1]), valid));
                    break;
            }
        }

        // Part 1

        muls.forEach((mul) -> result1 += mul.getP());

        System.out.println("result of part 1: " + result1);

        // Part 2
        
        muls.forEach((mul) -> { if(mul.isValid()) result2 += mul.getP(); });
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
