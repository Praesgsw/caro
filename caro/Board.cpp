#include "Board.h"
void PrintScoreBoard()
{
    // Bang 1
    Textcolor(FullGreen);
    gotoXY(SIZE * 4 + 19, 5);
    for (int i = 0; i < 8; i++) {
        gotoXY(SIZE * 4 + 25, i + 1);
        cout << char(219);
    }
    for (int i = 1; i < 9; i++) {
        gotoXY(SIZE * 4 + 61, i + 1);
        cout << char(219);
    }
    gotoXY(SIZE * 4 + 25, 1);
    for (int i = 0; i < 37; i++) {
        cout << char(220);
    }
    gotoXY(SIZE * 4 + 25, 8 + 1);
    for (int i = 0; i < 37; i++) {
        cout << char(223);
    }

    Textcolor(Black);
    gotoXY(SIZE * 4 + 40, 3);
    cout << "PLAYER 1";
    gotoXY(SIZE * 4 + 30, 5);
    cout << "So quan X : ";
    gotoXY(SIZE * 4 + 30, 6);
    cout << "So tran da thang : ";


    //Bang 2
    Textcolor(FullBlue);
    gotoXY(SIZE * 4 + 19, (SIZE * 2 - 1) / 2 + 1);
    for (int i = 1; i < 8; i++) {
        gotoXY(SIZE * 4 + 25, 13 + i);
        cout << char(219);
    }
    for (int i = 1; i < 8; i++) {
        gotoXY(SIZE * 4 + 61, 13 + i);
        cout << char(219);
    }
    gotoXY(SIZE * 4 + 25, 13);
    for (int i = 0; i < 37; i++) {
        cout << char(220);
    }
    gotoXY(SIZE * 4 + 25, 13 + 8);
    for (int i = 0; i < 37; i++) {
        cout << char(223);
    }

    Textcolor(Black);
    gotoXY(SIZE * 4 + 40, 16);
    cout << "PLAYER 2";
    Textcolor(Black);
    gotoXY(SIZE * 4 + 30, 18);
    cout << "So quan O : ";
    gotoXY(SIZE * 4 + 30, 19);
    cout << "So tran da thang : ";

    // Bang 3
    Textcolor(FullRed);
    gotoXY(SIZE * 4 + 19, (SIZE * 2 - 1) - 3);
    for (int i = 0; i < 10; i++) {
        gotoXY(SIZE * 4 + 25, SIZE * 2 - i);
        cout << char(219);
    }
    for (int i = 0; i < 10; i++) {
        gotoXY(SIZE * 4 + 61, SIZE * 2 - i);
        cout << char(219);
    }
    gotoXY(SIZE * 4 + 25, SIZE * 2);
    for (int i = 0; i < 37; i++) {
        cout << char(223);
    }
    gotoXY(SIZE * 4 + 25, SIZE * 2 - 10);
    for (int i = 0; i < 37; i++) {
        cout << char(220);
    }

    Textcolor(Black);
    gotoXY(SIZE * 4 + 31, 33);
    cout << "-----------------------";
    gotoXY(SIZE * 4 + 30, 35);
    cout << " W A S D : Move ";
    gotoXY(SIZE * 4 + 30, 36);
    cout << " G : Save Game ";
    gotoXY(SIZE * 4 + 30, 37);
    cout << " L : Load Game ";
    gotoXY(SIZE * 4 + 30, 38);
    cout << " ESC : Exit ";

    gotoXY(2, 1);
} // IN BANG DIEM

void drawBoard()
{
    system("color FA");
    //if (SiZe == 0) return;
    Textcolor(Black);
    // vẽ cột phải
    for (int i = 0; i < SIZE * 2; i++)
    {
        gotoXY(SIZE * 4, i + 1);
        if ((i + 1) % 2 == 1)
            cout << char(186);
        else
            cout << char(182);
    }

    // vẽ dòng ngang
    for (int i = 0; i < SIZE * 2; i = i + 2)
    {
        gotoXY(0, i);
        for (int j = 0; j < SIZE * 4; j++)
        {
            if (j % 4 == 0)
                cout << char(197);
            else
                cout << char(196);
        }
    }

    // vẽ cột trái
    for (int i = 0; i < SIZE * 2; i++)
    {
        gotoXY(0, i + 1);
        if ((i + 1) % 2 == 1)
            cout << char(186);
        else
            cout << char(199);
    }

    // vẽ cột dọc
    for (int i = 1; i < SIZE * 2; i = i + 2)
    {
        for (int j = 0; j < SIZE * 4; j = j + 4)
        {
            gotoXY(j, i);
            if (j == 0)
                continue;
            cout << char(179);
        }
    }

    // vẽ dòng đầu
    gotoXY(0, 0);
    for (int i = 0; i < SIZE * 4; i++)
    {
        if (i % 4 == 0)
            cout << char(209);
        else
            cout << char(205);
    }
    gotoXY(0, 0); cout << char(201);
    gotoXY(SIZE * 4, 0); cout << char(187);

    // vẽ dòng cuối
    gotoXY(0, SIZE * 2);
    for (int i = 0; i < SIZE * 4; i++)
    {
        if (i % 4 == 0)
            cout << char(207);
        else
            cout << char(205);
    }
    gotoXY(0, SIZE * 2); cout << char(200);
    gotoXY(SIZE * 4, SIZE * 2);
    cout << char(188);

    // về vị trí x y
    gotoXY(2, 1);
}
void box()
{
    int i = 5, j = 5;
    Textcolor(Red);
    gotoXY(35, j + 19);
    cout << "ESC : BACK";
}