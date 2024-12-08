package days;
import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;

public class Day08 {

    private static int result1 = 0;
    private static int result2 = 0;
    private static ArrayList<String> input = new ArrayList<>();

    public static void main(String[] args) {
        
        System.out.println("...starte...");

        String folderPath = "2024\\input\\";
        String path = folderPath + "input08.txt";
        readInput(new File(path));

        ArrayList<char[]> antinodes = new ArrayList<char[]>();
        for(int line = 0; line < input.size(); line ++) {
            antinodes.add(input.get(line).replaceAll("\\w", ".").toCharArray());
        }

        // Part 1
        // x1,y1 Koordinaten der ersten Antenne
        for(int y1 = 0; y1 < input.size(); y1++) {
            for(int x1 = 0; x1 < input.get(y1).length(); x1++) {
                char antenna1 = input.get(y1).charAt(x1);
                if(antenna1 == '.') continue; // continue wenn keine Antenne

                // x2,y2 Koordinaten der zweiten Antenne
                for(int y2 = y1; y2 < input.size(); y2++) {
                    for(int x2 = 0; x2 < input.get(y2).length(); x2++) {
                        if((x1 == x2 && y1 == y2) || input.get(y2).charAt(x2) != antenna1) continue; // continue wenn keine, falsche oder selbe Antenne
                        int dx = x1 - x2;
                        int dy = y1 - y2;
                        // Antinodes markieren wenn im grid
                        try { antinodes.get(y1+dy)[x1+dx] = '#'; } catch (IndexOutOfBoundsException e) { }
                        try { antinodes.get(y2-dy)[x2-dx] = '#'; } catch (IndexOutOfBoundsException e) { }
                    }
                }
            }
        }
        for(char[] carr : antinodes) for(char c : carr) if(c == '#') result1++;
        System.out.println("result of part 1: " + result1);

        // Part 2
        // x1,y1 Koordinaten der ersten Antenne
        for(int y1 = 0; y1 < input.size(); y1++) {
            for(int x1 = 0; x1 < input.get(y1).length(); x1++) {
                char antenna1 = input.get(y1).charAt(x1);
                if(antenna1 == '.') continue; // continue wenn keine Antenne

                // x2,y2 Koordinaten der zweiten Antenne
                for(int y2 = y1; y2 < input.size(); y2++) {
                    for(int x2 = 0; x2 < input.get(y2).length(); x2++) {
                        if((x1 == x2 && y1 == y2) || input.get(y2).charAt(x2) != antenna1) continue; // continue wenn keine, falsche oder selbe Antenne
                        int dx = x1 - x2, dy = y1 - y2;
                        dx /= gcd(dx, dy);
                        dy /= gcd(dx, dy);
                        int ndx = dx, ndy = dy;
                        // Antinodes markieren wenn im grid
                        while((y1-ndy < antinodes.size() && y1-ndy >= 0 && x1-ndx < antinodes.get(y1-ndy).length && x1-ndx >= 0) ||
                              (y2+ndy < antinodes.size() && y2+ndy >= 0 && x2+ndx < antinodes.get(y2+ndy).length && x2+ndx >= 0)) {
                            try { antinodes.get(y1-ndy)[x1-ndx] = '#'; } catch (IndexOutOfBoundsException e) { }
                            try { antinodes.get(y2+ndy)[x2+ndx] = '#'; } catch (IndexOutOfBoundsException e) { }
                            ndx += dx;
                            ndy += dy;
                        }
                    }
                }
            }
        }
        for(char[] carr : antinodes) for(char c : carr) if(c == '#') result2++;
        for(char[] carr : antinodes) System.out.println(carr);
        System.out.println("result of part 2: " + result2);
        System.out.println("...success...");
    }

    private static int gcd(int a, int b) {
        if(b == 0) return Math.abs(a);
        else return gcd(b, a % b);
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
