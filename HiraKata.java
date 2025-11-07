import java.util.*;
import java.io.*;
import java.util.concurrent.TimeUnit;

public class HiraKata {
    static class Score {
        int points = 0;
        int total = 0;

        double getPercentage() {
            return total == 0 ? 0.0 : ((double) points / total) * 100.0;
        }

        String showString() {
            return points + " / " + total + " (" + (int) getPercentage() + "%)";
        }
    }

    static int hiraPoints = 0;
    static int kataPoints = 0;
    static int mixedPoints = 0;

    static ArrayList<Score> hiraHistory = new ArrayList<>();
    static ArrayList<Score> kataHistory = new ArrayList<>();
    static ArrayList<Score> mixedHistory = new ArrayList<>();

    static Scanner sc = new Scanner(System.in);

    static ArrayList<String> hiraganaKeys = new ArrayList<>(Arrays.asList(
        "あ","い","う","え","お",
        "か","き","く","け","こ",
        "さ","し","す","せ","そ",
        "た","ち","つ","て","と",
        "な","に","ぬ","ね","の",
        "は","ひ","ふ","へ","ほ",
        "ま","み","む","め","も",
        "や","ゆ","よ",
        "ら","り","る","れ","ろ",
        "わ","を","ん",
        "が","ぎ","ぐ","げ","ご",
        "ざ","じ","ず","ぜ","ぞ",
        "だ","ぢ","づ","で","ど",
        "ば","び","ぶ","べ","ぼ",
        "ぱ","ぴ","ぷ","ぺ","ぽ",
        "きゃ","きゅ","きょ",
        "しゃ","しゅ","しょ",
        "ちゃ","ちゅ","ちょ",
        "にゃ","にゅ","にょ",
        "ひゃ","ひゅ","ひょ",
        "みゃ","みゅ","みょ",
        "りゃ","りゅ","りょ",
        "ぎゃ","ぎゅ","ぎょ",
        "じゃ","じゅ","じょ",
        "びゃ","びゅ","びょ",
        "ぴゃ","ぴゅ","ぴょ"
    ));

    static HashMap<String,String> hiragana = new HashMap<>();
    static HashMap<String,String> katakana = new HashMap<>();
    static ArrayList<String> katakanaKeys = new ArrayList<>();

