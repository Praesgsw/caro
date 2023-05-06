#include "Game.h"
int _Point::getX()
{
    return _x;
}
int _Point::getY()
{
    return _y;
}
int _Point::getCheck()
{
    return _check;
}
void _Point::setX(int pX)
{
    _x = pX;
}
void _Point::setY(int pY)
{
    _y = pY;
}
bool _Point::setCheck(int pCheck)
{
    if (pCheck == -1 || pCheck == 1 || pCheck == 0)
    {
        _check = pCheck;
        return true;
    }
    return false;
}
_Point::_Point()
{
    _x = 0;
    _y = 0;
    _check = 0;
}
_Point::_Point(int x, int y)
{
    _x = x;
    _y = y;
    _check = 0;
}
_Point::~_Point()
{
}

vector<_Point> win;
int _Board::getSize() { return _size; }
int _Board::getLeft() { return _left; }
int _Board::getTop() { return _top; }
int _Board::getXAt(int i, int j)
{
    return _pArr[i][j].getX();
}
int _Board::getYAt(int i, int j)
{
    return _pArr[i][j].getY();
}
_Board::_Board()
{
    for (int i = 0; i < _size; i++)
    {
        delete[] _pArr[i];
    }
    delete[] _pArr;
}
_Board::_Board(int pSize, int pX, int pY)
{
    _size = pSize;
    _left = pX;
    _top = pY;
    _pArr = new _Point * [pSize];
    for (int i = 0; i < pSize; i++)
    {
        _pArr[i] = new _Point[pSize];
    }
}
void _Board::loadData(int i, int j, int k)
{
    if (_size == 0)
        return;
    _pArr[i][j].setX(4 * j + _left + 2);
    _pArr[i][j].setY(2 * i + _top + 1);
    _pArr[i][j].setCheck(k);
    if (k == -1)
    {
        Textcolor(240); // X
        gotoXY(4 * j + _left + 2, 2 * i + _top + 1);
        cout << "X";
        CountX++;
    }
    if (k == 1)
    {
        Textcolor(240); // O
        gotoXY(4 * j + _left + 2, 2 * i + _top + 1);
        cout << "O";
        CountY++;
    }
}
void _Board::resetData()
{
    if (_size == 0)
        return;
    for (int i = 0; i < _size; i++)
    {
        for (int j = 0; j < _size; j++)
        {
            _pArr[i][j].setX(4 * j + _left + 2);
            _pArr[i][j].setY(2 * i + _top + 1);
            _pArr[i][j].setCheck(0);
        }
    }
}

int _Board::checkBoard(int pX, int pY, bool pTurn) // che do choi 0 : Player - 1 :Bot
{
    for (int i = 0; i < _size; i++)
    {
        for (int j = 0; j < _size; j++)
        {
            if (_pArr[i][j].getX() == pX && _pArr[i][j].getY() == pY && _pArr[i][j].getCheck() == 0)
            {
                if (pTurn)
                {
                    _pArr[i][j].setCheck(-1);
                    CountX++;
                } // X
                else
                {
                    _pArr[i][j].setCheck(1);
                    CountY++;
                } // O
                return _pArr[i][j].getCheck();
            }
        }
    }
    return 0;
}

