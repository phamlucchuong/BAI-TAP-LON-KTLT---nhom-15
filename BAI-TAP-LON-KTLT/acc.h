#ifndef acc.h
#define acc.h
#include<stdio.h>
#include<string.h>
#include<cctype>
#include<stdlib.h>
#include<unistd.h>
#include<conio.h>
#include"func.h"

typedef struct account{
	char userName[50];
	char passWord[50];
}account;

int random();
bool imNotRobot();
bool agreement();
bool compare(account a,account b);
bool checkingAccount(account a);
void signUp();
bool logIn();
#endif acc.h
