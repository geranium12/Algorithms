import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;


public class Kanon {
    private static int[][] weight; // новый массив весов
    private static int[][] boardA; // основной массив
    private static int[][] boardC; // новый массив заполнения ударов
    private static int[][] horse = {
            {0, 1, 0, 1, 0,},
            {1, 0, 0, 0, 1,},
            {0, 0, 0, 0, 0,},
            {1, 0, 0, 0, 1,},
            {0, 1, 0, 1, 0,},
    }; // новый массив заполнения ударов
    private static int sizeX;
    private static int sizeY;
    private static int maxWeight;
    private static long duration;


    private static int placeHorse(int bx, int by) {
        int[][] check = new int[5][5];

        int value = 0;
        int yh = 0;
        for (int y = by; y < by + 5; y++) {
            int xh = 0;
            for (int x = bx; x < bx + 5; x++) {
                int hit = horse[xh++][yh];
                if (hit == 0) { // нет hit пропускаем
                    continue;
                }
                if (boardC[x][y] == -2) { // занято
                    continue;
                }
                boardC[x][y] += hit;  // наносим удар и суммируем
                if (x > 1 && y > 1 && x < sizeX + 2 && y < sizeY + 2) { // поле не занято
                    value += hit; // если попадает на доску пишем вес
                }
            }
            yh++;
        }
        if (value > maxWeight) {
            maxWeight = value;
        }
        return value;
    }

    private static boolean removeHorse(int bx, int by) {
        int yh = 0;
        for (int y = by; y < by + 5; y++) {
            int xh = 0;
            for (int x = bx; x < bx + 5; x++) {
                int hit = horse[xh++][yh];
                if (hit == 0) {  // оптимизация
                    continue;
                }
                int value = boardC[x][y];
                if (value == -2) { // нет hit или занято пропускаем
                    continue;
                }
                if (x > 1 && y > 1 && x < sizeX + 2 && y < sizeY + 2) { // поле захвата
                    if (value < 2) { // ударная позиция и только этот конь бьет
                        return false; // выходим убирать нельзя
                    }
                }
            }
            yh++;
        }
// можно убирать
        yh = 0;
        for (int y = by; y < by + 5; y++) {
            int xh = 0;
            for (int x = bx; x < bx + 5; x++) {
                int hit = horse[xh++][yh];
                if (hit == 0) {  // оптимизация
                    continue;
                }
                int value = boardC[x][y];
                if (value == -2) { // занято пропускаем
                    continue;
                }
                boardC[x][y] = value - 1;  // ударная и незанятая позиция
            }
            yh++;
        }
        boardA[bx][by] = 0; // убрали коня
        weight[bx][by] = 0; // убрали его вес
        return true;
    }

    private static void check() {

// init arrays
        weight = new int[sizeX][sizeY]; // новый массив весов
        boardC = new int[sizeX + 4][sizeY + 4]; // новая доска массив заполнения ударов
// clone board to boardA, boardC
        for (int i = 0; i < sizeX; i++) {
            for (int j = 0; j < sizeY; j++) {
                boardC[i + 2][j + 2] = boardA[i][j];
            }
        }

        long startTime = System.nanoTime();
// start processing
// расставляем всех коней
        for (int x = 0; x < sizeX; x++) {
            for (int y = 0; y < sizeY; y++) {
                if (boardA[x][y] == 0) {
                    boardA[x][y] = 1; // поместить коня
                    weight[x][y] = placeHorse(x, y); // получаем число хитов от коня
                }
            }
        }
// убираем по одному начиная с младших весов
        for (int w = 1; w <= maxWeight; w++) {
            for (int x = 0; x < sizeX; x++) {
                for (int y = 0; y < sizeY; y++) {
                    if (weight[x][y] == w) {  // прогоняем сначала младшие веса
                        removeHorse(x, y);
                    }
                }
            }
        }
// finished processing
        duration = System.nanoTime() - startTime;
    }

    public static void main(String[] args) throws IOException {
        Scanner SC = new Scanner(new File("input.txt"));
        if (!SC.hasNext()) {
            SC.close();
            return;
        }
        long startTime = System.nanoTime();
        sizeX = SC.nextInt();
        sizeY = SC.nextInt();
        boardA = new int[sizeX][sizeY];  // нули сразу

        int blocked = SC.nextInt();
        for (int i = 0; i < blocked; ++i) {
            int x = SC.nextInt();
            int y = SC.nextInt();
            boardA[x - 1][y - 1] = -2;  // отрицательное число специально
        }

//============================================
        check();
        System.out.printf("duration:%.2f\n", duration / 1e6);
        showBoard(boardA, "boardA");
//============================================
        try {
            PrintWriter pw = new PrintWriter(new File("output.txt"));
            pw.println(1);
            for (int y = 0; y < sizeY; y++) {
                for (int x = 0; x < sizeX; x++) {
                    int value = boardA[x][y] == -2 ? 2 : boardA[x][y];
                    pw.print(value);
                }
                pw.println();
            }
            pw.println(" ");

            pw.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
        SC.close();
    }

    //===============================================
    private static void showBorder(int size, String name) {
        for (int i = 0; i < size; i++) {
            System.out.printf("=");
        }
        System.out.print(" " + name + " ");
        for (int i = 0; i < size; i++) {
            System.out.printf("=");
        }
        System.out.println();
    }

    private static void showBoard(int[][] array, String name) {
        int sizeX2 = array.length;
        int sizeY2 = array[0].length;
        showBorder(sizeX2, name); //===
        for (int y = 0; y < sizeY2; y++) {
            for (int x = 0; x < sizeX2; x++) {
                System.out.printf("% 2d ", array[x][y]);
            }
            System.out.println();
        }
        showBorder(sizeX2, "===="); //===
    }
}