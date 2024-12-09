package days;
import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;

public class Day09 {

    private static long result1 = 0;
    private static int result2 = 0;
    private static char[] input;

    public static void main(String[] args) {
        
        System.out.println("...starte...");

        String folderPath = "2024\\input\\";
        String path = folderPath + "input09.txt";
        readInput(new File(path));
        ArrayList<String> disk = new ArrayList<>();

        // Part 1
        // einlesen
        for(int i = 0; i < input.length; i++) {
            if(i % 2 == 0) for(int j = 0; j < input[i]-'0'; j++) disk.add(String.valueOf(i / 2));
            else for(int j = 0; j < input[i]-'0'; j++) disk.add(".");
        }

        // komprimieren
        int writePointer = 0;
        int readPointer = disk.size()-1;
        while(writePointer < readPointer) {
            while(disk.get(writePointer) != ".") writePointer++;
            while(disk.get(readPointer) == ".") {
                readPointer--;
                disk.removeLast();
            }
            disk.set(writePointer, disk.get(readPointer));
            disk.removeLast();
            writePointer++; readPointer--;
        }

        for(int i = 0; i < disk.size(); i++) result1 += i * Integer.parseInt(disk.get(i));
        System.out.println("result of part 1: " + result1);

        // Part 2
        
        System.out.println("result of part 2: " + result2);
        System.out.println("...success...");
    }
    
    private static void readInput(File file) {
        try {
            Scanner myReader = new Scanner(file);
            while(myReader.hasNextLine()) input = myReader.nextLine().toCharArray();
            myReader.close();
        } catch (Exception e) {
            e.printStackTrace();;
        }
    }
}
