// balloon1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//气球结构体
typedef struct ball
{
	double x;       //圆心x坐标
	double y;		//圆心y坐标
	double r;		//圆半径
}Ball;

//用来储存已经放置的气球
typedef struct ballList
{
	struct ballList * next;
	Ball ball;
}BallList;
//函数声明
void insert(Ball ball);						//插入气球到链表
double distance(Ball b1, Ball b2);          //判断气球圆心之间的距离
double abs(double num);					    //取绝对值
int judge(Ball b);							//判断新加入的气球是否符合规则
void putBall();								//改变气球的初始位置，求的满足条件的气球
											//全局变量
BallList *head = NULL;
double step = 0.01;							//改变气球位置的最小单位
int num = 0;                                //放置气球的个数
double sumr = 0;							//用来记录r^2之和

int main()
{
	int n, pointNum, i;
	printf("请输入空间内所要放置的气球数量: ");
	scanf_s("%d", &n);
	printf("\n球编号\t x坐标\t y坐标\t 半径\t r^2之和\n");
	for (i = 0; i < n; i++)
	{
		putBall();          //贪婪算法：每次都放一个符合条件的最大的球，放n次
	}
	printf("\nr^2之和为:\t %lf\n", sumr);
	while (1);
	return 0;
}

void insert(Ball ball)
{
	ballList * newBall = (ballList *)malloc(sizeof(ballList));
	newBall->ball = ball;
	newBall->next = head;
	head = newBall;
}

void putBall()
{
	Ball ball = { -1 + step, -1 + step, 0 };
	Ball maxBall = ball;
	int i, j;
	for (i = 0; ball.x < 1; ++i)
	{
		ball.x += step;  //x的坐标递增step以穷尽所有情况
		ball.y = -1 + step;
		for (j = 0; ball.y < 1; ++j)
		{
			ball.y += step;   //y的坐标不断递增step以穷尽所有情况
			ball.r = 0;
			double rstep = 0.1;
			while (rstep > 0.00001)
			{
				if (ball.r > maxBall.r)
				{
					maxBall = ball;
				}
				ball.r += rstep;
				if (!judge(ball))    //如果这样放的球不符合条件，则将半径递增的step减少十倍
				{
					ball.r -= rstep;
					rstep /= 10;
				}
			}
		}
	}
	if (judge(maxBall))
	{
		insert(maxBall);
		num++;
		sumr += maxBall.r * maxBall.r;
		printf("%d\t %.6lf\t %.6lf\t %.6lf\t %lf \n", num, maxBall.x, maxBall.y, maxBall.r, sumr);
	}
}

int judge(Ball b)
{
	if ((abs(b.x) + b.r) > 1 || (abs(b.y) + b.r) > 1)
	{
		return false;
	}
	ballList *tmp = head;
	while (tmp)
	{
		Ball ball = tmp->ball;
		if (distance(b, ball) < b.r + ball.r)
		{
			return false;
		}
		tmp = tmp->next;
	}
	return true;
}

double abs(double num)
{
	if (num > 0)
		return num;
	return 0 - num;
}

double distance(Ball b1, Ball b2)
{
	double x1 = b1.x;
	double y1 = b1.y;
	double x2 = b2.x;
	double y2 = b2.y;
	return pow((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2), 0.5);
}



