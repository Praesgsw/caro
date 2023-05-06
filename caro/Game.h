#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <mmsystem.h>
#include <vector>
#include <fstream>
using namespace std;
struct Diem
{
	int score1;
	int score2;
};

struct _Point
{
	int _x;
	int _y;
	// Tọa độ x y trên bàn cờ
	int _check;
	// Biến nhận biết X và O ( -1 = X , 1 = O, 0 = Ô trống )

public:
	bool setCheck(int);
	// Cài đặt biến _check
	int getX();
	// Lấy giá trị của _x
	int getY();
	// Lấy giá trị của _y
	int getCheck();
	// Lấy giá trị của _check
	void setX(int);
	// Cài đặt biến _x
	void setY(int);
	// Cài đặt biến _y
public:
	_Point(int, int);
	_Point();
	~_Point();
};
struct _Board
{
private:
	int _size;
	// Kích thước bàn cờ (size x size)
	int _left;
	int _top;
	// Tọa độ phía bên trái và trên bàn cờ.
	_Point** _pArr;
	// Mảng 2 chiều để chuyển đổi tọa độ (x,y) thành các ô trong mảng 2 chiều.
public:
	int getSize();
	// Lấy giá trị _size
	int getLeft();
	// Lấy giá trị _left
	int getTop();
	// Lấy giá trị _top
	int getXAt(int, int);
	int getYAt(int, int);
	// Lấy tọa độ x,y tại vị trí i,j trên bàn cờ mảng 2 chiều _pArr
	int get_Check(int i, int j) { return _pArr[i][j].getCheck(); }
	// Lấy giá trị _check trên mảng 2 chiều . nhận biết X O và ô trống.
	void loadData(int, int, int);
	// Load dữ liệu 
	void resetData();
	// Reset bàn cờ cho tất cả các ô trống _check = 0.
	int checkBoard(int, int, bool);
	// Kiểm tra X hay O
	int testBoard(int x, int y);
	// Kiểm tra thắng thua trên bàn cờ
	_Point Tim_Kiem_NuocDi_1(); // Tìm nước đi cho máy khó 
	long SoDiemTanCong_DuyetDoc(long, long, const long Defend_Score[], const long Attack_Score[]);
	long SoDiemTanCong_DuyetNgang(long, long, const long Defend_Score[], const long Attack_Score[]);
	long SoDiemTanCong_DuyetCheo1(long, long, const long Defend_Score[], const long Attack_Score[]);
	long SoDiemTanCong_DuyetCheo2(long, long, const long Defend_Score[], const long Attack_Score[]);
	long SoDiemPhongThu_DuyetDoc(long, long, const long Defend_Score[], const long Attack_Score[]);
	long SoDiemPhongThu_DuyetNgang(long, long, const long Defend_Score[], const long Attack_Score[]);
	long SoDiemPhongThu_DuyetCheo1(long, long, const long Defend_Score[], const long Attack_Score[]);
	long SoDiemPhongThu_DuyetCheo2(long, long, const long Defend_Score[], const long Attack_Score[]);
	// Duyệt Các Ô Trống tính điểm cho từng ô theo dọc , ngang , chéo ngược , chéo xuôi.
public:
	int checkWinRow(int x, int y, int value); // value (-1 hoac 1) hay X hoac O
	// Kiểm tra thắng theo dòng
	int checkWinCol(int x, int y, int value);
	// Kiểm tra thắng theo cột
	int checkfirstDiagonal(int x, int y, int value);
	// Kiểm tra thắng theo đường chéo thứ 1
	int checksecondDiagonal(int x, int y, int value);
	// Kiểm tra thắng theo đường chéo thứ 2
	int CountX; // Đếm nước cờ X
	int CountY; // Đếm nước cờ O
public:
	_Board(); // Xóa mảng 2 chiều chuyển đổi tạo độ.
	_Board(int pSize, int pX, int pY); // Tạo mảng 2 chiều để chuyển đổi tọa độ (x,y) thành các ô trong mảng.
	~_Board();
};

struct _Game
{
	_Board* _b;		// Khởi tạo 1 bàn cờ
	bool _turn;		// True là lượt người chơi 1 , false là người chơi 2.
	int _x, _y;		// Tọa độ
	int _command;	// Nhận phím
	bool _loop;		// True chơi tiếp, False out.
	int scorep1;  // Số trận thắng P1
	int scorep2;// Số trận thắng P2
	int chedo; // Đọc file để nhận biết chế độ chơi
	// -31 : Chế độ P vs P đang đến lượt X
	// -30 : Chế độ P vs P đang đến lượt O
	// -4  : Chế độ P vs Bot (Dễ) đang đến lượt X
	// -5  : Chế độ P vs Bot (Khó) đang đến lượt X
public:
	void setCountXY() {
		_b->CountX = 0;
		_b->CountY = 0;
	}
	// Cài đặt biến đếm nước cờ X và Y = 0.
	int getChedo() { return chedo; }
	// Nhận biết chế độ .
	int getScore1() { return scorep1; }
	int getScore2() { return scorep2; }
	// Lấy tỉ số thắng 
	void setScore1() { scorep1 = 0; }
	void setScore2() { scorep2 = 0; }
	// Cài đặt tỉ số thắng = 0 .
	int getCommand();
	// Lấy giá trị của phím nhập vào .
	void setCommand(int x) { _command = x; }
	// Cài đặt phím nhập vào
	bool isContinue();
	// Trò chơi tiếp tục
	char waitKeyBoard();
	// Chờ nhập phím
	char askContinue();
	// Chơi lại hay không ?

public:
	void startGame(); // Khởi tạo game . Bắt đầu game 
	void exitGame(); // Thoát Game
	void SaveGame(int n);  // Lưu Game đang chơi với biến n là chế độ và lượt .
	void LoadGame(char data[30]); // Khởi tạo game . Bắt đầu game ( trường hợp Load Game ) 
	void LichSuGame(int n);
public:
	int processFinish(int x, int y);
	// Kiểm tra thắng thua - tiếp tục
	bool processCheckBoard();
	// Đánh dấu X và O trên bàn cờ
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
	// Di chuyển lên - xuống - trái - phải
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }
	// Cài đặt biến _x _y 
	int getXatEnter();
	int getYatEnter();
	// Lấy giá trị _x _y 
	bool getTurn() { return _turn; }
	// Lấy giá trị của lượt chơi .
	void setTurn() { _turn = !_turn; }
	// Đảo lượt chơi
	void TimKiemNuocDi();
	// Tìm kiếm nước đi cho máy
	int DemNuocCoDaDi();
	// Đếm nước cờ đã đi được
public:
	_Game();
	_Game(int pSize, int pLeft, int pTop);
	~_Game();
};



const long Defend_Score1[7] = { 0, 24, 3072, 196608, 12582912, 805306368 };
const long Attack_Score1[7] = { 0, 192, 24576, 1572864, 100663296, 6442450944 };


//const  long Defend_Score1[7] = { 0, 8, 512, 32768, 2097152, 134217728 };
//const  long Attack_Score1[7] = { 0, 64, 4096, 262144, 16777216, 1073741824 };
// 2 mảng điểm tấn công phòng thủ cho máy khó 


int PlayerVsCom(Diem& a, int, char data[30]); // BOT HARD
int PlayerVsPlayer(Diem& a, int, char data[30]); // P VS P

