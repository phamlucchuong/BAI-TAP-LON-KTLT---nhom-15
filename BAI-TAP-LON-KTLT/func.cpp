#include"func.h"

void pause(){
	printf("\n\n\t\t An phim bat ky de tiep tuc hoac ESC de thoat!");
	int ch=getch();
	
	if( ch==KEY_ESC )
		exit(0);
	else {
		system("cls");
	}
}

int makeMenu2(int num , char title[],char op[][50]){
	int ch;
	int i;
	int option=0;
	int num2= ( num >10 ) ? 10 : num ;
	
	
	menu1:
	while( ch!= KEY_ENTER ) {
		
		printf("\n\t\t%s",title);
		for( i=0;i<num2;i++) {
			printf("\n\t %s %s",option==i?"> ":" ",op[i]);
		}
		
		ch=getch();
		switch(ch){
			
			case KEY_UP:
			 	if(option>0){
			 		option--;
				}
				break;
				
			case KEY_DOWN:
				if( num<10 ){
					if(option<num-1) option++;
				} else{
					if(option<num2){
						option++;
					} else {
						system("cls");
						goto menu2;
					}
				}
				break;
				
			default:
				break;
		}
		
		system("cls");
	}
	
	
	menu2:
	while( ch!= KEY_ENTER ) {
		
		printf("\n\t\t%s",title);
		for( i=num2;i<num;i++) {
			printf("\n\t %s %s",option==i?"> ":" ",op[i]);
		}
		
		ch=getch();
		switch(ch){
			
			case KEY_UP:
			 	if(option>num2){
			 		option--;
				} else {
					system("cls");
					goto menu1;
				}
				break;
				
			case KEY_DOWN:
				if(option<num-1){
					option++;
				}
				break;
				
			default:
				break;
		}
		
		system("cls");
	}
	
	
	return option+1;
}



void changeStudentInfo(){
	
	
	char ID[20];
	
	do{
		
		printf("\n\t\t\t\t***Thay doi thong tin noi tru***\n\n");
		
		printf("\n\t\t Nhap mssv:  ");
		gets(ID);
		
		
		if( checkingID1(ID) ){
			printf("\n\t\t Khong tim thay sinh vien!\a");
			sleep(1);
			system("cls");
			fflush(stdin);
			continue;
		}
		
		if( !checkingID2(ID) ){
			printf("\n\t\t Mssv khong hop le!\a");
			sleep(1);
			system("cls");
		}
		
	} while( checkingID1(ID) || !checkingID2(ID) );
	
	
	list* l=(list*)malloc(sizeof(list));
	creatList(l);
	l=readFromFile(l);
	
	
	node* temp=l->head;
	while( temp != NULL ){
		if( strcmp( temp->data.ID,ID ) == 0){
			system("cls");
			updateRoom(temp->data.rData,0);
			temp->data=enterStudent(temp->data, "Thay doi thong tin");
			writeToFile(l);
			printf("\n\t\t Thay doi thong tin thanh cong!\a");
			return;
		}
		
		temp=temp->next;
	}
	
}


void deleteRegister(){
	
	
	char ID[20];
	
	dele:
	do{
		
		printf("\n\t\t\t\t***Huy dang ky noi tru***\n\n");
		
		printf("\n\t\t Nhap mssv:  ");
		gets(ID);
		
		
		if( checkingID1(ID) ){
			printf("\n\t\t Khong tim thay sinh vien!\a");
			sleep(1);
			system("cls");
			fflush(stdin);
			continue;
		}
		
		if( !checkingID2(ID) ){
			printf("\n\t\t Mssv khong hop le!\a");
			sleep(1);
			system("cls");
		}
		
	} while( checkingID1(ID) || !checkingID2(ID) );
	
	
	list* l=(list*)malloc(sizeof(list));
	creatList(l);
	l=readFromFile(l);
	
	
	node* temp=l->head;
	node* prev=NULL;
	while (temp != NULL) {
		
        if ( strcmp(temp->data.ID,ID) == 0 ) {
        	
        	system("cls");
        	printf("\n\t\t\t\t***Huy dang ky noi tru***\n\n\n");
        	printStudent(temp->data,10,5,100,16); 	
			
			printf("\n\n\n\t Xac nhan xoa sinh vien?");
			int ch=getch();
			if ( ch == KEY_ENTER ){
					updateRoom(temp->data.rData,0);

					// truong hop dslk chi co mot node
					if (prev == NULL) {
                
    				    l->head = temp->next;
        
    				}
    				// truong hop dslk co nhieu hon 1 node
					else {
        
        				prev->next = temp->next;
        
    				}
					writeToFile(l);
        		    free(temp);
        		    printf("\n\t Xoa thong tin thanh cong!\a");
            		return;
			} else {
					system("cls");
					goto dele;
					
			}
			
        }
        
        prev = temp;
        temp = temp->next;
    }
	
}



