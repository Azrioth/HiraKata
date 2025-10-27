#include <iostream>
#include <unordered_map>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <algorithm>
#include <iomanip>

#ifdef _WIN32
    #include <windows.h>
    #include <io.h>
    #include <fcntl.h>
#endif


struct Score {
    int points = 0;
    int total = 0;

    double getPercentage() const {
        return (total == 0) ? 0.0 : (static_cast<double>(points) / total) * 100.0;
    }

    std::string showString() const {
        return std::to_string(points) + " / " + std::to_string(total)
            + " (" + std::to_string(static_cast<int>(getPercentage())) + "%)";
    }
};

Score getHighestScore(const std::vector<Score>& history) {
    if (history.empty()) return Score{};
    return *std::max_element(history.begin(), history.end(),
        [](const Score& a, const Score& b) {
            return a.getPercentage() < b.getPercentage();
        });
}

Score getTotalScore(const std::vector<Score>& history) {
    Score total;
    for (const auto& s : history) {
        total.points += s.points;
        total.total  += s.total;
    }
    return total;
}


int hiraPoints = 0;
int kataPoints = 0;
int mixedPoints = 0;

std::vector <Score> hiraHistory;
std::vector <Score> kataHistory;
std::vector <Score> mixedHistory;

// double maxHira = *std::max_element(std::begin(hiraHistory), std::end(hiraHistory));
// double maxKata = *std::max_element(std::begin(kataHistory), std::end(kataHistory));
// double maxMixed = *std::max_element(std::begin(mixedHistory), std::end(mixedHistory));

std::vector<std::wstring> hiraganaKeys = {
    L"あ", L"い", L"う", L"え", L"お",
    L"か", L"き", L"く", L"け", L"こ",
    L"さ", L"し", L"す", L"せ", L"そ",
    L"た", L"ち", L"つ", L"て", L"と",
    L"な", L"に", L"ぬ", L"ね", L"の",
    L"は", L"ひ", L"ふ", L"へ", L"ほ",
    L"ま", L"み", L"む", L"め", L"も",
    L"や",        L"ゆ",        L"よ",
    L"ら", L"り", L"る", L"れ", L"ろ",
    L"わ",                    L"を",
    L"ん",
    L"が", L"ぎ", L"ぐ", L"げ", L"ご",
    L"ざ", L"じ", L"ず", L"ぜ", L"ぞ",
    L"だ", L"ぢ", L"づ", L"で", L"ど",
    L"ば", L"び", L"ぶ", L"べ", L"ぼ",
    L"ぱ", L"ぴ", L"ぷ", L"ぺ", L"ぽ",
    L"きゃ", L"きゅ", L"きょ",
    L"しゃ", L"しゅ", L"しょ",
    L"ちゃ", L"ちゅ", L"ちょ",
    L"にゃ", L"にゅ", L"にょ",
    L"ひゃ", L"ひゅ", L"ひょ",
    L"みゃ", L"みゅ", L"みょ",
    L"りゃ", L"りゅ", L"りょ",
    L"ぎゃ", L"ぎゅ", L"ぎょ",
    L"じゃ", L"じゅ", L"じょ",
    L"びゃ", L"びゅ", L"びょ",
    L"ぴゃ", L"ぴゅ", L"ぴょ"
};

