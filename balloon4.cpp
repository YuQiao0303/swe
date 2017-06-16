// balloon4.cpp : �������̨Ӧ�ó������ڵ㡣
//
/*
�㷨˼�룺
1.���㷨����Ҫ˼���Ǽ����������Ѱ�����Ž⣬�ٶ�������������޵ģ���Բ�ܷŵ�λ�������޵ģ�
2.��νԲ�ܷŵ�λ�������޵���ָ��Բ��x��y����ľ���ֻ��ȡ��С�������λ������������Բ�ĵ�λ����10000����ͨ������ÿ��λ
���������������뾶r���Ӷ��ҳ���Щ������뾶��
3.��Ѱ�����뾶ʱ��ÿ��λ�õ����뾶�ľ���ֻ��ȡ��С�������λ��
4.�������������Բ������һ�������У�����һ��֮���Բ�ڽ���λ���ж�ʱ�������ѷ����Բ���бȽϣ��Ӷ��ж����Ƿ�����������
*/

#include "stdafx.h"
#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <Windows.h>

#define MAX_THREADS 2
//����
typedef struct ball
{
	double x;       //Բ��x����
	double y;		//Բ��y����
	double z;		//Բ��z����
	double r;		//Բ�뾶
}Ball;

//���������Ѿ����õ�����
typedef struct ballList
{
	struct ballList * next;
	Ball ball;
}BallList;

//
typedef struct MyData {
	int m;            //�̺߳����Ĳ�����Ҫ��ŵ����������
	int i;            //�̱߳��
} MYDATA, *PMYDATA;


//��������
void insert(Ball ball);						//��������
double distance(Ball b1, Ball b2);          //�ж�����֮��ľ���
double abs(double num);					    //ȡ����ֵ
int judge(Ball b);							//�ж��¼���������Ƿ���Ϲ���
void putBall();								//�ı�����ĳ�ʼλ�ã������������������
void putPoint(double x, double y, double z);			//���õ�
DWORD WINAPI threadfunc(LPVOID lpParam);
//ȫ�ֱ�������
BallList *head = NULL;                      //�ѷ��õ���������
double step = 0.01;							//�ı�����λ�õ���С��λ
int num = 0;                                //��������ĸ���
double sumr = 0;							//������¼r^2֮��
CRITICAL_SECTION cs;
int main()
{
	InitializeCriticalSection(&cs);
	int n, pointNum, i;
	printf("������ռ�����Ҫ���õ���������: ");
	scanf_s("%d", &n);
	printf("������ռ��ڵ������: ");
	scanf_s("%d", &pointNum);
	for (i = 0; i < pointNum; i++)
	{
		printf("�������%d���������(����ÿո����)��", i + 1);
		double x, y, z;
		scanf_s("%lf %lf %lf", &x, &y, &z);
		putPoint(x, y, z);
	}
	printf("\n����\t x����\t y����\t z����\t �뾶\t r^2֮��\n");

	PMYDATA pDataArray[MAX_THREADS];           //����
	DWORD   dwThreadIdArray[MAX_THREADS]; //�̺߳�������
	HANDLE  hThreadArray[MAX_THREADS];    //�̺߳����������

	 // Allocate memory for thread data.Ϊ�����ṹ���Ƿ���ռ�
	for (i = 0; i < MAX_THREADS; i++)
	{
		pDataArray[i] = (PMYDATA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(MYDATA));
	}
	// Generate unique data for each thread to work with.��������ֵ
	for (i = 0; i < MAX_THREADS; i++)
	{
		pDataArray[i]->m = n;
		pDataArray[i]->i = i;
	}
	//�����߳�
	for (i = 0; i < MAX_THREADS;i++)
	hThreadArray[i] = CreateThread(
		NULL,                   // default security attributes
		0,                      // use default stack size  
		threadfunc,       // thread function name
		pDataArray[i],          // argument to thread function 
		0,                      // use default creation flags 
		&dwThreadIdArray[i]);   // returns the thread identifier 



	/*��һ�����̺߳���Ҫ��ɵ�����
	for (i = 0; i < n; i++)
	{
		putBall();
	}
	*/


	printf("\nr^2֮��Ϊ:\t %lf\n", sumr);
	printf("\n\n");
	//ballList *temp = head;
	//int counter = 1;
	//while (temp!= NULL)
	//{
	//	printf("\n\n");
	//	printf("%d\t %.3lf\t %.3lf\t %.3lf\t %.3lf\t ", counter, temp->ball.x, temp->ball.y, temp->ball.z, temp->ball.r);
	//	counter++;
	//	temp = temp->next;
	//}
	printf("end");
	while (1);
	return 0;
}

void putPoint(double x, double y, double z)
{
	Ball ball = { x, y, z,0 };
	insert(ball);
	/*printf("putPoint~");*/
}

void insert(Ball ball)
{
	ballList * newBall = (ballList *)malloc(sizeof(ballList));
	newBall->ball = ball;
	newBall->next = head;
	head = newBall;
	/*printf("insert~");*/
}
DWORD WINAPI threadfunc(LPVOID lpParam)
{
	PMYDATA pDataArray = (PMYDATA)lpParam;
	int m,i;
	m = pDataArray->m;
	i = pDataArray->i;
	while(num<m)
	{
		EnterCriticalSection(&cs);
		putBall();
		printf("�����߳�%d������",i);
		LeaveCriticalSection(&cs);
	}
	
}
void putBall()
{
	Ball ball = { -1 + step, -1 + step, -1 + step,0 };
	Ball maxBall = ball;
	int i, j, k;
	for (i = 0; ball.x < 1; ++i)                 //
	{
		ball.x += step;
		ball.y = -1 + step;
		ball.z = -1 + step;
		for (j = 0; ball.y < 1; ++j)
		{
			ball.y += step;
			ball.z = -1 + step;
			for (k = 0; ball.z < 1; ++k)
			{
				ball.z += step;
				ball.r = 0;
				double rstep = 0.1;
				while (rstep > 0.00001)
				{
					if (ball.r > maxBall.r)
					{
						maxBall = ball;
					}
					ball.r += rstep;
					if (!judge(ball))
					{
						ball.r -= rstep;
						rstep /= 10;
					}
				}
			}
		}
	}
	if (judge(maxBall))
	{
		insert(maxBall);
		num++;
		sumr += maxBall.r * maxBall.r;
		printf("\n%d\t %.3lf\t %.3lf\t %.3lf\t %.3lf\t %lf ", num, maxBall.x, maxBall.y, maxBall.z, maxBall.r, sumr);
	}
}

int judge(Ball b)
{
	if ((abs(b.x) + b.r) > 1 || (abs(b.y) + b.r) > 1 || (abs(b.z) + b.r) > 1)
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
	double z1 = b1.z;
	double x2 = b2.x;
	double y2 = b2.y;
	double z2 = b2.z;
	return pow((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2)*(z1 - z2), 0.5);
}

