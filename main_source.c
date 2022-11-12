#pragma warning(disable: 6031)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include "cli.h"

#define G					9.80665
#define Pi					3.14159
#define SCR_WIDTH			150
#define SCR_HEIGHT			50
#define SPRITE_HEIGHT		8
#define DURATION			10

double h = 0;
double target_distance = 0;
double jet_vx = 0;

char *jet_sprite[SPRITE_HEIGHT] = {
" _____         ______",
"| : \\ | \\",
"| :  `\\______ | ______\\_______",
" \\'______              \\_____\\_____",
"   \\____ / -)_,-------- - ,_____________> --",
"             \\       /",
"              |     /",
"              |____ / __ ->"
};

void print_jet_sprite(int pos)
{
	for (int i = 0; i < 8; i++)
	{
		SetCursorCoord(pos, i);
		printf("%s\n", jet_sprite[i]);
	}
}

int main(int argc, char** argv)
{
	SetConsoleSize(SCR_WIDTH, SCR_HEIGHT);

	print_jet_sprite(70);
	SetCursorCoord(0, 0);
	printf("\n   --- �������� �Է¹ްڽ��ϴ� ---\n\n");
	printf("%-3s. �߻� ������ ����(Y)�� �Է��ϼ���: ", "i");
	scanf("%lf", &h);
	printf("   > �߻� ���� %6.1f m �Էµ�.\n", h);
	printf("%-3s. ź�� ������ ���� ��ǥ(X)�� �Է��ϼ���: ", "ii");
	scanf("%lf", &target_distance);
	printf("   > ź�� ���� %6.1f m �Էµ�.\n", target_distance);
	printf("%-3s. �������� ���� �ӷ�(Vx)�� �Է��ϼ���: ", "iii");
	scanf("%lf", &jet_vx);
	printf("   > ������ ���� �ӷ� %3.1f m/s �Էµ�.\n", jet_vx);
	double total_time = sqrt(2 * h / G);
	double distance = total_time * jet_vx;
	printf("[��� ���] �� �ð�: %.3lf��, �̵��� ���� �Ÿ�: %.3lfm\n", total_time, distance);

	WaitForInput();
	ClearConsole();
	printf("[��� ���] �� �ð�: %.3lf��, �̵��� ���� �Ÿ�: %.3lfm\n", total_time, distance);
	printf("[���� �м�] ��ǥ ����: %.3lfm, ź�� ����: %.3lfm\n", target_distance, distance);
	if (target_distance * 1.1 > distance && target_distance * 0.9 < distance)
		printf("[���� ���] 10% ������ ��ǥ ������ %.3lfm ���̷� �����Ͽ����ϴ�.\n", target_distance - distance);
	else
		printf("[���� ���] ź�� ź�� ������ 10%% ���� �ܿ� �ֽ��ϴ�.\n");
	for (int y = 0; y < SCR_HEIGHT - SPRITE_HEIGHT - 2; y++)
	{
		SetCursorCoord(0, y + SPRITE_HEIGHT);
		if (y == 0)
			printf("%6.1f ", h);
		else if (y == (SCR_HEIGHT - SPRITE_HEIGHT - 2) / 2)
			printf("%6.1f ", h / 2);
		else if (y == SCR_HEIGHT - SPRITE_HEIGHT - 3) 
			printf("%6.1f ", 0.0);
		else
			printf("       ");
		printf("��");
	}
	double distance_view = (target_distance > distance) ? target_distance : distance;
	for (int x = 7; x < SCR_WIDTH; x++)
	{
		SetCursorCoord(x, SCR_HEIGHT - 2);
		printf("��");
		if (x == 7)
		{
			SetCursorCoord(x, SCR_HEIGHT - 1);
			printf("%-6.1f", 0.0);
		}
		else if (x == (SCR_WIDTH - 7) / 2 + 4)
		{
			SetCursorCoord(x, SCR_HEIGHT - 1);
			printf("%-6.1f", distance_view / 2);
		}
		else if (x == SCR_WIDTH - 7)
		{
			SetCursorCoord(x, SCR_HEIGHT - 1);
			printf("%-6.1f", distance_view);
		}
	}
	if (target_distance < distance)
	{
		int POS = (int)((target_distance / distance) * (SCR_WIDTH - 7));
		if (POS < SCR_WIDTH - 7)
		{
			SetCursorCoord(POS, SCR_HEIGHT - 1);
			printf("T");
		}
	}
	SetCursorCoord(0, 0);
	double time_elapsed = 0.0;
	while (1)
	{
		if (time_elapsed > total_time)
			break;
		int x = (int)((jet_vx * time_elapsed) / distance_view * (SCR_WIDTH - 7));
		int y = (int)((1.0 / 2.0 * G * time_elapsed * time_elapsed) / h * (SCR_HEIGHT - SPRITE_HEIGHT - 2)) + SPRITE_HEIGHT;
		SetCursorCoord(9 + x, y);
		printf("*");
		time_elapsed += 0.1;
		_sleep(1);
	}
	WaitForInput();
	return EXIT_SUCCESS;
}