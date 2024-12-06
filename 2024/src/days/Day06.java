package days;
import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;

public class Day06 {

    private static int result1 = 0;
    private static int result2 = 0;
    private static ArrayList<String> input;
    private static ArrayList<String> marked;
    private static int x, y;

    @SuppressWarnings("unused")
    public static void main(String[] args) {
        
        System.out.println("...starte...");

        String folderPath = "2024\\input\\";
        String demoPath = folderPath + "demo-input.txt";
        String path = folderPath + "input06.txt";
        readInput(new File(path));

        long time = System.currentTimeMillis();

        x = 0; y = 0;
        int direction = 0; // 0-oben 1-rechts, 2-unten, 3-links
        findStart();

        // Part 1
        result1++; // startindex schon besucht

        marked = new ArrayList<>(input);
        marked.set(y, marked.get(y).substring(0, x) + "X" + marked.get(y).substring(x+1));

        while(x > 0 && x < input.get(y).length()-1 && y > 0 && y < input.size()-1) {
            switch (direction % 4) {
                case 0:
                    if(input.get(y-1).charAt(x) == '#') direction++;
                    else y--;
                    break;
                case 1:
                    if(input.get(y).charAt(x+1) == '#') direction++;
                    else x++;
                    break;
                case 2:
                    if(input.get(y+1).charAt(x) == '#') direction++;
                    else y++;
                    break;
                case 3:
                    if(input.get(y).charAt(x-1) == '#') direction++;
                    else x--;
                    break;
                default:
                System.out.println("undefined direction");
                    break;
            }
            // Feld markieren wenn noch nicht besucht und result1 inkrementieren
            if(marked.get(y).charAt(x) != 'X') {
                result1++;
                marked.set(y, marked.get(y).substring(0, x) + "X" + marked.get(y).substring(x+1));
            }
        }
        for(String line : marked) System.out.println(line);
        time = System.currentTimeMillis() - time;
        System.out.println("result of part 1: " + result1 + "  " + time + "ms");

        // Part 2
        time = System.currentTimeMillis();
        findStart(); // reset start coordinates und startmarkierung entfernen
        marked.set(y, marked.get(y).substring(0, x) + "X" + marked.get(y).substring(x+1));

        for(int i = 0; i < input.size(); i++) {
            for(int j = 0; j < input.get(i).length(); j++) {
                if(marked.get(i).charAt(j) != 'X') continue;

                findStart(); // reset start coordinates
                direction = 0; // reset direction
                ArrayList<String> visited = new ArrayList<>();
                visited.add(x + "," + y + "," + String.valueOf(direction % 4));

                // modifiziertes grid mit hindernis erstellen
                ArrayList<String> modInput = new ArrayList<>(input);
                modInput.set(i, modInput.get(i).substring(0, j) + "#" + modInput.get(i).substring(j+1));

                while(x > 0 && x < modInput.get(y).length()-1 && y > 0 && y < modInput.size()-1) {
                    switch (direction % 4) {
                        case 0:
                            if(modInput.get(y-1).charAt(x) == '#') direction++;
                            else y--;
                            break;
                        case 1:
                            if(modInput.get(y).charAt(x+1) == '#') direction++;
                            else x++;
                            break;
                        case 2:
                            if(modInput.get(y+1).charAt(x) == '#') direction++;
                            else y++;
                            break;
                        case 3:
                            if(modInput.get(y).charAt(x-1) == '#') direction++;
                            else x--;
                            break;
                        default:
                        System.out.println("undefined direction");
                            break;
                    }
                    // besuchtes Feld mit direction visited hinzufügen
                    if(visited.contains(x + "," + y + "," + String.valueOf(direction % 4))) {
                        x = -1; // abbruchbedingung
                        result2++;
                    } else visited.add(x + "," + y + "," + String.valueOf(direction % 4));
                }
            }
        }
        
        time = System.currentTimeMillis() - time;
        System.out.println("result of part 2: " + result2 + "  " + time + "ms");
        System.out.println("...success...");
    }
    private static void findStart() {
        for(int i = 0; i < input.size(); i++) {
            for(int l = 0; l < input.get(i).length(); l++) {
                if(input.get(i).charAt(l) == '^') {
                    x = l;
                    y = i;
                }
            }
        }
    }

    private static void readInput(File file) {
        input = new ArrayList<>();
        try {
            Scanner myReader = new Scanner(file);
            while(myReader.hasNextLine()) input.add(myReader.nextLine());
            myReader.close();
        } catch (Exception e) {
            e.printStackTrace();;
        }
    }
}
