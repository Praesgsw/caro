#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <mmsystem.h>
#include <time.h>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <time.h>
#define SIZE  20  // SIZE BÀN CỜ 
//Định nghĩa thông số màu hiển thị
#define Black			240
#define Blue		    241
#define Green		    242
#define Red      		244
#define Violet          245
#define FullBlue		17
#define BlueYellow		30
#define FullGreen		34
#define FullAzure       51
#define FullRed         68
#define YellowRed       100
#define FullYellow		102
#define Grey		    135
#define GreyBlue	    121
#define MintPink		189
#define defaultColor    7 
using namespace std;
using std::cout;
#pragma comment(lib, "winmm.lib")
// Dinh nghia ten ham 
static string menuItems[] = { "Player Vs Player", "Player Vs Computer", "Load Game", "History", "Instruction", "About", "Exit" };
static int numItems = sizeof(menuItems) / sizeof(menuItems[0]);
static int currentSelection = 0;

//Dinh nghia file ve
static string file_name[] = { "Caro.txt", "P1.txt", "P2.txt", "Draw.txt", "About.txt" };
extern bool isSoundOn;
void showCur();
void hideCur();
void SetConsole(int width, int height);
void Textcolor(int color);
void gotoXY(int x, int y);
void playSound(int);
int getConsoleInput();
void menu();
void clearConsole();
void setConsoleTitle();

int readMode(char a[30]); //Tìm kiếm file người dùng (hỗ trợ hàm LoadLoad)
void readNameFile(); //Hiển thị các người dùng đã lưu
void Load(); // Mở file người chơi đã lưu
void instruction(); //Mục hướng dẫn
void history(); //Mục history#pragma once
void About();  // thông tin

