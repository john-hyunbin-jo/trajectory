#pragma once

#ifndef __CLI_H_
#define __CLI_H_
// 현재 콘솔 크기를 변경하는 함수
void SetConsoleSize(int, int);
// 현재 콘솔의 기준 커서를 옮기는 함수
void SetCursorCoord(int, int);
// 현재 콘솔 내용을 모두 지우는 함수
void ClearConsole(void);
// 사용자 키 입력을 기다리는 함수
void WaitForInput(void);
#endif