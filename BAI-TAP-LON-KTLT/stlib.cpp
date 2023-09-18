#include"stlib.h"



void deleteEnd(char str[]){
	// xoa dau xuong dong o cuoi xau ki tu ( thay bang khoang trang )
	if(str[strlen(str)-1]=='\n'){
		str[strlen(str)-1]='\0';
	}
}

bool checkingMajor(char major[]) {
	
	// kiem tra ten nganh co hop le hay khong ( co trung voi 1 trong cac nganh cua truong hay khong ) ?
    char temp[20];
    FILE* fmajor = fopen("major.txt", "r");

    if (fmajor == NULL) {
        printf("\n\t\t * Loi mo file major.txt!\a");
        sleep(1);
        exit(0);
    }
    
    // doc du lieu tu file major.txt vao bien temp
    while (fgets(temp, sizeof(temp), fmajor) != NULL) {
    	// so sanh ten nganh voi cac nganh co san trong file
        if (strcmp(temp, major) == 0) {
            fclose(fmajor);
            return true;
        }
    }
    
    fclose(fmajor);
    return false;
}

classUnit enterClass( classUnit c ){
	
	// nhap ten lop
	do{
		printf("\n\t\t Nhap lop:  ");
		fflush(stdin);
		fgets(c.className,sizeof(c.className),stdin);
		strupr(c.className);								// viet hoa cac ki tu trong xau( ten lop)
	
		if( !checkingMajor(c.className) ){
			printf("\n\t\t Khong tim thay ma nganh %s\a",c.className);
			printf("\n\t\t Hay nhap ma nganh hop le!");
		}
	}while( !checkingMajor(c.className) );
	
	
	// nhap khoa
	do{
		printf("\n\t\t Nhap khoa:  ");
		scanf("%d",&c.course);
		
		if( c.course<55 || c.course>63 ){					// gioi han so khoa tu 55->63
			printf("\n\t\t Khoa khong hop le!\a");
			fflush(stdin);
			continue;
		}
	}while( c.course<55 || c.course>63 );	
	
	
	return c;
}


date timeSet(date d){
	// ham lay ngay gio he thong
	time_t rawtime;
   struct tm *timeinfo;

   time(&rawtime);
   timeinfo = localtime(&rawtime);

	// gan ngay gio he thong vao bien struct date d
   d.day = timeinfo->tm_mday;
   d.month = timeinfo->tm_mon + 1;
   d.year = timeinfo->tm_year + 1900;
   return d;
}

void upperString( char str[] ){
	// ham viet hoa chu dau cua xau ki tu
	for(int i=0;i<strlen(str);i++){
		if( i==0 || ( i>0 && str[i-1]==32 ) ){		// truong hop ky tu dau tien va ky tu sau dau khoang trang
			if(str[i]>=97 && str[i]<=122){			// truong hop ki tu dang viet thuong
				str[i]=str[i]-32;					//  (1)
			}
		} else{										// cac truong hop khong viet hoa
			if( str[i]>=65 && str[i]<=90 ){			// truong hop ki tu dang viet hoa
				str[i]=str[i]+32;					// (2)
			}
		}
	}
	
	// (1),(2) :  khoang cach cua chu viet hoa va chu viet thuong tren bang ma ascii la +-32
}

room chooseRoom( char gender[] ){
	
	room roomChoice;
	
	FILE* froom=fopen("roomData.dat","rb");
	if(froom==NULL){
		printf("\n\t\t * Khong the mo file roomData.dat!\a");
		exit(0);
	}
	
	
	// doc du lieu phong tu file roomData.dat
	room r[20];
	for(int i=0;i<20;i++){
		fread(&r[i],sizeof(room),1,froom);
	}
	
	fclose(froom);
	
	
	typedef struct rnode{
		room data;
		int index;
		rnode* next;
	}rnode;
	
	rnode* head=NULL;

	int gnum = ( strcmp( gender,"Nam" ) == 0 ) ? 1 : 0 ;		// tao bien gnum de phan loai gioi tinh, 0: nu / 1: nam
	int count= ( gnum==1 ) ? 14 : 8;							// tao bien count la so phong toi da ma nam / nu duoc o

	int num=1;
	for(int i=0;i<20;i++){
		
		if( r[i].gender == gnum || r[i].gender ==2){
			
			rnode* newNode=(rnode*)malloc(sizeof(rnode));
			newNode->data=r[i];
			newNode->index=num;
			newNode->next=NULL;
		
			if(head==NULL){
				head=newNode;

			} else{
				rnode* temp=head;
				while(temp->next!=NULL){
					temp=temp->next;
				}
		
				temp->next=newNode;
			}
			
			
			num++;
		}
	}
	
	
	//tao menu de chon phong
	choose:
	fflush(stdin);
	
	int ch;
	int option =1;
	
	while( ch!= KEY_ENTER ){
		printf("\n\t\t\t\t***Chon phong %s***\n\n", gender);
		for(rnode* temp=head; temp!=NULL; temp=temp->next){
			printf("\n\t\t %s Phong %s-%d%s: %d/%d nguoi, phong %s", option==temp->index ?">  ":" ",temp->data.range,temp->data.floor,temp->data.roomNumber,temp->data.num,temp->data.max,(temp->data.num<temp->data.max)?"con trong":"da day");
		}
		
		ch=getch();
		switch(ch){
			
			case KEY_UP:
				if(option>1){
					option--;
				} else option=count;
				break;
				
			case KEY_DOWN:
				if(option<count){
					option++;
				} else option=1;
				break;
			
			default:
				break;
		}
		
		
		system("cls");
	}
	
	for(rnode* temp=head;temp!=NULL;temp=temp->next){
		if( temp->index==option ){
			if(temp->data.num < temp->data.max){
				roomChoice=temp->data;
				return roomChoice;
			} else {
				fflush(stdin);
				printf("\n\t\t\t\t***Chon phong %s***\n\n", gender);
				printf("\n\n\n\n\t\t    Phong da day! Vui long chon phong khac!\a");
				break;
			}
		} else continue;
	}
	
	
	sleep(1);
	system("cls");
	ch=1;
	goto choose;
}

