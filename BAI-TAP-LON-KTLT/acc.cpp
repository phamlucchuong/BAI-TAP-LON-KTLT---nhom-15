#include"acc.h"


int random(){
	// tra ve mot so bat ky trong khoang tu min=0 den max=100
	int min=0,max=100;
	return min + (int)( rand() * (max - min + 1.0) / (1.0 + RAND_MAX) );
}


bool imNotRobot(){
	
	srand((unsigned int)time(NULL));
	
	int num1=random();
	int num2=random();
	
	// cho nguoi dung lam 1 bai toan nho de xac nhan danh tinh :v
	int result;
	printf("\n\t\t Ban co phai la robot?\n\t\t      %d  +  %d  =  ",num1,num2);
	scanf("%d",&result);
	if(result==num1+num2){
		printf("\n\t\t Cam on con nguoi!\a");
		return true;
	} else{
		printf("\n\t\t You are a stupid robot -.-\a");
		sleep(1);
		system("cls");
		return false;
	}
}

bool compare(account a,account b){
	// so sanh ten dang nhap va mat khau
	if(strcmp(a.userName,b.userName)==0 && strcmp(a.passWord,b.passWord)==0){
		return true;
	} else return false;
}

bool checkingAccount(account a){
	
	// ktra ten dang nhap co du toi thieu 6 ki tu
	if(strlen(a.userName)<6)
		return false;
	
	// ktra mat khau co du toi thieu 6 ki tu
	if(strlen(a.passWord)<6)
		return false;
	
	bool flag1=false,flag2=false, flag3=false;
	
	for( int i=0 ; i<strlen(a.passWord) ; i++ ){
		
		// kiem tra mat khau co chua so hay k?
		if( isdigit(a.passWord[i]) !=0 ){
			flag1=true;
			continue;
		}
		
		// kiem tra mat khau co chua ki tu dac biet hay k?
		if( ispunct(a.passWord[i]) !=0 ){
			flag2=true;
			continue;
		}
		
		// kiem tra mat khau co chua chu viet hoa hay k?
		if( isupper(a.passWord[i]) !=0 ){
			flag3=true;
			continue;
		}
	}
	
	// neu mat khau co du 3 yeu to tren thi duyet true va nguoc lai
	if( flag1==true && flag2==true && flag3==true ){
		return true;
	} else return false;
}

bool agreement(){
	
	// cho nguoi dung thong tin, yeu cau ve cach tao tai khoan moi
	int ch;
	int option=1;
	
	while(ch!=KEY_ENTER){
		printf("\n\t\t\t\t  ***DANG KY***\n\n");
		printf("\t\t\t  ***Dieu khoan ve mat khau***\n");
		printf("\n\t\t 1. Ten dang nhap co do dai toi thieu 6 ky tu");
		printf("\n\t\t 2. Mat khau co it nhat 6 ki tu, bao gom chu so,\n\t\t ki tu viet hoa va ki tu dac biet!");
		printf("\n\n\t\t %s Dong y va tiep tuc", option==1?"> ":" ");
		printf("\n\t\t %s Thoat", option==2?"> ":" ");
		
		ch=getch();
		
		switch(ch){
			
			case KEY_UP:
				if(option>1){
					option--;
				}
				break;
			case KEY_DOWN:
				if(option<2){
					option++;
				}
				break;
			default:
				break;
		}
			
		system("cls");
	}
		
	switch(option){
		case 1:
			return true;
			break;
		case 2:
			return false;
			break;
	}
}


void signUp(){
	
	account a,b;
	
	if(agreement()==false) return;
	
	// tao tai khoan
	signUp:
	printf("\n\t\t\t\t  ***DANG KY***\n\n");
	printf("\n\t\t Ten dang nhap:  ");
	scanf("%s",a.userName);
	
	printf("\n\t\t Mat khau:  ");
	scanf("%s",a.passWord);
	
	
	if( checkingAccount(a) == false ){
		printf("\n\t\t Ten dang nhap hoac mat khau khong hop le!\a");
		pause();
		goto signUp;
	}
	
	int code=2604;
	int xcode;
	// nhap ma bao mat
	code:
	printf("\n\t\t Ma bao mat:  ");
	scanf("%d",&xcode);
	if(xcode!=code){
		printf("\n\t\t Ma bao mat khong dung!\a");
		goto code;
	}
	
	// xac minh con nguoi
	if( imNotRobot()==false) return;
	sleep(1);
	
	FILE *f=fopen("account.txt","a+");
	if(f==NULL){
		printf("\n\t\t * Loi mo file account.txt!\a");
	}else {
		// kiem tra tai khoan vua tao da ton tai hay chua
		while(fscanf(f,"%s %s",b.userName,b.passWord)!=EOF){
			if(compare(a,b)==true){
				printf("\n\n\t\t Tai khoan da ton tai!\a");
				printf("\n\t\t Hay dang nhap hoac tao tai khoan khac!");
				pause();
				goto signUp;
			}
		}
		fprintf(f,"%-50s %-50s\n",a.userName,a.passWord);
		printf("\n\n\t\t Tao tai khoan thanh cong!\a");
		pause();
	}
	fclose(f);
}

bool logIn(){
	
	account a;
	
	// dang nhap
	logIn:
	printf("\n\t\t\t\t***DANG NHAP***\n\n");
	printf("\n\t\t Ten dang nhap:  ");
	scanf("%s",a.userName);
	printf("\n\t\t Mat khau:  ");
	scanf("%s",a.passWord);
	
	
	FILE *f2=fopen("account.txt","r");
	account b;
	if(f2==NULL){
		printf("\n\t\t ** Loi mo file account.txt!\a");
	} else{
		// kiem tra tai khoan vua nhap co chinh xac hay khong?
		while(fscanf(f2,"%s %s",b.userName,b.passWord) != EOF){
			if(compare(a,b)==true){
				if( !imNotRobot() ) {
					fclose(f2);
					return false;
				} else {
					printf("\n\n\t\t Dang nhap thanh cong!\a");
					fclose(f2);
					return true;
				}
			}
		}
	}
	
	fclose(f2);
	printf("\n\n\t\t Dang nhap that bai!\a");
	printf("\n\t\t Tai khoan hoac mat khau khong dung!");
	pause();
	goto logIn;
}