int _Board::checkWinRow(int x, int y, int value)
{
    int dong, cot;
    int loop = 1;
    int test = -1;
    int check2dau = 0;
    int countRowLeft = 0, countRowRight = 0;
    dong = (x - _left - 2) / 4;
    cot = (y - _top - 1) / 2;
    int dongtrai, dongphai; // Xet dem X ve phia trai, va ve phia phai
    dongtrai = dongphai = dong;
    // Xet X chien thang
    // Xet hang ngang
    while (_pArr[cot][dongtrai].getCheck() == value)
    {
        win.push_back(_pArr[cot][dongtrai]);
        countRowLeft++;
        if (dongtrai == 0)
            break;
        dongtrai--;
    }
    while (_pArr[cot][dongphai].getCheck() == value)
    {
        win.push_back(_pArr[cot][dongphai]);
        countRowRight++;
        if (dongphai == _size - 1)
            break;
        dongphai++;
    }
    if (_pArr[cot][dongtrai].getCheck() == -value && _pArr[cot][dongphai].getCheck() == -value)
        check2dau = 1;
    if ((countRowLeft + countRowRight - 1) == 5 && (check2dau == 0))
    {
        test = 1;
    }
    else
        test = 0;
    if (test == 1)
    {
        PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
        while (loop < 30)
        {
            Textcolor(rand() % 15 + 1);
            for (int i = 0; i < win.size(); i++)
            {
                gotoXY(win[i].getX(), win[i].getY());
                if (win[i].getCheck() == -1)
                    cout << "X";
                else
                    cout << "O";
            }
            Sleep(100);
            loop++;
        }
    }
    else
        win.clear();
    return test;
}
int _Board::checkWinCol(int x, int y, int value) // Xet chien thang theo hang doc
{
    int dong, cot;
    int test = -1, loop = 1;
    int check2dau = 0;
    int countColTop = 0, countColBot = 0;
    dong = (x - _left - 2) / 4;
    cot = (y - _top - 1) / 2;
    int cottren, cotduoi; // Xet bien dem ve phia tren, va ve phia duoi
    cottren = cotduoi = cot;
    // Xet chien thang
    // Xet hang doc
    while (_pArr[cottren][dong].getCheck() == value)
    {
        countColTop++;
        win.push_back(_pArr[cottren][dong]);
        if (cottren == 0)
            break;
        cottren--;
    }
    while (_pArr[cotduoi][dong].getCheck() == value)
    {
        countColBot++;
        win.push_back(_pArr[cotduoi][dong]);
        if (cotduoi == _size - 1)
            break;
        cotduoi++;
    }
    if (_pArr[cottren][dong].getCheck() == -value && _pArr[cotduoi][dong].getCheck() == -value)
        check2dau = 1;
    if ((countColTop + countColBot - 1) == 5 && (check2dau == 0))
    {
        test = 1;
    }
    else
        test = 0;
    if (test == 1)
    {
        // PlaySound(TEXT("win.wav"), NULL, SND_FILENAME | SND_ASYNC);
        while (loop < 30)
        {
            Textcolor(rand() % 15 + 1);
            for (int i = 0; i < win.size(); i++)
            {
                gotoXY(win[i].getX(), win[i].getY());
                if (win[i].getCheck() == -1)
                    cout << "X";
                else
                    cout << "O";
            }
            Sleep(100);
            loop++;
        }
    }
    else
        win.clear();
    return test;
}
int _Board::checksecondDiagonal(int x, int y, int value)
{
    int dong, cot;
    int test = -1, loop = 1;
    int check2dau = 0;
    int countDiaTop = 0, countDiaBot = 0;
    dong = (x - _left - 2) / 4;
    cot = (y - _top - 1) / 2;
    int cottren, cotduoi; // Xet dem X ve phia tren, va ve phia duoi
    int dongphai, dongtrai;
    cottren = cotduoi = cot;
    dongphai = dongtrai = dong;
    // Xet X chien thang
    // Xet hang ngang
    while (_pArr[cottren][dongtrai].getCheck() == value)
    {
        win.push_back(_pArr[cottren][dongtrai]);
        countDiaTop++;
        if (cottren == 0 || dongtrai == 0)
            break;
        cottren--;
        dongtrai--;
    }

    while (_pArr[cotduoi][dongphai].getCheck() == value)
    {
        win.push_back(_pArr[cotduoi][dongphai]);
        countDiaBot++;
        if (cotduoi == _size - 1 || dongphai == _size - 1)
            break;
        cotduoi++;
        dongphai++;
    }
    if (_pArr[cottren][dongtrai].getCheck() == -value && _pArr[cotduoi][dongphai].getCheck() == -value)
        check2dau = 1;
    if ((countDiaTop + countDiaBot - 1) == 5 && (check2dau == 0))
    {
        test = 1;
    }
    else
        test = 0;
    if (test == 1)
    {
        PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
        while (loop < 30)
        {
            Textcolor(rand() % 15 + 1);
            for (int i = 0; i < win.size(); i++)
            {
                gotoXY(win[i].getX(), win[i].getY());
                if (win[i].getCheck() == -1)
                    cout << "X";
                else
                    cout << "O";
            }
            Sleep(100);
            loop++;
        }
    }
    else
        win.clear();
    return test;
}
int _Board::checkfirstDiagonal(int x, int y, int value)
{
    int dong, cot;
    int test = -1, loop = 1;
    int check2dau = 0;
    int countDiaTop = 0, countDiaBot = 0;
    dong = (x - _left - 2) / 4;
    cot = (y - _top - 1) / 2;
    int cottren, cotduoi; // Xet dem X ve phia tren, va ve phia duoi
    int dongphai, dongtrai;
    cottren = cotduoi = cot;
    dongphai = dongtrai = dong;
    // Xet X chien thang
    // Xet hang ngang
    while (_pArr[cottren][dongphai].getCheck() == value)
    {
        countDiaTop++;
        win.push_back(_pArr[cottren][dongphai]);
        if (cottren == 0 || dongphai == _size - 1)
            break;
        cottren--;
        dongphai++;
    }
    while (_pArr[cotduoi][dongtrai].getCheck() == value)
    {
        win.push_back(_pArr[cotduoi][dongtrai]);
        countDiaBot++;
        if (cotduoi == _size - 1 || dongtrai == 0)
            break;
        cotduoi++;
        dongtrai--;
    }
    if (_pArr[cottren][dongphai].getCheck() == -value && _pArr[cotduoi][dongtrai].getCheck() == -value)
        check2dau = 1;
    if ((countDiaTop + countDiaBot - 1) == 5 && (check2dau == 0))
    {
        test = 1;
    }
    else
        test = 0;
    if (test == 1)
    {
        PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
        while (loop < 30)
        {
            Textcolor(rand() % 15 + 1);
            for (int i = 0; i < win.size(); i++)
            {
                gotoXY(win[i].getX(), win[i].getY());
                if (win[i].getCheck() == -1)
                {
                    cout << "X";
                }
                else
                {
                    cout << "O";
                }
            }
            Sleep(100);
            loop++;
        }
    }
    else
        win.clear();
    return test;
}
int _Board::testBoard(int x, int y)
{
    // X chien thang
    if (checkWinRow(x, y, -1) == 1)
        return -1;
    if (checkWinCol(x, y, -1) == 1)
        return -1;
    if (checkfirstDiagonal(x, y, -1) == 1)
        return -1;
    if (checksecondDiagonal(x, y, -1) == 1)
        return -1;
    // O chien thang
    if (checkWinRow(x, y, 1) == 1)
        return 1;
    if (checkWinCol(x, y, 1) == 1)
        return 1;
    if (checkfirstDiagonal(x, y, 1) == 1)
        return 1;
    if (checksecondDiagonal(x, y, 1) == 1)
        return 1;
    if (CountX + CountY == SIZE * SIZE)
        return 0;
    return 2;
}
_Board::~_Board()
{
}

