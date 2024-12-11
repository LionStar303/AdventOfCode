package days;
import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;

public class Day10 {

    private static int result1 = 0;
    private static int result2 = 0;
    private static ArrayList<char[]> input = new ArrayList<>();

    public static void main(String[] args) {
        
        System.out.println("...starte...");

        String folderPath = "2024\\input\\";
        String path = folderPath + "input10.txt";
        readInput(new File(path));

        // Part 1
        for(int y = 0; y < input.size(); y++) {
            char[] line = input.get(y);
            for(int x = 0; x < line.length; x++) {
                if(line[x] == '0') {
                    result1 += getPaths1(new ArrayList<String>(), x, y, '0');
                }
            }
        }
        System.out.println("result of part 1: " + result1);

        // Part 2
        for(int y = 0; y < input.size(); y++) {
            char[] line = input.get(y);
            for(int x = 0; x < line.length; x++) {
                if(line[x] == '0') {
                    result2 += getPaths2(x, y, '0');
                }
            }
        }        
        System.out.println("result of part 2: " + result2);
        System.out.println("...success...");
    }

    private static int getPaths1(ArrayList<String> visited, int x, int y, char c) {
        if(c == '9' && input.get(y)[x] == '9' && !visited.contains(x + "," + y)) {
            visited.add(x + "," + y);
            return 1;
        }
        int res = 0; c++; // char um 1
        try { if(input.get(y-1)[x] == c) res += getPaths1(visited, x, y-1, c); } catch (Exception e) { }
        try { if(input.get(y+1)[x] == c) res += getPaths1(visited, x, y+1, c); } catch (Exception e) { }
        try { if(input.get(y)[x-1] == c) res += getPaths1(visited, x-1, y, c); } catch (Exception e) { }
        try { if(input.get(y)[x+1] == c) res += getPaths1(visited, x+1, y, c); } catch (Exception e) { }
        return res;
    }

    private static int getPaths2(int x, int y, char c) {
        if(c == '9' && input.get(y)[x] == '9') return 1;
        int res = 0; c++; // char um 1
        try { if(input.get(y-1)[x] == c) res += getPaths2(x, y-1, c); } catch (Exception e) { }
        try { if(input.get(y+1)[x] == c) res += getPaths2(x, y+1, c); } catch (Exception e) { }
        try { if(input.get(y)[x-1] == c) res += getPaths2(x-1, y, c); } catch (Exception e) { }
        try { if(input.get(y)[x+1] == c) res += getPaths2(x+1, y, c); } catch (Exception e) { }
        return res;
    }
    
    private static void readInput(File file) {
        try {
            Scanner myReader = new Scanner(file);
            while(myReader.hasNextLine()) input.add(myReader.nextLine().toCharArray());
            myReader.close();
        } catch (Exception e) {
            e.printStackTrace();;
        }
    }
}
