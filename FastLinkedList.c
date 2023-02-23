#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
					// FastLinkedList Algortihm   -   Muhammed Ali Lale
	
typedef struct node{
	int value;
	struct node *next;
	struct node *down; //pointer of child nodes
}NODE;
NODE **head; //Dynamic array that holds pointers

NODE* createNode(); 
void addNode(NODE*,int); //Adds the node that come from createnode() to end of the linked list
void printList();	//to print the Linked List Tree
void chooseRandom(int*, int); //chooses random and unique values and hold them in the given array
void sortArray(int*,int); //sorts the given array 
int setList(int,int); //Adds parent nodes to list and creates FastLinkedList tree
void MENU(int,int); 	
void search(int); //to search an element in the list
int deleteElement(int,int); //to delete and element from the list
void addElement(int); //to add a new element to the list

int main(){
	int *array; //it holds the inputs
	int i,size,MAX;
	printf(" Please enter the size of the list: ");
	scanf("%d",&size);	//size of the list
	array = (int*)malloc(size*sizeof(int)); //create a dynamic array
	for(i=0;i<size;i++){
		printf("Element %d: ",i+1);	//List elements
		scanf("%d",&array[i]);
	}
	sortArray(array,size);	//The linked list elements should be sorted
	head = (NODE**)malloc(2*sizeof(NODE*)); //array keeps the linked lists
	if(head==NULL){
		printf(	"Not enough space!");
		exit(1);
	}

	head[0]=NULL;	//head[0] keeps the base linked list
	for(i=0; i<size; i++){
		addNode(createNode(),0);
	}
	NODE *p = head[0];
	for(i=0; i<size; i++){	//to assign the inputs to the linked list
		p->value=array[i];
		p->down = NULL;	
		p = p->next;
	}	

	int maxLevel=setList(size,1); //setList() function returns the height of the fast linked list tree
	printList(maxLevel);	//prints the lists to the screen
	MENU(maxLevel,size);	//maxLevel and size of the list will be used at MENU functions
	return 0;
}

NODE* createNode(){
	NODE *p; //temp node
	p = (NODE*)malloc(sizeof(NODE));
	if(p == NULL){
		printf("Not enough space!");
		exit(1);
	}
	p->next=NULL;
	return p;	
}

void addNode(NODE* element,int level){ //add the node that come from createNode() to and of the linked list
	NODE *p;
	if(head[level]==NULL){	//
		head[level] = element;
		return;
	}
	for(p=head[level]; p->next!=NULL; p=p->next); //goes to end of the linked list
	p->next = element;
}

void printList(int maxLevel){
	NODE *first;	//it will keep the head of the first level list
	int i;
	printf("\n\nLIST:\t");
	NODE *q;
	for(i=maxLevel-1;i>=0;i--){ //print the lists from maximum level to level 0.
		q=head[i];
		for(first=head[0]; first!=NULL; first=first->next){
			if(q!=NULL && q->value==first->value){ //column aligment
				printf("%2d -",q->value);
				q=q->next;
			}
			else{
				printf("----"); //fill the blanks
			}
		}
		printf("\n\t");
	}
}

void chooseRandom(int array[], int size){
	srand(time(NULL));
	int i,j,randomNumber,flag;
	array[0]=rand()%size; //choose first random number
	int n=(size+1)/2;
	for(i=1; i<n; i++){
		flag=1;
		randomNumber=rand()%size; //choose random numbers
		for(j=0;j<i;j++){
			if(array[j]==randomNumber){	//if the chosen number is not used before
				flag=0;
			}
		}
		if(flag==1){
			array[i]=randomNumber;	//then assign 
		}
		else{
			i--;	//if it was chosen i--; to chose again
		}
	}
}

void sortArray(int *array, int n){
	int i,j,tmp;
	for(i=0; i<n-1; i++){
		for(j=0; j<n-1-i; j++){
			if (array[j+1] < array[j]){
				tmp = array[j];
				array[j] = array[j+1];
				array[j+1] = tmp;
			}
		}
	}
}

int setList(int size,int m){
	int i,j;
	int n=(size+1)/2;
	head[m]=NULL;
	for(j=0;j<n;j++){
		addNode(createNode(),m); //create new linked list
	}
	int *array;
	array = (int*)malloc(n*sizeof(int));
	chooseRandom(array,size);
	sortArray(array,n);

// the elements of random numbers array will show the index of linked list
// when it is equal to the counter make the assigments
	i=0;
	int count=0;
	NODE *p;
	NODE *q=head[m];
	for(p=head[m-1];p!=NULL; p=p->next){
		if(count==array[i]){	
			q->down = p;
			q->value = p->value;
			q = q->next;
			i++;
		}
		count++;
	}
	if(n==1){ //end of the recursive function
		return m+1;//return the height of the lists
	}
	head=realloc(head,(m+2)*sizeof(NODE*)); 
	setList(n,m+1);	//call the function until the end
}