std::unordered_map<std::wstring, std::wstring> hiragana = {
    {L"あ", L"a"}, {L"い", L"i"}, {L"う", L"u"}, {L"え", L"e"}, {L"お", L"o"},
    {L"か", L"ka"}, {L"き", L"ki"}, {L"く", L"ku"}, {L"け", L"ke"}, {L"こ", L"ko"},
    {L"さ", L"sa"}, {L"し", L"shi"}, {L"す", L"su"}, {L"せ", L"se"}, {L"そ", L"so"},
    {L"た", L"ta"}, {L"ち", L"chi"}, {L"つ", L"tsu"}, {L"て", L"te"}, {L"と", L"to"},
    {L"な", L"na"}, {L"に", L"ni"}, {L"ぬ", L"nu"}, {L"ね", L"ne"}, {L"の", L"no"},
    {L"は", L"ha"}, {L"ひ", L"hi"}, {L"ふ", L"fu"}, {L"へ", L"he"}, {L"ほ", L"ho"},
    {L"ま", L"ma"}, {L"み", L"mi"}, {L"む", L"mu"}, {L"め", L"me"}, {L"も", L"mo"},
    {L"や", L"ya"},             {L"ゆ", L"yu"},             {L"よ", L"yo"},
    {L"ら", L"ra"}, {L"り", L"ri"}, {L"る", L"ru"}, {L"れ", L"re"}, {L"ろ", L"ro"},
    {L"わ", L"wa"},                         {L"を", L"wo"},
    {L"ん", L"n"},

    {L"が", L"ga"}, {L"ぎ", L"gi"}, {L"ぐ", L"gu"}, {L"げ", L"ge"}, {L"ご", L"go"},
    {L"ざ", L"za"}, {L"じ", L"ji"}, {L"ず", L"zu"}, {L"ぜ", L"ze"}, {L"ぞ", L"zo"},
    {L"だ", L"da"}, {L"ぢ", L"ji"}, {L"づ", L"zu"}, {L"で", L"de"}, {L"ど", L"do"},
    {L"ば", L"ba"}, {L"び", L"bi"}, {L"ぶ", L"bu"}, {L"べ", L"be"}, {L"ぼ", L"bo"},
    {L"ぱ", L"pa"}, {L"ぴ", L"pi"}, {L"ぷ", L"pu"}, {L"ぺ", L"pe"}, {L"ぽ", L"po"},

    {L"きゃ", L"kya"}, {L"きゅ", L"kyu"}, {L"きょ", L"kyo"},
    {L"しゃ", L"sha"}, {L"しゅ", L"shu"}, {L"しょ", L"sho"},
    {L"ちゃ", L"cha"}, {L"ちゅ", L"chu"}, {L"ちょ", L"cho"},
    {L"にゃ", L"nya"}, {L"にゅ", L"nyu"}, {L"にょ", L"nyo"},
    {L"ひゃ", L"hya"}, {L"ひゅ", L"hyu"}, {L"ひょ", L"hyo"},
    {L"みゃ", L"mya"}, {L"みゅ", L"myu"}, {L"みょ", L"myo"},
    {L"りゃ", L"rya"}, {L"りゅ", L"ryu"}, {L"りょ", L"ryo"},
    {L"ぎゃ", L"gya"}, {L"ぎゅ", L"gyu"}, {L"ぎょ", L"gyo"},
    {L"じゃ", L"ja"},  {L"じゅ", L"ju"},  {L"じょ", L"jo"},
    {L"びゃ", L"bya"}, {L"びゅ", L"byu"}, {L"びょ", L"byo"},
    {L"ぴゃ", L"pya"}, {L"ぴゅ", L"pyu"}, {L"ぴょ", L"pyo"}

};

std::vector<std::wstring> katakanaKeys = {
    L"ア", L"イ", L"ウ", L"エ", L"オ",
    L"カ", L"キ", L"ク", L"ケ", L"コ",
    L"サ", L"シ", L"ス", L"セ", L"ソ",
    L"タ", L"チ", L"ツ", L"テ", L"ト",
    L"ナ", L"ニ", L"ヌ", L"ネ", L"ノ",
    L"ハ", L"ヒ", L"フ", L"ヘ", L"ホ",
    L"マ", L"ミ", L"ム", L"メ", L"モ",
    L"ヤ",        L"ユ",        L"ヨ",
    L"ラ", L"リ", L"ル", L"レ", L"ロ",
    L"ワ",                    L"ヲ",
    L"ン",
    L"ガ", L"ギ", L"グ", L"ゲ", L"ゴ",
    L"ザ", L"ジ", L"ズ", L"ゼ", L"ゾ",
    L"ダ", L"ヂ", L"ヅ", L"デ", L"ド",
    L"バ", L"ビ", L"ブ", L"ベ", L"ボ",
    L"パ", L"ピ", L"プ", L"ペ", L"ポ",
    L"キャ", L"キュ", L"キョ",
    L"シャ", L"シュ", L"ショ",
    L"チャ", L"チュ", L"チョ",
    L"ニャ", L"ニュ", L"ニョ",
    L"ヒャ", L"ヒュ", L"ヒョ",
    L"ミャ", L"ミュ", L"ミョ",
    L"リャ", L"リュ", L"リョ",
    L"ギャ", L"ギュ", L"ギョ",
    L"ジャ", L"ジュ", L"ジョ",
    L"ビャ", L"ビュ", L"ビョ",
    L"ピャ", L"ピュ", L"ピョ"
};

