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
};
//static _Point* point;
static _Point** _pArr;
	bool setCheck(int pCheck, int i, int j);
	// Cài đặt biến _check
	int getX(int i, int j);
	// Lấy giá trị của _x
	int getY(int i, int j);
	// Lấy giá trị của _y
	int getCheck(int i, int j);
	// Lấy giá trị của _check
	void setX(int pX, int i, int j);
	// Cài đặt biến _x
	void setY(int pY, int i, int j);
	// Cài đặt biến _y

	//setPoint(int, int);
	//_Point();

	struct _Board
	{
		int _size;
		// Kích thước bàn cờ (size x size)
		int _left;
		int _top;
		// Tọa độ phía bên trái và trên bàn cờ.
		
		// Mảng 2 chiều để chuyển đổi tọa độ (x,y) thành các ô trong mảng 2 chiều.
		int CountX; // Đếm nước cờ X
		int CountY; // Đếm nước cờ O
	};
	static _Board* _b;		// Khởi tạo 1 bàn cờ
	template <class T>
	int getSize(T* _b);
	// Lấy giá trị _size
	template <class T>
	int getLeft(T* _b);
	// Lấy giá trị _left
	template <class T>
	int getTop(T* _b);
	// Lấy giá trị _top
	int getXAt(int, int);
	int getYAt(int, int);
	// Lấy tọa độ x,y tại vị trí i,j trên bàn cờ mảng 2 chiều _pArr
	static int get_Check(int i, int j) { return getCheck(i,j); }
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
	int checkWinRow(int x, int y, int value); // value (-1 hoac 1) hay X hoac O
	// Kiểm tra thắng theo dòng
	int checkWinCol(int x, int y, int value);
	// Kiểm tra thắng theo cột
	int checkfirstDiagonal(int x, int y, int value);
	// Kiểm tra thắng theo đường chéo thứ 1
	int checksecondDiagonal(int x, int y, int value);
	// Kiểm tra thắng theo đường chéo thứ 2

	//_Board(); // Xóa mảng 2 chiều chuyển đổi tạo độ.
	//_Board(int pSize, int pX, int pY); // Tạo mảng 2 chiều để chuyển đổi tọa độ (x,y) thành các ô trong mảng.
	//~_Board();


	struct _Game
	{
		
		bool _turn;		// True là lượt người chơi 1 , false là người chơi 2.
		int _x, _y;		// Tọa độ
		bool _loop;		// True chơi tiếp, False out.
		int scorep1;  // Số trận thắng P1
		int scorep2;// Số trận thắng P2
		int chedo; // Đọc file để nhận biết chế độ chơi
		// -31 : Chế độ P vs P đang đến lượt X
		// -30 : Chế độ P vs P đang đến lượt O
		// -4  : Chế độ P vs Bot (Dễ) đang đến lượt X
		// -5  : Chế độ P vs Bot (Khó) đang đến lượt X
		int CountX;
		int CountY;
	};
	static _Game* g;


	// Cài đặt biến đếm nước cờ X và Y = 0.
	//int getChedo() { return g->chedo; }
	// Nhận biết chế độ .
	static int getScore1() { return g->scorep1; }
	static int getScore2() { return g->scorep2; }
	// Lấy tỉ số thắng 
	static void setScore1() { g->scorep1 = 0; }
	static void setScore2() { g->scorep2 = 0; }
	// Cài đặt tỉ số thắng = 0 .
	static bool isContinue();
	// Trò chơi tiếp tục
	static char askContinue();
	// Chơi lại hay không ?

	void startGame(); // Khởi tạo game . Bắt đầu game 
	void exitGame(); // Thoát Game
	void SaveGame(int n);  // Lưu Game đang chơi với biến n là chế độ và lượt .
	void LoadGame(char data[30]); // Khởi tạo game . Bắt đầu game ( trường hợp Load Game ) 
	void LichSuGame(int n);

	int processFinish(int x, int y);
	// Kiểm tra thắng thua - tiếp tục
	bool processCheckBoard();
	// Đánh dấu X và O trên bàn cờ
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
	// Di chuyển lên - xuống - trái - phải
	static void gsetX(int x) { g->_x = x; }
	static void gsetY(int y) { g->_y = y; }
	// Cài đặt biến _x _y 
	int getXatEnter();
	int getYatEnter();
	// Lấy giá trị _x _y 
	static bool getTurn() { return g->_turn; }
	// Lấy giá trị của lượt chơi .
	static void setTurn() { g->_turn = !g->_turn; }
	// Đảo lượt chơi
	void TimKiemNuocDi();
	// Tìm kiếm nước đi cho máy
	int DemNuocCoDaDi();
	// Đếm nước cờ đã đi được
	static void setGame(int pSize, int pLeft, int  pTop);
	/*_Game();
	_Game(int pSize, int pLeft, int pTop);
	~_Game();*/




const long Defend_Score1[7] = { 0, 24, 3072, 196608, 12582912, 805306368 };
const long Attack_Score1[7] = { 0, 192, 24576, 1572864, 100663296, 6442450944 };


//const  long Defend_Score1[7] = { 0, 8, 512, 32768, 2097152, 134217728 };
//const  long Attack_Score1[7] = { 0, 64, 4096, 262144, 16777216, 1073741824 };
// 2 mảng điểm tấn công phòng thủ cho máy khó 


int PlayerVsCom(Diem& a, int, char data[30]); // BOT HARD
int PlayerVsPlayer(Diem& a, int, char data[30]); // P VS P

template <class T>
static void gsetCountXY(T* g);

void Box();
void PvPaskForRestart(Diem& a, int& load, char data[30]);
void PvCaskForRestart(Diem& a, int& load, char data[30]);

static int input = -1;

void clearConsoleLine(int y);