void MENU(int maxLevel,int size){
	printf("\n\n\t\t***MENU***\t\n");
	printf(" 1. Search a parameter at the list. \n");
	printf(" 2. Add a new element to the list. \n");
	printf(" 3. Delete an element form the list. \n");
	printf(" 4. Exit \n");
	printf("\n   Please choose your option: ");
	int opt;
	scanf("%d",&opt);
	
	switch(opt){
		case 1:
			search(maxLevel);
			printf("\n Press any key to continue...");
			getch();
			system("CLS");
			printList(maxLevel);
			MENU(maxLevel,size);
			break;
		case 2:
			addElement(maxLevel);
			head = (NODE**)realloc(head,2*sizeof(NODE*)); //create new list
			size++;
			maxLevel=setList(size,1);
			printf("\n Press any key to continue...");
			getch();
			system("CLS");
			printList(maxLevel);
			MENU(maxLevel,size);
			break;
		case 3:
			if(deleteElement(maxLevel,size)){ //if the element deleted
				head = (NODE**)realloc(head,2*sizeof(NODE*)); //create new list
				size--;
				maxLevel=setList(size,1);
			}
			printf("\n Press any key to continue...");
			getch();
			system("CLS");
			printList(maxLevel);
			MENU(maxLevel,size);
			break;
		case 4:
			exit(0);
		default:
			system("CLS");
			printList(maxLevel);
			printf("\n\n Please make your choise between 1-4! :");
			MENU(maxLevel,size);
	}
}

void search(int LEVEL){
	NODE *p;
	int par;
	p=head[--LEVEL];
	printf("\n Please enter the parameter you want to find: ");
	scanf("%d", &par);
	while(p->value!=par && (p->next!=NULL || LEVEL!=0)){ //ends if the paramter has found or reachs the end of the lists
		if(p->value > par){	
			if(LEVEL==0){
				printf("\n %d does not exist",par);
				return;
			}
			p=head[--LEVEL];
		}
		else if(p->next==NULL || p->next->value>par){
			if(LEVEL==0){
				printf("\n %d does not exist",par);
				return;
			}
			LEVEL--;
			p=p->down;
		}		
		else{
			p=p->next;
		}
	}

	if(p->value==par){
		printf("\n %d has found at Level %d",par,LEVEL+1);
	}
	else{
		printf("\n %d does not exist",par);
	}
}

int deleteElement(int maxLevel,int size){
	int par;
	printf("\n Please enter the parameter you want to delete: ");
	scanf("%d",&par);
	NODE *temp, *delNode;
	if(head[0]->value==par){
		delNode=head[0];	
		head[0]=head[0]->next;
		free(delNode);
	}
	else{	//if the parameter doesn't exist
		for(temp=head[0];  temp->next!=NULL && temp->next->value!=par; temp=temp->next);
			if(temp->next==NULL){
				printf("\n %d does not exist! ",par);
				return 0; //not deleted
			}	
		delNode=temp->next;	
		temp->next=temp->next->next;
		free(delNode);
	}
	//free all the parent nodes
	int i;
	NODE *p,*del;
	for(i=maxLevel-2; i>0; i--){
		p=head[i]->next;
		while(p->next!=NULL){
			del=p;
			p=p->next;
			free(del);
		}
		free(p);
	}
	for(i=1;i<maxLevel;i++){
		free(head[i]);
	}
	
	return 1; //if an element deleted
}
	
void addElement(int maxLevel){
	int par;
	printf("\n Please enter the parameter you want to add: ");
	scanf("%d",&par);
	NODE *temp, *addNode;
	for(temp=head[0];  temp->next!=NULL && temp->next->value<par; temp=temp->next);
	addNode=(NODE*)malloc(sizeof(NODE));
	//add new node
	addNode->next=temp->next;
	temp->next=addNode;
	temp->next->value=par;
	//free all parent nodes
	int i;
	NODE *p,*del;
	for(i=maxLevel-2; i>0; i--){
		p=head[i]->next;
		while(p->next!=NULL){
			del=p;
			p=p->next;
			free(del);
		}
		free(p);
	}
	for(i=1;i<maxLevel;i++){
		free(head[i]);
	}
}	
	