// Xu li AI
long _Board::SoDiemTanCong_DuyetNgang(long Dong, long Cot, const long Defend_Score[], const long Attack_Score[])
{
    long iScoreTempNgang = 0;
    long iScoreAttack = 0;
    int iSoQuanTa = 0;
    int iSoQuanDich = 0;
    int iSoQuanTa2 = 0;
    int iSoQuanDich2 = 0;
    for (int iDem = 1; iDem < 6 && Cot + iDem < _size; iDem++)
    {
        if (_pArr[Dong][Cot + iDem].getCheck() == 1)
            iSoQuanTa++;
        if (_pArr[Dong][Cot + iDem].getCheck() == -1)
        {
            iSoQuanDich++;
            break;
        }
        if (_pArr[Dong][Cot + iDem].getCheck() == 0)
        {
            for (int iDem2 = 2; iDem2 < 7 && Cot + iDem2 < _size; iDem2++)
            {
                if (_pArr[Dong][Cot + iDem2].getCheck() == 1)
                    iSoQuanTa2++;
                if (_pArr[Dong][Cot + iDem2].getCheck() == -1)
                {
                    iSoQuanDich2++;
                    break;
                }
                if (_pArr[Dong][Cot + iDem2].getCheck() == 0)
                    break;
            }
            break;
        }
    }
    for (int iDem = 1; iDem < 6 && Cot - iDem >= 0; iDem++)
    {
        if (_pArr[Dong][Cot - iDem].getCheck() == 1)
            iSoQuanTa++;
        if (_pArr[Dong][Cot - iDem].getCheck() == -1)
        {
            iSoQuanDich++;
            break;
        }
        if (_pArr[Dong][Cot - iDem].getCheck() == 0)
        {
            for (int iDem2 = 2; iDem2 < 7 && Cot - iDem2 >= 0; iDem2++)
            {
                if (_pArr[Dong][Cot - iDem2].getCheck() == 1)
                    iSoQuanTa2++;
                if (_pArr[Dong][Cot - iDem2].getCheck() == -1)
                {
                    iSoQuanDich2++;
                    break;
                }
                if (_pArr[Dong][Cot - iDem2].getCheck() == 0)
                    break;
            }
            break;
        }
    }
    if (iSoQuanDich == 2)
        return 0;
    if (iSoQuanDich == 0)
        iScoreTempNgang += Attack_Score[iSoQuanTa] * 2;
    else
        iScoreTempNgang += Attack_Score[iSoQuanTa];
    if (iSoQuanDich2 == 0)
        iScoreTempNgang += Attack_Score[iSoQuanTa2] * 2;
    else
        iScoreTempNgang += Attack_Score[iSoQuanTa2];

    if (iSoQuanTa >= iSoQuanTa2)
        iScoreTempNgang -= 1;
    else
        iScoreTempNgang -= 2;
    if (iSoQuanTa == 4)
        iScoreTempNgang *= 2;
    if (iSoQuanTa == 0)
        iScoreTempNgang += Defend_Score[iSoQuanDich] * 2;
    else
        iScoreTempNgang += Defend_Score[iSoQuanDich];
    if (iSoQuanTa2 == 0)
        iScoreTempNgang += Defend_Score[iSoQuanDich2] * 2;
    else
        iScoreTempNgang += Defend_Score[iSoQuanDich2];
    return iScoreTempNgang;
}
long _Board::SoDiemTanCong_DuyetDoc(long Dong, long Cot, const long Defend_Score[], const long Attack_Score[])
{
    long iScoreTempDoc = 0;
    long iScoreAttack = 0;
    int iSoQuanTa = 0;
    int iSoQuanDich = 0;
    int iSoQuanTa2 = 0;
    int iSoQuanDich2 = 0;
    for (int iDem = 1; iDem < 6 && Dong + iDem < _size; iDem++)
    {
        if (_pArr[Dong + iDem][Cot].getCheck() == 1)
            iSoQuanTa++;
        if (_pArr[Dong + iDem][Cot].getCheck() == -1)
        {
            iSoQuanDich++;
            break;
        }
        if (_pArr[Dong + iDem][Cot].getCheck() == 0)
        {
            for (int iDem2 = 2; iDem2 < 7 && Dong + iDem2 < _size; iDem2++)
            {
                if (_pArr[Dong + iDem2][Cot].getCheck() == 1)
                    iSoQuanTa2++;
                if (_pArr[Dong + iDem2][Cot].getCheck() == -1)
                {
                    iSoQuanDich2++;
                    break;
                }
                if (_pArr[Dong + iDem2][Cot].getCheck() == 0)
                    break;
            }
            break;
        }
    }
    for (int iDem = 1; iDem < 6 && Dong - iDem >= 0; iDem++)
    {
        if (_pArr[Dong - iDem][Cot].getCheck() == 1)
            iSoQuanTa++;
        if (_pArr[Dong - iDem][Cot].getCheck() == -1)
        {
            iSoQuanDich++;
            break;
        }
        if (_pArr[Dong - iDem][Cot].getCheck() == 0)
        {
            for (int iDem2 = 2; iDem2 < 7 && Dong - iDem2 >= 0; iDem2++)
            {
                if (_pArr[Dong - iDem2][Cot].getCheck() == 1)
                    iSoQuanTa2++;
                if (_pArr[Dong - iDem2][Cot].getCheck() == -1)
                {
                    iSoQuanDich2++;
                    break;
                }
                if (_pArr[Dong - iDem2][Cot].getCheck() == 0)
                {
                    break;
                }
            }
            break;
        }
    }

    if (iSoQuanDich == 2)
        return 0;
    if (iSoQuanDich == 0)
        iScoreTempDoc += Attack_Score[iSoQuanTa] * 2;
    else
        iScoreTempDoc += Attack_Score[iSoQuanTa];
    if (iSoQuanDich2 == 0)
        iScoreTempDoc += Attack_Score[iSoQuanTa2] * 2;
    else
        iScoreTempDoc += Attack_Score[iSoQuanTa2];

    if (iSoQuanTa >= iSoQuanTa2)
        iScoreTempDoc -= 1;
    else
        iScoreTempDoc -= 2;
    if (iSoQuanTa == 4)
        iScoreTempDoc *= 2;
    if (iSoQuanTa == 0)
        iScoreTempDoc += Defend_Score[iSoQuanDich] * 2;
    else
        iScoreTempDoc += Defend_Score[iSoQuanDich];
    if (iSoQuanTa2 == 0)
        iScoreTempDoc += Defend_Score[iSoQuanDich2] * 2;
    else
        iScoreTempDoc += Defend_Score[iSoQuanDich2];
    return iScoreTempDoc;
}

