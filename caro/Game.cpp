#include "Game.h"
#include "Menu.h"
#include "Board.h"
#include <string.h>
template <class T>
void setCountXY(T* _b) {
    _b->CountX = 0;
    _b->CountY = 0;
}
int getX(int i, int j)
{
    return _pArr[i][j]._x;
}
int getY(int i, int j)
{
    return _pArr[i][j]._y;
}
int getCheck(int i, int j)
{
    return _pArr[i][j]._check;
}
void setX(int pX, int i, int j)
{
    _pArr[i][j]._x = pX;
}
void setY(int pY, int i, int j)
{
    _pArr[i][j]._y = pY;
}
bool setCheck(int pCheck, int i, int j)
{
    if (pCheck == -1 || pCheck == 1 || pCheck == 0)
    {
        _pArr[i][j]._check = pCheck;
        return true;
    }
    return false;
}
void startPoint(int i, int j)
{
    _pArr[i][j]._x = 0;
    _pArr[i][j]._y = 0;
    _pArr[i][j]._check = 0;
}
void setPoint(int x, int y, int i, int j)
{
    _pArr[i][j]._x = x;
    _pArr[i][j]._y = y;
    _pArr[i][j]._check = 0;
}

vector<_Point> win;
template <class T>
int getSize(T *_b) { return _b->_size; }
template <class T>
int getLeft(T* _b) { return _b->_left; }
template <class T>
int getTop(T* _b) { return _b->_top; }
int getXAt(int i, int j)
{
    return getX(i, j);
}
int getYAt(int i, int j)
{
    return getY(i,j);
}
void deleteBoard()
{
    for (int i = 0; i < _b->_size; i++)
    {
        delete[] _pArr[i];
    }
    delete[] _pArr;
}
void setBoard(int pSize, int pX, int pY)
{
    _b->_size = pSize;
    _b->_left = pX;
    _b->_top = pY;  
    _pArr = new _Point * [pSize];
    for (int i = 0; i < pSize; i++)
    {
        _pArr[i] = new _Point[pSize];
    }
}
// sửa tới đây 11:00 06/05/2023
// chưa sửa cần mới xóa các đối tượng thôi 
void loadData(int i, int j, int k)
{
    if (_b->_size == 0)
        return;
    //Gán tọa độ x trong bàn cờ thành giá trị của [i] trong mảng 2 chiều.
    setX(4 * j + _b->_left + 2, i, j);
    //Gán tọa độ y trong bàn cờ thành giá trị của [j] trong mảng 2 chiều.
    setY(2 * i + _b->_top + 1, i,j);
    //Gán trạng thái của ô trong bàn cờ (X, O, ô trống) vào các phần tử trong mảng.
    setCheck(k,i,j);
    //Nếu trạng thái ô là quân X, ghi quân X ra màn hình, đếm số quân X tăng lên 1.
    if (k == -1)
    {
        Textcolor(Blue); // X
        gotoXY(4 * j + _b->_left + 2, 2 * i + _b->_top + 1);
        cout << "X";
        _b->CountX++;
    }
    //Nếu trạng thái ô là quân O, ghi quân O ra màn hình, đếm số quân O tăng lên 1.
    if (k == 1)
    {
        Textcolor(Red); // O
        gotoXY(4 * j + _b->_left + 2, 2 * i + _b->_top + 1);
        cout << "O";
        _b->CountY++;
    }
}

void resetData()
{
    if (_b->_size == 0)
        return;
    for (int i = 0; i < _b->_size; i++)
    {
        for (int j = 0; j < _b->_size; j++)
        {
            setX(4 * j + _b->_left + 2, i,j);
            setY(2 * i + _b->_top + 1,i,j);
            //Gán tất cả các ô trong bàn cờ ở trạng thái ô trống -> Reset lại bàn cờ.
            setCheck(0,i,j);
        }
    }
}

int checkBoard(int pX, int pY, bool pTurn) // chế độ chơi 0: Player - 1: Bot
{
    for (int i = 0; i < _b->_size; i++)
    {
        for (int j = 0; j < _b->_size; j++)
        {
            if (getX(i,j) == pX && getY(i,j) == pY && getCheck(i,j) == 0)
            {
                //Nếu là chế độ PVP -> Người chơi X đánh trước.
                if (pTurn)
                {
                    setCheck(-1,i,j);
                    _b->CountX++;
                }
                //Nếu la chế độ PVE (Bot) -> Máy (O) đánh trước.
                else
                {
                    setCheck(1,i,j);
                    _b->CountY++;
                }
                //Trả về kết quả xem ai đánh trước (X hay O)
                return getCheck(i,j);
            }
        }
    }
    return 0;
}

