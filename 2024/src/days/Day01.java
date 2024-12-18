package days;
import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;

public class Day01 {

    private static ArrayList<Integer> myList;
    private static ArrayList<Integer> historianList;

    @SuppressWarnings("unused")
    public static void main(String[] args) {
        
        System.out.println("...starte...");

        int result = 0;

        String folderPath = "2024\\input\\";
        String demoPath = folderPath + "demoInput.txt";
        String path = folderPath + "input01.txt";
        readInput(new File(path));

        myList.sort(null);
        historianList.sort(null);

        for(int i = 0; i < myList.size(); i++) {
            result += Math.abs(myList.get(i) - historianList.get(i));
        }

        System.out.println("result of part 1: " + result);

        // Part 2

        result = 0;
        for(int i : myList) {
            int n = 0;
            for(int l : historianList) {
                if(i == l) n++;
            }
            result += i * n;
        }
        System.out.println("result of part 2: " + result);
        System.out.println("...success...");
    }
    
    private static void readInput(File file) {
        myList = new ArrayList<Integer>();
        historianList = new ArrayList<Integer>();
        try {
            Scanner myReader = new Scanner(file);
            while(myReader.hasNextLine()) {
                String line = myReader.nextLine();
                String[] entries = new String[2];
                entries = line.split("   ");
                myList.add(Integer.parseInt(entries[0]));
                historianList.add(Integer.parseInt(entries[1]));
            }
            myReader.close();
        } catch (Exception e) {
            e.printStackTrace();;
        }
    }
}
