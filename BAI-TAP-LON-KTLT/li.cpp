#include"li.h"

node* makeNode(student st){
	// khoi tao node moi, cap phat vung nho nho node moi
	node* newNode=(node*)malloc(sizeof(node));
	// gan du lieu cho node moi va tam thoi cho phan lien ket = NULL
	newNode->data=st;
	newNode->next=NULL;
	return newNode;
}

void creatList(list* l){
	// tao list, node head quan li dslk
	l->head=NULL;
}

void pushBack(list*l, node* newNode){
	
	// ham them node vao cuoi dslk
	
	// truong hop dslk trong, chua co node nao trong danh sach
	if(l->head==NULL){
		l->head=newNode;
		return;
	}
	// truong hop dslk da co phan tu 
	else{
		
		node* temp=l->head;
		while(temp->next!=NULL){
			temp=temp->next;
		}
		
		temp->next=newNode;
	}
}


void deleteNode(list* l, node* oldNode){
	
	// ham xoa node trong dslk
	
	// tao node tam thoi de quan ly dslk
	node* temp = l->head;
	// tao node lui de luu vi tri cua node truoc 
    node* prev = NULL;

	// truong hop dslk chi co mot node
	if (prev == NULL) {
                
        l->head = temp->next;
        
    }
    // truong hop dslk co nhieu hon 1 node
	else {
        
        prev->next = temp->next;
        
    }
    
}