long _Board::SoDiemTanCong_DuyetCheo1(long Dong, long Cot, const long Defend_Score[], const long Attack_Score[])
{
    long iScoreTempCheoNguoc = 0;
    long iScoreAttack = 0;
    int iSoQuanTa = 0;
    int iSoQuanDich = 0;
    int iSoQuanTa2 = 0;
    int iSoQuanDich2 = 0;
    for (int iDem = 1; iDem < 6 && Cot + iDem < _size && Dong + iDem < _size; iDem++)
    {
        if (_pArr[Dong + iDem][Cot + iDem].getCheck() == 1)
            iSoQuanTa++;
        if (_pArr[Dong + iDem][Cot + iDem].getCheck() == -1)
        {
            iSoQuanDich++;
            break;
        }
        if (_pArr[Dong + iDem][Cot + iDem].getCheck() == 0)
        {
            for (int iDem2 = 2; iDem2 < 7 && Cot + iDem2 < _size && Dong + iDem2 < _size; iDem2++)
            {
                if (_pArr[Dong + iDem2][Cot + iDem2].getCheck() == 1)
                    iSoQuanTa2++;
                if (_pArr[Dong + iDem2][Cot + iDem2].getCheck() == -1)
                {
                    iSoQuanDich2++;
                    break;
                }
                if (_pArr[Dong + iDem2][Cot + iDem2].getCheck() == 0)
                {
                    break;
                }
            }
            break;
        }
    }
    for (int iDem = 1; iDem < 6 && Cot - iDem >= 0 && Dong - iDem >= 0; iDem++)
    {
        if (_pArr[Dong - iDem][Cot - iDem].getCheck() == 1)
            iSoQuanTa++;
        if (_pArr[Dong - iDem][Cot - iDem].getCheck() == -1)
        {
            iSoQuanDich++;
            break;
        }
        if (_pArr[Dong - iDem][Cot - iDem].getCheck() == 0)
        {
            for (int iDem2 = 2; iDem2 < 7 && Cot - iDem2 >= 0 && Dong - iDem2 >= 0; iDem2++)
            {
                if (_pArr[Dong - iDem2][Cot - iDem2].getCheck() == 1)
                    iSoQuanTa2++;
                if (_pArr[Dong - iDem2][Cot - iDem2].getCheck() == -1)
                {
                    iSoQuanDich2++;
                    break;
                }
                if (_pArr[Dong - iDem2][Cot - iDem2].getCheck() == 0)
                    break;
            }
            break;
        }
    }
    if (iSoQuanDich == 2)
        return 0;
    if (iSoQuanDich == 0)
        iScoreTempCheoNguoc += Attack_Score[iSoQuanTa] * 2;
    else
        iScoreTempCheoNguoc += Attack_Score[iSoQuanTa];
    if (iSoQuanDich2 == 0)
        iScoreTempCheoNguoc += Attack_Score[iSoQuanTa2] * 2;
    else
        iScoreTempCheoNguoc += Attack_Score[iSoQuanTa2];

    if (iSoQuanTa >= iSoQuanTa2)
        iScoreTempCheoNguoc -= 1;
    else
        iScoreTempCheoNguoc -= 2;
    if (iSoQuanTa == 4)
        iScoreTempCheoNguoc *= 2;
    if (iSoQuanTa == 0)
        iScoreTempCheoNguoc += Defend_Score[iSoQuanDich] * 2;
    else
        iScoreTempCheoNguoc += Defend_Score[iSoQuanDich];
    if (iSoQuanTa2 == 0)
        iScoreTempCheoNguoc += Defend_Score[iSoQuanDich2] * 2;
    else
        iScoreTempCheoNguoc += Defend_Score[iSoQuanDich2];
    return iScoreTempCheoNguoc;
}
long _Board::SoDiemTanCong_DuyetCheo2(long Dong, long Cot, const long Defend_Score[], const long Attack_Score[])
{
    long iScoreTempCheoXuoi = 0;
    long iScoreAttack = 0;
    int iSoQuanTa = 0;
    int iSoQuanDich = 0;
    int iSoQuanTa2 = 0;
    int iSoQuanDich2 = 0;
    for (int iDem = 1; iDem < 6 && Cot - iDem >= 0 && Dong + iDem < _size; iDem++)
    {
        if (_pArr[Dong + iDem][Cot - iDem].getCheck() == 1)
            iSoQuanTa++;
        if (_pArr[Dong + iDem][Cot - iDem].getCheck() == -1)
        {
            iSoQuanDich++;
            break;
        }
        if (_pArr[Dong + iDem][Cot - iDem].getCheck() == 0)
        {
            for (int iDem2 = 2; iDem2 < 7 && Cot - iDem2 >= 0 && Dong + iDem2 < _size; iDem2++)
            {
                if (_pArr[Dong + iDem2][Cot - iDem2].getCheck() == 1)
                    iSoQuanTa2++;
                if (_pArr[Dong + iDem2][Cot - iDem2].getCheck() == -1)
                {
                    iSoQuanDich2++;
                    break;
                }
                if (_pArr[Dong + iDem2][Cot - iDem2].getCheck() == 0)
                    break;
            }
            break;
        }
    }
    for (int iDem = 1; iDem < 6 && Cot + iDem < _size && Dong - iDem >= 0; iDem++)
    {
        if (_pArr[Dong - iDem][Cot + iDem].getCheck() == 1)
            iSoQuanTa++;
        if (_pArr[Dong - iDem][Cot + iDem].getCheck() == -1)
        {
            iSoQuanDich++;
            break;
        }
        if (_pArr[Dong - iDem][Cot + iDem].getCheck() == 0)
        {
            for (int iDem2 = 2; iDem2 < 7 && Cot + iDem2 < _size && Dong - iDem2 >= 0; iDem2++)
            {
                if (_pArr[Dong - iDem2][Cot + iDem2].getCheck() == 1)
                    iSoQuanTa2++;
                if (_pArr[Dong - iDem2][Cot + iDem2].getCheck() == -1)
                {
                    iSoQuanDich2++;
                    break;
                }
                if (_pArr[Dong - iDem2][Cot + iDem2].getCheck() == 0)
                    break;
            }
            break;
        }
    }
    if (iSoQuanDich == 2)
        return 0;
    if (iSoQuanDich == 0)
        iScoreTempCheoXuoi += Attack_Score[iSoQuanTa] * 2;
    else
        iScoreTempCheoXuoi += Attack_Score[iSoQuanTa];
    if (iSoQuanDich2 == 0)
        iScoreTempCheoXuoi += Attack_Score[iSoQuanTa2] * 2;
    else
        iScoreTempCheoXuoi += Attack_Score[iSoQuanTa2];

    if (iSoQuanTa >= iSoQuanTa2)
        iScoreTempCheoXuoi -= 1;
    else
        iScoreTempCheoXuoi -= 2;
    if (iSoQuanTa == 4)
        iScoreTempCheoXuoi *= 2;
    if (iSoQuanTa == 0)
        iScoreTempCheoXuoi += Defend_Score[iSoQuanDich] * 2;
    else
        iScoreTempCheoXuoi += Defend_Score[iSoQuanDich];
    if (iSoQuanTa2 == 0)
        iScoreTempCheoXuoi += Defend_Score[iSoQuanDich2] * 2;
    else
        iScoreTempCheoXuoi += Defend_Score[iSoQuanDich2];
    return iScoreTempCheoXuoi;
}

