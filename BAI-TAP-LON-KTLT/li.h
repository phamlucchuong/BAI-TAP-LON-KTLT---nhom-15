#ifndef li.h
#define li.h
#include<stdio.h>
#include<stdlib.h>
#include"stlib.h"

typedef struct node{
	student data;		// du lieu cua node co kieu du lieu la student
	node* next;			// chua dia chi cua node tiep theo de lien ket
}node;

typedef struct list{
	node* head;			// tao node dau cua list de quan li dslk
}list;


node* makeNode(student st);
void creatList(list* l);
void pushBack(list* l,node* newNode);
void deleteNode(list* l,node* oldNode);



#endif li.h