bool checkingName(char name[]){
	
	for(int i=0;i<strlen(name);i++){
		
		if( isdigit(name[i])) return false;				// kiem tra mot ki tu trong ten co phai la so hay khong?
		if( ispunct(name[i])) return false;				// kiem tra mot ki tu trong ten co phai la ki tu dac biet hay khong?
	}
	
	return true;
}

bool checkingID1(char ID[]){
	
    FILE* fID = fopen("student.dat", "rb");

    if (fID == NULL) {
        printf("\n\t\t * Loi mo file student.dat!\a");
        sleep(1);
        exit(0);
    }
    
    
    // kiem tra xem mssv da ton tai hay chua/da dang ky hay chua?
    student st;
    while (fread(&st, sizeof(st),1, fID) == 1) {
    	if( strcmp(ID,st.ID) == 0 ){
    		fclose(fID);
    		return false;
		}
    }
    
    return true;
}

bool checkingID2(char ID[]){
	// kiem tra mssv co chua ki tu dac biet, khoang trang, dau xuong dong hay khong?
	for(int i=0;i<strlen(ID);i++){
		if( ispunct(ID[i]) || ID[i]=='\0' || ID[i]=='\n' ){
			return false;
		}
	}
	
	return true;
}

bool checkingBirthday(date d){

	// kiem tra hinh thuc cua ngay thang nam co hop le hay khong?
	if (d.day < 1 || d.day > 31 || d.month < 1 || d.month > 12 || d.year < 1943 || d.year > 2023) {
        return false;
    }
    
    // kiem tra so ngay cua thang 2
    if (d.month == 2) {
        if ( d.year % 400 == 0 || (d.year % 4 == 0 && d.year % 100 != 0) ) {
            if (d.day > 29) {
                return false;
            }
        } else {
            if (d.day > 28) {
                return false;
            }
        }
        
    } else if (d.month == 4 || d.month == 6 || d.month == 9 || d.month == 11) {
        if (d.day > 30) {
            return false;
        }
    }
	
	
	return true;
}

date enterDate(date d){
	do{
		printf("\n\t\t Nhap ngay thang nam sinh (dd/mm/yyyy):  ");
		scanf("%d%d%d",&d.day,&d.month,&d.year);
		
		if( !checkingBirthday(d) ){
			printf("\n\t\t Hay nhap ngay sinh hop le!\a");
			fflush(stdin);
			continue;
		}
		
	}while( !checkingBirthday(d) );
	
	return d;
}


bool checkingPnumber(char pnumber[]){
	
	// kiem tra so dien thoai
	for(int i=0;i<strlen(pnumber);i++){
		if( !isdigit(pnumber[i]) ) return false;			// kiem tra cac ky tu trong sdt co phai la so hay k?
	}
	
	return true;
}

void updateRoom(room a , int mode){
	
	
	// cap nhat so nguoi o trong phong, mode 1 la dki phong, mode=0 la huy dang ky
	FILE* froom=fopen("roomData.dat","rb");
	
	if(froom == NULL){
		printf("\n\t\t * Khong the mo file roomData.dat!\a");
		return;
	}
	
	room r[20];
	for(int i=0;i<20;i++){
		fread(&r[i], sizeof(r[i]), 1, froom);
	}
	
	for(int i=0;i<20;i++){
		if( strcmp(a.range,r[i].range) == 0 && a.floor == r[i].floor && strcmp(a.roomNumber,r[i].roomNumber) ==0 ){
			if( mode==1 )
				r[i].num= r[i].num + 1;
			else
				r[i].num= r[i].num - 1;
			fclose(froom);
			break;
		}
	}
	
	froom=fopen("roomData.dat","wb");
	for(int i=0;i<20;i++){
		fwrite(&r[i],sizeof(r[i]),1,froom);
	}
	
	fclose(froom);
}

