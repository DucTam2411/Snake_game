#include<iostream>
#include<windows.h>
#include<ctime>
#include<cstdlib>
#include<conio.h>
using namespace std;

bool gameOver; //Kiem tra tinh dung cua tro choi
const int width = 30; //Chieu rong khung
const int height = 15; // Chieu cao khung
int x, y, fruitX, fruitY, score; //Toa do con ran, thuc an va diem
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN }; //Huong di cua con ran
eDirection dir;
int tailX[100];
int tailY[100];
int nTail;

//Thiet lap cac gia tri ban dau cua game
void setup()
{
	//Cai dat tro choi
	gameOver = false;
	dir = STOP;
	//Vi tri ban dau cua con ran, giua khung
	x = width / 2;
	y = height / 2;
	//Vi tri cua thuc an la ngau nhien
	fruitX = 1 + rand() % (width - 1);
	fruitY = 1 + rand() % (height - 1);
	//Diem so ban dau cua tro choi
	score = 0;
}



void draw()
{
	system("cls"); //Xoa man hinh //Khong biet de lam gi thi len mang doc them

	//In phan tren cua khung
	for (int i = 0; i < width; i++)
	{
		cout << '#';
	}
	cout << endl;

	//In vien hai ben cua khung
	//Gap toa do cua ran se in ra con ran
	//Gap toa do thuc an se in ra thuc an
	//Con lai in ra khoan trong
	for (int i(0); i < height; i++)
	{
		for (int j(0); j < width; j++)
		{
			if (j == 0)
				cout << '#'; //Khung trai
			else if (j == width - 1)
				cout << '#'; //Khung phai
			else if (i == y && j == x) //Con ran
				cout << 'O';
			else if (i == fruitY && j == fruitX) //Thuc an
				cout << '*';
			else //khoang trong
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << 'o';
						print = true;
					}
				}
				if (!print)
					cout << ' ';

			}
		}
		cout << endl;


	}

	//In phan duoi cua khung
	for (int i = 0; i < width; i++)
	{
		cout << '#';
	}
	cout << endl;

	cout << "Score: " << score << endl;
}

void input()
{
	if (_kbhit()) //Kiem tra co bam phim khong
	{
		switch (_getch()) //Neu bam thi lay phim do
		{
		case 'a': //Phim a -> Trai
			dir = LEFT;
			break;
		case 'd': //Phim d -> Phai
			dir = RIGHT;
			break;
		case 'w': //Phim w -> Len
			dir = UP;
			break;
		case 's': //Phim s -> Xuong
			dir = DOWN;
			break;
		case 'q': //Phim q -> Thoat game
			gameOver = true;
			break;
		}
	}
}

void logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;//Giong temp -> Doi cho
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		//Khi con ran di chuyen thi duoi di chuyen theo
		//Nen mang chua con ran se duoc doi tu dau xuong duoi

		//Hoat dong giong ham swap
		prev2X = tailX[i];
		prev2Y = tailY[i];

		tailX[i] = prevX;
		tailY[i] = prevY;

		prevX = prev2X;
		prevY = prev2Y;

	}
	switch (dir)
	{
	case LEFT:
		x--; //Qua trai toa do x giam 1
		break;
	case RIGHT:
		x++; //Qua phai toa do x tang 1
		break;
	case UP:
		y--; //Len tren toa do y giam 1
		break;
	case DOWN:
		y++; //Xuong duoi toa do x giam 1
		break;
	default:
		break;
	}

	if (x == width - 1 || x == 0 || y == height || y == -1) //Dung vao khung thi game over
		gameOver = true;

	for (int i(0); i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;

	if (x == fruitX && y == fruitY) //Ran an thuc an
	{
		score++; //Diem tang sau khi an

		fruitX = 1 + rand() % (width - 1); //Sau khi an thi sinh ra thuc an moi ngau nhien
		fruitY = 1 + rand() % (height - 1);
		nTail++; //Do dai tang sau khi an moi
	}
}
int main()
{
	srand(time(NULL));
	setup();
	while (gameOver == false)
	{
		draw();
		input();
		logic();
		Sleep(100);
	}
	if (gameOver == true)
	{
		Sleep(500);
		cout << "Game ket thuc !!!";
	}
}