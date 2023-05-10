#include "Menu.h"
#include "Board.h"
#include "Game.h"
#include <thread>
#include <chrono>
#include <future>
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#endif
bool isSoundOn = true;
void showCur()
{
    CONSOLE_CURSOR_INFO Info;
    Info.bVisible = TRUE;
    Info.dwSize = 20;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void hideCur()
{
    CONSOLE_CURSOR_INFO Info;
    Info.bVisible = FALSE;
    Info.dwSize = 20;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
void setConsoleTitle() {
    //system("color FA");
    string narrow_str = "Caro Nhom 7";
    int length = MultiByteToWideChar(CP_UTF8, 0, narrow_str.c_str(), -1, NULL, 0);
    std::wstring wide_str(length, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, narrow_str.c_str(), -1, &wide_str[0], length);
    SetConsoleTitle(wide_str.c_str());
}
void SetConsole(int width, int height) {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, width, height, TRUE);
}
void Textcolor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
void gotoXY(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void playSound(int i) {
    static vector<const wchar_t*> soundFile{ L"beep.wav", L"move.wav",
       L"tick.wav", L"votay.wav", L"win.wav", L"win1.wav", L"background.wav" };
    if (isSoundOn == true) {
        PlaySound(soundFile[i], NULL, SND_FILENAME | SND_ASYNC);
    }
}
int getConsoleInput() {
    int c = _getch();
    if (c == 0 || c == 224)
    {
        switch (_getch())
        {
        case 72:				//move up
            return 2;
        case 75:				//move left
            return 3;
        case 77:				//move right
            return 4;
        case 80:				//move down
            return 5;
        default:
            return 0;
        }
    }
    else
    {
        if (c == 27)                  //esc
            return 1;
        else if (c == 87 || c == 119) //W, w
            return 2;
        else if (c == 65 || c == 97)  //A, a
            return 3;
        else if (c == 68 || c == 100) //D, d
            return 4;
        else if (c == 83 || c == 115) //S, s
            return 5;
        else if (c == 13)             //Enter
            return 6;
        else if (c == 76 || c == 108) //L, l  lưu game
            return 7;
        else if (c == 84 || c == 116) //T, t  load game
            return 10;
        else if (c == 89 || c == 121) //Y, y
            return 11;
        else if (c == 77 || c == 109) //M, m turn off sound
            return 8;
        else if (c == 78 || c == 110) //N, n turn on sound
            return 9;
        else
            return 0;
    }
}
void clearConsole() {
    system("cls");
}
void instruction()
{
    clearConsole();
    system("color FA");
    Draw(0, 20, 1);
    Textcolor(Violet);
    gotoXY(35, 19);
    cout << "------------------------------------ Instruction -----------------------------------";
    gotoXY(71, 20);
    cout << "( HUONG DAN )" << endl;
    gotoXY(40, 22);
    cout << char(254) << " Ban co gom 20x20 o vuong." << endl;
    gotoXY(40, 24);
    cout << char(254) << " Su dung cac phim W A S D de di chuyen va Enter de danh." << endl;
    gotoXY(40, 30);
    cout << "3. Luat choi cu du 5 quan co X hoac O theo hang ngang, doc, cheo se chien thang." << endl;
    gotoXY(40, 32);
    cout << "4. Luat choi tuan theo quy dinh chan 2 dau " << endl;
    Textcolor(MintPink);
    gotoXY(46, 26);  cout << "   W   ";
    Textcolor(Grey);
    gotoXY(46, 28);  cout << "   S   ";
    Textcolor(BlueYellow);
    gotoXY(37, 28);  cout << "   A   ";
    Textcolor(100);
    gotoXY(55, 28);  cout << "   D   ";
    Textcolor(MintPink);
    gotoXY(84, 26);  cout << "  " << char(036) << "  ";
    Textcolor(Grey);
    gotoXY(84, 28); cout << "  " << char(037) << "  ";
    Textcolor(30);
    gotoXY(77, 28);  cout << "  " << char(021) << "  ";
    Textcolor(100);
    gotoXY(91, 28);  cout << "  " << char(020) << "  ";
    Textcolor(GreyBlue);
    gotoXY(113, 26);     cout << "         ";
    gotoXY(109, 27);   cout << "     ENTER   ";
    gotoXY(109, 28); cout << "             ";
    int y = 31;
    Textcolor(Grey);
    gotoXY(65, 38);  cout << "   S   ";
    Textcolor(Black);
    gotoXY(73, 38);
    cout << " : BACK";
    do {
        int input = getConsoleInput();
        if (input == 5 || input == 1)
        {
            y++;
            if (y == 32)
            {
                clearConsole();
                menu();
            }
            break;
        }
    } while (input != 5 && input != 1);
}
void About()
{
    clearConsole();
    Draw(4, 20, 1);
    int y = 31;
    Textcolor(Grey);
    gotoXY(65, 38);  cout << "   S   ";
    Textcolor(Black);
    gotoXY(73, 38);
    cout << " : BACK";
    do {
        int input = getConsoleInput();
        if (input == 5 || input == 1)
        {
            y++;
            if (y == 32)
            {
                clearConsole();
                menu();
            }
            break;
        }
    } while (input != 5 && input != 1);
}
void history() {
    clearConsole();
    system("color FA");
    Draw(0, 20, 1);
    Textcolor(Green);
    gotoXY(40, 19);
    cout << "-------------------------- LIST FILE NAME History --------------------------";
    int i = 22;
    Textcolor(Black);
    fstream f;
    f.open("Lich Su.txt", ios::in);
    string line;
    while (getline(f, line)) {
        string s, s1, buffer;
        size_t pos = line.find(' ');
        s = line.substr(0, pos);
        line.erase(0, pos);
        pos = line.find(' ');
        s1 = line.substr(0, pos);
        line.erase(0, pos);
        buffer = line;
        gotoXY(60, i);
        cout << s << " " << s1 << setw(50) << left << buffer;
        i++;
    }

    int y = 31;
    f.close();
    Textcolor(Grey);
    gotoXY(70, i + 5);  cout << "   S   ";
    Textcolor(Black);
    gotoXY(78, i + 5);
    cout << " : BACK";
    do{
        int input = getConsoleInput();
        if (input == 5 || input == 1)
        {
            y++;
            if (y == 32)
            {
                clearConsole();
                menu();
            }
            break;
        }
    } while (input != 5 && input != 1);
}
int readMode(char a[30])
{
    int d1, d2, chedo;
    ifstream f;
    f.open(a, ios::in);
    if (!f) {
        /*playSound(7);*/
        Textcolor(Black);
        gotoXY(58, 33);
        cout << " FILE KHONG TON TAI!" << endl;
        Sleep(400);
        Load();
        int y = 31;
        Textcolor(Grey);
        gotoXY(60, 38);  cout << "   S   ";
        Textcolor(Black);
        gotoXY(68, 38);
        cout << " : BACK";
        int input = getConsoleInput();
        if (input == 5 || input == 1)
        {
            y++;
            if (y == 32)
            {
                clearConsole();
                menu();
            }
        }
        Sleep(1500);

    }
    else
        f >> d1 >> d2 >> chedo;
    f.close();
    return chedo;
}
void readNameFile()
{
    Textcolor(Red);
    gotoXY(40, 18);
    cout << "----------------------------- LIST FILE NAME -----------------------------";
    int i = 20;
    ifstream f;
    f.open("Name.txt", ios::in);
    while (!f.eof())
    {
        Textcolor(Black);
        char s[30];
        f >> s;
        gotoXY(73, i);
        cout << s;
        i++;
    }
    f.close();

}
void exitFunction() {
    
}
void Load()
{
    int n = 100;
    clearConsole();
    Draw(0, 10, 1);
    readNameFile();
    char data[30];

    int y = 31;
    Textcolor(Red);
    gotoXY(60, 38);  cout << "S";
    Textcolor(Red);
    gotoXY(68, 38);
    cout << " : BACK";
    Textcolor(Red);
    gotoXY(60, 39);  cout << "Y";
    Textcolor(Red);
    gotoXY(68, 39);
    cout << " : CONTINUE";
    do {
        int input = getConsoleInput();
        if (input == 5 || input == 1)
        {
            y++;
            if (y == 32)
            {
                clearConsole();
                menu();
            }
            break;
        }
        if (input == 11) {
            clearConsoleLine(38);
            clearConsoleLine(39);
            gotoXY(58, 32);
            showCur();
            Textcolor(Red);
            cout << "ENTER FILE NAME: ";
            cin.getline(data, 30);
            break;
        }
    } while (input != 5 && input != 1 && input != 11);
    
    
    int chedo = readMode(data);
    cout << chedo << endl;
    if (chedo == -30 || chedo == -31)
    {
        Diem a;
        a.score1 = 0;
        a.score2 = 0;
        int t = PlayerVsPlayer(a, chedo, data);
        if (t == 27)
        {
            clearConsole();
            menu();
        }
    }
    if (chedo == -4)
    {
        Diem a;
        a.score1 = 0;
        a.score2 = 0;
        int t = PlayerVsCom(a, -4, data);
        if (t == 27)
        {
            clearConsole();
            menu();
        }
    }
}
void menu()
{
    system("color FA");
    setConsoleTitle();
    char s[30];
    int x = 70;
    int y = 19;
    // Initial menu setup
    Draw(0, 10, 1); 
    
    for (int i = 0; i < numItems; i++)
    {
        Textcolor(Black);
        gotoXY(x, y + i);
        cout << menuItems[i];
    }
    // Additional menu setup
    Textcolor(Black);
    gotoXY(x - 15, y + numItems + 6);
    cout << "W - S : Move ( Off Unikey) ";
    gotoXY(x - 3, y + numItems + 7);
    cout << "Enter : Select ";
    gotoXY(x , y + numItems + 9);
    cout << "M: mute";
   
    char ch = ' '; // Initialize character input variable
    // Main loop to handle user input and menu selection
    while (ch != 'x') // Loop until user inputs 'x' to exit
    {
        // Highlight new selection
        Textcolor(Red);
        gotoXY(x, y + currentSelection);
        cout << menuItems[currentSelection];
        Textcolor(15);
        int input = 0;
        input = getConsoleInput(); // Get keyboard input
        // Clear current selection
        Textcolor(Black);
        gotoXY(x, y + currentSelection);
        cout << menuItems[currentSelection];
        if (input == 9) {
            isSoundOn = true;
            playSound(6);
        }
        if (input == 8)
        {
            isSoundOn = false;
            PlaySound(0, 0, 0);
        }
        if (input == 5 || ch == 's')
        {
            playSound(1);
            // Move down one row
            currentSelection = (currentSelection + 1) % numItems;
        }
        if (input == 2 || ch == 'w')
        {
            playSound(1);
            // Move up one row
            currentSelection = (currentSelection - 1 + numItems) % numItems;
        }
        if (input == 6 || ch == '\r') // Check for Enter key press
        {
            playSound(2);
            // Call corresponding function for selected menu item
            switch (currentSelection)
            {
            case 0:
            {
                clearConsole();
                Diem a;
                a.score1 = 0;
                a.score2 = 0;
                int t = PlayerVsPlayer(a, 0, s);
                if (t == 27)
                {
                    clearConsole();
                    menu();
                }
                break;
            }
            case 1:
            {
                clearConsole();
                Diem a;
                a.score1 = 0;
                a.score2 = 0;
                int t = PlayerVsCom(a, 0, s);
                if (t == 27)
                {
                    clearConsole();
                    menu();
                }
                break;
            }
            case 2:
            {
                clearConsole();
                Load();
                break;
            }
            case 3:
            {
                clearConsole();
                history();
                break;
            }
            case 4:
            {
                clearConsole();
                instruction();
                break;
            }
            case 5:
            {
                clearConsole();
                About();
                break;
            }
            case 6:
            {
                clearConsole();
                exit(0);
                break;
            }
            }
        }
        
    }
}