long _Board::SoDiemPhongThu_DuyetDoc(long Dong, long Cot, const long Defend_Score[], const long Attack_Score[])
{
    long iScoreTempDoc = 0;
    long iScoreDefend = 0;
    int iSoQuanDich = 0;
    int iSoQuanTa = 0;
    int iSoQuanDich2 = 0;
    int iSoQuanTa2 = 0;
    for (int iDem = 1; iDem < 6 && Dong + iDem < _size; iDem++)
    {
        if (_pArr[Dong + iDem][Cot].getCheck() == 1)
        {
            iSoQuanTa++;
            break;
        }
        if (_pArr[Dong + iDem][Cot].getCheck() == -1)
            iSoQuanDich++;
        if (_pArr[Dong + iDem][Cot].getCheck() == 0)
        {
            for (int iDem2 = 2; iDem2 < 7 && Dong + iDem2 < _size; iDem2++)
            {
                if (_pArr[Dong + iDem2][Cot].getCheck() == 1)
                {
                    iSoQuanTa2++;
                    break;
                }
                if (_pArr[Dong + iDem2][Cot].getCheck() == -1)
                    iSoQuanDich2++;
                if (_pArr[Dong + iDem2][Cot].getCheck() == 0)
                    break;
            }
            break;
        }
    }
    for (int iDem = 1; iDem < 6 && Dong - iDem >= 0; iDem++)
    {
        if (_pArr[Dong - iDem][Cot].getCheck() == 1)
        {
            iSoQuanTa++;
            break;
        }
        if (_pArr[Dong - iDem][Cot].getCheck() == -1)
            iSoQuanDich++;
        if (_pArr[Dong - iDem][Cot].getCheck() == 0)
        {
            for (int iDem2 = 2; iDem2 < 7 && Dong - iDem2 >= 0; iDem2++)
            {
                if (_pArr[Dong - iDem2][Cot].getCheck() == 1)
                {
                    iSoQuanTa2++;
                    break;
                }
                if (_pArr[Dong - iDem2][Cot].getCheck() == -1)
                    iSoQuanDich2++;
                if (_pArr[Dong - iDem2][Cot].getCheck() == 0)
                    break;
            }
            break;
        }
    }

    if (iSoQuanTa == 2)
        return 0;
    if (iSoQuanTa == 0)
        iScoreTempDoc += Defend_Score[iSoQuanDich] * 2;
    else
        iScoreTempDoc += Defend_Score[iSoQuanDich];
    if (iSoQuanDich >= iSoQuanDich2)
        iScoreTempDoc -= 1;
    else
        iScoreTempDoc -= 2;
    if (iSoQuanDich == 4)
        iScoreTempDoc *= 2;
    return iScoreTempDoc;
}

long _Board::SoDiemPhongThu_DuyetNgang(long Dong, long Cot, const long Defend_Score[], const long Attack_Score[])
{
    long iScoreTempNgang = 0;
    long iScoreDefend = 0;
    int iSoQuanDich = 0;
    int iSoQuanTa = 0;
    int iSoQuanDich2 = 0;
    int iSoQuanTa2 = 0;
    for (int iDem = 1; iDem < 6 && Cot + iDem < _size; iDem++)
    {
        if (_pArr[Dong][Cot + iDem].getCheck() == 1)
        {
            iSoQuanTa++;
            break;
        }
        if (_pArr[Dong][Cot + iDem].getCheck() == -1)
            iSoQuanDich++;
        if (_pArr[Dong][Cot + iDem].getCheck() == 0)
        {
            for (int iDem2 = 2; iDem2 < 7 && Cot + iDem2 < _size; iDem2++)
            {
                if (_pArr[Dong][Cot + iDem2].getCheck() == 1)
                {
                    iSoQuanTa2++;
                    break;
                }
                if (_pArr[Dong][Cot + iDem2].getCheck() == -1)
                    iSoQuanDich2++;
                if (_pArr[Dong][Cot + iDem2].getCheck() == 0)
                    break;
            }
            break;
        }
    }
    for (int iDem = 1; iDem < 6 && Cot - iDem >= 0; iDem++)
    {
        if (_pArr[Dong][Cot - iDem].getCheck() == 1)
        {
            iSoQuanTa++;
            break;
        }
        if (_pArr[Dong][Cot - iDem].getCheck() == 0)
        {
            for (int iDem2 = 2; iDem2 < 7 && Cot - iDem2 >= 0; iDem2++)
            {
                if (_pArr[Dong][Cot - iDem2].getCheck() == 1)
                {
                    iSoQuanTa2++;
                    break;
                }
                if (_pArr[Dong][Cot - iDem2].getCheck() == 0)
                    break;
                if (_pArr[Dong][Cot - iDem2].getCheck() == -1)
                    iSoQuanDich2++;
            }
            break;
        }
        if (_pArr[Dong][Cot - iDem].getCheck() == -1)
            iSoQuanDich++;
    }

    if (iSoQuanTa == 2)
        return 0;
    if (iSoQuanTa == 0)
        iScoreTempNgang += Defend_Score[iSoQuanDich] * 2;
    else
        iScoreTempNgang += Defend_Score[iSoQuanDich];
    if (iSoQuanDich >= iSoQuanDich2)
        iScoreTempNgang -= 1;
    else
        iScoreTempNgang -= 2;
    if (iSoQuanDich == 4)
        iScoreTempNgang *= 2;
    return iScoreTempNgang;
}

long _Board::SoDiemPhongThu_DuyetCheo1(long Dong, long Cot, const long Defend_Score[], const long Attack_Score[])
{
    long iScoreTempCheoNguoc = 0;
    long iScoreDefend = 0;
    int iSoQuanDich = 0;
    int iSoQuanTa = 0;
    int iSoQuanDich2 = 0;
    int iSoQuanTa2 = 0;
    for (int iDem = 1; iDem < 6 && Cot + iDem < _size && Dong + iDem < _size; iDem++)
    {
        if (_pArr[Dong + iDem][Cot + iDem].getCheck() == 1)
        {
            iSoQuanTa++;
            break;
        }
        if (_pArr[Dong + iDem][Cot + iDem].getCheck() == 0)
        {
            for (int iDem2 = 2; iDem2 < 7 && Cot + iDem2 < _size && Dong + iDem2 < _size; iDem2++)
            {
                if (_pArr[Dong + iDem2][Cot + iDem2].getCheck() == 1)
                {
                    iSoQuanTa2++;
                    break;
                }
                if (_pArr[Dong + iDem2][Cot + iDem2].getCheck() == 0)
                    break;
                if (_pArr[Dong + iDem2][Cot + iDem2].getCheck() == -1)
                    iSoQuanDich2++;
            }
            break;
        }
        if (_pArr[Dong + iDem][Cot + iDem].getCheck() == -1)
            iSoQuanDich++;
    }
    for (int iDem = 1; iDem < 6 && Cot - iDem >= 0 && Dong - iDem >= 0; iDem++)
    {
        if (_pArr[Dong - iDem][Cot - iDem].getCheck() == 1)
        {
            iSoQuanTa++;
            break;
        }

        if (_pArr[Dong - iDem][Cot - iDem].getCheck() == 0)
        {
            for (int iDem2 = 2; iDem2 < 7 && Cot - iDem2 >= 0 && Dong - iDem2 >= 0; iDem2++)
            {
                if (_pArr[Dong - iDem2][Cot - iDem2].getCheck() == 1)
                {
                    iSoQuanTa2++;
                    break;
                }

                if (_pArr[Dong - iDem2][Cot - iDem2].getCheck() == 0)
                    break;
                if (_pArr[Dong - iDem2][Cot - iDem2].getCheck() == -1)
                    iSoQuanDich2++;
            }
            break;
        }
        if (_pArr[Dong - iDem][Cot - iDem].getCheck() == -1)
            iSoQuanDich++;
    }
    if (iSoQuanTa == 2)
        return 0;
    if (iSoQuanTa == 0)
        iScoreTempCheoNguoc += Defend_Score[iSoQuanDich] * 2;
    else
        iScoreTempCheoNguoc += Defend_Score[iSoQuanDich];
    if (iSoQuanDich >= iSoQuanDich2)
        iScoreTempCheoNguoc -= 1;
    else
        iScoreTempCheoNguoc -= 2;
    if (iSoQuanDich == 4)
        iScoreTempCheoNguoc *= 2;
    return iScoreTempCheoNguoc;
}

