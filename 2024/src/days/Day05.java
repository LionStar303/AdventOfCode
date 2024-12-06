package days;
import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;

public class Day05 {

    private static int result1 = 0;
    private static int result2 = 0;
    private static ArrayList<String> ordering;
    private static ArrayList<String> updates;
    private static ArrayList<String[]> valids;

    @SuppressWarnings("unused")
    public static void main(String[] args) {
        
        System.out.println("...starte...");

        String folderPath = "2024\\input\\";
        String demoPath = folderPath + "demo-input.txt";
        String path = folderPath + "input05.txt";
        readInput(new File(path));
        updates = new ArrayList<>();
        valids = new ArrayList<>();

        ordering.forEach((line) -> {
            if(line.length() < 4) {
                updates = new ArrayList<>(ordering.subList(ordering.indexOf(line)+1, ordering.size()));
                ordering = new ArrayList<>(ordering.subList(0, ordering.indexOf(line)));
            }
        });
        System.out.println(ordering);
        System.out.println();
        System.out.println(updates);

        // Part 1
        for(String u : updates) {
            String[] update = u.split(",");
            if(updateValid(update)) {
                valids.add(update);
            }
        }
        for(String[] u : valids)  result1 += Integer.parseInt(u[u.length/2]);
        System.out.println("result of part 1: " + result1);

        // Part 2
        for(String u : updates) {
            String[] update = u.split(",");
            fixUpdate(update); // fix update und addiere zu result 2
        }
        result2 -= result1;
        System.out.println("result of part 2: " + result2);
        System.out.println("...success...");
    }

    private static void fixUpdate(String[] update) {
        for(int i = 0; i < update.length-1; i++) {
            for(int j = i+1; j < update.length; j++) {
                if(ordering.contains(update[j] + "|" + update[i])) {
                    String s = update[j];
                    update[j] = update[i];
                    update[i] = s;
                }
            }
        }
        if(!updateValid(update)) {
            fixUpdate(update);
        } else {
            result2 += Integer.parseInt(update[update.length/2]);
        }
    }

    private static boolean updateValid(String[] update) {
        for(int i = 0; i < update.length-1; i++) {
            for(int j = i+1; j < update.length; j++) {
                if(ordering.contains(update[j] + "|" + update[i])) {
                    return false;
                }
            }
        }
        return true;
    }
    
    private static void readInput(File file) {
        try {
            ordering = new ArrayList<>();
            Scanner myReader = new Scanner(file);
            while(myReader.hasNextLine()) ordering.add(myReader.nextLine());
            myReader.close();
        } catch (Exception e) {
            e.printStackTrace();;
        }
    }
}
