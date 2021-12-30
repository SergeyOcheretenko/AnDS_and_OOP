#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdbool.h>

void gotoxy(int x, int y){
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Pos;
    Pos.X = x;
    Pos.Y = y;
    SetConsoleCursorPosition(consoleHandle, Pos);
    printf("0");
    Sleep(0.5);
}

int main() {
  HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD Pos;
  Pos.X = 0;
  Pos.Y = 0;
  bool Flag = true;
  SetConsoleCursorPosition(consoleHandle, Pos);
  while(Pos.X != 81 && Pos.Y != 24){
    if (Pos.X == 0) {
      gotoxy(Pos.X, Pos.Y);
      Pos.Y++;
      gotoxy(Pos.X, Pos.Y);
      Pos.Y--;
      Pos.X++;
      Flag = !Flag;
    }
    else if (Pos.Y == 0) {
      gotoxy(Pos.X, Pos.Y);
      Pos.X++;
      gotoxy(Pos.X, Pos.Y);
      Pos.X--;
      Pos.Y++;
      Flag = !Flag;
    }
    else if (Pos.X == 80) {
      gotoxy(Pos.X, Pos.Y);
      Pos.Y++;
      gotoxy(Pos.X, Pos.Y);
      Pos.X--;
      Pos.Y++;
      Flag = !Flag;
    }
    else if (Pos.Y == 23) {
      gotoxy(Pos.X, Pos.Y);
      Pos.X++;
      gotoxy(Pos.X, Pos.Y);
      Pos.X++;
      Pos.Y--;
      Flag = !Flag;
    }
    else {
      gotoxy(Pos.X, Pos.Y);
      if (Flag == true) {
        Pos.X--;
        Pos.Y++;
      }
      else {
        Pos.X++;
        Pos.Y--;
      }
    }
    Sleep(2);
  }
  return 0;
}