    static {
        // ---- Hiragana ----
        hiragana.put("あ","a"); hiragana.put("い","i"); hiragana.put("う","u"); hiragana.put("え","e"); hiragana.put("お","o");
        hiragana.put("か","ka"); hiragana.put("き","ki"); hiragana.put("く","ku"); hiragana.put("け","ke"); hiragana.put("こ","ko");
        hiragana.put("さ","sa"); hiragana.put("し","shi"); hiragana.put("す","su"); hiragana.put("せ","se"); hiragana.put("そ","so");
        hiragana.put("た","ta"); hiragana.put("ち","chi"); hiragana.put("つ","tsu"); hiragana.put("て","te"); hiragana.put("と","to");
        hiragana.put("な","na"); hiragana.put("に","ni"); hiragana.put("ぬ","nu"); hiragana.put("ね","ne"); hiragana.put("の","no");
        hiragana.put("は","ha"); hiragana.put("ひ","hi"); hiragana.put("ふ","fu"); hiragana.put("へ","he"); hiragana.put("ほ","ho");
        hiragana.put("ま","ma"); hiragana.put("み","mi"); hiragana.put("む","mu"); hiragana.put("め","me"); hiragana.put("も","mo");
        hiragana.put("や","ya"); hiragana.put("ゆ","yu"); hiragana.put("よ","yo");
        hiragana.put("ら","ra"); hiragana.put("り","ri"); hiragana.put("る","ru"); hiragana.put("れ","re"); hiragana.put("ろ","ro");
        hiragana.put("わ","wa"); hiragana.put("を","wo"); hiragana.put("ん","n");

        hiragana.put("が","ga"); hiragana.put("ぎ","gi"); hiragana.put("ぐ","gu"); hiragana.put("げ","ge"); hiragana.put("ご","go");
        hiragana.put("ざ","za"); hiragana.put("じ","ji"); hiragana.put("ず","zu"); hiragana.put("ぜ","ze"); hiragana.put("ぞ","zo");
        hiragana.put("だ","da"); hiragana.put("ぢ","ji"); hiragana.put("づ","zu"); hiragana.put("で","de"); hiragana.put("ど","do");
        hiragana.put("ば","ba"); hiragana.put("び","bi"); hiragana.put("ぶ","bu"); hiragana.put("べ","be"); hiragana.put("ぼ","bo");
        hiragana.put("ぱ","pa"); hiragana.put("ぴ","pi"); hiragana.put("ぷ","pu"); hiragana.put("ぺ","pe"); hiragana.put("ぽ","po");

        hiragana.put("きゃ","kya"); hiragana.put("きゅ","kyu"); hiragana.put("きょ","kyo");
        hiragana.put("しゃ","sha"); hiragana.put("しゅ","shu"); hiragana.put("しょ","sho");
        hiragana.put("ちゃ","cha"); hiragana.put("ちゅ","chu"); hiragana.put("ちょ","cho");
        hiragana.put("にゃ","nya"); hiragana.put("にゅ","nyu"); hiragana.put("にょ","nyo");
        hiragana.put("ひゃ","hya"); hiragana.put("ひゅ","hyu"); hiragana.put("ひょ","hyo");
        hiragana.put("みゃ","mya"); hiragana.put("みゅ","myu"); hiragana.put("みょ","myo");
        hiragana.put("りゃ","rya"); hiragana.put("りゅ","ryu"); hiragana.put("りょ","ryo");
        hiragana.put("ぎゃ","gya"); hiragana.put("ぎゅ","gyu"); hiragana.put("ぎょ","gyo");
        hiragana.put("じゃ","ja"); hiragana.put("じゅ","ju"); hiragana.put("じょ","jo");
        hiragana.put("びゃ","bya"); hiragana.put("びゅ","byu"); hiragana.put("びょ","byo");
        hiragana.put("ぴゃ","pya"); hiragana.put("ぴゅ","pyu"); hiragana.put("ぴょ","pyo");

        // ---- Katakana ----
        katakana.put("ア","a"); katakana.put("イ","i"); katakana.put("ウ","u"); katakana.put("エ","e"); katakana.put("オ","o");
        katakana.put("カ","ka"); katakana.put("キ","ki"); katakana.put("ク","ku"); katakana.put("ケ","ke"); katakana.put("コ","ko");
        katakana.put("サ","sa"); katakana.put("シ","shi"); katakana.put("ス","su"); katakana.put("セ","se"); katakana.put("ソ","so");
        katakana.put("タ","ta"); katakana.put("チ","chi"); katakana.put("ツ","tsu"); katakana.put("テ","te"); katakana.put("ト","to");
        katakana.put("ナ","na"); katakana.put("ニ","ni"); katakana.put("ヌ","nu"); katakana.put("ネ","ne"); katakana.put("ノ","no");
        katakana.put("ハ","ha"); katakana.put("ヒ","hi"); katakana.put("フ","fu"); katakana.put("ヘ","he"); katakana.put("ホ","ho");
        katakana.put("マ","ma"); katakana.put("ミ","mi"); katakana.put("ム","mu"); katakana.put("メ","me"); katakana.put("モ","mo");
        katakana.put("ヤ","ya"); katakana.put("ユ","yu"); katakana.put("ヨ","yo");
        katakana.put("ラ","ra"); katakana.put("リ","ri"); katakana.put("ル","ru"); katakana.put("レ","re"); katakana.put("ロ","ro");
        katakana.put("ワ","wa"); katakana.put("ヲ","wo"); katakana.put("ン","n");

        katakana.put("ガ","ga"); katakana.put("ギ","gi"); katakana.put("グ","gu"); katakana.put("ゲ","ge"); katakana.put("ゴ","go");
        katakana.put("ザ","za"); katakana.put("ジ","ji"); katakana.put("ズ","zu"); katakana.put("ゼ","ze"); katakana.put("ゾ","zo");
        katakana.put("ダ","da"); katakana.put("ヂ","ji"); katakana.put("ヅ","zu"); katakana.put("デ","de"); katakana.put("ド","do");
        katakana.put("バ","ba"); katakana.put("ビ","bi"); katakana.put("ブ","bu"); katakana.put("ベ","be"); katakana.put("ボ","bo");
        katakana.put("パ","pa"); katakana.put("ピ","pi"); katakana.put("プ","pu"); katakana.put("ペ","pe"); katakana.put("ポ","po");

        katakana.put("キャ","kya"); katakana.put("キュ","kyu"); katakana.put("キョ","kyo");
        katakana.put("シャ","sha"); katakana.put("シュ","shu"); katakana.put("ショ","sho");
        katakana.put("チャ","cha"); katakana.put("チュ","chu"); katakana.put("チョ","cho");
        katakana.put("ニャ","nya"); katakana.put("ニュ","nyu"); katakana.put("ニョ","nyo");
        katakana.put("ヒャ","hya"); katakana.put("ヒュ","hyu"); katakana.put("ヒョ","hyo");
        katakana.put("ミャ","mya"); katakana.put("ミュ","myu"); katakana.put("ミョ","myo");
        katakana.put("リャ","rya"); katakana.put("リュ","ryu"); katakana.put("リョ","ryo");
        katakana.put("ギャ","gya"); katakana.put("ギュ","gyu"); katakana.put("ギョ","gyo");
        katakana.put("ジャ","ja"); katakana.put("ジュ","ju"); katakana.put("ジョ","jo");
        katakana.put("ビャ","bya"); katakana.put("ビュ","byu"); katakana.put("ビョ","byo");
        katakana.put("ピャ","pya"); katakana.put("ピュ","pyu"); katakana.put("ピョ","pyo");

        // Katakana keys list (so quiz can randomize)
        katakanaKeys.addAll(Arrays.asList(
            "ア","イ","ウ","エ","オ",
            "カ","キ","ク","ケ","コ",
            "サ","シ","ス","セ","ソ",
            "タ","チ","ツ","テ","ト",
            "ナ","ニ","ヌ","ネ","ノ",
            "ハ","ヒ","フ","ヘ","ホ",
            "マ","ミ","ム","メ","モ",
            "ヤ","ユ","ヨ",
            "ラ","リ","ル","レ","ロ",
            "ワ","ヲ","ン",
            "ガ","ギ","グ","ゲ","ゴ",
            "ザ","ジ","ズ","ゼ","ゾ",
            "ダ","ヂ","ヅ","デ","ド",
            "バ","ビ","ブ","ベ","ボ",
            "パ","ピ","プ","ペ","ポ",
            "キャ","キュ","キョ",
            "シャ","シュ","ショ",
            "チャ","チュ","チョ",
            "ニャ","ニュ","ニョ",
            "ヒャ","ヒュ","ヒョ",
            "ミャ","ミュ","ミョ",
            "リャ","リュ","リョ",
            "ギャ","ギュ","ギョ",
            "ジャ","ジュ","ジョ",
            "ビャ","ビュ","ビョ",
            "ピャ","ピュ","ピョ"
        ));
    }
    static void clearScreen() {
        try {
            if (System.getProperty("os.name").contains("Windows"))
                new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
            else
                new ProcessBuilder("clear").inheritIO().start().waitFor();
        } catch (Exception ignored) {}
    }

