package days;
import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;

public class Day09 {

    private static long result1 = 0;
    private static long result2 = 0;
    private static char[] input;

    public static void main(String[] args) {
        
        System.out.println("...starte...");

        String folderPath = "2024\\input\\";
        String path = folderPath + "input09.txt";
        readInput(new File(path));

        // einlesen
        ArrayList<String> disk = new ArrayList<>();
        for(int i = 0; i < input.length; i++) {
            if(i % 2 == 0) for(int j = 0; j < input[i]-'0'; j++) disk.add(String.valueOf(i / 2));
            else for(int j = 0; j < input[i]-'0'; j++) disk.add(".");
        }

        // Part 1
        result1 = part1(new ArrayList<>(disk));
        System.out.println("result of part 1: " + result1);

        // Part 2
        result2 = part2(new ArrayList<>(disk));
        System.out.println("result of part 2: " + result2);
        System.out.println("...success...");
    }

    private static long part1(ArrayList<String> disk) {
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
        long res = 0;
        for(int i = 0; i < disk.size(); i++) res += i * Integer.parseInt(disk.get(i));
        return res;
    }

    private static long part2(ArrayList<String> disk) {
        // komprimieren
        int readPointer = disk.size()-1;
        while(readPointer > 0) {
            // nächste Datei finden
            while(disk.get(readPointer) == ".")  readPointer--;
            // Größe der Datei ermitteln
            int len = 0, id = Integer.parseInt(disk.get(readPointer));
            while(readPointer >= 0 && disk.get(readPointer) != "." && Integer.parseInt(disk.get(readPointer)) == id)  { readPointer--; len++; }
            // ausreichen großen Block suchen
            int free = 0, writePointer = 0;
            while(free < len && writePointer < readPointer+1) {
                if(disk.get(writePointer) == ".") free++;
                else free = 0;
                writePointer++;
            }
            if(free < len) continue; // weiter wenn kein ausreichend großer Block
            writePointer -= len;
            for(int i = 0; i < len; i++) {
                disk.set(writePointer+i, disk.get(readPointer+i+1));
                disk.set(readPointer+i+1, ".");
            }
        }
        long res = 0;
        for(int i = 0; i < disk.size(); i++) if(disk.get(i) != ".") res += i * Integer.parseInt(disk.get(i));
        return res;
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
