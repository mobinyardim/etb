#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

//functions

void gotoxy(int x, int y);
void mvbr();
void gameover();
void delay(int n);
int SetBallsX();
void ShowConsoleCursor(bool showFlag);

//class
class informations
{
	int level ;
	int HitPoint ;
	int score ;
	int HighScore;
public:
	informations() { level = 0; score = 0; HitPoint = 5; }
	void ResetInfo();
	void ScoreUp() { score++; }
	void HitPointDown() { HitPoint--; }
	void LevelUp() { level++; }
	int GetScore() { return score; }
	int GetHitPoint() { return HitPoint; }
	int GetLevel() { return level; }
	int GetHighScore(){ return HighScore;}
	void SetHighScore();
};
informations inf;
class screen
{
public:
	void sc0();
	void sc1();
	void clrscr1();
	void clrscr();

} sc;

class board
{
	int y;
	int x;
public:
	board();
		void SetBoard();
		void Moveboard(int h);
	int Getx() { return x; }
	int Gety() { return y; }

}br;

class balls
{
	int n;
	int xy[2][10];
	int ballsNumber();
	void SetFirstCoord(); 
public :
	balls();
	void Creatball();

}bl;
//class screen 

void screen::sc0()

{
	cout << "\n                                                   welcome to etb \n\n";
	cout << "                                         _________________________________\n";
	cout << "                                        |                                 |\n";
	cout << "                                        |   catch '@' to score points     |\n";
	cout << "                                        |                                 |\n";
	cout << "      press '->' to move right          |  first, you have 5 hit points.  |\n";
	cout << "                                        |                                 |\n";
	cout << "                                        |   by missing '@' and catching   |\n";
	cout << "                                        |                                 |\n";
	cout << "      press '<-' to move left           |  bombs 'o' your hit point will  |\n";
	cout << "                                        |                                 |\n";
	cout << "                                        |  be reduced.                    |\n";
	cout << "                                        |                                 |\n";
	cout << "                                        |  and by catching '*' your hit   |\n";
	cout << "                                        |                                 |\n";
	cout << "                                        |  point will be increased.       |\n";
	for (int i = 0; i <7; i++)
		cout << "                                        |                                 |\n";
	cout << "                                        |      press any key to play      |\n";
	cout << "                                        |                                 |\n";
	cout << "                                        |       created by m.yardim       |\n";
	cout << "                                        |_________________________________|\n";
	for (;;) {
		if (_kbhit()) {
			_getch();
			clrscr1();
			break;
		}
		gotoxy(47, 25);
		cout << "                     ";
		Sleep(100);
		gotoxy(47, 25);
		cout << "press any key to play";
		Sleep(50);
	}
}
void screen::sc1()

{
	cout << "\n\n";
	cout << "                                         __________________________________\n";
	cout << "                 ___________________    |                                  |\n";
	cout << "                |                   |   |                                  |\n";
	cout << "                | best score : 0    |   |                                  |\n";
	cout << "                |                   |   |                                  |\n";
	cout << "                |      score : 0    |   |                                  |\n";
	cout << "                |                   |   |                                  |\n";
	cout << "                |  hit point : 5    |   |                                  |\n";
	cout << "                |                   |   |                                  |\n";
	cout << "                |      level : 0    |   |                                  |\n";
	cout << "                |___________________|   |                                  |\n";

	for (int i = 0; i<14; i++)
	{
		cout << "                                        |                                  |\n";
	}
	cout << "                                        |__________________________________|\n";
}
void screen::clrscr1()

{
	gotoxy(0, 0);
	cout << "*";
	for (int i = 1; i <= 89; i++) {
		int x = i, y = 0;
		gotoxy(x, y);
		cout << "*";
		for (int j = 0; j <i; j++) {
			if (y >28)
				break;
			y++;
			gotoxy(x, y);
			cout << "*";
		}
		for (int k = 0; k <i; k++) {
			if (i > 29)
				break;
			x--;
			gotoxy(x, y);
			cout << "*";
		}
		Sleep(10);
	}
	gotoxy(0, 0);
	cout << " ";
	for (int i = 1; i <= 89; i++) {
		int x = i, y = 0;
		gotoxy(x, y);
		cout << " ";
		for (int j = 0; j <i; j++) {
			if (y >28)
				break;
			y++;
			gotoxy(x, y);
			cout << " ";
		}
		for (int k = 0; k <i; k++) {
			if (i > 29)
				break;
			x--;
			gotoxy(x, y);
			cout << " ";
		}
		Sleep(10);
	}

	system("cls");
}
void screen::clrscr()

{
	if (_getch())
	{
		for (int i = 0; i < 30; i++)
			for (int j = 0; j <75; j++) {
				Sleep(0.5);
				gotoxy(j, i);
				cout << " ";
			}
		system("cls");
	}
}

//class balls