void searchingRoom(){
	
	
	char op1[][50]={
			 		 "D30-001", "D30-002",
				   	 "D60-001", "D60-002",
					 "D62-001", "D62-002",
					 "D7T-001", "D7T-002", 
				   	 "D7T-101", "D7T-102",
				   	 "D7T-201", "D7T-202", 
					 "D7T-301", "D7T-302", 
					 "D7T-401", "D7T-402", 
					 "D7T-501", "D7T-502", 
					 "D7T-601", "D7T-602"
											};
					 
	
	room r[20];
	FILE* froom=fopen("roomData.dat","rb");
	for(int i=0;i<20;i++){
		fread(&r[i],sizeof(r[i]),1,froom);
	}
	fclose;
	
	
	int index = makeMenu2(20,"\t\t***Tra cuu phong\n",op1);
	index--;
	
	printf("\n\t\t\t\t***Tra cuu phong***\n\n");
	if( r[index].num == 0){
		printf("\n Phong %s-%d%s trong",r[index].range,r[index].floor,r[index].roomNumber);
	} else {
		printf("\n Phong %s-%d%s: %d/%d nguoi, phong %s",r[index].range,r[index].floor,r[index].roomNumber,r[index].num,r[index].max,( r[index].num < r[index].max)?"con trong":"da day");
		printf("\n Danh sach sinh vien:\n");
	}
	
	list* l=(list*)malloc(sizeof(list));
	creatList(l);
	l=readFromFile(l);
	
	node* temp=l->head;
	while( temp!= NULL ){
		if( strcmp(temp->data.rData.range,r[index].range) == 0  && temp->data.rData.floor == r[index].floor && strcmp(temp->data.rData.roomNumber,r[index].roomNumber) == 0 ){
			
			printf("  %s\n",temp->data.name);
		}
		
		temp=temp->next;
	}
	
	date d=timeSet(d);
	printf("\n\n Hoa don sinh hoat: \n  Dien:  %ld Vnd\n  Nuoc:  %ld Vnd\n  Tong cong:  %ld Vnd",electricityPrice*r[index].num*d.day,waterPrice*r[index].num*d.day,electricityPrice*r[index].num*d.day+waterPrice*r[index].num*d.day);
	pause();
}


void searchingStudent(){



	char ID[20];
	
	
	do{
		
		printf("\n\t\t\t\t***Tim kiem sinh vien***\n\n");
		
		printf("\n\t\t Nhap mssv:  ");
		gets(ID);
		
		
		if( checkingID1(ID) ){
			printf("\n\t\t Khong tim thay sinh vien!\a");
			sleep(1);
			system("cls");
			fflush(stdin);
			continue;
		}
		
		if( !checkingID2(ID) ){
			printf("\n\t\t Mssv khong hop le!\a");
			sleep(1);
			system("cls");
		}
		
	} while( checkingID1(ID) || !checkingID2(ID) );
	
	
	list* l=(list*)malloc(sizeof(list));
	creatList(l);
	l=readFromFile(l);	
	
	
	node* temp=l->head;
	while( temp != NULL ){
		if( strcmp( temp->data.ID,ID ) == 0 ){
			printStudent(temp->data,10,5,100,16);
			return;
		}
		
		temp=temp->next;
	}
	
}


void searching(){
	
	char op[][50]={" Sinh vien","Phong" };
	
	int selection=makeMenu(50,6,30,4,2,"\t\t***Menu tra cuu***\n\n",op);
	switch(selection){
		
		case 1:
			fflush(stdin);
			searchingStudent();
			break;
			
		case 2:
			searchingRoom();
			break;	
	}
	
}


list* readFromFile(list* l){
    FILE *f = fopen("student.dat", "rb");
    if (f == NULL){
        printf("\n\t\t * Loi mo file student.dat!\a");
        exit(0);
    }
    
    student st;
    while (fread( &st, sizeof(st), 1, f) == 1){
    	node* newNode=makeNode(st);
        pushBack(l,newNode);
    }
    
    fclose(f);
    return l;
}

