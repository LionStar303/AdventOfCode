package days;
import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class Day06 {

    private static int result1 = 0;
    private static int result2 = 0;
    public static ArrayList<String> input;
    public static ArrayList<String> marked;
    public static int x, y;

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

        try {
            findStart(); // reset start coordinates und startmarkierung entfernen
            marked.set(y, marked.get(y).substring(0, x) + "." + marked.get(y).substring(x+1));

            ExecutorService es = Executors.newFixedThreadPool(Runtime.getRuntime().availableProcessors());
            List<Future<?>> futures = new ArrayList<>();
            final int START_X = x;
            final int START_Y = y;

            for(int i = 0; i < input.size(); i++) {
                for(int j = 0; j < input.get(i).length(); j++) {
                    if(marked.get(i).charAt(j) != 'X') continue;

                    final int row = i;
                    final int col = j;
            
                    futures.add(es.submit(() -> {
                        int cx = START_X, cy = START_Y, d = 0;
                        ArrayList<String> visited = new ArrayList<>();
                        visited.add(cx + "," + cy + "," + (d % 4));
                        
                        // modifiziertes grid mit hindernis erstellen
                        ArrayList<String> modInput = new ArrayList<>(input);
                        modInput.set(row, modInput.get(row).substring(0, col) + "#" + modInput.get(row).substring(col+1));

                        while(cx > 0 && cx < modInput.get(cy).length()-1 && cy > 0 && cy < modInput.size()-1) {
                            switch (d % 4) {
                                case 0:
                                    if(modInput.get(cy-1).charAt(cx) == '#') d++;
                                    else cy--;
                                    break;
                                case 1:
                                    if(modInput.get(cy).charAt(cx+1) == '#') d++;
                                    else cx++;
                                    break;
                                case 2:
                                    if(modInput.get(cy+1).charAt(cx) == '#') d++;
                                    else cy++;
                                    break;
                                case 3:
                                    if(modInput.get(cy).charAt(cx-1) == '#') d++;
                                    else cx--;
                                    break;
                                default:
                                    System.out.println("undefined direction");
                                    break;
                            }
                            // besuchtes Feld mit direction visited hinzufügen
                            if(visited.contains(cx + "," + cy + "," + (d % 4))) {
                                cx = -1; // abbruchbedingung
                                synchronized (Day06.class) {
                                    result2++; // Use synchronization for shared data
                                }
                            } else visited.add(cx + "," + cy + "," + (d % 4));
                        }
                    }));
                }
            }

            // Wait for all tasks to finish
            for (Future<?> future : futures) {
                future.get(); // Wait for completion
            }
    
            es.shutdown(); // Shutdown the executor
            
        } catch (Exception e) {
            e.printStackTrace();
        }
        
        time = System.currentTimeMillis() - time;
        System.out.println("result of part 2: " + result2 + "  " + time + "ms");
        System.out.println("...success...");
    }
    public static void findStart() {
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