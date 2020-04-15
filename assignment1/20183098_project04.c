#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FALSE 0
#define TRUE 1
//Last in First out
//노드 구조체 선언
typedef struct Stack_Node{//typedefine, 구조체를 하나의 자료형으로 선언한다. 
    int data;           //값
    struct Stack_Node* link;  //노드 링크포인터
}StackNode;

//스택 구조체 선언
typedef struct Linked_Stack{
    int elementNum;     // 현재 저장된 원소의 개수 
    StackNode* topNodePtr;// 헤더노드로써 노드 구조체를 하나 선언한다.  노드의 추가, 삭제를 간편하게 구현하기 위함
}Stack;

Stack* newStack(){
    Stack* returnPtr = NULL;
    returnPtr = (Stack*)malloc(sizeof(Stack));
    if(returnPtr!=NULL){
        memset(returnPtr,0,sizeof(Stack));
    }
    else{
        printf("memory allocation failed");
        return NULL;
    } 
    return returnPtr;
}

StackNode* pushStack(Stack* stackPtr, StackNode element){
    int outPut = FALSE;
    StackNode* newNodePtr = NULL;
    newNodePtr = (StackNode*)malloc(sizeof(StackNode));
    if(newNodePtr!=NULL){
        
        memset(newNodePtr,0,sizeof(StackNode));
        *newNodePtr = element;
        newNodePtr->link = stackPtr->topNodePtr;// 추가되는 노드의 꼬리주소를 탑 노드의 머리주소로 지정 
        //즉, 탑노드가 된다. 
		stackPtr->topNodePtr = newNodePtr;
        stackPtr->elementNum++;//원소개수 추가 
        outPut = TRUE;
    }
    else{
        printf("memory allocation failed");
        return outPut;
    }
    return outPut;
}
//탑노드 제거 
StackNode* popStack(Stack* stackPtr){
    int outPut = FALSE;
    StackNode* deleteNodePtr = NULL;
    if(stackPtr->elementNum>0){
    deleteNodePtr = stackPtr->topNodePtr;//삭제될 노드의 머리주소를 헤더노드의 꼬리주소로 변경 
    stackPtr -> topNodePtr = deleteNodePtr->link;//헤더노드의 꼬리주소를 삭제될 노드의 꼬리주소(즉 다음칸 머리로) 연결
    deleteNodePtr->link = NULL; //삭제될 노드 링크주소 삭제
    stackPtr->elementNum--;//구조체 원소개수 감소 
	return printf("%d\n",deleteNodePtr->data);
    free(deleteNodePtr);
    outPut = TRUE;
    }
    else {
        printf("ERROR element is not exist");
        return outPut;
    }
}

void displayStack(Stack* stackPtr){
    StackNode* nodePtr = NULL;
    int i;
    nodePtr = stackPtr->topNodePtr;
    while(nodePtr != NULL){
        printf("%d\n",nodePtr->data);
        nodePtr = nodePtr->link;
    }
}

int main(void){
    Stack* stackPtr = NULL;
    StackNode* nodePtr = NULL;
    stackPtr = newStack();
    int state,element;
    char intention = NULL;
    StackNode value;
    while(state < 4){
        printf("1: push\n");
        printf("2: pop\n");
        printf("3: display\n");
        printf("4: exit\n");
        printf("enter your choice: ");
        scanf("%d",&state);
        while(state == 1){
			printf("Enter element in stack: ");
            scanf("%d",&element);
			value.data = element;
            pushStack(stackPtr,value);
			while(getchar()=='\n')break;
			printf("Pushed an element (Y/N): ");
			scanf("%c",&intention);
			if(intention=='n'){
				  break;
			}
        }
        if(state == 2){		
            printf("deleted data is: ");
			popStack(stackPtr);           
        }
        else if(state == 3){
            displayStack(stackPtr);
			printf("\n");           
        }
        else if(state == 4){
            break;
        }
    }
}