// Windows의 콘솔 환경 제어를 위한 소스 코드
// cli.h에 정의

// References:
// 콘솔 다루기 - https://rottk.tistory.com/entry/%EC%BD%98%EC%86%94-%EB%8B%A4%EB%A3%A8%EA%B8%B0-Escape-Sequence-C

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include "cli.h"

void SetConsoleSize(int width, int height)
{
	char buffer[256];
	snprintf(buffer, 256, "mode con: cols=%d lines=%d", width, height);
	system(buffer);
}

void SetCursorCoord(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void ClearConsole()
{
	system("CLS");
}

void WaitForInput()
{
	fflush(stdin);
	while (!_kbhit());
	_getch();
}