//Hàm xét chiến thắng của X (hoặc O) theo hàng 
int checkWinRow(int x, int y, int value)
{
    int dong, cot;
    int loop = 1;
    int test = -1;
    int check2dau = 0;
    int countRowLeft = 0, countRowRight = 0;
    dong = (x - _b->_left - 2) / 4;
    cot = (y - _b->_top - 1) / 2;
    int dongtrai, dongphai; // Xét đếm X (hoặc O) về phía trái và về phía phải.
    dongtrai = dongphai = dong;
    //Xét về phía trái ô đang xét.
    //Nếu ngay tại vị trí đang xét là X (hoặc O) thì
    while (getCheck(cot, dongtrai) == value)
    {
        //Giá trị của countRowLeft++;
        win.push_back(_pArr[cot][dongtrai]);
        countRowLeft++;
        //Nếu (dongtrai==0), đây là ô sát phía bên trái của bàn cờ, không thể di chuyển sang trái được nữa -> Thoát khỏi vòng lặp.
        if (dongtrai == 0)
            break;
        //Lùi sáng trái bàn cờ 1 đơn vị
        dongtrai--;
    }
    //Xét về phía phải ô đang xét.
    //Nếu ngay vị trí đang xét là X (hoặc O) thì
    while (getCheck(cot, dongphai) == value)
    {
        //Giá trị của countRowRight++;
        win.push_back(_pArr[cot][dongphai]);
        countRowRight++;
        //Nếu (dongphai == _size - 1), đây là ô sát phía bên phải của bàn cờ, không thể di chuyển sang phải được nữa -> Thoát khỏi vòng lặp.
        if (dongphai == _b->_size - 1)
            break;
        dongphai++;
    }
    //Đây là trường hợp xét chặn 2 đầu.
    //Nếu ở 2 đầu những ô theo hàng mà ta đang xét là O (hoặc X) thì luật chặn 2 đầu được áp dụng.
    //Nếu ở 2 đầu những ô theo hàng mà ta đang xét chỉ có 1 quân O (hoặc X), đầu còn lại là ô trống thì luật 2 đầu không được áp dụng.
    if (getCheck(cot, dongtrai) == -value && getCheck(cot, dongphai) == -value)
        check2dau = 1;
    //Nếu có 5 quân X (hoặc O) liên tiếp gần nhau và luật chặn 2 đầu không được áp dụng thì trả về test=1 -> Chiến thắng
    if ((countRowLeft + countRowRight - 1) == 5 && (check2dau == 0))
    {
        test = 1;
    }
    //Nếu không thì trả về test=0 -> Thua cuộc.
    else
        test = 0;
    //Nếu chiến thắng
    if (test == 1)
    {
        //Nổi nhạc chiến thắng/
        playSound(4);
        //Dùng vòng lặp để đổi màu 5 quân X (hoặc O) chiến thắng.
        while (loop < 30)
        {
            Textcolor(rand() % 15 + 1);
            for (int i = 0; i < win.size(); i++)
            {
                gotoXY(win[i]._x, win[i]._y);
                if (win[i]._check == -1)
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
int checkWinCol(int x, int y, int value) // Xet chien thang theo hang doc
{
    int dong, cot;
    int test = -1, loop = 1;
    int check2dau = 0;
    int countColTop = 0, countColBot = 0;
    dong = (x - _b->_left - 2) / 4;
    cot = (y - _b->_top - 1) / 2;
    int cottren, cotduoi; // Xet bien dem ve phia tren, va ve phia duoi
    cottren = cotduoi = cot;
    // Xet chien thang
    // Xet hang doc
    while (getCheck(cottren,dong) == value)
    {
        countColTop++;
        win.push_back(_pArr[cottren][dong]);
        if (cottren == 0)
            break;
        cottren--;
    }
    while (getCheck(cotduoi, dong) == value)
    {
        countColBot++;
        win.push_back(_pArr[cotduoi][dong]);
        if (cotduoi == _b->_size - 1)
            break;
        cotduoi++;
    }
    if (getCheck(cottren, dong) == -value && getCheck(cotduoi, dong) == -value)
        check2dau = 1;
    if ((countColTop + countColBot - 1) == 5 && (check2dau == 0))
    {
        test = 1;
    }
    else
        test = 0;
    if (test == 1)
    {
        while (loop < 30)
        {
            Textcolor(rand() % 15 + 1);
            for (int i = 0; i < win.size(); i++)
            {
                gotoXY(win[i]._x, win[i]._y);
                if (win[i]._check == -1)
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
int checksecondDiagonal(int x, int y, int value)
{
    int dong, cot;
    int test = -1, loop = 1;
    int check2dau = 0;
    int countDiaTop = 0, countDiaBot = 0;
    dong = (x - _b->_left - 2) / 4;
    cot = (y - _b->_top - 1) / 2;
    int cottren, cotduoi; // Xet dem X ve phia tren, va ve phia duoi
    int dongphai, dongtrai;
    cottren = cotduoi = cot;
    dongphai = dongtrai = dong;
    // Xet X chien thang
    // Xet hang ngang
    while (getCheck(cottren, dongtrai) == value)
    {
        win.push_back(_pArr[cottren][dongtrai]);
        countDiaTop++;
        if (cottren == 0 || dongtrai == 0)
            break;
        cottren--;
        dongtrai--;
    }

    while (getCheck(cotduoi, dongphai) == value)
    {
        win.push_back(_pArr[cotduoi][dongphai]);
        countDiaBot++;
        if (cotduoi == _b->_size - 1 || dongphai == _b->_size - 1)
            break;
        cotduoi++;
        dongphai++;
    }
    if (getCheck(cottren, dongtrai) == -value && getCheck(cotduoi, dongphai) == -value)
        check2dau = 1;
    if ((countDiaTop + countDiaBot - 1) == 5 && (check2dau == 0))
    {
        test = 1;
    }
    else
        test = 0;
    if (test == 1)
    {
        while (loop < 30)
        {
            Textcolor(rand() % 15 + 1);
            for (int i = 0; i < win.size(); i++)
            {
                gotoXY(win[i]._x, win[i]._y);
                if (win[i]._check == -1)
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
int checkfirstDiagonal(int x, int y, int value)
{
    int dong, cot;
    int test = -1, loop = 1;
    int check2dau = 0;
    int countDiaTop = 0, countDiaBot = 0;
    dong = (x - _b->_left - 2) / 4;
    cot = (y - _b->_top - 1) / 2;
    int cottren, cotduoi; // Xet dem X ve phia tren, va ve phia duoi
    int dongphai, dongtrai;
    cottren = cotduoi = cot;
    dongphai = dongtrai = dong;
    // Xet X chien thang
    // Xet hang ngang
    while (getCheck(cottren, dongphai) == value)
    {
        countDiaTop++;
        win.push_back(_pArr[cottren][dongphai]);
        if (cottren == 0 || dongphai == _b->_size - 1)
            break;
        cottren--;
        dongphai++;
    }
    while (getCheck(cotduoi, dongtrai) == value)
    {
        win.push_back(_pArr[cotduoi][dongtrai]);
        countDiaBot++;
        if (cotduoi == _b->_size - 1 || dongtrai == 0)
            break;
        cotduoi++;
        dongtrai--;
    }
    if (getCheck(cottren, dongphai) == -value && getCheck(cotduoi, dongtrai) == -value)
        check2dau = 1;
    if ((countDiaTop + countDiaBot - 1) == 5 && (check2dau == 0))
    {
        test = 1;
    }
    else
        test = 0;
    if (test == 1)
    {
        while (loop < 30)
        {
            Textcolor(rand() % 15 + 1);
            for (int i = 0; i < win.size(); i++)
            {
                gotoXY(win[i]._x, win[i]._y);
                if (win[i]._check == -1)
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
int testBoard(int x, int y)
{
    //Đây là những trường hợp mà quân X chiến thắng.
    if (checkWinRow(x, y, -1) == 1)
        return -1;
    if (checkWinCol(x, y, -1) == 1)
        return -1;
    if (checkfirstDiagonal(x, y, -1) == 1)
        return -1;
    if (checksecondDiagonal(x, y, -1) == 1)
        return -1;
    //Đây là những trường hợp mà quân O chiến thắng.
    if (checkWinRow(x, y, 1) == 1)
        return 1;
    if (checkWinCol(x, y, 1) == 1)
        return 1;
    if (checkfirstDiagonal(x, y, 1) == 1)
        return 1;
    if (checksecondDiagonal(x, y, 1) == 1)
        return 1;
    if (_b->CountX + _b->CountY == SIZE * SIZE)
        return 0;
    return 2;
}

// Xu li AI
long SoDiemTanCong_DuyetNgang(long Dong, long Cot, const long Defend_Score[], const long Attack_Score[])
{
    long iScoreTempNgang = 0;
    long iScoreAttack = 0;
    int iSoQuanTa = 0;
    int iSoQuanDich = 0;
    int iSoQuanTa2 = 0;
    int iSoQuanDich2 = 0;
    //Phía trên ô đang xét. (Ta gọi là trường hợp 1).
    for (int iDem = 1; iDem < 6 && Cot + iDem < _b->_size; iDem++)
    {
        //Nếu phía trên ô đang xét là quân ta, iSoQuanTa++; (số quân ta).
        if (getCheck(Dong, Cot + iDem) == 1)
            iSoQuanTa++;
        //Nếu phía trên ô đang xét là quân địch, iSoQuanDich++; (số quân địch) và thoát khỏi vòng lặp (Trường hợp 1).
        if (getCheck(Dong, Cot + iDem) == -1)
        {
            iSoQuanDich++;
            break;
        }
        //Nếu phía trên ô đang xét là ô trống, ta sẽ xét phía trên ô trống này.
        if (getCheck(Dong, Cot + iDem) == 0)
        {
            for (int iDem2 = 2; iDem2 < 7 && Cot + iDem2 < _b->_size; iDem2++)
            {
                //Nếu phía trên ô trống là quân ta, iSoQuanTa2++; (Số quân ta 2).
                if (getCheck(Dong, Cot + iDem2) == 1)
                    iSoQuanTa2++;
                //Nếu phía trên ô trống là quân địch, iSoQuanDich2++; (Số quân địch 2) và thoát khỏi vòng lặp.
                if (getCheck(Dong, Cot + iDem2) == -1)
                {
                    iSoQuanDich2++;
                    break;
                }
                //Nếu phía trên ô trống là ô trống, thoát khỏi vòng lặp.
                if (getCheck(Dong, Cot + iDem2) == 0)
                    break;
            }
            //Thoát khỏi vòng lặp.
            break;
        }
    }
    //Phía dưới ô đang xét. (Ta gọi là trường hợp 2).
    for (int iDem = 1; iDem < 6 && Cot - iDem >= 0; iDem++)
    {
        //Nếu phía dưới ô đang xét là quân ta, iSoQuanTa++; (số quân ta).
        if (getCheck(Dong, Cot - iDem) == 1)
            iSoQuanTa++;
        //Nếu phía dưới ô đang xét là quân địch, iSoQuanDich++; (số quân địch) và thoát khỏi vòng lặp (Trường hợp 2).
        if (getCheck(Dong, Cot - iDem) == -1)
        {
            iSoQuanDich++;
            break;
        }
        //Nếu phía dưới ô đang xét là ô trống, ta sẽ xét phía trên ô trống này.
        if (getCheck(Dong, Cot - iDem) == 0)
        {
            for (int iDem2 = 2; iDem2 < 7 && Cot - iDem2 >= 0; iDem2++)
            {
                //Nếu phía dưới ô trống là quân ta, iSoQuanTa2++; (Số quân ta 2).
                if (getCheck(Dong, Cot - iDem2) == 1)
                    iSoQuanTa2++;
                //Nếu phía dưới ô trống là quân địch, iSoQuanDich2++; (Số quân địch 2).
                if (getCheck(Dong, Cot - iDem2) == -1)
                {
                    iSoQuanDich2++;
                    break;
                }
                //Nếu phía dưới ô trống là ô trống, thoát khỏi vòng lặp.
                if (getCheck(Dong, Cot - iDem2) == 0)
                    break;
            }
            //Thoát khỏi vòng lặp.
            break;
        }
    }
    //const long Defend_Score1[7] = { 0, 24, 3072, 196608, 12582912, 805306368 };
    //const long Attack_Score1[7] = { 0, 192, 24576, 1572864, 100663296, 6442450944 };
    //Giả sử X là quân ta, O là quân địch, E là ô trống, H là ô đang xét.

    //Cột: Bị địch chặn 2 đầu tại ô đang xét  -> Điểm tấn công của ô = 0.
    //Mô tả: ... O ... H ... O ... 
    if (iSoQuanDich == 2)
        return 0;
    //Cột: 5 ô phía trên và 5 ô phía dưới ô đang xét không có bất kì quân địch nào -> Điểm tấn công của ô phụ thuộc vào số quân ta trong khoảng đó.
    //Số điểm tấn công của ô cộng thêm Attack_Score[số quân ta]*2;
    if (iSoQuanDich == 0)
        iScoreTempNgang += Attack_Score[iSoQuanTa] * 2;
    //Cột: Bị duy nhất 1 địch chặn tại đầu trên hoặc đầu dưới tại ô đang xét.
    //Mô tả: ... O ... H ...... hoặc ...... H ... 0 ...
    //Số điểm tấn công của ô cộng thêm Attack_Score[số quân ta];
    else
        iScoreTempNgang += Attack_Score[iSoQuanTa];
    //Không tồn tại quân địch sao cho có ô trống ngay phía dưới quân địch (trường hợp 1) hoặc ngay phía trên quân địch (trường hợp 2) -> Tránh trường hợp đánh vào khoảng trống giữa ta và địch để tấn công, sau đó lại bị địch chặn 2 đầu.
    //Đây là trường hợp không có bất kì quân địch nào hoặc nếu có thì quân địch phải sát ngay với quân ta.
    //Số điểm tấn công của ô cộng thêm Attack_Score[số quân ta]*2;
    if (iSoQuanDich2 == 0)
        iScoreTempNgang += Attack_Score[iSoQuanTa2] * 2;
    //Tồn tại quân địch sao cho có ô trống ngay phía dưới quân địch (trường hợp 1) hoặc ngay phía trên quân địch (trường hợp 2) -> Trường hợp này dễ rơi vào tình huống đánh vào khoảng trống giữa ta và địch để tấn công, sau đó lại bị địch chặn 2 đầu.
    //Đây là trường hợp có tồn tại ô trống giữa ô đang xét và quân địch ở phía trên hoặc phía dưới ô đang xét.
    //Số điểm tấn công của ô cộng thêm Attack_Score[số quân ta];
    else
        iScoreTempNgang += Attack_Score[iSoQuanTa2];
    //Xét trên khoảng 10 ô xung quanh ô đang xét. Nếu số quân ta liền nhau nhiều hơn số quân ta trong khoảng đang xét nhưng không liền nhau thì:
    //Số điểm tấn công của ô -1 (Ưu tiên trường hợp quân ta liền nhau).
    if (iSoQuanTa >= iSoQuanTa2)
        iScoreTempNgang -= 1;
    //Nếu những ô liền nhau ít hơn thì:
    //Số điểm tấn công của ô -2 (Không ưu tiên hơn trường hợp những ô liền nhau).
    else
        iScoreTempNgang -= 2;
    //Nếu số quân liền nhau của ta là 4 -> Số điểm của ô nhân đôi (Số điểm tấn công của ô tăng cực nhiều) -> Chắc chắn thắng.
    if (iSoQuanTa == 4)
        iScoreTempNgang *= 2;
    //Đây là trường hợp 2 ô trên dưới ô đang xét không có ô nào là quân ta.
    //Số điểm tấn công của ô phụ thuộc vào số quân địch ở 2 ô này, số điểm tấn công của ô công thêm Defend_Score[số quân địch]*2; (Ưu tiên vì quân địch nhiều).
    if (iSoQuanTa == 0)
        iScoreTempNgang += Defend_Score[iSoQuanDich] * 2;
    //Đây là trường hợp trong khoảng đang xét có số quân ta bất kì.
    //Số điểm tân công của ô phụ thuộc vào số quân địch ở 2 ô này, số điểm tấn công của ô công thêm Defend_Score[số quân địch]; (Không ưu tiên vì quân ta đang nhiều, thiên về tấn công);
    else
        iScoreTempNgang += Defend_Score[iSoQuanDich];
    //Không tồn tại quân ta sao cho có ô trống ngay phía dưới quân ta (trường hợp 1) hoặc ngay phía trên quân ta (trường hợp 2) -> Các ô quân ta đang liền nhau, ưu tiên tấn công -> Số điểm tấn công của ô tăng nhiều.
    //Số điểm tấn công của ô phụ thuộc vào số quân địch chặn đầu, số điểm tấn công của ô công thêm Defend_Score[số quân địch]*2;
    if (iSoQuanTa2 == 0)
        iScoreTempNgang += Defend_Score[iSoQuanDich2] * 2;
    //Tồn tại quân ta sao cho có ô trống ngay phía dưới quân ta (trường hợp 1) hoặc ngay phía trên quân ta (trường hợp 2) -> Các ô quân ta đang không liền nhau, không ưu tiên -> Số điểm tấn công của ô tăng ít.
    //Số điểm tấn công của ô phụ thuộc vào số quân địch chặn đầu, số điểm tấn công của ô công thêm Defend_Score[số quân địch];
    else
        iScoreTempNgang += Defend_Score[iSoQuanDich2];
    return iScoreTempNgang;
}
long SoDiemTanCong_DuyetDoc(long Dong, long Cot, const long Defend_Score[], const long Attack_Score[])
{
    long iScoreTempDoc = 0;
    long iScoreAttack = 0;
    int iSoQuanTa = 0;
    int iSoQuanDich = 0;
    int iSoQuanTa2 = 0;
    int iSoQuanDich2 = 0;
    for (int iDem = 1; iDem < 6 && Dong + iDem < _b->_size; iDem++)
    {
        if (getCheck(Dong + iDem, Cot) == 1)
            iSoQuanTa++;
        if (getCheck(Dong + iDem, Cot) == -1)
        {
            iSoQuanDich++;
            break;
        }
        if (getCheck(Dong + iDem, Cot) == 0)
        {
            for (int iDem2 = 2; iDem2 < 7 && Dong + iDem2 < _b->_size; iDem2++)
            {
                if (getCheck(Dong + iDem2, Cot) == 1)
                    iSoQuanTa2++;
                if (getCheck(Dong + iDem2, Cot) == -1)
                {
                    iSoQuanDich2++;
                    break;
                }
                if (getCheck(Dong + iDem2, Cot) == 0)
                    break;
            }
            break;
        }
    }
    for (int iDem = 1; iDem < 6 && Dong - iDem >= 0; iDem++)
    {
        if (getCheck(Dong - iDem, Cot) == 1)
            iSoQuanTa++;
        if (getCheck(Dong - iDem, Cot) == -1)
        {
            iSoQuanDich++;
            break;
        }
        if (getCheck(Dong - iDem, Cot) == 0)
        {
            for (int iDem2 = 2; iDem2 < 7 && Dong - iDem2 >= 0; iDem2++)
            {
                if (getCheck(Dong - iDem2, Cot) == 1)
                    iSoQuanTa2++;
                if (getCheck(Dong - iDem2, Cot) == -1)
                {
                    iSoQuanDich2++;
                    break;
                }
                if (getCheck(Dong - iDem2, Cot) == 0)
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

long SoDiemTanCong_DuyetCheo1(long Dong, long Cot, const long Defend_Score[], const long Attack_Score[])
{
    long iScoreTempCheoNguoc = 0;
    long iScoreAttack = 0;
    int iSoQuanTa = 0;
    int iSoQuanDich = 0;
    int iSoQuanTa2 = 0;
    int iSoQuanDich2 = 0;
    for (int iDem = 1; iDem < 6 && Cot + iDem < _b->_size && Dong + iDem < _b->_size; iDem++)
    {
        if (getCheck(Dong + iDem, Cot + iDem) == 1)
            iSoQuanTa++;
        if (getCheck(Dong + iDem, Cot + iDem) == -1)
        {
            iSoQuanDich++;
            break;
        }
        if (getCheck(Dong + iDem, Cot + iDem) == 0)
        {
            for (int iDem2 = 2; iDem2 < 7 && Cot + iDem2 < _b->_size && Dong + iDem2 < _b->_size; iDem2++)
            {
                if (getCheck(Dong + iDem2, Cot + iDem2) == 1)
                    iSoQuanTa2++;
                if (getCheck(Dong + iDem2, Cot + iDem2) == -1)
                {
                    iSoQuanDich2++;
                    break;
                }
                if (getCheck(Dong + iDem2, Cot + iDem2) == 0)
                {
                    break;
                }
            }
            break;
        }
    }
    for (int iDem = 1; iDem < 6 && Cot - iDem >= 0 && Dong - iDem >= 0; iDem++)
    {
        if (getCheck(Dong - iDem, Cot - iDem) == 1)
            iSoQuanTa++;
        if (getCheck(Dong - iDem, Cot - iDem) == -1)
        {
            iSoQuanDich++;
            break;
        }
        if (getCheck(Dong - iDem, Cot - iDem) == 0)
        {
            for (int iDem2 = 2; iDem2 < 7 && Cot - iDem2 >= 0 && Dong - iDem2 >= 0; iDem2++)
            {
                if (getCheck(Dong - iDem2, Cot - iDem2) == 1)
                    iSoQuanTa2++;
                if (getCheck(Dong - iDem2, Cot - iDem2) == -1)
                {
                    iSoQuanDich2++;
                    break;
                }
                if (getCheck(Dong - iDem2, Cot - iDem2) == 0)
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
long SoDiemTanCong_DuyetCheo2(long Dong, long Cot, const long Defend_Score[], const long Attack_Score[])
{
    long iScoreTempCheoXuoi = 0;
    long iScoreAttack = 0;
    int iSoQuanTa = 0;
    int iSoQuanDich = 0;
    int iSoQuanTa2 = 0;
    int iSoQuanDich2 = 0;
    for (int iDem = 1; iDem < 6 && Cot - iDem >= 0 && Dong + iDem < _b->_size; iDem++)
    {
        if (getCheck(Dong + iDem, Cot - iDem) == 1)
            iSoQuanTa++;
        if (getCheck(Dong + iDem, Cot - iDem) == -1)
        {
            iSoQuanDich++;
            break;
        }
        if (getCheck(Dong + iDem, Cot - iDem) == 0)
        {
            for (int iDem2 = 2; iDem2 < 7 && Cot - iDem2 >= 0 && Dong + iDem2 < _b->_size; iDem2++)
            {
                if (getCheck(Dong + iDem2, Cot - iDem2) == 1)
                    iSoQuanTa2++;
                if (getCheck(Dong + iDem2, Cot - iDem2) == -1)
                {
                    iSoQuanDich2++;
                    break;
                }
                if (getCheck(Dong + iDem2, Cot - iDem2) == 0)
                    break;
            }
            break;
        }
    }
    for (int iDem = 1; iDem < 6 && Cot + iDem < _b->_size && Dong - iDem >= 0; iDem++)
    {
        if (getCheck(Dong - iDem, Cot + iDem) == 1)
            iSoQuanTa++;
        if (getCheck(Dong - iDem, Cot + iDem) == -1)
        {
            iSoQuanDich++;
            break;
        }
        if (getCheck(Dong - iDem, Cot + iDem) == 0)
        {
            for (int iDem2 = 2; iDem2 < 7 && Cot + iDem2 < _b->_size && Dong - iDem2 >= 0; iDem2++)
            {
                if (getCheck(Dong - iDem2, Cot + iDem2) == 1)
                    iSoQuanTa2++;
                if (getCheck(Dong - iDem2, Cot + iDem2) == -1)
                {
                    iSoQuanDich2++;
                    break;
                }
                if (getCheck(Dong - iDem2, Cot + iDem2) == 0)
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

long SoDiemPhongThu_DuyetDoc(long Dong, long Cot, const long Defend_Score[], const long Attack_Score[])
{
    long iScoreTempDoc = 0;
    long iScoreDefend = 0;
    int iSoQuanDich = 0;
    int iSoQuanTa = 0;
    int iSoQuanDich2 = 0;
    int iSoQuanTa2 = 0;
    for (int iDem = 1; iDem < 6 && Dong + iDem < _b->_size; iDem++)
    {
        if (getCheck(Dong + iDem, Cot) == 1)
        {
            iSoQuanTa++;
            break;
        }
        if (getCheck(Dong + iDem, Cot) == -1)
            iSoQuanDich++;
        if (getCheck(Dong + iDem, Cot) == 0)
        {
            for (int iDem2 = 2; iDem2 < 7 && Dong + iDem2 < _b->_size; iDem2++)
            {
                if (getCheck(Dong + iDem2, Cot) == 1)
                {
                    iSoQuanTa2++;
                    break;
                }
                if (getCheck(Dong + iDem2, Cot) == -1)
                    iSoQuanDich2++;
                if (getCheck(Dong + iDem2, Cot) == 0)
                    break;
            }
            break;
        }
    }
    for (int iDem = 1; iDem < 6 && Dong - iDem >= 0; iDem++)
    {
        if (getCheck(Dong - iDem, Cot) == 1)
        {
            iSoQuanTa++;
            break;
        }
        if (getCheck(Dong - iDem, Cot) == -1)
            iSoQuanDich++;
        if (getCheck(Dong - iDem, Cot) == 0)
        {
            for (int iDem2 = 2; iDem2 < 7 && Dong - iDem2 >= 0; iDem2++)
            {
                if (getCheck(Dong - iDem2, Cot) == 1)
                {
                    iSoQuanTa2++;
                    break;
                }
                if (getCheck(Dong - iDem2, Cot) == -1)
                    iSoQuanDich2++;
                if (getCheck(Dong - iDem2, Cot) == 0)
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

long SoDiemPhongThu_DuyetNgang(long Dong, long Cot, const long Defend_Score[], const long Attack_Score[])
{
    long iScoreTempNgang = 0;
    long iScoreDefend = 0;
    int iSoQuanDich = 0;
    int iSoQuanTa = 0;
    int iSoQuanDich2 = 0;
    int iSoQuanTa2 = 0;
    //Phía trên ô đang xét. (Ta gọi là trường hợp 1).
    for (int iDem = 1; iDem < 6 && Cot + iDem < _b->_size; iDem++)
    {
        //Nếu phía trên ô đang xét là quân ta, iSoQuanTa++; (số quân ta) và thoát khỏi vòng lặp (Trường hợp 1).
        if (getCheck(Dong , Cot + iDem) == 1)
        {
            iSoQuanTa++;
            break;
        }
        //Nếu phía trên ô đang xét là quân địch, iSoQuanDich++; (số quân địch).
        if (getCheck(Dong, Cot + iDem) == -1)
            iSoQuanDich++;
        //Nếu phía trên ô đang xét là ô trống, ta sẽ xét phía trên ô trống này.
        if (getCheck(Dong, Cot + iDem) == 0)
        {
            for (int iDem2 = 2; iDem2 < 7 && Cot + iDem2 < _b->_size; iDem2++)
            {
                //Nếu phía trên ô trống là quân ta, iSoQuanTa2++; (Số quân ta 2) và thoát khỏi vòng lặp.
                if (getCheck(Dong, Cot + iDem2) == 1)
                {
                    iSoQuanTa2++;
                    break;
                }
                //Nếu phía trên ô trống là quân địch, iSoQuanDich2++; (Số quân địch 2).
                if (getCheck(Dong, Cot + iDem2) == -1)
                    iSoQuanDich2++;
                if (getCheck(Dong, Cot + iDem2) == 0)
                    //Nếu phía trên ô trống là ô trống, thoát khỏi vòng lặp.
                    break;
            }
            //Thoát khỏi vòng lặp.
            break;
        }
    }
    //Phía dưới ô đang xét. (Ta gọi là trường hợp 2).
    for (int iDem = 1; iDem < 6 && Cot - iDem >= 0; iDem++)
    {
        //Nếu phía dưới ô đang xét là quân ta, iSoQuanTa++; (số quân ta) và thoát khỏi vòng lặp (Trường hợp 2).
        if (getCheck(Dong, Cot - iDem) == 1)
        {
            iSoQuanTa++;
            break;
        }
        //Nếu phía dưới ô đang xét là quân địch, iSoQuanDich++; (số quân địch).
        if (getCheck(Dong, Cot - iDem) == -1)
            iSoQuanDich++;
        //Nếu phía dưới ô đang xét là ô trống, ta sẽ xét phía trên ô trống này.
        if (getCheck(Dong, Cot - iDem) == 0)
        {
            for (int iDem2 = 2; iDem2 < 7 && Cot - iDem2 >= 0; iDem2++)
            {
                //Nếu dưới trên ô trống là quân ta, iSoQuanTa2++; (Số quân ta 2) và thoát khỏi vòng lặp.
                if (getCheck(Dong, Cot - iDem2) == 1)
                {
                    iSoQuanTa2++;
                    break;
                }
                //Nếu phía dưới ô trống là quân địch, iSoQuanDich2++; (Số quân địch 2).
                if (getCheck(Dong, Cot - iDem2) == 0)
                    break;
                //Nếu phía dưới ô trống là ô trống, thoát khỏi vòng lặp.
                if (getCheck(Dong, Cot - iDem2) == -1)
                    iSoQuanDich2++;
            }
            //Thoát khỏi vòng lặp.
            break;
        }

    }
    //const long Defend_Score1[7] = { 0, 24, 3072, 196608, 12582912, 805306368 };
    //const long Attack_Score1[7] = { 0, 192, 24576, 1572864, 100663296, 6442450944 };
    //Giả sử X là quân ta, O là quân địch, E là ô trống, H là ô đang xét.

    //Cột: Đây là trường hợp 2 ô trên dưới của ô đang xét đầu là quân ta -> Thiên về tấn công -> Điểm phòng thủ của ô sẽ là 0.
    //Mô tả: ... X ... H ... X ...
    if (iSoQuanTa == 2)
        return 0;
    //Cột: 5 ô phía trên và 5 ô phía dưới ô đang xét không có bất kì ta nào (Trường hợp ưu tiên nhiều về phòng thủ) -> Điểm phòng thủ của ô phụ thuộc vào số quân địch trong khoảng đó.
    //Số điểm phòng thủ của ô cộng thêm Defend_Score[số quân địch]*2;
    if (iSoQuanTa == 0)
        iScoreTempNgang += Defend_Score[iSoQuanDich] * 2;
    //Cột: Tồn tại duy nhất 1 quân ta tại đầu trên hoặc đầu dưới tại ô đang xét.
    //Mô tả: ... X ... H ...... hoặc ...... H ... X ...
    //Số điểm phòng thủ phụ thuộc vào số quân địch trong khoảng đang xét. Số điểm phòng thủ của ô cộng thêm Defend_Score[số quân địch];
    else
        iScoreTempNgang += Defend_Score[iSoQuanDich];
    //Xét trên khoảng 10 ô xung quanh ô đang xét. Nếu số quân địch liền nhau nhiều hơn số quân địch trong khoảng đang xét nhưng không liền nhau thì:
    //Số điểm phòng của ô -1 (Ưu tiên trường hợp quân địch liền nhau).
    if (iSoQuanDich >= iSoQuanDich2)
        iScoreTempNgang -= 1;
    //Nếu những ô liền nhau ít hơn thì:
    //Số điểm phòng thủ của ô -2 (Không ưu tiên hơn trường hợp những ô quân địch liền nhau).
    else
        iScoreTempNgang -= 2;
    //Đât là trường hợp 4 quân địch liền nhau -> Ưu tiên phòng thủ lên mức cao độ nhất.
    //->Số điêm phòng thủ tăng nhanh. Số điểm phòng thủ của ô cộng nhân đôi.
    if (iSoQuanDich == 4)
        iScoreTempNgang *= 2;
    return iScoreTempNgang;
}

long SoDiemPhongThu_DuyetCheo1(long Dong, long Cot, const long Defend_Score[], const long Attack_Score[])
{
    long iScoreTempCheoNguoc = 0;
    long iScoreDefend = 0;
    int iSoQuanDich = 0;
    int iSoQuanTa = 0;
    int iSoQuanDich2 = 0;
    int iSoQuanTa2 = 0;
    for (int iDem = 1; iDem < 6 && Cot + iDem < _b->_size && Dong + iDem < _b->_size; iDem++)
    {
        if (getCheck(Dong + iDem, Cot + iDem) == 1)
        {
            iSoQuanTa++;
            break;
        }
        if (getCheck(Dong + iDem, Cot + iDem) == 0)
        {
            for (int iDem2 = 2; iDem2 < 7 && Cot + iDem2 < _b->_size && Dong + iDem2 < _b->_size; iDem2++)
            {
                if (getCheck(Dong + iDem2, Cot + iDem2) == 1)
                {
                    iSoQuanTa2++;
                    break;
                }
                if (getCheck(Dong + iDem2, Cot + iDem2) == 0)
                    break;
                if (getCheck(Dong + iDem2, Cot + iDem2) == -1)
                    iSoQuanDich2++;
            }
            break;
        }
        if (getCheck(Dong + iDem, Cot + iDem) == -1)
            iSoQuanDich++;
    }
    for (int iDem = 1; iDem < 6 && Cot - iDem >= 0 && Dong - iDem >= 0; iDem++)
    {
        if (getCheck(Dong - iDem, Cot - iDem) == 1)
        {
            iSoQuanTa++;
            break;
        }

        if (getCheck(Dong - iDem, Cot - iDem) == 0)
        {
            for (int iDem2 = 2; iDem2 < 7 && Cot - iDem2 >= 0 && Dong - iDem2 >= 0; iDem2++)
            {
                if (getCheck(Dong - iDem2, Cot - iDem2) == 1)
                {
                    iSoQuanTa2++;
                    break;
                }

                if (getCheck(Dong - iDem2, Cot - iDem2) == 0)
                    break;
                if (getCheck(Dong - iDem2, Cot - iDem2) == -1)
                    iSoQuanDich2++;
            }
            break;
        }
        if (getCheck(Dong - iDem, Cot - iDem) == -1)
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

long SoDiemPhongThu_DuyetCheo2(long Dong, long Cot, const long Defend_Score[], const long Attack_Score[])
{
    long iScoreTempCheoXuoi = 0;
    long iScoreDefend = 0;
    int iSoQuanDich = 0;
    int iSoQuanTa = 0;
    int iSoQuanDich2 = 0;
    int iSoQuanTa2 = 0;
    for (int iDem = 1; iDem < 6 && Cot - iDem >= 0 && Dong + iDem < _b->_size; iDem++)
    {
        if (getCheck(Dong + iDem, Cot - iDem) == 1)
        {
            iSoQuanTa++;
            break;
        }
        if (getCheck(Dong + iDem, Cot - iDem) == 0)
        {
            for (int iDem2 = 2; iDem2 < 7 && Cot - iDem2 >= 0 && Dong + iDem2 < _b->_size; iDem2++)
            {
                if (getCheck(Dong + iDem2, Cot - iDem2) == 1)
                {
                    iSoQuanTa2++;
                    break;
                }
                if (getCheck(Dong + iDem2, Cot - iDem2) == 0)
                    break;
                if (getCheck(Dong + iDem2, Cot - iDem2) == -1)
                    iSoQuanDich2++;
            }
            break;
        }
        if (getCheck(Dong + iDem, Cot - iDem) == -1)
            iSoQuanDich++;
    }
    for (int iDem = 1; iDem < 6 && Cot + iDem < _b->_size && Dong - iDem >= 0; iDem++)
    {
        if (getCheck(Dong - iDem, Cot + iDem) == 1)
        {
            iSoQuanTa++;
            break;
        }
        if (getCheck(Dong - iDem, Cot + iDem) == 0)
        {
            for (int iDem2 = 2; iDem < 7 && Cot + iDem2 < _b->_size && Dong - iDem2 >= 0; iDem2++)
            {
                if (getCheck(Dong - iDem2, Cot + iDem2) == 1)
                {
                    iSoQuanTa2++;
                    break;
                }
                if (getCheck(Dong - iDem2, Cot + iDem2) == 0)
                    break;
                if (getCheck(Dong - iDem2, Cot + iDem2) == -1)
                    iSoQuanDich2++;
            }
            break;
        }
        if (getCheck(Dong - iDem, Cot + iDem) == -1)
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
_Point Tim_Kiem_NuocDi_1()
{
    //Đây là điểm tại ô mà ta đang xét trên bàn cờ.
    _Point Oco;
    int dong = 0, cot = 0;
    //Ta sẽ dùng biến 'Diem' để tìm ra ô có điểm số cao nhất, ô nào có điểm số cao nhất sẽ được đánh X vào.
    long Diem = 0;
    //Dùng vòng lặp chay qua tất cả các ô trên bàn cờ.
    for (int i = 0; i < _b->_size; i++)
    {
        for (int j = 0; j < _b->_size; j++)
        {
            //Đặt điểm tấn công, điểm phòng thủ cho tất cả các ô này ban đầu bằng 0.
            long DiemTanCong = 0;
            long DiemPhongThu = 0;
            //Vì ta chỉ có thể tấn công hay phòng thủ ở những ô đang trống, lọc lấy những ô trống bằng dòng code _pArr[i][j].getCheck() == 0;
            if (getCheck(i,j) == 0)
            {
                //Tính số điểm tấn công của ô trống bằng tổng tất cả số điểm tấn công của ô theo hàng, theo cột, theo đường chéo 1 và theo đường chéo 2.
                //Số điểm tấn công của ô theo cột.
                DiemTanCong += SoDiemTanCong_DuyetDoc(i, j, Defend_Score1, Attack_Score1);
                //Số điểm tấn công của ô theo hàng.
                DiemTanCong += SoDiemTanCong_DuyetNgang(i, j, Defend_Score1, Attack_Score1);
                //Số điểm tấn công của ô theo đường chéo 1.
                DiemTanCong += SoDiemTanCong_DuyetCheo1(i, j, Defend_Score1, Attack_Score1);
                //Số điểm tấn công của ô theo đường chéo 2.
                DiemTanCong += SoDiemTanCong_DuyetCheo2(i, j, Defend_Score1, Attack_Score1);
                //Tính số điểm phòng thủ của ô trống bằng tổng tất cả số điểm phòng thủ của ô theo hàng, theo cột, theo đường chéo 1 và theo đường chéo 2.
                //Số điểm phòng thủ của ô theo cột.
                DiemPhongThu += SoDiemPhongThu_DuyetDoc(i, j, Defend_Score1, Attack_Score1);
                //Số điểm phòng thủ của ô theo hàng.
                DiemPhongThu += SoDiemPhongThu_DuyetNgang(i, j, Defend_Score1, Attack_Score1);
                //Số điểm phòng thủ của ô theo đường chéo 1.
                DiemPhongThu += SoDiemPhongThu_DuyetCheo1(i, j, Defend_Score1, Attack_Score1);
                //Số điểm phòng thủ của ô theo đường chéo 2.
                DiemPhongThu += SoDiemPhongThu_DuyetCheo2(i, j, Defend_Score1, Attack_Score1);
                //Tại ô đang xét, nếu điểm tấn công lớn hơn điểm phòng thủ của ô
                if (DiemTanCong > DiemPhongThu)
                {
                    //Nếu điểm nhỏ hơn điểm tấn công thì gán điểm có giá trị mới bằng giá trị của điểm tấn công của ô đang xét.
                    if (Diem < DiemTanCong)
                    {
                        //Gán giá trị mới cho điểm.
                        Diem = DiemTanCong;
                        //Lấy ra dòng cần đánh vào quân X.
                        dong = i;
                        //Lấy ra cột cần đánh vào quân X.
                        cot = j;
                    }
                }
                //Ngược lại, nếu tại ô đang xét, điểm phòng thủ lớn hơn điểm tấn công của ô.
                else
                {
                    //Nếu điểm nhỏ hơn điểm phòng thủ thì gán điểm có giá trị mới bằng giá trị của điểm phòng thủ của ô đang xét.
                    if (Diem < DiemPhongThu)
                    {
                        //Gán giá trị mới cho điểm.
                        Diem = DiemPhongThu;
                        //Lấy ra dòng cần đánh vào quân X.
                        dong = i;
                        //Lấy ra cột cần đánh vào quân X.
                        cot = j;
                    }
                }
            }
        }
    }
    //Đánh X vào ô có điểm cao nhất (Ô mà tại đó biến 'Diem' có giá trị cao nhất).
    Oco._x = cot * 4 + 2;
    //Đánh Y vào ô có điểm cao nhất (Ô mà tại đó biến 'Diem' có giá trị cao nhất).
    Oco._y = dong * 2 + 1;
    return Oco;
}
template <class T>
void setTurn(T* g) {
    g->_turn = !g->_turn;
}
template <class T>
void gsetCountXY(T* g) {
    g->CountX = 0;
    g->CountY = 0;
}
void clearConsoleLine(int y) {
    COORD position = { 0, y };
    DWORD count;
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', info.dwSize.X, position, &count);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}
int PlayerVsPlayer(Diem& a, int load, char data[30])
{
    int k = 1;
    showCur();
    setGame(SIZE, 0, 0);
    setCountXY(g);
    setCountXY(_b);
    if (load == -30)
    {
        setTurn();
        LoadGame(data);
    }
    else if (load == -31)
    {
        setTurn();
        LoadGame(data);
    }
    else
        startGame();
    PrintScoreBoard();
    Textcolor(244);
    gotoXY(SIZE * 4 + 32, 32);
    cout << " PLAYER VS PLAYER ";
    Textcolor(Blue);
    gotoXY(SIZE * 4 + 30 + 19, 6);
    //In điểm số 1.
    cout << a.score1;
    Textcolor(Red);
    gotoXY(SIZE * 4 + 30 + 19, 19);
    //In điểm số 2
    cout << a.score2;
    gotoXY(2, 1);
    while (isContinue())
    {
            auto input = getConsoleInput();
                    //Đọc phím A: dịch chuyển con trỏ trong bàn cờ sang trái 1 đơn vị.
             if (input == 3)
                {
                    moveLeft();
                }
                    //Đọc phím D: dịch chuyển con trỏ trong bàn cờ sang phải 1 đơn vị.
             if (input == 4)
                {
                    moveRight();
                }
                    //Đọc phím W: dịch chuyển con trỏ trong bàn cờ đi lên 1 đơn vị.
             if (input == 2)
                {
                    moveUp();
                }
                    //Đọc phím S: dịch chuyển con trỏ trong bàn cờ đi xuống 1 đơn vị.
             if (input == 5)
                {
                    moveDown();
                }
                    //Đọc phím L: thực hiện lưu game hiện hành vào tập tin.
             if (input == 7)
                {
                 playSound(2);
                    if (getTurn() == 1)
                        SaveGame(-31);
                    else
                        SaveGame(-30);

                }
                    //Đọc phím T: thực hiện load game.
             if (input == 10)
                {
                 playSound(2);
                    Load();
                }
                    //Đọc phím Enter: thực hiện đánh quân X vào vị trí hiện tại của con trỏ trên bàn cờ.
             if (input == 6)
                {
                 playSound(2);
                    int x = getXatEnter();
                    int y = getYatEnter();
                    if (processCheckBoard())
                    {
                        switch (processFinish(x, y))
                        {
                        case -1:
                        {
                            playSound(4);
                            a.score1++;
                            PvPaskForRestart(a, load, data);
                            break;
                        }
                        case 1:
                        {
                            playSound(4);
                            a.score2++;
                            PvPaskForRestart(a, load, data);
                            break;
                        }
                        case 0:
                        {
                            playSound(4);
                            PvPaskForRestart(a, load, data);
                            break;
                        }
                        }
                    }

                }
             if (input == 1)
             {
                 playSound(2);
                 gotoXY(50, 42); cout << "You should game before you exit. Would you to exit game?";
                 gotoXY(50, 43); cout << "Y: Yes           N: No";
                 do {
                     int yn = getConsoleInput();
                     if (yn == 11 || yn == 9)
                     {
                         if (yn == 9) {
                             clearConsoleLine(42);
                             clearConsoleLine(43);
                             int x = getXatEnter();
                             int y = getYatEnter();
                             gotoXY(x, y);
                             break;
                         }
                         else {
                             return 27;
                         }
                     }
                 } while (true);
             }
    }
}

void PvPaskForRestart(Diem &a,int& load, char data[30])
{
    int k = 1;
    while (k)
    {
        int input = getConsoleInput();
        if (input == 11)
        {
            playSound(2);
            load = 0;
            PlayerVsPlayer(a, load, data);
        }
        else if(input == 1)
        {
            playSound(2);
            clearConsole();
            menu();
        }
    }
}
void PvCaskForRestart(Diem& a, int& load, char data[30])
{
    int k = 1;
    while (k)
    {
        int input = getConsoleInput();
        if (input == 11)
        {
            playSound(2);
            load = 0;
            PlayerVsCom(a, load, data);
        }
        else if (input == 1)
        {
            playSound(2);
            clearConsole();
            menu();
        }
    }
}
void enterCom(Diem& a, int load, char data[30]) {
        int x = getXatEnter();
        int y = getYatEnter();
        if (processCheckBoard())
        {
            switch (processFinish(x, y))
            {
            case -1:
            {
                playSound(4);
                a.score1++;
                PvCaskForRestart(a, load, data);
                break;
            }
            case 1:
            {
                playSound(4);
                a.score2++;
                PvCaskForRestart(a, load, data);
                break;
            }
            case 0:
            {
                playSound(4);
                PvCaskForRestart(a, load, data);
                break;
            }
            }
        }
}
int PlayerVsCom(Diem& a, int load, char data[30])
{
    int k = 1;
    showCur();
    setGame(SIZE, 0, 0);
    setCountXY(_b);
    setCountXY(g); // Đếm số lượng x số lượng y.
    //Người dùng load game để tiếp tục chơi.
    if (load == -4)
    {
        LoadGame(data);
    }
    //Tạo màn hình để chơi và set lượt chơi tùy vào chế độ.
    else
    {
        startGame();
        setTurn();
    }
    //In bảng điểm ra màn hình.
    PrintScoreBoard();
    Textcolor(244);
    gotoXY(SIZE * 4 + 32, 32);
    cout << " PLAYER VS COMPUTER ";
    Textcolor(Blue);
    gotoXY(SIZE * 4 + 30 + 19, 6);
    //In điểm số 1.
    cout << a.score1;
    Textcolor(Red);
    gotoXY(SIZE * 4 + 30 + 19, 19);
    //In điểm số 2
    cout << a.score2;
    gotoXY(2, 1);
    while (isContinue())
    {
        if (!getTurn())
        {
            //Đặt vị trí đánh đầu tiên cho người cho may
            if (DemNuocCoDaDi() == 0)
            {
                gsetX((SIZE * 4 / 2) - 2);
                gsetY((SIZE * 2 / 2) - 1);
                gotoXY((SIZE * 4 / 2) - 2, (SIZE * 2 / 2) - 1);
                enterCom(a, load, data);
            }
            //Đặt vị trí đánh đầu tiên cho máy.
            else 
            {
				TimKiemNuocDi();
                int x = getXatEnter();
                int y = getYatEnter();
                gotoXY(x, y);
                enterCom(a, load, data);
            }
        }
        int input = getConsoleInput();
        if (input == 7)
                {
                    SaveGame(-4);
                }
        if (input == 1)
        {
            playSound(2);
            gotoXY(50, 42); cout << "You should game before you exit. Would you to exit game?";
            gotoXY(50, 43); cout << "Y: Yes           N: No";
            do {
                int yn = getConsoleInput();
                if (yn == 11 || yn == 9)
                {
                    if (yn == 9) {
                        clearConsoleLine(42);
                        clearConsoleLine(43);
                        int x = getXatEnter();
                        int y = getYatEnter();
                        gotoXY(x, y);
                        break;
                    }
                    else {
                        return 27;
                    }
                }
            } while (true);
        }
        //Đọc phím A: dịch chuyển con trỏ trong bàn cờ sang trái 1 đơn vị.
                
                if (input == 3)
                {
                    moveLeft();

                }
                //Đọc phím D: dịch chuyển con trỏ trong bàn cờ sang phải 1 đơn vị.
                if (input == 4)
                {
                    moveRight();

                }
                //Đọc phím W: dịch chuyển con trỏ trong bàn cờ đi lên 1 đơn vị.
                if (input == 2)
                {
                    moveUp();

                }
                //Đọc phím S: dịch chuyển con trỏ trong bàn cờ đi xuống 1 đơn vị.
                if (input == 5)
                {
                    moveDown();
                }
                //Đọc phím L: thực hiện lưu game hiện hành vào tập tin.
                
                //Đọc phím T: thực hiện load game.
                if (input == 10)
                {
                    playSound(2);
                    Load();
                }
                //Đọc phím Enter: thực hiện đánh quân X vào vị trí hiện tại của con trỏ trên bàn cờ.
                if (input == 6)
                {
                    playSound(2);
                    enterCom(a, load, data);
                }      
    }
}
void setGame(int pSize, int pLeft, int  pTop)
{
    _b = new _Board;
    g = new _Game;
    cout << 1;
    setBoard(pSize, pLeft, pTop);
    cout << 2;
    g->_loop = 1;
    cout << 2.5;
    g->_turn = 1;
    cout << 3;
    cout << 4;
    g->_x = pLeft;
    cout << 5;
    g->_y = pTop;
    cout << 6;
}

//Hàm bắt phím vừa được nhập từ bàn phím.
//Hmaf trả về kết quả liệu người chơi có muốn chơi tiếp hay thoát game? (Nếu _loop=1 -> Chơi tiếp, _loop=0 -> Thoát game).
bool isContinue() { return g->_loop; }
//Hàm để chờ người chơi nhập phím bất kì từ Keyboard.
//Hàm đặt vị trí hiện thông báo liệu người chơi liệu muốn chơi tiếp hay thoát game?
char askContinue()
{
    gotoXY(0, getYAt(getSize(_b) - 1, getSize(_b) - 1) + 4);
    return _getch();
}
//Hàm để bắt đầu 1 game mới.
void startGame()
{
    clearConsole();
    //Reset lại toàn bộ dữ liệu (Tất cả các ô trên bàn cờ đều là ô trống -> check=0).
    resetData();
    //Vẽ bàn cờ.
    drawBoard();
    g->_x = getXAt(0, 0);
    g->_y = getYAt(0, 0);
    //Nếu là lượt của người chơi O.
    if (g->_turn == 1)
    {
        Textcolor(Blue);
        gotoXY(SIZE * 4 + 32, 26);
        cout << " Den luot PLAYER 1 ";
    }
    //Nếu là lượt của người chơi X.
    else
    {
        Textcolor(Red);
        gotoXY(SIZE * 4 + 32, 26);
        cout << " Den luot PLAYER 2 ";
    }
   /* Textcolor(Blue);
    gotoXY(SIZE * 4 + 30 + 11, 4);
    cout << _b->CountX;
    Textcolor(Red);
    gotoXY(SIZE * 4 + 30 + 11, 14);
    cout << _b->CountY;*/
}
//Nếu người chơi chọn thoát game thì gán _loop=0 để thực hiện thoát game.
void exitGame()
{
    g->_loop = false;
}
//Hàm để di chuyển con trỏ trong bàn cờ sang phải 1 đơn vị.
void moveRight()
{
    if (g->_x < getXAt(getSize(_b) - 1, getSize(_b) - 1))
    {
        g->_x += 4;
        gotoXY(g->_x, g->_y);
    }
}
//Hàm để di chuyển con trỏ trong bàn cờ sang trái 1 đơn vị.
void moveLeft() {
    if (g->_x > getXAt(0, 0))
    {
        g->_x -= 4;
        gotoXY(g->_x, g->_y);
    }
}
//Hàm để di chuyển con trỏ trong bàn cờ đi xuống 1 đơn vị.
void moveDown() {
    if (g->_y < getYAt(getSize(_b) - 1, getSize(_b) - 1))
    {
        g->_y += 2;
        gotoXY(g->_x, g->_y);
    }
}
//Hàm để di chuyển con trỏ trong bàn cờ đi lên 1 đơn vị.
void moveUp() {
    if (g->_y > getYAt(0, 0))
    {
        g->_y -= 2;
        gotoXY(g->_x, g->_y);
    }
}
//Hàm để đánh quân X hoặc O vào vị trí hiện tại củ+ ba con trỏ trên bàn cờ.
bool processCheckBoard()
{
    //Check xem ô đang chứa con trỏ được chọn trong bàn cờ chứa giá trị X hay O?
    switch (checkBoard(g->_x, g->_y, g->_turn))
    {
        //Nếu là chứa giá trị X:
    case -1:
        //In chữ X màu xanh dương ra màn hình.
        Textcolor(Blue);
        cout << "X";
        gotoXY(SIZE * 4 + 32, 26);
        //Sau khi X đánh xong, hiện ra chữ đến lượt người chơi tiếp theo.
        cout << " Den luot PLAYER 2 ";
        gotoXY((SIZE * 4) + 30 + 12, 5);
        cout << _b->CountX;
        Textcolor(Red);
        gotoXY(SIZE * 4 + 30 + 12, 18);
        cout << _b->CountY;
        //gotoXY(g->_x, g->_y);
        break;
        //Nếu là chứa giá trị O:
    case 1:
        Textcolor(Red);
        //In chữ O màu đỏ ra màn hình
        cout << "O";
        Textcolor(Blue);
        gotoXY(SIZE * 4 + 32, 26);
        //Sau khi O đánh xong, hiện ra chữ đến lượt người chơi tiếp theo.
        cout << " Den luot PLAYER 1 ";
        Textcolor(Red);
        gotoXY((SIZE * 4) + 30 + 12, 5);
        cout << _b->CountX;
        Textcolor(Red);
        gotoXY(SIZE * 4 + 30 + 12, 18);
        cout << _b->CountY;

        break;
        //Nếu là ô trống, không thực hiện hành động gì tại vị trí mà con trỏ đang ở trong bàn cờ.
    case 0:
        return false;
        break;
    }
    return true;
}
//Hàm để đếm tổng số nước cờ đã đi.
int DemNuocCoDaDi()
{
    return _b->CountX + _b->CountY;
}
//Hàm để kiểm tra xem liệu người chơi X thắng, hay người chơi O thắng, hay 2 người chơi X và O hòa nhau -> Từ đó in kết quả ra màn hình.
int processFinish(int x, int y)
{
    gotoXY(0, getYAt(getSize(_b) - 1, getSize(_b) - 1) + 2);
    //Hàm kiểm tra xem người chơi X hay O thắng?
    int pWhoWin = testBoard(x, y);
    switch (pWhoWin)
    {
        //Trường hợp người chơi X thắng, hiện ra màn hình P1 chiến thắng và lưu kết quả vào lịch sử.
    case -1:
        Draw(1, 10, 10);
        Box();
        LichSuGame(1);
        break;
        //Trường hợp người chơi O thắng, hiện ra màn hình P2 chiến thắng và lưu kết quả vào lịch sử.
    case 1:
        Draw(2, 10, 10);
        Box();
        LichSuGame(2);
        break;
        //Trường hợp 2 người chơi hòa nhau, hiện ra màn hình 2 người chơi hòa nhau và lưu kết quả vào lịch sử.
    case 0:
        Draw(3, 10, 10);
        Box();
        LichSuGame(0);
        break;
        //Trường hợp chưa có 2 chiến thắng, đổi lượt để người chơi tiếp theo đánh.
    case 2:
        g->_turn = !g->_turn;
    }
    gotoXY(g->_x, g->_y);// Trả về vị trí hiện hành của con trỏ màn hình bàn cờ
    return pWhoWin;
}
//Hàm lấy giá trị x.
int getXatEnter()
{
    return g->_x;
}
//Hàm lấy giá trị y.
int getYatEnter()
{
    return g->_y;
}
//Hàm tìm kiếm nước đi cho máy dựa vào hàm Tim_Kiem_NuocDi_1() đã được xây dựng ở trên.
void TimKiemNuocDi()
{
    _Point temp = Tim_Kiem_NuocDi_1();
    g->_x = temp._x;
    g->_y = temp._y;
}
//Hàm viết kết quả trò chơi vào Lịch sử.
void LichSuGame(int n)
{
    Diem a = { 0 };
    string data;
    ofstream f1;
    ofstream f2;
    gotoXY(35, SIZE * 2 + 1);

    if (n == 1) data = "P1 WIN ";
    if (n == 2) data = "P2 WIN ";
    if (n == 0) data = "DRAW ";
    f1.open(data, ios::out);
    f2.open("Lich Su.txt", ios::app);

    char buffer[80];
    time_t now = time(NULL);
    ctime_s(buffer, sizeof(buffer), &now);

    std::string time = "";
    for (int i = 0; i < strlen(buffer); i++) {
        time += buffer[i];
    }
    data += time;
    f2 << data << " " << endl;
    //thong tin
    f1 << a.score1 << " " << a.score2 << " " << n << endl;
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            f1 << get_Check(i, j) << " ";
        }
        f1 << endl;
    }
    f1.close();
    f2.close();
}

//Hàm Save game để có thể tiếp tục chơi tiếp mỗi khi thoát game.
void SaveGame(int n) {
    Diem a = { 0 };
    fstream f2("Name.txt", ios::in);
    bool flag = false;
    char data[30];
    do {
        gotoXY(35, SIZE * 2 + 1);
        cout << "ENTER FILE NAME: ";
        cin.getline(data, 30);
        char line[30];
        f2.clear();
        f2.seekg(0, ios::beg);
        flag = false;
        while (f2.getline(line, '\n')) {
            if (strcmp(data, line) == 0) {
                flag = true;
                clearConsoleLine(SIZE * 2 + 1);
                gotoXY(35, SIZE * 2 + 3);
                cout << "ERROR: File name already exists. Please choose another name.\n";
                break;
            }
            else   clearConsoleLine(SIZE * 2 + 3);
        }
    } while (flag == true);
    f2.close();
    f2.open("Name.txt", ios::app);
    f2 << data << endl;
    f2.close();

    ofstream f1;
    f1.open(data, ios::out);
    f1 << a.score1 << " " << a.score2 <<" "<< n << endl;
    f1.close();


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
                playSound(2);
                t = 0;
                clearConsole();
                menu();
                break;
            }
        }
    }

}
//Hàm Load dữ liệu game từ tập tin mỗi khi người chơi muốn chơi tiếp sau khi thoát game để có thể tiếp tục chơi ở dữ liệu cũ.
void LoadGame(char data[30])
{
    Diem a;
    //NHAP FILE
    ifstream f;
    f.open(data, ios::in);
    if (!f) {
        gotoXY(35, 46);
        cout << "\n FILE KHONG TON TAI!" << endl;
    }
    else
    {
        f >> a.score1 >> a.score2 >> g->chedo;
        clearConsole();
        //thong tin
        //ban co
        int k;
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                f >> k;
                loadData(i, j, k);
            }
        }
        g->_x = getXAt(0, 0);
        g->_y = getYAt(0, 0);
        drawBoard();
        f.close();
    }
    gotoXY((SIZE * 4) + 30 + 12, 5);
    cout << _b->CountX;
    Textcolor(Red);
    gotoXY(SIZE * 4 + 30 + 12, 18);
    cout << _b->CountY;
    if (g->_turn == 1)
    {
        Textcolor(Blue);
        gotoXY(SIZE * 4 + 32, 26);
        cout << " Den luot PLAYER 1 ";
    }
    else
    {
        Textcolor(Red);
        gotoXY(SIZE * 4 + 32, 26);
        cout << " Den luot PLAYER 2 ";
    }
}

void Box()
{
    int i = 8, j = 8;
    Textcolor(Blue);
    gotoXY(50, j + 18);
    cout << "Y   : Play Again";
    gotoXY(50, j + 19);
    cout << "ESC : BACK";
}