long _Board::SoDiemPhongThu_DuyetCheo2(long Dong, long Cot, const long Defend_Score[], const long Attack_Score[])
{
    long iScoreTempCheoXuoi = 0;
    long iScoreDefend = 0;
    int iSoQuanDich = 0;
    int iSoQuanTa = 0;
    int iSoQuanDich2 = 0;
    int iSoQuanTa2 = 0;
    for (int iDem = 1; iDem < 6 && Cot - iDem >= 0 && Dong + iDem < _size; iDem++)
    {
        if (_pArr[Dong + iDem][Cot - iDem].getCheck() == 1)
        {
            iSoQuanTa++;
            break;
        }
        if (_pArr[Dong + iDem][Cot - iDem].getCheck() == 0)
        {
            for (int iDem2 = 2; iDem2 < 7 && Cot - iDem2 >= 0 && Dong + iDem2 < _size; iDem2++)
            {
                if (_pArr[Dong + iDem2][Cot - iDem2].getCheck() == 1)
                {
                    iSoQuanTa2++;
                    break;
                }
                if (_pArr[Dong + iDem2][Cot - iDem2].getCheck() == 0)
                    break;
                if (_pArr[Dong + iDem2][Cot - iDem2].getCheck() == -1)
                    iSoQuanDich2++;
            }
            break;
        }
        if (_pArr[Dong + iDem][Cot - iDem].getCheck() == -1)
            iSoQuanDich++;
    }
    for (int iDem = 1; iDem < 6 && Cot + iDem < _size && Dong - iDem >= 0; iDem++)
    {
        if (_pArr[Dong - iDem][Cot + iDem].getCheck() == 1)
        {
            iSoQuanTa++;
            break;
        }
        if (_pArr[Dong - iDem][Cot + iDem].getCheck() == 0)
        {
            for (int iDem2 = 2; iDem < 7 && Cot + iDem2 < _size && Dong - iDem2 >= 0; iDem2++)
            {
                if (_pArr[Dong - iDem2][Cot + iDem2].getCheck() == 1)
                {
                    iSoQuanTa2++;
                    break;
                }
                if (_pArr[Dong - iDem2][Cot + iDem2].getCheck() == 0)
                    break;
                if (_pArr[Dong - iDem2][Cot + iDem2].getCheck() == -1)
                    iSoQuanDich2++;
            }
            break;
        }
        if (_pArr[Dong - iDem][Cot + iDem].getCheck() == -1)
            iSoQuanDich++;
    }

    if (iSoQuanTa == 2)
        return 0;
    if (iSoQuanTa == 0)
        iScoreTempCheoXuoi += Defend_Score[iSoQuanDich] * 2;
    else
        iScoreTempCheoXuoi += Defend_Score[iSoQuanDich];
    if (iSoQuanDich >= iSoQuanDich2)
        iScoreTempCheoXuoi -= 1;
    else
        iScoreTempCheoXuoi -= 2;
    if (iSoQuanDich == 4)
        iScoreTempCheoXuoi *= 2;
    return iScoreTempCheoXuoi;
}
_Point _Board::Tim_Kiem_NuocDi_1()
{
    _Point Oco;
    int dong = 0, cot = 0;
    long Diem = 0;
    for (int i = 0; i < _size; i++)
    {
        for (int j = 0; j < _size; j++)
        {
            long DiemTanCong = 0;
            long DiemPhongThu = 0;
            if (_pArr[i][j].getCheck() == 0)
            {
                DiemTanCong += SoDiemTanCong_DuyetDoc(i, j, Defend_Score1, Attack_Score1);
                DiemTanCong += SoDiemTanCong_DuyetNgang(i, j, Defend_Score1, Attack_Score1);
                DiemTanCong += SoDiemTanCong_DuyetCheo1(i, j, Defend_Score1, Attack_Score1);
                DiemTanCong += SoDiemTanCong_DuyetCheo2(i, j, Defend_Score1, Attack_Score1);
                DiemPhongThu += SoDiemPhongThu_DuyetDoc(i, j, Defend_Score1, Attack_Score1);
                DiemPhongThu += SoDiemPhongThu_DuyetNgang(i, j, Defend_Score1, Attack_Score1);
                DiemPhongThu += SoDiemPhongThu_DuyetCheo1(i, j, Defend_Score1, Attack_Score1);
                DiemPhongThu += SoDiemPhongThu_DuyetCheo2(i, j, Defend_Score1, Attack_Score1);

                if (DiemTanCong > DiemPhongThu)
                {
                    if (Diem < DiemTanCong)
                    {
                        Diem = DiemTanCong;
                        dong = i;
                        cot = j;
                    }
                }
                else
                {
                    if (Diem < DiemPhongThu)
                    {
                        Diem = DiemPhongThu;
                        dong = i;
                        cot = j;
                    }
                }
            }
        }
    }
    Oco.setX(cot * 4 + 2);
    Oco.setY(dong * 2 + 1);
    return Oco;
}