    static void printAsciiArt() {
        System.out.println("""
   __          __  _                             _           _    _ _           _  __     _          _ 
   \\ \\        / / | |                           | |         | |  | (_)         | |/ /    | |        | |
    \\ \\  /\\  / /__| | ___ ___  _ __ ___   ___   | |_ ___    | |__| |_ _ __ __ _| ' / __ _| |_ __ _  | |
     \\ \\/  \\/ / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\  | __/ _ \\   |  __  | | '__/ _` |  < / _` | __/ _` | | |
      \\  /\\  /  __/ | (_| (_) | | | | | |  __/  | || (_) |  | |  | | | | | (_| | . \\ (_| | || (_| | |_|
       \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|   \\__\\___/   |_|  |_|_|_|  \\__,_|_|\\_\\__,_|\\__\\__,_| (_)
""");
    }

    static Score getHighestScore(List<Score> history) {
        return history.isEmpty() ? new Score() :
            Collections.max(history, Comparator.comparingDouble(Score::getPercentage));
    }

    static Score getTotalScore(List<Score> history) {
        Score total = new Score();
        for (Score s : history) {
            total.points += s.points;
            total.total += s.total;
        }
        return total;
    }

    static void hiraganaQuiz(int rounds) {
        hiraPoints = 0;
        System.out.println("Starting Hiragana Quiz! Type the romaji for the given Hiragana character.");
        try { TimeUnit.SECONDS.sleep(2); } catch (InterruptedException e) {}

        Random rand = new Random();
        for (int i = 0; i < rounds; i++) {
            int index = rand.nextInt(hiraganaKeys.size());
            String character = hiraganaKeys.get(index);
            String answer = hiragana.get(character);

            System.out.print((i+1) + ". What is the romaji for " + character + "?\n");
            String userInput = sc.next();

            if (userInput.equals(answer)) {
                System.out.println("Correct!\n");
                hiraPoints++;
            } else {
                System.out.println("Wrong! The correct answer is: " + answer + "\n");
            }
        }

        System.out.println("おつかれ! You got a score of " + hiraPoints + " / " + rounds + "!");
        Score current = new Score();
        current.points = hiraPoints;
        current.total = rounds;
        hiraHistory.add(current);

        System.out.println("Press Enter to return to the main menu...");
        sc.nextLine(); sc.nextLine();
        clearScreen();
        mainMenu();
    }