student enterStudent(student st, char title[]){
	
	student a;
	FILE* f=fopen("student.dat","rb");
	while ( fread(&a,sizeof(a),1,f) == 1 ){
		fread(&a,sizeof(a),1,f);
	}
	fclose(f);
	
	
	loop:
	printf("\n\t\t\t\t***%s***\n\n", title);
	
	do{
		printf("\n\t\t Nhap ten sinh vien:  ");
		fflush(stdin);
		fgets(st.name,sizeof(st.name),stdin);
		deleteEnd(st.name);
		upperString(st.name);
		
		if( !checkingName(st.name) ){
			printf("\n\t\t Hay nhap ten hop le!\a");
			
		}
	} while( !checkingName(st.name) );
	
	
	do{
		printf("\n\t\t Nhap mssv:  ");
		gets(st.ID);
		
		if( strcmp( title, "Dang ky noi tru" )==0 && !checkingID1(st.ID) ){
			printf("\n\t\t Ban da dang ky roi!\a");
			sleep(1);
			system("cls");
			goto loop;
		}
		
		if( !checkingID2(st.ID) ){
			printf("\n\t\t Mssv khong hop le!\a");
		}
		
	} while( !checkingID2(st.ID) );
	


	st.cData=enterClass(st.cData);
	
	
	do{
		printf("\n\t\t Gioi tinh:  ");
		scanf("%s",st.gData);
		upperString(st.gData);
		
		if( strcmp(st.gData,"Nam")!=0 && strcmp(st.gData,"Nu")!=0 ){
			printf("\n\t\t Gioi tinh khong hop le!\a");
		}
	} while( strcmp(st.gData,"Nam")!=0 && strcmp(st.gData,"Nu")!=0 );
	getchar();
	
	
	do{
		printf("\n\t\t Nhap so dien thoai:  ");
		fflush(stdin);
		scanf("%s",st.pNumber);
		
		if( !checkingPnumber(st.pNumber) ){
			printf("\n\t\t Hay nhap so dien thoai hop le!\a");
		}
	}while( !checkingPnumber(st.pNumber) );
	
	
	do{
		printf("\n\t\t Nhap ngay thang nam sinh (dd/mm/yyyy):  ");
		scanf("%d%d%d",&st.birthday.day,&st.birthday.month,&st.birthday.year);
		
		if( !checkingBirthday(st.birthday) ){
			printf("\n\t\t Hay nhap ngay sinh hop le!\a");
			fflush(stdin);
			continue;
		}
	}while( !checkingBirthday(st.birthday) );
	
	
	st.cardNum=a.cardNum+1;
	
	
	system("cls");
	st.rData=chooseRoom(st.gData);
	st.dormitoryFee=st.rData.price;
	
	
	st.dateRegister=timeSet(st.dateRegister);
	
	
	system("cls");
	printf("\n\t\t\t\t***Phieu dang ky noi tru***\n\n");
	printStudent(st,10,5,100,16);
	
	int ch;
	printf("\n\n\t An ENTER de xac nhan dang ky\t\tAn ESC de quay lai");
	confirm:
	ch=getch();
	switch(ch){
		case KEY_ENTER:
			updateRoom(st.rData, 1);
			return st;
			break;
		case KEY_ESC:
			system("cls");
			goto loop;
			break;
		default:
			goto confirm;
			break;
	}
	
} 

void printDate(date d){
	
	if(d.day<10 && d.month<10)
		printf("0%d / 0%d / %d",d.day,d.month,d.year);
	
	else if(d.day<10 && d.month>10)	
		printf("0%d / %d / %d",d.day,d.month,d.year);
	
	else if(d.day>10 && d.month<10)
		printf("%d / 0%d / %d",d.day,d.month,d.year);
	
	else printf("%d / %d / %d",d.day,d.month,d.year);
	
}

void printClass(classUnit c){
	printf("\n Lop %s khoa %d",c.className,c.course);
}

//void printStudent(student st){
//	printf("\n Ten:  %s",st.name);
//	printf("\t Gioi tinh:  %s",st.gData);
//	printClass(st.cData);
//	printf("\t\t Mssv:  %s",st.ID);
//	printf("\n Ngay sinh:  ");
//	printDate(st.birthday);
//	printf("\n So dien thoai:  %s",st.pNumber);
//	printf("\n So the :  %d",st.cardNum);
//	printf("\t\t Phong:  %s-%d%s",st.rData.range,st.rData.floor,st.rData.roomNumber);
//	printf("\n Ngay dang ky noi tru:  ");
//	printDate(st.dateRegister);
//	printf("\n Le phi phong:  %ld Vnd/thang",st.dormitoryFee);
//}



