#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<graphics.h>
#include<conio.h>
#define _CRT_SECURE_NO_WARNINGS
typedef struct Pointxy
{
	int x;
	int y;
}Point;
struct Snake
{
	int num;//�ߵĽ���
	Point xy[100];//�����һ�ٽ�
	char position;//����
	int score;
}snake;
struct Food
{
	Point fdxy;//ʳ�������
	int foodgrade;//ʳ��ķ���
	int flag;//ʳ���Ƿ����
}food;
HWND hwnd = NULL;
enum moveposition { right = 77, left = 75, down = 80, up = 72 };//ö��
void drawSnake();
void initSnake();
void moveSnake();
void initFood();
void drawFood();
void eatFood();
int Died();
void keyDown();
void showScore();
void Pause();
void throught();
int main()
{
	hwnd = initgraph(640, 480);//���ڳߴ�
	setbkcolor(BLACK);//������ɫ
	srand((unsigned int)time(NULL));
	initSnake();
	while (1)
	{
		cleardevice();//ˢ��
		if (food.flag == 0)
		{
			initFood();
		}
		drawFood();
		drawSnake();
		if (Died())break;
		eatFood();
		showScore();
		moveSnake();
		throught();
		while (_kbhit())
		{
			Pause();
			keyDown();
		}

		Sleep(75);
	
	}
	
	_getch();//��ֹ����
	closegraph();
	return 0;
}
void initSnake()
{
	snake.xy[2].x = 0;
	snake.xy[2].y = 0;

	snake.xy[1].x = 10;
	snake.xy[1].y = 0;

	snake.xy[0].x = 20;
	snake.xy[0].y = 0;
	snake.num = 3;
	snake.position = right;//��ʼ������

	food.flag = 0;
	snake.score = 0;
}
void drawSnake()
{
	for (int i = 0; i < snake.num; i++)
	{
		setlinecolor(RED);
		setfillcolor(YELLOW);
		fillrectangle(snake.xy[i].x, snake.xy[i].y, snake.xy[i].x + 10, snake.xy[i].y + 10);
	}
}
void moveSnake()
{
	//����һ����ȫ����Ϊ��һ�ڵ�����
	for (int i = snake.num - 1;i>0; i--)
	{
		snake.xy[i].x = snake.xy[i - 1].x;
		snake.xy[i].y = snake.xy[i - 1].y;
	}
	switch (snake.position)
	{
	case right:
		snake.xy[0].x += 10;
		break;
	case left:
		snake.xy[0].x -= 10;
		break;
	case down:
		snake.xy[0].y += 10;
		break;
	case up:
		snake.xy[0].y -= 10;
		break;
	default:
		break;

	}
}
void keyDown()
{
	char userKey = 0;
	userKey = _getch();
	switch (userKey)
	{
	case right:
		if (snake.position != left)snake.position = right;
		break;
	case left:
		if (snake.position != right)snake.position = left;
		break;
	case down:
		if (snake.position != up)snake.position = down;
		break;
	case up:
		if (snake.position != down)snake.position = up;
		break;
	default:
		break;
	}
}
void initFood()
{
	food.fdxy.x = rand() % 65 * 10;
	food.fdxy.y = rand() % 48 * 10;
	food.flag = 1;
	for (int i = 0; i < snake.num; i++)
	{
		if (food.fdxy.x == snake.xy[i].x && food.fdxy.y == snake.xy[i].y)//ʳ�ﲻ��������
		{
			food.fdxy.x = rand() % 65 * 10;
			food.fdxy.y = rand() % 48 * 10;
		}
	}
}
void drawFood()
{
	setlinecolor(BLACK);
	setfillcolor(GREEN);
	fillrectangle(food.fdxy.x, food.fdxy.y, food.fdxy.x + 10, food.fdxy.y + 10);
}
void eatFood()
{
	if (food.fdxy.x == snake.xy[0].x && food.fdxy.y == snake.xy[0].y)
	{
		snake.num++;
		food.flag = 0;
		snake.score += 1;
	}
}
int Died()
{
	/*if (snake.xy[0].x > 620 || snake.xy[0].x <= 0 || snake.xy[0].y > 460 || snake.xy[0].y < 0)
	{
		outtextxy(200, 200, "�㴴���ˣ�");
		MessageBox(hwnd, "Gameover", "ײǽ��", MB_OK);
		return 1;
	}*/
	for (int i = 1; i < snake.num; i++)
	{
		if (snake.xy[0].x == snake.xy[i].x && snake.xy[0].y == snake.xy[i].y)
		{
			outtextxy(200, 200, "������Լ���");
			MessageBox(hwnd, "Gameover", "������", MB_OK);
			return 1;
		}
	}


	return 0;
}
void showScore()
{
	char grade[100] = "";
	sprintf_s(grade, "%d", snake.score);
	setbkmode(TRANSPARENT);
	settextcolor(LIGHTBLUE);
	outtextxy(560, 20, "����:");
	outtextxy(610, 20, grade);
}
void Pause()
{
	if (_getch() == 32)
	{
		while (_getch() != 32);
	}
}
void throught()
{
	if (snake.xy[0].x > 630)
	{
		snake.xy[0].x = 0;
	}
	if (snake.xy[0].x < 0)
	{
		snake.xy[0].x = 630;
	}
	if (snake.xy[0].y > 470)
	{
		snake.xy[0].y = 0;
	}
	if (snake.xy[0].y <0)
	{
		snake.xy[0].y = 470;
	}
}