int PlayerVsCom(Diem& a, int load, char data[30])
{
    int n = 99;
    int k = 1;
    HienTroChuot();
    _Game g(SIZE, 0, 0);
    g.setCountXY(); // đếm số lượng x số lượng i
    if (load == -4)
    {
        g.LoadGame(data);
    }
    else
    {
        g.startGame();
        g.setTurn();
    }
    PrintScoreBoard();
    Textcolor(244);
    gotoXY(SIZE * 4 + 33, 32);
    cout << " PLAYER VS Computer ";
    Textcolor(240);
    gotoXY(SIZE * 4 + 30 + 19, 3);
    cout << a.score1;
    Textcolor(240);
    gotoXY(SIZE * 4 + 30 + 18, 16);
    cout << a.score2;
    gotoXY(2, 1);
    while (g.isContinue())
    {
        if (!g.getTurn())
        {
            if (g.DemNuocCoDaDi() == 0)
            {
                g.setX((SIZE * 4 / 2) - 2);
                g.setY((SIZE * 2 / 2) - 1);
                gotoXY((SIZE * 4 / 2) - 2, (SIZE * 2 / 2) - 1);
                g.setCommand(13);
            }
            else
            {
                g.TimKiemNuocDi();
                int x = g.getXatEnter();
                int y = g.getYatEnter();
                gotoXY(x, y);
                Sleep(300);
                g.setCommand(13);
            }
        }
        else
            g.waitKeyBoard();
        if (g.getCommand() == 27)
        {
            PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
            return 27;
        }
        else
        {
            switch (g.getCommand())
            {
            case 'A':
                PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                g.moveLeft();
                break;
            case 'D':
                PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                g.moveRight();
                break;
            case 'W':
                PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                g.moveUp();
                break;
            case 'S':
                PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                g.moveDown();
                break;
            case 'L':
                PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                g.SaveGame(-4);
                break;
            case 'T':
                PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                LoadLoad();
                break;
            case 13:
                PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                int x = g.getXatEnter();
                int y = g.getYatEnter();
                if (g.processCheckBoard())
                {
                    switch (g.processFinish(x, y))
                    {
                    case -1:
                        PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                        a.score1++;
                        while (k)
                        {
                            if (_kbhit())
                            {
                                switch (_getch())
                                {
                                case 'y':
                                    PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                                    load = 0;
                                    return PlayerVsCom(a, load, data);
                                    break;
                                case 27:
                                    PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                                    system("cls");
                                    menu();
                                    break;
                                }
                            }
                        }

                        break;
                    case 1:
                        PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                        a.score2++;
                        while (k)
                        {
                            if (_kbhit())
                            {
                                switch (_getch())
                                {
                                case 'y':
                                    PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                                    load = 0;
                                    return PlayerVsCom(a, load, data);
                                    break;
                                case 27:
                                    PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                                    system("cls");
                                    menu();
                                    break;
                                }
                            }
                        }

                        break;
                    case 0:
                        while (k)
                        {
                            if (_kbhit())
                            {
                                switch (_getch())
                                {
                                case 'y':
                                    PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                                    load = 0;
                                    return PlayerVsCom(a, load, data);
                                    break;
                                case 27:
                                    PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                                    system("cls");
                                    menu();
                                    break;
                                }
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
}

int PlayerVsPlayer(Diem& a, int load, char data[30])
{
    int k = 1;
    int n = 99;
    HienTroChuot();
    _Game g(SIZE, 0, 0);
    g.setCountXY();
    if (load == -30)
    {
        g.setTurn();
        g.LoadGame(data);
    }
    else if (load == -31)
    {
        g.LoadGame(data);
    }
    else
        g.startGame();
    PrintScoreBoard();
    Textcolor(240);
    gotoXY(SIZE * 4 + 32, 32);
    cout << " PLAYER VS PLAYER ";
    Textcolor(240);
    gotoXY(SIZE * 4 + 30 + 18, 6);
    cout << a.score1;
    Textcolor(240);
    gotoXY(SIZE * 4 + 30 + 18, 19);
    cout << a.score2;
    gotoXY(2, 1);
    while (g.isContinue())
    {
        g.waitKeyBoard();
        if (g.getCommand() == 27)
        {
            PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
            return 27;
        }

        else
        {
            switch (g.getCommand())
            {
            case 'A':
                PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                g.moveLeft();
                break;
            case 'D':
                PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                g.moveRight();
                break;
            case 'W':
                PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                g.moveUp();
                break;
            case 'S':
                PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                g.moveDown();
                break;
            case 'G':
                PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                if (g.getTurn() == 1)
                    g.SaveGame(-31);
                else
                    g.SaveGame(-30);
                break;
            case 'L':
                PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                LoadLoad();
                break;
            case 13:
                PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                int x = g.getXatEnter();
                int y = g.getYatEnter();
                if (g.processCheckBoard())
                {
                    switch (g.processFinish(x, y))
                    {
                    case -1:
                        a.score1++;
                        while (k)
                        {
                            if (_kbhit())
                            {
                                switch (_getch())
                                {
                                case 'y':
                                    PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                                    load = 0;
                                    return PlayerVsPlayer(a, load, data);
                                    break;
                                case 27:
                                    PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                                    system("cls");
                                    menu();
                                    break;
                                }
                            }
                        }
                        break;
                    case 1:
                        PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                        a.score2++;
                        while (k)
                        {
                            if (_kbhit())
                            {
                                switch (_getch())
                                {
                                case 'y':
                                    PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                                    load = 0;
                                    return PlayerVsPlayer(a, load, data);
                                    break;
                                case 27:
                                    PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                                    system("cls");
                                    menu();
                                    break;
                                }
                            }
                        }
                        break;
                    case 0:
                        PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                        while (k)
                        {
                            if (_kbhit())
                            {
                                switch (_getch())
                                {
                                case 'y':
                                    PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                                    load = 0;
                                    return PlayerVsPlayer(a, load, data);
                                    break;
                                case 27:
                                    PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                                    system("cls");
                                    menu();
                                    break;
                                }
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
}

_Game::_Game(int pSize, int pLeft, int  pTop)
{
    _b = new _Board(pSize, pLeft, pTop);
    _loop = _turn = true;
    _command = -1;
    _x = pLeft;
    _y = pTop;
}
int _Game::getCommand() { return _command; }
bool _Game::isContinue() { return _loop; }
char _Game::waitKeyBoard()
{
    _command = toupper(_getch());
    return _command;
}
char _Game::askContinue()
{
    gotoXY(0, _b->getYAt(_b->getSize() - 1, _b->getSize() - 1) + 4);
    return waitKeyBoard();
}
void _Game::startGame()
{
    system("cls");
    _b->resetData();
    drawBoard();
    _x = _b->getXAt(0, 0);
    _y = _b->getYAt(0, 0);
    if (_turn == 1)
    {
        Textcolor(243);
        gotoXY(SIZE * 4 + 32, 26);
        cout << " Den luot PLAYER 1 ";
    }
    else
    {
        Textcolor(243);
        gotoXY(SIZE * 4 + 32, 26);
        cout << " Den luot PLAYER 2 ";
    }
    Textcolor(240);
    gotoXY(SIZE * 4 + 30 + 12, 5);
    cout << _b->CountX;
    Textcolor(240);
    gotoXY(SIZE * 4 + 30 + 12, 18);
    cout << _b->CountY;
}
void _Game::exitGame()
{
    _loop = false;
}
void _Game::moveRight()
{
    if (_x < _b->getXAt(_b->getSize() - 1, _b->getSize() - 1))
    {
        _x += 4;
        gotoXY(_x, _y);
    }
}

void _Game::moveLeft() {
    if (_x > _b->getXAt(0, 0))
    {
        _x -= 4;
        gotoXY(_x, _y);
    }
}
void _Game::moveDown() {
    if (_y < _b->getYAt(_b->getSize() - 1, _b->getSize() - 1))
    {
        _y += 2;
        gotoXY(_x, _y);
    }
}
void _Game::moveUp() {
    if (_y > _b->getYAt(0, 0))
    {
        _y -= 2;
        gotoXY(_x, _y);
    }
}
bool _Game::processCheckBoard()
{
    switch (_b->checkBoard(_x, _y, _turn))
    {
    case -1:
        Textcolor(240);
        cout << "X";
        gotoXY((SIZE * 4) + 30 + 12, 5);
        cout << _b->CountX;
        Textcolor(241);
        gotoXY(SIZE * 4 + 32, 26);
        cout << " Den luot PLAYER 2 ";

        gotoXY(_x, _y);
        break;
    case 1:
        Textcolor(240);
        cout << "O";
        Textcolor(240);
        gotoXY(SIZE * 4 + 32, 26);
        Textcolor(244);
        cout << " Den luot PLAYER 1 ";
        Textcolor(240);
        gotoXY(SIZE * 4 + 30 + 12, 18);
        cout << _b->CountY;

        break;
    case 0:
        return false;
        break;
    }
    return true;
}
int _Game::DemNuocCoDaDi()
{
    return _b->CountX + _b->CountY;
}
int _Game::processFinish(int x, int y)
{
    gotoXY(0, _b->getYAt(_b->getSize() - 1, _b->getSize() - 1) + 2);
    int pWhoWin = _b->testBoard(x, y);
    switch (pWhoWin)
    {
    case -1:
        Draw(1, x, y);
        LichSuGame(1);
        break;
    case 1:
        Draw(2, x, y);
        LichSuGame(2);
        break;
    case 0:
        Draw(3, x, y);
        LichSuGame(0);
        break;
    case 2:
        _turn = !_turn;
    }
    gotoXY(_x, _y);// Trả về vị trí hiện hành của con trỏ màn hình bàn cờ
    return pWhoWin;
}
int _Game::getXatEnter()
{
    return _x;
}
int _Game::getYatEnter()
{
    return _y;
}
void _Game::TimKiemNuocDi()
{
    _x = _b->Tim_Kiem_NuocDi_1().getX();
    _y = _b->Tim_Kiem_NuocDi_1().getY();
}
_Game::~_Game()
{
    delete _b;
}

void _Game::LichSuGame(int n)
{
    string data;
    fstream f2;
    gotoXY(35, SIZE * 2 + 1);

    if (n == 1) data = "P1  WIN ";
    if (n == 2) data = "P2 WIN ";
    if (n == 0) data = "DRAW ";
    f2.open("History.txt", ios::app);
    time_t now = time(0); // Lấy thời gian hiện tại
    char buffer[80];
    errno_t error = ctime_s(buffer, sizeof(buffer), &now);
    data = data + string(buffer);
    f2 << data << " " << endl;
    f2.close();

    gotoXY(35, SIZE * 2 + 2);
    cout << "ESC : BACK";
    int t = 1;
    while (t)
    {
        if (_kbhit())
        {
            switch (_getch())
            {
            case 27:
                t = 0;
                system("cls");
                menu();
                break;
            }
        }
    }
}
void _Game::SaveGame(int n)
{
    char data[30];
    ofstream f1;
    ofstream f2;
    gotoXY(35, SIZE * 2 + 1);
    cout << "ENTER FILE NAME: ";
    Textcolor(Black);
    cin.getline(data, 30);
    f1.open(data, ios::out);
    f2.open("Name.txt", ios::app);
    f2 << data << " " << endl;
    //thong tin
    f1 << scorep1 << " " << scorep2 << " " << n << endl;
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            f1 << _b->get_Check(i, j) << " ";
        }
        f1 << endl;
    }
    f1.close();
    f2.close();
    gotoXY(35, SIZE * 2 + 2);
    cout << "ESC : BACK";
    int t = 1;
    while (t)
    {
        if (_kbhit())
        {
            switch (_getch())
            {
            case 27:
                PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
                t = 0;
                system("cls");
                menu();
                break;
            }
        }
    }
}
void _Game::LoadGame(char data[30])
{

    //NHAP FILE
    ifstream f;
    f.open(data, ios::in);
    if (!f) {
        gotoXY(35, 46);
        cout << "\n FILE KHONG TON TAI!" << endl;
    }
    else
    {
        f >> scorep1 >> scorep2 >> chedo;
        system("cls");
        //thong tin
        //ban co
        int k;
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                f >> k;
                _b->loadData(i, j, k);
            }
        }
        _x = _b->getXAt(0, 0);
        _y = _b->getYAt(0, 0);
        drawBoard();
        f.close();
    }
    Textcolor(243);
    gotoXY(SIZE * 4 + 30 + 12, 6);
    cout << _b->CountX;
    Textcolor(244);
    gotoXY(SIZE * 4 + 30 + 12, 16);
    cout << _b->CountY;
    if (_turn == 1)
    {
        Textcolor(243);
        gotoXY(SIZE * 4 + 32, 26);
        cout << " Den luot PLAYER 1 ";
    }
    else
    {
        Textcolor(244);
        gotoXY(SIZE * 4 + 32, 26);
        cout << " Den luot PLAYER 2 ";
    }
}