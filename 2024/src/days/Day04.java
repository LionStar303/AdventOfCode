package days;
import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;

public class Day04 {
    enum Direction {
        TOP,
        TOP_RIGHT,
        RIGHT,
        BOTTOM_RIGHT,
        BOTTOM,
        BOTTOM_LEFT,
        LEFT,
        TOP_LEFT
    }

    private static int result1 = 0;
    private static int result2 = 0;
    private static ArrayList<char[]> input;
    private static ArrayList<char[]> valids;

    @SuppressWarnings("unused")
    public static void main(String[] args) {
        
        System.out.println("...starte...");

        String folderPath = "2024\\input\\";
        String demoPath = folderPath + "demo-input.txt";
        String path = folderPath + "input04.txt";
        readInput(new File(path));
        valids = new ArrayList<>();

        for(int line = 0; line < input.size(); line++) {
            valids.add(String.valueOf(input.get(line)).replaceAll("[X,M,A,S]",".").toCharArray());
        }
        /*for(char[] line : valids) {
            for(char c : line) System.out.print(c);
            System.out.println();
        }*/

        // Part 1

        for(int line = 0; line < input.size(); line++) {
            for(int i = 0; i < input.get(line).length; i++) {
                check(input, line, i, 'X', Direction.TOP);
                check(input, line, i, 'X', Direction.TOP_RIGHT);
                check(input, line, i, 'X', Direction.RIGHT);
                check(input, line, i, 'X', Direction.BOTTOM_RIGHT);
                check(input, line, i, 'X', Direction.BOTTOM);
                check(input, line, i, 'X', Direction.BOTTOM_LEFT);
                check(input, line, i, 'X', Direction.LEFT);
                check(input, line, i, 'X', Direction.TOP_LEFT);
            }
        }

        System.out.println("result of part 1: " + result1);

        // Part 2
        
        System.out.println("result of part 2: " + result2);
        System.out.println("...success...");
    }

    private static char getNext(char c) {
        switch (c) {
            case 'X': return 'M';
            case 'M': return 'A';
            case 'A': return 'S';
            default: return'.';
        }
    }

    private static void check(ArrayList<char[]> input, int line, int i, char c, Direction direction) {
        if(line < 0 || line > input.size()-1) return;     // return wenn zu weit oben oder zu weit unten
        if(i < 0 || i > input.get(line).length-1) return; // return wenn zu weit rechts oder zu weit links
        if(input.get(line)[i] != c) return;               // return wenn falscher Buchstabe

        if(c == 'S') {     // return wenn Ziel erreicht
            result1++;
            return;
        }
        switch (direction) {
            case TOP: line--; break;
            case TOP_RIGHT: line--; i++; break;
            case RIGHT: i++; break;
            case BOTTOM_RIGHT: line++; i++; break;
            case BOTTOM: line++; break;
            case BOTTOM_LEFT: line++; i--; break;
            case LEFT: i--; break;
            case TOP_LEFT: line--; i--; break;
            default: break;
        }
        check(input, line, i, getNext(c), direction);        // check top
    }
    
    private static void readInput(File file) {
        try {
            input = new ArrayList<>();
            Scanner myReader = new Scanner(file);
            while(myReader.hasNextLine()) input.add(myReader.nextLine().toCharArray());
            myReader.close();
        } catch (Exception e) {
            e.printStackTrace();;
        }
    }
}