    static void katakanaQuiz(int rounds) {
        kataPoints = 0;
        System.out.println("Starting Katakana Quiz! Type the romaji for the given Katakana character.");
        try { TimeUnit.SECONDS.sleep(2); } catch (InterruptedException e) {}

        Random rand = new Random();
        for (int i = 0; i < rounds; i++) {
            int index = rand.nextInt(katakanaKeys.size());
            String character = katakanaKeys.get(index);
            String answer = katakana.get(character);

            System.out.print((i+1) + ". What is the romaji for " + character + "?\n");
            String userInput = sc.next();

            if (userInput.equals(answer)) {
                System.out.println("Correct!\n");
                kataPoints++;
            } else {
                System.out.println("Wrong! The correct answer is: " + answer + "\n");
            }
        }

        System.out.println("おつかれ! You got a score of " + kataPoints + " / " + rounds + "!");
        Score current = new Score();
        current.points = kataPoints;
        current.total = rounds;
        kataHistory.add(current);

        System.out.println("Press Enter to return to the main menu...");
        sc.nextLine(); sc.nextLine();
        clearScreen();
        mainMenu();
    }

    static void mixedQuiz(int rounds) {
        mixedPoints = 0;
        System.out.println("Starting Mixed Quiz!");
        try { TimeUnit.SECONDS.sleep(2); } catch (InterruptedException e) {}

        Random rand = new Random();
        for (int i = 0; i < rounds; i++) {
            boolean isHira = rand.nextBoolean();
            String character, answer;
            if (isHira) {
                int index = rand.nextInt(hiraganaKeys.size());
                character = hiraganaKeys.get(index);
                answer = hiragana.get(character);
            } else {
                int index = rand.nextInt(katakanaKeys.size());
                character = katakanaKeys.get(index);
                answer = katakana.get(character);
            }

            System.out.print((i+1) + ". What is the romaji for " + character + "?\n");
            String userInput = sc.next();

            if (userInput.equals(answer)) {
                System.out.println("Correct!\n");
                mixedPoints++;
            } else {
                System.out.println("Wrong! The correct answer is: " + answer + "\n");
            }
        }

        System.out.println("おつかれ! You got a score of " + mixedPoints + " / " + rounds + "!");
        Score current = new Score();
        current.points = mixedPoints;
        current.total = rounds;
        mixedHistory.add(current);

        System.out.println("Press Enter to return to the main menu...");
        sc.nextLine(); sc.nextLine();
        clearScreen();
        mainMenu();
    }

