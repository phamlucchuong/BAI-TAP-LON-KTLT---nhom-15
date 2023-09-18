#ifndef stlib.h
#define stlib.h
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<windows.h>
#include<unistd.h>
#include<conio.h>


#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13
#define KEY_ESC 27

typedef struct classUnit{
	char className[20];
	int course;
}classUnit;

typedef struct date{
	int day,month,year;
}date;

 enum livingBill { electricityPrice = 8000, waterPrice = 1900 };

typedef struct room{
	char range[5];
	int floor;
	char roomNumber[4];
	int num;
	int max;
	int gender;
	long int price;
	long int livingFee=0;
}room;

typedef struct student{
	char name[50];
	char ID[20];
	classUnit cData;
	char gData[10];
	char pNumber[20];
	date birthday;
	int cardNum;
	room rData;
	date dateRegister;
	long int dormitoryFee;
}student;


void deleteEnd(char str[]);
void upperString();
classUnit enterClass(classUnit c);
date timeSet(date d);
date enterDate(date d);
void updateRoom(room a, int mode);
room chooseRoom(char gender);
bool checkingName(char name[]);
bool checkingID1(char ID[]);
bool checkingID2(char ID[]);
bool checkingMajor(char major[]);
bool checkingBirthday(date d);
bool checkingPnumber(char pnumber[]);
student enterStudent(student st, char title[]);
void printDate(date d);
void printStudent(student st, int x, int y, int w, int h);
//void printStudent(student st);


void SET_COLOR(int color);
void gotoXY(int x,int y);
void box(int x, int y, int w, int h);
void nBox(int x, int y, int w, int h, int sl, char op[][50]);

#endif stlib.h