std::unordered_map<std::wstring, std::wstring> katakana = {
    {L"ア", L"a"}, {L"イ", L"i"}, {L"ウ", L"u"}, {L"エ", L"e"}, {L"オ", L"o"},
    {L"カ", L"ka"}, {L"キ", L"ki"}, {L"ク", L"ku"}, {L"ケ", L"ke"}, {L"コ", L"ko"},
    {L"サ", L"sa"}, {L"シ", L"shi"}, {L"ス", L"su"}, {L"セ", L"se"}, {L"ソ", L"so"},
    {L"タ", L"ta"}, {L"チ", L"chi"}, {L"ツ", L"tsu"}, {L"テ", L"te"}, {L"ト", L"to"},
    {L"ナ", L"na"}, {L"ニ", L"ni"}, {L"ヌ", L"nu"}, {L"ネ", L"ne"}, {L"ノ", L"no"},
    {L"ハ", L"ha"}, {L"ヒ", L"hi"}, {L"フ", L"fu"}, {L"ヘ", L"he"}, {L"ホ", L"ho"},
    {L"マ", L"ma"}, {L"ミ", L"mi"}, {L"ム", L"mu"}, {L"メ", L"me"}, {L"モ", L"mo"},
    {L"ヤ", L"ya"},             {L"ユ", L"yu"},             {L"ヨ", L"yo"},
    {L"ラ", L"ra"}, {L"リ", L"ri"}, {L"ル", L"ru"}, {L"レ", L"re"}, {L"ロ", L"ro"},
    {L"ワ", L"wa"},                         {L"ヲ", L"wo"},
    {L"ン", L"n"},

    {L"ガ", L"ga"}, {L"ギ", L"gi"}, {L"グ", L"gu"}, {L"ゲ", L"ge"}, {L"ゴ", L"go"},
    {L"ザ", L"za"}, {L"ジ", L"ji"}, {L"ズ", L"zu"}, {L"ゼ", L"ze"}, {L"ゾ", L"zo"},
    {L"ダ", L"da"}, {L"ヂ", L"ji"}, {L"ヅ", L"zu"}, {L"デ", L"de"}, {L"ド", L"do"},
    {L"バ", L"ba"}, {L"ビ", L"bi"}, {L"ブ", L"bu"}, {L"ベ", L"be"}, {L"ボ", L"bo"},
    {L"パ", L"pa"}, {L"ピ", L"pi"}, {L"プ", L"pu"}, {L"ペ", L"pe"}, {L"ポ", L"po"},

    {L"キャ", L"kya"}, {L"キュ", L"kyu"}, {L"キョ", L"kyo"},
    {L"シャ", L"sha"}, {L"シュ", L"shu"}, {L"ショ", L"sho"},
    {L"チャ", L"cha"}, {L"チュ", L"chu"}, {L"チョ", L"cho"},
    {L"ニャ", L"nya"}, {L"ニュ", L"nyu"}, {L"ニョ", L"nyo"},
    {L"ヒャ", L"hya"}, {L"ヒュ", L"hyu"}, {L"ヒョ", L"hyo"},
    {L"ミャ", L"mya"}, {L"ミュ", L"myu"}, {L"ミョ", L"myo"},
    {L"リャ", L"rya"}, {L"リュ", L"ryu"}, {L"リョ", L"ryo"},
    {L"ギャ", L"gya"}, {L"ギュ", L"gyu"}, {L"ギョ", L"gyo"},
    {L"ジャ", L"ja"},  {L"ジュ", L"ju"},  {L"ジョ", L"jo"},
    {L"ビャ", L"bya"}, {L"ビュ", L"byu"}, {L"ビョ", L"byo"},
    {L"ピャ", L"pya"}, {L"ピュ", L"pyu"}, {L"ピョ", L"pyo"}
};

std::unordered_map<int, std::wstring> categoryMap = {
    {1, L"Hiragana"},
    {2, L"Katakana"},
    {3, L"Mixed"}
};

void mainMenu();