balls::balls()
{
	n = 0;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 2; j++)
			xy[i][j] = 0;
}
void balls::SetFirstCoord()
{
	srand(time(0));
	for(int i=0 ; i <n ; i++)
		xy[0][i]= (rand() % 34) + 41;
	for (int i = 0; i <n; i++)
		xy[1][i] = 4;
}
int balls::ballsNumber()
{
	srand(time(0));
	int x;
	if (inf.GetLevel() <= 3)
		x = (rand() % 4) + 1;

	else if (inf.GetLevel() > 3 && inf.GetLevel() <= 6)
		x = (rand() % 7) + 1;

	else if (inf.GetLevel() > 6 && inf.GetLevel() <= 9)
		x = (rand() % 10) + 1;

	else
		x = (rand() % 10) + 1;

	return x;

}
void balls::Creatball()
{
	for (int i = 0; ; i++)
	{
		n = ballsNumber();
		SetFirstCoord();
		int counter = 0;
		for (int j = 0; ; j++)
		{
			if (counter >= n / 2)
				delay(75);
			else
				delay(200);
			if (j < n)
			{
				gotoxy(xy[0][j], xy[1][j]);
				cout << "@";
				mvbr();
			}
			mvbr();
			for (int k = 0; k < (j%n) + 1; k++)
			{
				if (xy[0][k])
				{
					gotoxy(xy[0][k], xy[1][k]);
					cout << " ";
					xy[1][k]++;
				}
				// score and level 
				if (xy[0][k])
					if (xy[1][k] == 25) {
						if ((xy[0][k] - br.Getx()) < 10 && (xy[0][k] - br.Getx()) >= 0) {
							xy[0][k] = 0;
							inf.ScoreUp();
								gotoxy(31, 7);
								cout << inf.GetScore();
							

							if (inf.GetScore() && (inf.GetScore() % 10 == 0))
							{
								inf.LevelUp();
								gotoxy(31, 11);
								cout << inf.GetLevel();
							}
							counter++;
						}
					}
				// hit poin and game over
				if (xy[0][k])
					if (xy[1][k] == 27) {
						xy[0][k] = 0;
						inf.HitPointDown();
						gotoxy(31, 9);
						cout << inf.GetHitPoint();
						counter++;
						if (inf.GetHitPoint() == 0)
						{
							break;
						}
					}
				// down balls 
				if (xy[0][k])
				{
					gotoxy(xy[0][k], xy[1][k]);
					cout << "@";
				}
			}//for 3
			if (counter == n)
			{
				break;
			}
			if (inf.GetHitPoint() == 0)
			{
				break;
			}
		}//for2
		if (inf.GetHitPoint() == 0)
		{
			if (inf.GetScore() > inf.GetHighScore())
			{
				inf.SetHighScore();
			}
			break;
		}
	}//for1
}

//class board

board::board()

{
	y = 25, x = 53;
}

void board::SetBoard()
{
	gotoxy(x, y);
	cout << "==========";
}

void board::Moveboard(int h)

{
	if (h == 224) {
		h = _getch();
		if (x<65)
			if (h == 77) {
				gotoxy(x, y);
				cout << " ";
				gotoxy(x + 10, y);
				cout << "=";
				x++;
			}
		if (x > 41)
			if (h == 75) {
				gotoxy(x + 9, y);
				cout << " ";
				gotoxy(x - 1, y);
				cout << "=";
				x--;
			}
	}
}

//class inf

void informations::ResetInfo()
{
	level = 0, HitPoint = 5, score = 0;
	fstream mobin("text.txt", ios::in);
	if (mobin.is_open())
	{
		string str;
		getline(mobin, str);
		HighScore = atoi(str.c_str());
	}
	else
	{
		fstream mobin("text.txt", ios::out);
		mobin.flush();
		mobin << 0;
		HighScore = 0;
		mobin.close();
	}
	mobin.close();
	gotoxy(31, 5);
	cout << HighScore;
}
void informations::SetHighScore()
{
	fstream file("text.txt", ios::out);
	file.clear();
	fstream file2("text.txt", ios::out);
	file2 << score;
}

////////////////////////////////////////////////////////////////////
int main()
{
	ShowConsoleCursor(false);

	sc.sc0();
	sc.sc1();
	inf.ResetInfo();
	br.SetBoard();
	bl.Creatball();
	for (;;) {
		if (_kbhit()) {
			_getch();
			system("cls");
			break;
		}
		gotoxy(47, 25);
		cout << "                     ";
		Sleep(100);
		gotoxy(47, 25);
		cout << "     game over :'( ";
		Sleep(50);
	}
	return 0;
}


void mvbr()
{
	for (int i = 0; i< 250; i++)
		if (_kbhit())
			br.Moveboard(_getch());
}
void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}
void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}
void delay(int n)
{
	time_t start, finish;
	start = clock();
	mvbr();
	for (;;)
	{
		mvbr();
		finish = clock();
		if ((finish - start)> n)
			break;
	}
}
void gameover()
{
	for (;;) {
		if (_kbhit()) {
			cin.clear();
			sc.clrscr();
			break;
		}

		gotoxy(41, 25);
		cout << "                                  ";
		Sleep(100);
		gotoxy(41, 25);
		cout << "       :')  game over :P          ";
		Sleep(50);
	}
	gotoxy(45, 15);
	cout << " for reply press ' r ' ";
	gotoxy(45, 17);
	cout << " for exite press ' e ' ";
} 