void writeToFile(list* l){
	
	FILE* fnode=fopen("student.dat","wb");
	if(fnode==NULL){
		printf("\n\t\t * Loi mo file student.dat!\a");
		sleep(1);
		exit(0);
	}
	
	node* temp=l->head;
    while ( temp != NULL){
        fwrite( &(temp->data), sizeof(temp->data), 1, fnode);
        temp=temp->next;
    }
    
    fclose(fnode);
}


void boardingRegister(){

	list* l=(list*)malloc(sizeof(list));
	creatList(l);
	l=readFromFile(l);
	student st=enterStudent(st, "Dang ky noi tru" );
	node* newNode=makeNode(st);
	pushBack(l,newNode);
	writeToFile(l);
	printf("\n\t\t\tDang ky noi tru thanh cong!\a");
	free(l);
	
}







//void SET_COLOR(int color) {
//	WORD wColor;
//    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
//    CONSOLE_SCREEN_BUFFER_INFO csbi;
//    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
//    {
//        wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
//        SetConsoleTextAttribute(hStdOut, wColor);
//    }
//}
//
//
//void gotoXY(int x,int y) {
//    HANDLE hConsoleOutput;
//    COORD Cursor_an_Pos = {x,y};
//    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
//    SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
//} 
//
//
//void box(int x, int y, int w, int h){
//	if(w<=1 || h<=1) 
//		return;
//	SET_COLOR(6);
//	for(int ix=x; ix<=x+w; ix++){
//		gotoXY(ix,y);
//		printf("%c",char(171));  
//		gotoXY(ix,y+h);
//		printf("%c",char(187)); 
//	}
//	for(int iy=y; iy<=y+h; iy++){
//		gotoXY(x,iy);
//		printf("%c",char(94));
//		gotoXY(x+w,iy);
//		printf("%c",char(94));
//	}
//	gotoXY(x,y); printf("%c",char(139));
//	gotoXY(x+w,y); printf("%c", char(139));
//	gotoXY(x,y+h); printf("%c", char(155));
//	gotoXY(x+w,y+h); printf("%c", char(155));
//} 
//
//
//void nBox(int x, int y, int w, int h, int sl, char op[][50]){
//	for(int i=0; i<sl; i++){
//		box(x,y+(i*4),w,h); // i=0 => (x,y), i=1 => (x,y+4)
//	}
//	SET_COLOR(7);
//	int k=0,l=0;	
//	for(int j=2; j<=sl*4-2; j+=4){
//		gotoXY(x+1,y+j);
////		switch(j){
////			case 2:
////				printf("\t%s",op[0]);
////				break;
////			case 6:
////				printf("\t\t%s",op[1]);
////				break;
////			case 10:
////				printf("\t\t%s",op[2]);
////				break;
////			case 14:
////				printf("\t\t\t%s",op[3]);
////				break; 
////		}
//
//
//		if(j==l+2){
//			printf("\t%s",op[k]);
//			k++;
//			l+=4;
//		}
//		
//		
//	}
//}
//
//int makeMenu(int x, int y, int w, int h, int n, char title[], char op[][50]){	
//
//   	int ch;
//	int option=0;
//	int i=0;
//	while(ch!=13){
//		gotoXY(55,3);
//		printf("%s",title);
//		nBox(50,6,43,4,n,op); 
////		if(option == 1){
////			gotoXY(x-10,y+2);
////			printf("%s",">>>"); 
////		}
////		else if(option == 2){
////			gotoXY(x-10,y+6);
////			printf("%s",">>>"); 
////		} 
////		else if(option == 3){
////			gotoXY(x-10,y+10);
////			printf("%s",">>>"); 
////		} 
////		else{
////			gotoXY(x-10,y+14);
////			printf("%s",">>>"); 
////		} 
//
//
//
//		if(option==i){
////			gotoXY(x-10,y+2+(i-1)*4);
//			gotoXY(x-10,y+2+i*4);
//			printf("%s",">>>");
//			
//		}
//		
//			
//		ch=getch();
//		
//		switch(ch){
//			
//			case KEY_UP:
//				if(option>0){
//					option--;
//					i--;
//				}
//				else {
//					option = n-1;
//					i = n-1;
//				}
//				break; 
//			case KEY_DOWN:
//				if(option<n-1){
//					option++;
//					i++;
//				}
//				else {
//					option = 0;
//					i = 0;
//				}
//			default:
//				break;
//		}
//		
//		system("cls");
//	}
//	
//	
//	
//	
//	
//	
//	  
//	  
//	  
//	return option+1;
//}
