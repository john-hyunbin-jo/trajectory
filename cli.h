#pragma once

#ifndef __CLI_H_
#define __CLI_H_
// ���� �ܼ� ũ�⸦ �����ϴ� �Լ�
void SetConsoleSize(int, int);
// ���� �ܼ��� ���� Ŀ���� �ű�� �Լ�
void SetCursorCoord(int, int);
// ���� �ܼ� ������ ��� ����� �Լ�
void ClearConsole(void);
// ����� Ű �Է��� ��ٸ��� �Լ�
void WaitForInput(void);
#endif