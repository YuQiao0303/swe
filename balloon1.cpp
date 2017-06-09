// balloon1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//����ṹ��
typedef struct ball
{
	double x;       //Բ��x����
	double y;		//Բ��y����
	double r;		//Բ�뾶
}Ball;

//���������Ѿ����õ�����
typedef struct ballList
{
	struct ballList * next;
	Ball ball;
}BallList;
//��������
void insert(Ball ball);						//������������
double distance(Ball b1, Ball b2);          //�ж�����Բ��֮��ľ���
double abs(double num);					    //ȡ����ֵ
int judge(Ball b);							//�ж��¼���������Ƿ���Ϲ���
void putBall();								//�ı�����ĳ�ʼλ�ã������������������
											//ȫ�ֱ���
BallList *head = NULL;
double step = 0.01;							//�ı�����λ�õ���С��λ
int num = 0;                                //��������ĸ���
double sumr = 0;							//������¼r^2֮��

int main()
{
	int n, pointNum, i;
	printf("������ռ�����Ҫ���õ���������: ");
	scanf_s("%d", &n);
	printf("\n����\t x����\t y����\t �뾶\t r^2֮��\n");
	for (i = 0; i < n; i++)
	{
		putBall();          //̰���㷨��ÿ�ζ���һ�����������������򣬷�n��
	}
	printf("\nr^2֮��Ϊ:\t %lf\n", sumr);
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
		ball.x += step;  //x���������step����������
		ball.y = -1 + step;
		for (j = 0; ball.y < 1; ++j)
		{
			ball.y += step;   //y�����겻�ϵ���step����������
			ball.r = 0;
			double rstep = 0.1;
			while (rstep > 0.00001)
			{
				if (ball.r > maxBall.r)
				{
					maxBall = ball;
				}
				ball.r += rstep;
				if (!judge(ball))    //��������ŵ��򲻷����������򽫰뾶������step����ʮ��
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
		printf("%d\t %.3lf\t %.3lf\t %.3lf\t %lf \n", num, maxBall.x, maxBall.y, maxBall.r, sumr);
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


