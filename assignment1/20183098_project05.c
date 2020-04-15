#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FALSE 0
#define TRUE 1
//First in First out
//선입선출을 원칙으로 한다. 

//노드 구조체 선언
typedef struct Queue_Node{//typedefine, 구조체를 하나의 자료형으로 선언한다. 
    int data;           //값
    struct Queue_Node* link;  //노드 링크포인터
}QueueNode;

//큐 구조체 선언
typedef struct Linked_Queue{
    int elementNum;     // 현재 저장된 원소의 개수 
    QueueNode* headNode;
    QueueNode* tailNode;
}Queue;

//큐 생성 
Queue* newQueue(){
    Queue *rtnPtr = NULL;//포인터변수 선언
    rtnPtr = (Queue*)malloc(sizeof(Queue));//구조체 크기만큼 메모리 할당 
    if(rtnPtr != NULL){//메모리 할당 성공여부 확인
        memset(rtnPtr,0,sizeof(Queue));//메모리 공간 초기화 
    }
    else{
        printf("memory allocation failed");//실패 리턴 
        return NULL;
    }
    return rtnPtr;
}
int QueueEmpty(Queue* queuePtr){//큐가 비었는지 확인 
    int outPut = FALSE;
    if(queuePtr != NULL){
        if(queuePtr->elementNum==0){
            outPut = TRUE;
        }
    }
    return outPut;
}
//인큐함수 큐 노드 생성 큐가 공백일때 새로 추가되는 노드의 꼬리주소는 NULL값으로 지정하고 헤드노드와 꼬리노드를 새로운 노드의 헤드노드로 지정한다.
QueueNode* enQueue(Queue* queuePtr, QueueNode element){
    int outPut = FALSE;
    QueueNode* nodePtr = NULL;//추가될 노드 초기화 
    nodePtr = (QueueNode*)malloc(sizeof(QueueNode));//노드 메모리 할당
    if(nodePtr!=NULL){//메모리 할당 확인 
        nodePtr->data = element.data;//노드에 원소값 삽입 
        nodePtr->link = NULL;//새로 생성하는 노드의 다음 주소값은 NULL로 지정 
        if(QueueEmpty(queuePtr) == TRUE){//큐가 비어있다면 
            queuePtr->headNode = nodePtr;//큐의 헤드노드를 새로 생성되는 노드의 머리주소로 지정 
            queuePtr->tailNode = nodePtr;//'' '' 꼬리노드를 '' '' '' 머리주소로 지정 
        }
        else{//아니라면 
            queuePtr->tailNode->link = nodePtr;// 마지막 노드의 다꼬리주소로 새로 생성될 노드로 지정 
            queuePtr->tailNode = nodePtr;//큐의 마지막 노드로 지정 선입선출
        }
        queuePtr->elementNum++;
        outPut = TRUE;
        return outPut;
    }
    else printf("memory allocation failed");
    return outPut;
}
//디큐함수
QueueNode* deQueue(Queue* queuePtr){
    QueueNode* nodePtr = NULL;
    if(QueueEmpty(queuePtr) == FALSE){//큐안에 다른노드가 있는가?
        nodePtr = queuePtr->headNode;//선입선출이므로 제거될 노드(헤더노드)지정
        queuePtr ->headNode = queuePtr->headNode->link;// 다음노드를 헤더노드로 지정 
        nodePtr->link = NULL;//제거될 노드 링크를 NULL로 지정 
        queuePtr->elementNum--;//큐 카운트 감소 
		return printf("%d",nodePtr->data);
        free(nodePtr);
        if(QueueEmpty(queuePtr) == TRUE){//제거한 노드가 마지막일경우 
            queuePtr->tailNode = NULL;//꼬리주소를 null로 지정 
			printf("there is no element to delete");
        }
    }
	printf("there is no element to delete");
    return queuePtr;
}
//원소리턴 
void displayQueue(Queue* queuePtr){
    QueueNode* nodePtr;
    nodePtr = queuePtr->headNode;
    while(nodePtr!=NULL){
        printf("%d ",nodePtr->data);
        nodePtr = nodePtr->link;
    }
}
int main(void){
    Queue* queuePtr = NULL;
    QueueNode* nodePtr = NULL;
    queuePtr = newQueue();
    int state,element;
    char intention = NULL;
    QueueNode value;
    while(TRUE){
        printf("1: Insertion\n");
        printf("2: Deletion\n");
        printf("3: Display\n");
        printf("0: exit\n");
        printf("Select Option: ");
        scanf("%d",&state);
        if(state == 1){
			printf("Element : ");
            scanf("%d",&element);
			value.data = element;
            //  enQueue(queuePtr,value);
        	if(enQueue(queuePtr,value) == TRUE)printf("Succesfully Insert\n");
			//while(getchar()=='\n')break;
			//break;
			}
        else if(state == 2){
            printf("deleted data is: ");
			deQueue(queuePtr);
			printf("\n");            
        }
        else if(state == 3){
            displayQueue(queuePtr);
			printf("\n");            
        }
        else if(state == 0){
            break;
        }
    }
}