#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FALSE 0
#define TRUE 1
/*
리스트 구조체 안에 노드 구조체가 원소로써 연결리스트가 형성됨 
*/
//노드 구조체 선언
typedef struct Linked_Node{//typedefine, 구조체를 하나의 자료형으로 선언한다. 
    int data;           //값
    struct LinkNode* link;  //노드 링크포인터
}ListNode;

//리스트 구조체 선언
typedef struct Linked_List{
    int elementNum;     // 현재 저장된 원소의 개수 
    ListNode headerNode;// 헤더노드로써 노드 구조체를 하나 선언한다.  노드의 추가, 삭제를 간편하게 구현하기 위함
}List;

// 리스트 생성
List* newLinkedList(){
    List* ptr = NULL;//리스트구조체의 포인터 변수 초기화
    ptr = (List*)malloc(sizeof(List));//리스트 만큼의 메모리를 동적할당 하여 시작주소 반환
    if(ptr!=NULL){//ptr에 동적할당이 잘 되었는지 확인 
        memset(ptr,0,sizeof(List));//할당된 메모리를0으로 초기화 한다. 
        }
    else{
        printf("memory allocate fail");//malloc 함수가 메모리할당에 실패하면 NULL값을 리턴한다. 
        return NULL;
        }
}
//리스트 길이 리턴
int linkedListLength(List* listPtr){
    int outPut = 0;
    return outPut = listPtr->elementNum;//리스트 구조체 멤버 elementNum 노드개수 리턴 
}
// 노드추가 생성된 리스트의 첫주소에 저장 하고 위치지정 및 노드 데이터에 들어갈 값 지정 
ListNode* addNode(List* listPtr, int position, ListNode element){
    int outPut = FALSE;
    int i = 0;
    ListNode* preNodePtr = NULL; //이전노드주소
    ListNode* newNodePtr = NULL; //새노드주소
    if(position>=0 && position<=listPtr->elementNum){//포지션 값이 원소개수보다 같거나 작은지 판단 

        newNodePtr = (ListNode*)malloc(sizeof(ListNode));// 새노드 크기만큼 동적 메모리 할당 및 처음주소반환
        if(newNodePtr != NULL){ //메모리 할당이 잘 되었는지 확인 
            newNodePtr->data = element.data; // 메모리가 할당된 노드 구조체 포인터에서 멤버연산자로 data 변수에 접근.
            //함수에서 받은 원소 값(element)를 구조체 data에 대입 
            //*newNodePtr = element;// 노드 구조체에 
            newNodePtr->link = NULL;//다음노드 포인터를 NULL로 초기화 
            preNodePtr = &(listPtr->headerNode);// 이전노드 주소에 리스트 헤더노드주소 즉 처음으로 초기화
            for(i=0;i<position; i++){
                preNodePtr = preNodePtr->link;//position-1만큼 노드링크 이동
                //헤더노드 주소를 처음으로 루프를 1번 돌때마다 한 노드씩 지나간다(머리->꼬리(다음노드머리))
            }
            newNodePtr->link = preNodePtr->link;//삽입될 노드 꼬리주소->삽입되기 전 노드의 꼬리주소
            //그러니까 삽입될 노드의 오른쪽에 있는노드 주소를 삽입될 노드 꼬리링크로 연결 
            preNodePtr->link = newNodePtr;//이전노드 꼬리주소->삽입될 노드 노드 머리주소 
            listPtr->elementNum++;//생성 시 모든 멤버가 0으로 초기화 되므로 노드를 생성하면 원소 리스트안에 새노드(원소)
            //가 생가므로 +1
            outPut = TRUE;
        }
        else{
            printf("memory allocation failed");
            return outPut;
        }
    }
    else{
        printf("position value is unaviliable");
        return outPut;
    }
    return outPut;
}
ListNode* rtnElement(List* listPtr, int position){
    ListNode* returnPtr = NULL;
    ListNode* nodePtr = NULL;
    if(position >=0 && position < listPtr->elementNum){
        nodePtr = &(listPtr->headerNode);//헤더노드의 주소를 저장(처음)
        for(int i =0;i<=position;i++){
            nodePtr = nodePtr->link;//position 만큼의 노드로 이동 
        }
        returnPtr = nodePtr;//position 위치에 있는 노드 포인터 리턴
    }
    return returnPtr;
}
ListNode* deleteNode(List* listPtr, int position){
    int outPut = FALSE;
    int nodeCount=0;
    ListNode* deleteNode = NULL;
    ListNode* nodePtr = NULL;
    nodeCount = linkedListLength(listPtr);//삭제하기 전 노드갯수 측정
    if(position>=0 && position<nodeCount){//포지션 값이 노드개수보다 같거나 작은지 판단 
        nodePtr = &(listPtr->headerNode);//헤더노드로 초기화
        for(int i=0;i<position-1;i++){
            nodePtr = nodePtr->link;//삭제할 노드의 바로 앞(왼쪽)까지 이동 
        }
        deleteNode = nodePtr->link;//삭제할 노드의 바로 앞 노드 꼬리주소(삭제할 노드의 머리주소) 저장 
        nodePtr->link = deleteNode->link;//삭제할 노드의 바로 앞 노드 꼬리주소(삭제할 노드 머리주소) 
        //즉 바로 앞 노드의 꼬리주소가  삭제할 노드의 꼬리주소(왼쪽노드 머리주소) 가 된다. 
        //이렇게 됨으로 써 삭제노드는 리스트 링크가 끊긴다. 
        free(deleteNode);//끊긴노드 메모리 해제
        listPtr->elementNum--;//리스트 노드크기 감소 
        outPut = TRUE;
    }
    else{
        printf("position value is unaviliable");
        return outPut;
    }
}

int main(void){

    List* listPtr= newLinkedList();//리스트 생성
    ListNode node;//원소를 임시저장할 구조체 노드 선언 링크 x 
    
    int elementNum,elementValue,choiceFunc,elementIndex,newValue;
    printf("element in List: ");
    scanf("%d",&elementNum);
    for(int i=0;i<elementNum;i++){
        scanf("%d",&elementValue);
        node.data = elementValue;//입력받은 값을 앞서 선언한 노드구조체의 데이터 멤버에 저장 
        addNode(listPtr,i,node);//노드생성함수호출 및 원소저장 
    }
    printf("Stored data in array: ");
    for(int j = 0;j<elementNum;j++) printf("%d ", rtnElement(listPtr,j)->data);
    printf("\n");
    printf("1.Insertion  2.Deletion");
    scanf("%d",&choiceFunc);
    if(choiceFunc==1){//기능선택
        printf("Enter position for element: ");
        scanf("%d",&elementIndex);
        printf("Enter new element: ");
        scanf("%d",&newValue);
        node.data = newValue;
        addNode(listPtr,elementIndex-1,node);
        printf("Stored data in array: ");
        for(int k = 0;k<elementNum+1;k++) printf("%d ", rtnElement(listPtr,k)->data);
        printf("\n");
    }
    else if(choiceFunc==2){
        printf("Enter position for element: ");
        scanf("%d",&elementIndex);
        deleteNode(listPtr,elementIndex);
        printf("Stored data in array: ");
        for(int m = 0;m<elementNum-1;m++) printf("%d ", rtnElement(listPtr,m)->data);
        printf("\n");
    }
    else printf("ERROR");
}