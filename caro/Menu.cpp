#include "Menu.h"
#include "Board.h"
#include "Game.h"
void HienTroChuot()
{
    CONSOLE_CURSOR_INFO Info;
    Info.bVisible = TRUE;
    Info.dwSize = 20;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void AnTroChuot()
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

int playSound(int i, char c)
{
    static vector<const wchar_t*> soundFile{ L"beep.wav", L"move.wav",
        L"tick.wav", L"votay.wav", L"win.wav", L"win1.wav", L"background.wav"};
    if (c == 77 || c == 109) {
        return 0;
    }
    if (c == 78 || c == 110){
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
        else if (c == 72 || c == 104) //H, h
            return 7;
        else if (c == 77 || c == 109)//M, m turn off sound
            return 8;
        else if (c == 78 || c == 110) //N, n turn on sound
            return 9;
        else
            return 0;
    }
}
void ClearConsole() {
    system("cls");
}
void Instruction()
{
    ClearConsole();
    Draw(1, 50, 1);
    Textcolor(Violet);
    gotoXY(70, 18);
    cout << "Instruction";
    gotoXY(70, 19);
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
    gotoXY(50, 26);  cout << "   W   ";
    Textcolor(Grey);
    gotoXY(50, 28);  cout << "   S   ";
    Textcolor(BlueYellow);
    gotoXY(41, 28);  cout << "   A   ";
    Textcolor(100);
    gotoXY(59, 28);  cout << "   D   ";
    Textcolor(MintPink);
    gotoXY(88, 26);  cout << "  " << char(036) << "  ";
    Textcolor(Grey);
    gotoXY(88, 28); cout << "  " << char(037) << "  ";
    Textcolor(30);
    gotoXY(81, 28);  cout << "  " << char(021) << "  ";
    Textcolor(100);
    gotoXY(95, 28);  cout << "  " << char(020) << "  ";
    Textcolor(GreyBlue);
    gotoXY(117, 26);     cout << "         ";
    gotoXY(113, 27);   cout << "     ENTER   ";
    gotoXY(113, 28); cout << "             ";
    Textcolor(Grey);
    gotoXY(70, 36);  cout << "   S   ";
    Textcolor(Black);
    gotoXY(77, 36);
    cout << " : BACK";
    char command = ' ';
    command = _getch();
    if (command == 's' or command == 'S') {
        ClearConsole();
        menu();
    }
    

}
void About()
{
    ClearConsole();
    Draw(0, 50, 1);
    Textcolor(Black);
    gotoXY(60, 18);
    cout << "ABOUT";
    gotoXY(50, 21);
    cout << "DO AN GAME CARO - LOP 22CTT4 - HCMUS\n";
    gotoXY(50, 22);
    cout << "GV huong dan:    Truong Toan Thinh\n";
    gotoXY(50, 23);
    cout << "Ho ten:          Pham Tan Nghia               MSSV   : 22120230.\n";
    gotoXY(50, 24);
    cout << "Ho ten:          Tran Duc Minh                MSSV   : 22120212.\n";
    gotoXY(50, 25);
    cout << "Ho ten:          Mai Nhat Nam                 MSSV   : 22120219.\n";
    gotoXY(50, 26);
    cout << "Ho ten:          Hoang Thanh Thao Nguyen      MSSV   : 22120235.\n";
    gotoXY(50, 27);
    cout << "Ho ten:          Vo Thanh Long                MSSV   : 22120195.\n";



    Textcolor(Grey);
    gotoXY(70, 30);  cout << "   S   ";
    Textcolor(Black);
    gotoXY(110, 30);
    cout << " : BACK";
    char command = ' ';
    command = _getch();
    if (command == 's' or command == 'S') {
        ClearConsole();
        menu();
    }

}
void Draw(int i, int x, int y) {
    fstream file;
    file.open(file_name[i], ios::in);
    if (file.is_open()) {
        string line;
        int j = 0;
        while (getline(file, line)) {
            gotoXY(x, y + j);
            Textcolor(rand() % 10 + 1);
            cout << line << endl;
            j++;
        }
        file.close();
    }
}
void History() {
    ClearConsole();
    Draw(0, 50, 1);
    Textcolor(Green);
    gotoXY(68, 19);
    cout << "LIST FILE NAME History";
    int i = 22;

    fstream f;
    f.open("History.txt", ios::in);
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
        gotoXY(50, i);
        cout << s << " " << s1 << setw(50) << left << buffer;
        i++;
    }
   
    int y = 31;
    f.close();
    Textcolor(Grey);
    gotoXY(70, 38);  cout << "   S   ";
    Textcolor(Black);
    gotoXY(78, 38);
    cout << " : BACK";
    switch (_getch())
    {
    case 's':
        /*playSound(1);*/
        y++;
        if (y == 32)
        {
            ClearConsole();
            menu();
        }
    }
}
int ReadChedo(char a[30])
{
    int d1, d2, chedo;
    ifstream f;
    f.open(a, ios::in);
    if (!f) {
        /*playSound(7);*/
        Textcolor(Black);
        gotoXY(60, 34);
        cout << " FILE KHONG TON TAI!" << endl;
        int y = 31;
        Textcolor(Grey);
        gotoXY(60, 38);  cout << "   S   ";
        Textcolor(Black);
        gotoXY(68, 38);
        cout << " : BACK";
        switch (_getch())
        {
        case 's':
            /*playSound(1);*/
            y++;
            if (y == 32)
            {
                ClearConsole();
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
void ReadNameFile()
{
    Textcolor(Black);
    gotoXY(60, 18);
    cout << "LIST FILE NAME";
    int i = 19;
    ifstream f;
    f.open("Name.txt", ios::in);
    while (!f.eof())
    {
        char s[30];
        f >> s;
        gotoXY(50, i);
        cout << s;
        i++;
    }
    f.close();

}
void LoadLoad()
{
    int n = 100;
    ClearConsole();
    Draw(0, 50, 1);
    ReadNameFile();
    char data[30];
    gotoXY(50, 32);
    HienTroChuot();
    cout << "ENTER FILE NAME: ";
    cin.getline(data, 30);
    int chedo = ReadChedo(data);
    if (chedo == -30 || chedo == -31)
    {
        Diem a;
        a.score1 = 0;
        a.score2 = 0;
        int t = PlayerVsPlayer(a, chedo, data);
        if (t == 27)
        {
            ClearConsole();
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
            ClearConsole();
            menu();
        }
    }

}
void menu()
{
    setConsoleTitle();
    char s[30];
    int x = 50;
    int y = 20;
    // Initial menu setup
    Draw(0, x, y-19);
    for (int i = 0; i < numItems; i++)
    {
        gotoXY(x, y + i);
        cout << menuItems[i];
    }

    // Additional menu setup
    gotoXY(x, y + numItems + 2);
    cout << "W - S : Move ( Off Unikey - Off Caps Lock ) ";
    gotoXY(x, y + numItems + 3);
    cout << "Enter : Select ";
    gotoXY(x, y + numItems + 5);
    cout << "M: mute";

    char ch = ' '; // Initialize character input variable

    // Main loop to handle user input and menu selection
    while (ch != 'x') // Loop until user inputs 'x' to exit
    {
        //playSound(6, 'n');
        int input = 0;
        input = getConsoleInput(); // Get keyboard input

        // Clear current selection
        Textcolor(15);
        gotoXY(x, y + currentSelection);
        cout << menuItems[currentSelection];
        if (input == 9 || ch == 'n')
        {
            playSound(6, 'n');
         }
        if (input == 5 || ch == 's')
        {
            // Move down one row
            currentSelection = (currentSelection + 1) % numItems;
        }
        else if (input == 2 || ch == 'w')
        {
            // Move up one row
            currentSelection = (currentSelection - 1 + numItems) % numItems;
        }
        else if (input == 8 || ch == 'm') 
        {
            playSound(0, 'm');
        }
        else if (input == 6 || ch == '\r') // Check for Enter key press
        {
            // Call corresponding function for selected menu item
            switch (currentSelection)
            {
            case 0:
            {
                ClearConsole();
                Diem a;
                a.score1 = 0;
                a.score2 = 0;
                int t = PlayerVsPlayer(a, 0, s);
                if (t == 27)
                {
                    ClearConsole();
                    menu();
                }
                break;
            }
                case 1:
                {
                    ClearConsole();
                    Diem a;
                    a.score1 = 0;
                    a.score2 = 0;
                    int t = PlayerVsCom(a, 0, s);
                    if (t == 27)
                    {

                        system("cls");
                        menu();
                    }
                    break;
                }
                case 2:
                {
                    ClearConsole();
                    LoadLoad();
                    break;
                }
                case 3:
                {
                    ClearConsole();
                    History();
                    break;
                }
                case 4:
                {
                    ClearConsole();
                    Instruction();
                    break;
                }
                case 5:
                {
                    ClearConsole();
                    About();
                    break;
                }
                case 6:
                    ClearConsole();
                    exit(0);
                //ch = 'x';
                break;
                /* case 8:
                playSound(1, 'm');
                break;
                case 9:
                playSound(6);
                break;*/
             }
        }

        // Highlight new selection
        Textcolor(12);
        gotoXY(x, y + currentSelection);
        cout << menuItems[currentSelection];
        Textcolor(15);
    }
}