void SET_COLOR(int color) {
	WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}


void gotoXY(int x,int y) {
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = {x,y};
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
} 


void box(int x, int y, int w, int h){
	if(w<=1 || h<=1) 
		return;
	SET_COLOR(6);
	for(int ix=x; ix<=x+w; ix++){
		gotoXY(ix,y);
		printf("%c",char(171));  
		gotoXY(ix,y+h);
		printf("%c",char(187)); 
	}
	for(int iy=y; iy<=y+h; iy++){
		gotoXY(x,iy);
		printf("%c",char(94));
		gotoXY(x+w,iy);
		printf("%c",char(94));
	}
	gotoXY(x,y); printf("%c",char(139));
	gotoXY(x+w,y); printf("%c", char(139));
	gotoXY(x,y+h); printf("%c", char(155));
	gotoXY(x+w,y+h); printf("%c", char(155));
} 


void nBox(int x, int y, int w, int h, int sl, char op[][50]){
	for(int i=0; i<sl; i++){
		box(x,y+(i*4),w,h); // i=0 => (x,y), i=1 => (x,y+4)
	}
	SET_COLOR(7);
	int k=0,l=0;	
	for(int j=2; j<=sl*4-2; j+=4){
		gotoXY(x+1,y+j);
//		switch(j){
//			case 2:
//				printf("\t%s",op[0]);
//				break;
//			case 6:
//				printf("\t\t%s",op[1]);
//				break;
//			case 10:
//				printf("\t\t%s",op[2]);
//				break;
//			case 14:
//				printf("\t\t\t%s",op[3]);
//				break; 
//		}


		if(j==l+2){
			printf("\t%s",op[k]);
			k++;
			l+=4;
		}
		
		
	}
}

int makeMenu(int x, int y, int w, int h, int n, char title[], char op[][50]){	

   	int ch;
	int option=0;
	int i=0;
	while(ch!=13){
		gotoXY(55,3);
		printf("%s",title);
		nBox(50,6,43,4,n,op); 
//		if(option == 1){
//			gotoXY(x-10,y+2);
//			printf("%s",">>>"); 
//		}
//		else if(option == 2){
//			gotoXY(x-10,y+6);
//			printf("%s",">>>"); 
//		} 
//		else if(option == 3){
//			gotoXY(x-10,y+10);
//			printf("%s",">>>"); 
//		} 
//		else{
//			gotoXY(x-10,y+14);
//			printf("%s",">>>"); 
//		} 



		if(option==i){
//			gotoXY(x-10,y+2+(i-1)*4);
			gotoXY(x-10,y+2+i*4);
			printf("%s",">>>");
			
		}
		
			
		ch=getch();
		
		switch(ch){
			
			case KEY_UP:
				if(option>0){
					option--;
					i--;
				}
				else {
					option = n-1;
					i = n-1;
				}
				break; 
			case KEY_DOWN:
				if(option<n-1){
					option++;
					i++;
				}
				else {
					option = 0;
					i = 0;
				}
			default:
				break;
		}
		
		system("cls");
	}
	  
	return option+1;
}




void printStudent(student st, int x, int y, int w, int h){
	box(10,5,90,16);
	gotoXY(x+((90-28)/2),y+1);
	printf("___PHIEU DANG KY NOI TRU___");
	for(int i=3 ;i<=13; i+=2){
		gotoXY(x+2,y+i);
		switch(i){
			case 3:
				printf("Ten: %-50s",st.name);
				break;
			case 5:
				printf("Lop: %s",st.cData.className);
				break;
			case 7:
				printf("Khoa: %d",st.cData.course);
				break;
			case 9:
				printf("Ngay sinh: ");
				printDate(st.birthday);
				break;
			case 11:
				printf("So the: %d",st.cardNum);
				break;		
		}
		gotoXY(x+50,y+i);
			switch(i){
				case 3:
					printf("Gioi tinh: %-5s",st.gData);
					break;
				case 7:
					printf("MSSV: %-20s",st.ID);
					break;
				case 9:
					printf("So dien thoai: %-20s",st.pNumber);
					break;
				case 11:
					printf("Phong: %s-%d%s",st.rData.range,st.rData.floor,st.rData.roomNumber);
					break;
			}
	}
	gotoXY(w-40,y+13);
	printf("Ngay dang ky noi tru: ");
	printDate(st.dateRegister);
	
	gotoXY(w-30,y+15);
	printf("Le phi: %ld Vnd/thang",st.dormitoryFee);
}