    static void displayTables() {
        clearScreen();

        // Column headers
        String[] vowels = {"a", " i", "  u", "   e", "    o"};
        String[] comboVowels = {"a", "  u", "    o"};

        // Row headers
        String[] consonants = {
            "", "k", "s", "t", "n", "h", "m", "y", "r", "w", "g", "z/j", "d/j", "b", "p"
        };
        String[] comboConsonants = {
            "ky", "sh", "ch", "ny", "hy", "my", "ry", "gy", "jy", "by", "py"
        };

        // Hiragana gojūon
        String[][] hiraTable = {
            {"あ", "い", "う", "え", "お"},
            {"か", "き", "く", "け", "こ"},
            {"さ", "し", "す", "せ", "そ"},
            {"た", "ち", "つ", "て", "と"},
            {"な", "に", "ぬ", "ね", "の"},
            {"は", "ひ", "ふ", "へ", "ほ"},
            {"ま", "み", "む", "め", "も"},
            {"や", "　", "ゆ", "　", "よ"},
            {"ら", "り", "る", "れ", "ろ"},
            {"わ", "　", "　", "　", "を"},
            {"が", "ぎ", "ぐ", "げ", "ご"},
            {"ざ", "じ", "ず", "ぜ", "ぞ"},
            {"だ", "ぢ", "づ", "で", "ど"},
            {"ば", "び", "ぶ", "べ", "ぼ"},
            {"ぱ", "ぴ", "ぷ", "ぺ", "ぽ"},
        };

        // Katakana gojūon
        String[][] kataTable = {
            {"ア", "イ", "ウ", "エ", "オ"},
            {"カ", "キ", "ク", "ケ", "コ"},
            {"サ", "シ", "ス", "セ", "ソ"},
            {"タ", "チ", "ツ", "テ", "ト"},
            {"ナ", "ニ", "ヌ", "ネ", "ノ"},
            {"ハ", "ヒ", "フ", "ヘ", "ホ"},
            {"マ", "ミ", "ム", "メ", "モ"},
            {"ヤ", "　", "ユ", "　", "ヨ"},
            {"ラ", "リ", "ル", "レ", "ロ"},
            {"ワ", "　", "　", "　", "ヲ"},
            {"ガ", "ギ", "グ", "ゲ", "ゴ"},
            {"ザ", "ジ", "ズ", "ゼ", "ゾ"},
            {"ダ", "ヂ", "ヅ", "デ", "ド"},
            {"バ", "ビ", "ブ", "ベ", "ボ"},
            {"パ", "ピ", "プ", "ペ", "ポ"},
        };

        // Hiragana combination
        String[][] hiraCombo = {
            {"きゃ", "きゅ", "きょ"},
            {"しゃ", "しゅ", "しょ"},
            {"ちゃ", "ちゅ", "ちょ"},
            {"にゃ", "にゅ", "にょ"},
            {"ひゃ", "ひゅ", "ひょ"},
            {"みゃ", "みゅ", "みょ"},
            {"りゃ", "りゅ", "りょ"},
            {"ぎゃ", "ぎゅ", "ぎょ"},
            {"じゃ", "じゅ", "じょ"},
            {"びゃ", "びゅ", "びょ"},
            {"ぴゃ", "ぴゅ", "ぴょ"}
        };

        // Katakana combination
        String[][] kataCombo = {
            {"キャ", "キュ", "キョ"},
            {"シャ", "シュ", "ショ"},
            {"チャ", "チュ", "チョ"},
            {"ニャ", "ニュ", "ニョ"},
            {"ヒャ", "ヒュ", "ヒョ"},
            {"ミャ", "ミュ", "ミョ"},
            {"リャ", "リュ", "リョ"},
            {"ギャ", "ギュ", "ギョ"},
            {"ジャ", "ジュ", "ジョ"},
            {"ビャ", "ビュ", "ビョ"},
            {"ピャ", "ピュ", "ピョ"}
        };

        // Helper for tables
        java.util.function.BiConsumer<String[][], String[]> printTable = (table, headerSet) -> {
            System.out.printf("%-8s", " ");
            for (String v : headerSet) System.out.printf("%-8s", v);
            System.out.println();
            System.out.println("-----------------------------------------------------");
        };

        // --------------------
        // HIRAGANA
        // --------------------
        System.out.println("\n========================= HIRAGANA =========================");
        printTable.accept(hiraTable, vowels);
        for (int i = 0; i < hiraTable.length; i++) {
            System.out.printf("%-8s", consonants[i]);
            for (String cell : hiraTable[i]) {
                System.out.printf("%-8s", cell);
            }
            System.out.println();
        }

        // --------------------
        // HIRAGANA COMBINATION
        // --------------------
        System.out.println("\n================== HIRAGANA COMBINATION ==================");
        printTable.accept(hiraCombo, comboVowels);
        for (int i = 0; i < hiraCombo.length; i++) {
            System.out.printf("%-8s", comboConsonants[i]);
            for (String cell : hiraCombo[i]) {
                System.out.printf("%-8s", cell);
            }
            System.out.println();
        }

        // --------------------
        // KATAKANA
        // --------------------
        System.out.println("\n========================= KATAKANA =========================");
        printTable.accept(kataTable, vowels);
        for (int i = 0; i < kataTable.length; i++) {
            System.out.printf("%-8s", consonants[i]);
            for (String cell : kataTable[i]) {
                System.out.printf("%-8s", cell);
            }
            System.out.println();
        }

        // --------------------
        // KATAKANA COMBINATION
        // --------------------
        System.out.println("\n================== KATAKANA COMBINATION ==================");
        printTable.accept(kataCombo, comboVowels);
        for (int i = 0; i < kataCombo.length; i++) {
            System.out.printf("%-8s", comboConsonants[i]);
            for (String cell : kataCombo[i]) {
                System.out.printf("%-8s", cell);
            }
            System.out.println();
        }

        System.out.println("\nPress Enter to return to the main menu...");
        sc.nextLine();
        clearScreen();
        mainMenu();
    }

static void mainMenu() {
    printAsciiArt();

    System.out.println("\t      -------------------------------------------------------------------------");
    System.out.println("\t      |   「HiraKata」へようこそ！ Your Hiragana / Katakana practice buddy!   |");
    System.out.println("\t      -------------------------------------------------------------------------\n");

    System.out.println("Category\tMost Recent\t\tHighest\t\t\tTotal");
    System.out.println("-----------------------------------------------------------------------------");

    if (!hiraHistory.isEmpty()) {
        Score recent = hiraHistory.get(hiraHistory.size() - 1);
        Score highest = getHighestScore(hiraHistory);
        Score total = getTotalScore(hiraHistory);
        System.out.println("Hiragana\t" + recent.showString() + "\t\t" + highest.showString() + "\t\t" + total.showString());
    } else {
        System.out.println("Hiragana\tNo records yet.");
    }

    if (!kataHistory.isEmpty()) {
        Score recent = kataHistory.get(kataHistory.size() - 1);
        Score highest = getHighestScore(kataHistory);
        Score total = getTotalScore(kataHistory);
        System.out.println("Katakana\t" + recent.showString() + "\t\t" + highest.showString() + "\t\t" + total.showString());
    } else {
        System.out.println("Katakana\tNo records yet.");
    }

    if (!mixedHistory.isEmpty()) {
        Score recent = mixedHistory.get(mixedHistory.size() - 1);
        Score highest = getHighestScore(mixedHistory);
        Score total = getTotalScore(mixedHistory);
        System.out.println("Mixed\t\t" + recent.showString() + "\t\t" + highest.showString() + "\t\t" + total.showString());
    } else {
        System.out.println("Mixed\t\tNo records yet.");
    }

    System.out.println("-----------------------------------------------------------------------------");
    System.out.println("(1) Hiragana\n(2) Katakana\n(3) Mix of both\n(4) Reference Tables\n(5) Quit\n");

    int choice;
    while (true) {
        System.out.print("Your choice: ");
        if (sc.hasNextInt()) {
            choice = sc.nextInt();
            sc.nextLine(); // clear buffer
            if (choice >= 1 && choice <= 5) break;
        } else {
            sc.nextLine(); // clear invalid input
        }
        System.out.println("Invalid input. Please select 1–5.");
    }

    if (choice == 5) {
        System.out.println("ありがとう! See you next time!");
        System.out.println("Exiting in 3 seconds...");
        try{
            Thread.sleep(3000);
        } catch(InterruptedException e){
            Thread.currentThread().interrupt();
        }
        System.exit(0);
    }

    // Reference tables don’t need “rounds”
    if (choice == 4) {
        clearScreen();
        displayTables();
        return; // go back to main menu afterward
    }

    int rounds = 0;
    while (rounds <= 0) {
        System.out.print("How many rounds? ");
        if (sc.hasNextInt()) {
            rounds = sc.nextInt();
            sc.nextLine();
            if (rounds <= 0) System.out.println("Please enter a positive number.");
        } else {
            System.out.println("Invalid input. Please enter a number.");
            sc.nextLine();
        }
    }

    clearScreen();

    switch (choice) {
        case 1 -> hiraganaQuiz(rounds);
        case 2 -> katakanaQuiz(rounds);
        case 3 -> mixedQuiz(rounds);
        default -> System.out.println("Invalid choice.");
    }
}

    public static void main(String[] args) {
        try {
            // --- Force UTF-8 encoding globally ---
            System.setProperty("file.encoding", "UTF-8");
            Locale.setDefault(Locale.forLanguageTag("ja-JP"));
            System.out.flush();
            System.err.flush();

            // --- Detect OS and configure accordingly ---
            String os = System.getProperty("os.name").toLowerCase();

            if (os.contains("win")) {
                // For Windows: switch console to UTF-8
                new ProcessBuilder("cmd", "/c", "chcp 65001 > nul").inheritIO().start().waitFor();
            } 

            // --- Set up UTF-8 IO streams explicitly ---
            System.setOut(new java.io.PrintStream(System.out, true, "UTF-8"));
            System.setErr(new java.io.PrintStream(System.err, true, "UTF-8"));

            // --- Start program ---
            clearScreen();
            mainMenu();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }


}
