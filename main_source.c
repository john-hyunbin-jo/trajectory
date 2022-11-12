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
	printf("\n   --- 설정값을 입력받겠습니다 ---\n\n");
	printf("%-3s. 발사 지점의 높이(Y)를 입력하세요: ", "i");
	scanf("%lf", &h);
	printf("   > 발사 높이 %6.1f m 입력됨.\n", h);
	printf("%-3s. 탄착 지점의 수평 좌표(X)를 입력하세요: ", "ii");
	scanf("%lf", &target_distance);
	printf("   > 탄착 지점 %6.1f m 입력됨.\n", target_distance);
	printf("%-3s. 전투기의 수평 속력(Vx)를 입력하세요: ", "iii");
	scanf("%lf", &jet_vx);
	printf("   > 전투기 수평 속력 %3.1f m/s 입력됨.\n", jet_vx);
	double total_time = sqrt(2 * h / G);
	double distance = total_time * jet_vx;
	printf("[계산 결과] 총 시간: %.3lf초, 이동한 수평 거리: %.3lfm\n", total_time, distance);

	WaitForInput();
	ClearConsole();
	printf("[계산 결과] 총 시간: %.3lf초, 이동한 수평 거리: %.3lfm\n", total_time, distance);
	printf("[적중 분석] 목표 지점: %.3lfm, 탄착 지점: %.3lfm\n", target_distance, distance);
	if (target_distance * 1.1 > distance && target_distance * 0.9 < distance)
		printf("[적중 결과] 10% 오차로 목표 지점에 %.3lfm 차이로 도달하였습니다.\n", target_distance - distance);
	else
		printf("[적중 결과] 탄알 탄착 지점이 10%% 오차 외에 있습니다.\n");
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
		printf("│");
	}
	double distance_view = (target_distance > distance) ? target_distance : distance;
	for (int x = 7; x < SCR_WIDTH; x++)
	{
		SetCursorCoord(x, SCR_HEIGHT - 2);
		printf("─");
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