void printAsciiArt() {
    std::wcout << LR"( __          __  _                             _           _    _ _           _  __     _          _ 
 \ \        / / | |                           | |         | |  | (_)         | |/ /    | |        | |
  \ \  /\  / /__| | ___ ___  _ __ ___   ___   | |_ ___    | |__| |_ _ __ __ _| ' / __ _| |_ __ _  | |
   \ \/  \/ / _ \ |/ __/ _ \| '_ ` _ \ / _ \  | __/ _ \   |  __  | | '__/ _` |  < / _` | __/ _` | | |
    \  /\  /  __/ | (_| (_) | | | | | |  __/  | || (_) |  | |  | | | | | (_| | . \ (_| | || (_| | |_|
     \/  \/ \___|_|\___\___/|_| |_| |_|\___|   \__\___/   |_|  |_|_|_|  \__,_|_|\_\__,_|\__\__,_| (_)
                                                                                                     
                                                                                                     )" << std::endl;
}



void clearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void hiraganaQuiz(int rounds) {
    hiraPoints = 0;
    std::wcout << L"Starting Hiragana Quiz! Type the romaji for the given Hiragana character." << std::endl;
    std::wcout << L"If you're having trouble viewing the characters, please zoom in." << std::endl << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    for (int i = 0; i < rounds; i++) {
        int index = std::rand() % hiraganaKeys.size();
        std::wstring character = hiraganaKeys[index];
        std::wstring answer = hiragana[character];

        std::wcout << i+1 <<L". What is the romaji for " << character << L"?" << std::endl;
        std::wstring userInput;
        std::wcin >> userInput;

        if (userInput == answer) {
            std::wcout << L"Correct!" << std::endl << std::endl;
            hiraPoints++;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        } else {
            std::wcout << L"Wrong! The correct answer is: " << answer << std::endl << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    std::wcout << L"おつかれ! You got a score of " << hiraPoints << L" / " << rounds << "!"<< std::endl;
    Score currentScore;
    currentScore.points = hiraPoints;
    currentScore.total = rounds;
    hiraHistory.push_back(currentScore);

    std::wcout << L"Press Enter to return to the main menu...";
    std::wcin.ignore();
    std::wcin.get();

    clearScreen();
    mainMenu();

}

void katakanaQuiz(int rounds) {
    kataPoints = 0;
    std::wcout << L"Starting Katakana Quiz! Type the romaji for the given Katakana character." << std::endl;
    std::wcout << L"If you're having trouble viewing the characters, please zoom in." << std::endl << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    for (int i = 0; i < rounds; i++) {
        int index = std::rand() % katakanaKeys.size();
        std::wstring character = katakanaKeys[index];
        std::wstring answer = katakana[character];

        std::wcout << i+1 <<L". What is the romaji for " << character << L"?" << std::endl;
        std::wstring userInput;
        std::wcin >> userInput;

        if (userInput == answer) {
            std::wcout << L"Correct!" << std::endl << std::endl;
            kataPoints++;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        } else {
            std::wcout << L"Wrong! The correct answer is: " << answer << std::endl << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    std::wcout << L"おつかれ! You got a score of " << kataPoints << L" / " << rounds << "!"<< std::endl;
    Score currentScore;
    currentScore.points = kataPoints;
    currentScore.total = rounds;
    kataHistory.push_back(currentScore);

    std::wcout << L"Press Enter to return to the main menu...";
    std::wcin.ignore();
    std::wcin.get();
    clearScreen();
    mainMenu();
}

void mixedQuiz(int rounds) {
    mixedPoints = 0;
    std::wcout << L"Starting Mixed Quiz! Type the romaji for the given character." << std::endl;
    std::wcout << L"If you're having trouble viewing the characters, please zoom in." << std::endl << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    for (int i = 0; i < rounds; i++) {
        bool isHiragana = std::rand() % 2;
        std::wstring character;
        std::wstring answer;

        if (isHiragana) {
            int index = std::rand() % hiraganaKeys.size();
            character = hiraganaKeys[index];
            answer = hiragana[character];
        } else {
            int index = std::rand() % katakanaKeys.size();
            character = katakanaKeys[index];
            answer = katakana[character];
        }

        std::wcout << i+1 <<L". What is the romaji for " << character << L"?" << std::endl;
        std::wstring userInput;
        std::wcin >> userInput;

        if (userInput == answer) {
            std::wcout << L"Correct!" << std::endl << std::endl;
            mixedPoints++;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        } else {
            std::wcout << L"Wrong! The correct answer is: " << answer << std::endl << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    std::wcout << L"おつかれ! You got a score of " << mixedPoints << L" / " << rounds << "!"<< std::endl;
    Score currentScore;
    currentScore.points = mixedPoints;
    currentScore.total = rounds;
    mixedHistory.push_back(currentScore);

    std::wcout << L"Press Enter to return to the main menu...";
    std::wcin.ignore();
    std::wcin.get();
    clearScreen();
    mainMenu();
}

void displayTables() {
    // Use ideographic (full-width) space for empty cells so columns align visually
    const std::wstring FW_SPACE = L"　"; // U+3000

    std::vector<std::wstring> rowLabels = {
        L" ", L"k", L"s", L"t", L"n", L"h", L"m", L"y", L"r", L"w", L"n", L"g", L"z/j", L"d/j", L"b", L"p"
    };

    std::vector<std::wstring> combinationrowLabels = {
        L"ky", L"sh", L"ch", L"ny", L"hy", L"my", L"ry", L"gy", L"jy", L"by", L"py"
    };

    std::vector<std::vector<std::wstring>> hiraTable = {
        {L"あ", L"い", L"う", L"え", L"お"},
        {L"か", L"き", L"く", L"け", L"こ"},
        {L"さ", L"し", L"す", L"せ", L"そ"},
        {L"た", L"ち", L"つ", L"て", L"と"},
        {L"な", L"に", L"ぬ", L"ね", L"の"},
        {L"は", L"ひ", L"ふ", L"へ", L"ほ"},
        {L"ま", L"み", L"む", L"め", L"も"},
        {L"や", L" ", L"ゆ", L" ", L"よ"},
        {L"ら", L"り", L"る", L"れ", L"ろ"},
        {L"わ", L" ", L" ", L" ", L"を"},
        {L"ん", L" ", L" ", L" ", L" "},
        {L"が", L"ぎ", L"ぐ", L"げ", L"ご"},
        {L"ざ", L"じ", L"ず", L"ぜ", L"ぞ"},
        {L"だ", L"ぢ", L"づ", L"で", L"ど"},
        {L"ば", L"び", L"ぶ", L"べ", L"ぼ"},
        {L"ぱ", L"ぴ", L"ぷ", L"ぺ", L"ぽ"}
    };

    std::vector<std::vector<std::wstring>> combinationHiraTable = {
        {L"きゃ", L"きゅ", L"きょ"},
        {L"しゃ", L"しゅ", L"しょ"},
        {L"ちゃ", L"ちゅ", L"ちょ"},
        {L"にゃ", L"にゅ", L"にょ"},
        {L"ひゃ", L"ひゅ", L"ひょ"},
        {L"みゃ", L"みゅ", L"みょ"},
        {L"りゃ", L"りゅ", L"りょ"},
        {L"ぎゃ", L"ぎゅ", L"ぎょ"},
        {L"じゃ", L"じゅ", L"じょ"},
        {L"びゃ", L"びゅ", L"びょ"},
        {L"ぴゃ", L"ぴゅ", L"ぴょ"}
    };

    std::vector<std::vector<std::wstring>> kataTable = {
        {L"ア", L"イ", L"ウ", L"エ", L"オ"},
        {L"カ", L"キ", L"ク", L"ケ", L"コ"},
        {L"サ", L"シ", L"ス", L"セ", L"ソ"},
        {L"タ", L"チ", L"ツ", L"テ", L"ト"},
        {L"ナ", L"ニ", L"ヌ", L"ネ", L"ノ"},
        {L"ハ", L"ヒ", L"フ", L"ヘ", L"ホ"},
        {L"マ", L"ミ", L"ム", L"メ", L"モ"},
        {L"ヤ", L" ", L"ユ", L" ", L"ヨ"},
        {L"ラ", L"リ", L"ル", L"レ", L"ロ"},
        {L"ワ", L" ", L" ", L" ", L"ヲ"},
        {L"ン", L" ", L" ", L" ", L" "},
        {L"ガ", L"ギ", L"グ", L"ゲ", L"ゴ"},
        {L"ザ", L"ジ", L"ズ", L"ゼ", L"ゾ"},
        {L"ダ", L"ヂ", L"ヅ", L"デ", L"ド"},
        {L"バ", L"ビ", L"ブ", L"ベ", L"ボ"},
        {L"パ", L"ピ", L"プ", L"ペ", L"ポ"}
    };

    std::vector<std::vector<std::wstring>> combinationKataTable = {
        {L"キャ", L"キュ", L"キョ"},
        {L"シャ", L"シュ", L"ショ"},
        {L"チャ", L"チュ", L"チョ"},
        {L"ニャ", L"ニュ", L"ニョ"},
        {L"ヒャ", L"ヒュ", L"ヒョ"},
        {L"ミャ", L"ミュ", L"ミョ"},
        {L"リャ", L"リュ", L"リョ"},
        {L"ギャ", L"ギュ", L"ギョ"},
        {L"ジャ", L"ジュ", L"ジョ"},
        {L"ビャ", L"ビュ", L"ビョ"},
        {L"ピャ", L"ピュ", L"ピョ"}
    };

    clearScreen();

    // Header
    std::wcout << L"\n---------- Hiragana Table ----------" << std::endl;
    std::wcout << std::left << std::setw(6) << L" " 
               << std::setw(6) << L"a" 
               << std::setw(6) << L" i" 
               << std::setw(6) << L"  u" 
               << std::setw(6) << L"   e" 
               << std::setw(6) << L"    o" 
               << std::endl;
    std::wcout << std::wstring(36, L'-') << std::endl;

    for (size_t i = 0; i < hiraTable.size(); ++i) {
        std::wcout << std::left << std::setw(6) << rowLabels[i];
        for (const auto& ch_in : hiraTable[i]) {
            std::wstring ch = (ch_in == L" " ? FW_SPACE : ch_in);
            std::wcout << std::left << std::setw(6) << ch;
        }
        std::wcout << std::endl;
    }
    std::wcout << std::wstring(36, L'-') << std::endl;

    std::wcout << L"\n---- Combination Hiragana Table ----" << std::endl;
    std::wcout << std::left << std::setw(6) << L" " 
               << std::setw(6) << L" a" 
               << std::setw(6) << L"   u" 
               << std::setw(6) << L"     o" 
               << std::endl;
    std::wcout << std::wstring(36, L'-') << std::endl;

    for (size_t i = 0; i < combinationHiraTable.size(); ++i) {
        std::wcout << std::left << std::setw(6) << combinationrowLabels[i];
        for (const auto& ch_in : combinationHiraTable[i]) {
            std::wstring ch = (ch_in == L" " ? FW_SPACE : ch_in);
            std::wcout << std::left << std::setw(6) << ch;
        }
        std::wcout << std::endl;
    }
    std::wcout << std::wstring(36, L'-') << std::endl;

    std::wcout << L"\n---------- Katakana Table ----------" << std::endl;
    std::wcout << std::left << std::setw(6) << L" " 
               << std::setw(6) << L"a" 
               << std::setw(6) << L" i" 
               << std::setw(6) << L"  u" 
               << std::setw(6) << L"   e" 
               << std::setw(6) << L"    o" 
               << std::endl;
    std::wcout << std::wstring(36, L'-') << std::endl;

    for (size_t i = 0; i < kataTable.size(); ++i) {
        std::wcout << std::left << std::setw(6) << rowLabels[i];
        for (const auto& ch_in : kataTable[i]) {
            std::wstring ch = (ch_in == L" " ? FW_SPACE : ch_in);
            std::wcout << std::left << std::setw(6) << ch;
        }
        std::wcout << std::endl;
    }
    std::wcout << std::wstring(36, L'-') << std::endl;

    std::wcout << L"\n---- Combination Katakana Table ----" << std::endl;
    std::wcout << std::left << std::setw(6) << L" " 
               << std::setw(6) << L" a" 
               << std::setw(6) << L"   u" 
               << std::setw(6) << L"     o" 
               << std::endl;
    std::wcout << std::wstring(36, L'-') << std::endl;

    for (size_t i = 0; i < combinationKataTable.size(); ++i) {
        std::wcout << std::left << std::setw(6) << combinationrowLabels[i];
        for (const auto& ch_in : combinationKataTable[i]) {
            std::wstring ch = (ch_in == L" " ? FW_SPACE : ch_in);
            std::wcout << std::left << std::setw(6) << ch;
        }
        std::wcout << std::endl;
    }

    std::wcout << L"\nPress Enter to return to the main menu...";
    std::wcin.ignore();
    std::wcin.get();
    clearScreen();
    mainMenu();
}

void mainMenu(){
    printAsciiArt();

    int choice;
    int rounds;
    
    std::wcout << L"\t      -------------------------------------------------------------------------" << std::endl;
    std::wcout << L"\t      |   「HiraKata」へようこそ！ Your Hiragana / Katakana practice buddy!   |" << std::endl;
    std::wcout << L"\t      -------------------------------------------------------------------------" << std::endl << std::endl;

    std::wcout << L"--------------------------------------------------------------------------------------" << std::endl;
    std::wcout << L"Category\tMost Recent Score\tHighest Score\t\tTotal Score" << std::endl <<std::endl;
    
    // --- Hiragana ---
    if (!hiraHistory.empty()) {
        Score recent = hiraHistory.back();
        Score highest = getHighestScore(hiraHistory);
        Score total = getTotalScore(hiraHistory);

        std::wcout << L"Hiragana\t"
            << recent.showString().c_str() << L"\t\t"
            << highest.showString().c_str() << L"\t\t"
            << total.showString().c_str() << std::endl;
    } else {
        std::wcout << L"Hiragana\tNo records yet.\t\tNo records yet.\t\tNo records yet.\n";
    }

    // --- Katakana ---
    if (!kataHistory.empty()) {
        Score recent = kataHistory.back();
        Score highest = getHighestScore(kataHistory);
        Score total = getTotalScore(kataHistory);

        std::wcout << L"Katakana\t"
            << recent.showString().c_str() << L"\t\t"
            << highest.showString().c_str() << L"\t\t"
            << total.showString().c_str() << std::endl;
    } else {
        std::wcout << L"Katakana\tNo records yet.\t\tNo records yet.\t\tNo records yet.\t\n";
    }

    // --- Mixed ---
    if (!mixedHistory.empty()) {
        Score recent = mixedHistory.back();
        Score highest = getHighestScore(mixedHistory);
        Score total = getTotalScore(mixedHistory);

        std::wcout << L"Mixed\t\t"
            << recent.showString().c_str() << L"\t\t"
            << highest.showString().c_str() << L"\t\t"
            << total.showString().c_str() << std::endl;
    } else {
        std::wcout << L"Mixed\t\tNo records yet.\t\tNo records yet.\t\tNo records yet.\n";
    }

    std::wcout << L"--------------------------------------------------------------------------------------\n\n";

    std::wcout << L"Select the number of what you would like to practice:" << std::endl;
    std::wcout << L"(1) Hiragana\n(2) Katakana\n(3) Mix of both\n(4) Reference Tables\n(5) Quit\n" << std::endl;
    std::wcout << L"Your choice: ";
    
    while (true){
        std::wcin >> choice;
        if (choice >=1 && choice <=3) break;
        if (!std::wcin >> choice){
            std::wcin.clear();
            std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::wcout << L"Invalid input. Please select from the choices provided" << std::endl;
            choice = 0;
            std::wcout << L"Your choice: ";
            continue;
        }
        if (choice == 4) {
            clearScreen();
            displayTables();
        }
        if (choice == 5) {
            std::wcout << L"ありがとう! See you next time!" << std::endl;
            std::wcout << L"Exiting in 3 seconds..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(3));
            exit(0);
        }
        std::wcout << L"Invalid choice. Please select from the choices provided" << std::endl;
        std::wcout << L"Your choice: ";
    }
    std::wcout << L"----------------------------------------\n\n";
    std::wcout << L"How many rounds would you like to play?\n" << std::endl;
    std::wcout << L"Your choice: ";
    
    while (true){
        std::wcin >> rounds;
        if (!std::wcin >> rounds){
            std::wcin.clear();
            std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::wcout << L"Invalid input. Please input a positive number" << std::endl;
            rounds = 0;
            std::wcout << L"Your choice: ";
            continue;
        }
        if (rounds > 0) break;
        std::wcout << L"Please enter a positive number for rounds" << std::endl;
        std::wcout << L"Your choice: ";
    }

    auto it = categoryMap.find(choice);
    if (it == categoryMap.end()) {
        std::wcout << L"Error: Invalid category choice." << std::endl;
        return;
    }
    std::wcout << L"----------------------------------------\n";
    std::wcout << L"\nYou have selected " << it->second << " with a question count of " << rounds << L"! がんばって！" << std::endl << std::endl;
    std::wcout << L"Press Enter to begin your practice!";
    std::wcin.ignore();
    std::wcin.get();
    clearScreen();

    switch(choice){
        case 1:
            hiraganaQuiz(rounds);
            break;
        case 2:
            katakanaQuiz(rounds);
            break;
        case 3:
            mixedQuiz(rounds);
            break;
        default:
            std::wcout << L"Error: Invalid category choice." << std::endl;
    }

}

int wmain() {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
        _setmode(_fileno(stdout), _O_U8TEXT);
    #endif

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    clearScreen();
    mainMenu();

    


    return 0;
}
