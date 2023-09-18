#ifndef func.h
#define func.h
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include"stlib.h"
#include"li.h"



void pause();
int makeMenu(int x, int y, int w, int h, int n,  char title[], char op[][50]);
void changeStudentInfo();
void deleteRegister();
void searchingRoom();
void searchingStudent();
void searching();
void writeToFile(list* l);
list* readFromFile(list* l);
void boardingRegister();

//void SET_COLOR(int color);
//void gotoXY(int x,int y);
//void box(int x, int y, int w, int h);
//void nBox(int x, int y, int w, int h, int sl, char op[][50]);

#endif func.h
