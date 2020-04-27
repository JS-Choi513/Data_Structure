/*AVL 트리는 Adelson-Velskii 와 Landis에 의해 제안된 트리이다. 
핵심개념은 왼쪽 서브트리와 오른쪽 서브트리의 높이차이를 1이하로 유지한다는 것이다. |H(l) - H(r)| <=1*/
/*균형인수 BF(Balance Factor)는 왼쪽 서브트리의 높이에서 오른쪽 서브트리의 높이를 뺀 값을 말한다.*/
/* BF = H(l) - H(r) AVL 이진트리에서는 앞서 제약조건에 의해 균형인수 BF  의 값이 -1,0,1 중 하나가 되어야 한다.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define VALUE_SIZE 100 //저장 자료의 길이 정의   
#define TRUE 1
#define FALSE 0


typedef struct AVLtreeNodeDataType{
    int key; // 검색 키
    char value[VALUE_SIZE + 1]; // 데이터 
}AVLtreeNodeData;

typedef struct AVLtreeNodeType{
    AVLtreeNodeData data;
    int balance; // 균형인수 저장 
    int height; // 현재높이 저장
    struct AVLtreeNodeType *leftChildPtr;//왼쪽자식노드
    struct AVLtreeNodeType *rightChildPtr;// 오른쪽 자식노드 
}AVLNode;

typedef struct Stack_Node{//typedefine, 구조체를 하나의 자료형으로 선언한다. 
    struct AVLtreeNodeType* data;           //값
    struct Stack_Node* link;  //노드 링크포인터
}StackNode;

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
    //    return outPut;
    }
    return outPut;
}
//탑노드 제거 
StackNode* popStack(Stack* stackPtr){
    /*int outPut = FALSE;
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
    */
   StackNode* returnPtr = NULL;
   if(stackPtr != NULL){
       if(isStackEmpty(stackPtr) == FALSE){
           returnPtr = stackPtr->topNodePtr;
           stackPtr->topNodePtr = returnPtr->link;
           returnPtr->link = NULL;
           stackPtr->elementNum--;
       }
   }
   return returnPtr;
}

StackNode* peekStack(Stack* pStack)
{
	StackNode* returnPtr = NULL;
	if (pStack != NULL) {
		if (isStackEmpty(pStack) == FALSE) {
			returnPtr = pStack->topNodePtr;
		}
	}

	return returnPtr;
}

void deleteStack(Stack* stackPtr)
{
	StackNode *nodePtr = NULL;
	StackNode *delNodePtr = NULL;

	if (stackPtr != NULL) {
		nodePtr = stackPtr->topNodePtr;
		while(nodePtr != NULL) {
			delNodePtr = nodePtr;
			nodePtr = nodePtr->link;
			free(delNodePtr);
		}
		free(stackPtr);
	}	
}

int isStackFull(Stack* pStack)
{
	int outPut = FALSE;
	return outPut;
}

int isStackEmpty(Stack* pStack)
{
	int outPut = FALSE;

	if (pStack != NULL) {
		if (pStack->elementNum == 0) {
			outPut = TRUE;
		}
	}

	return outPut;
}
/////////////////////////////////////////////////////////// AVL 트리 구조체 
typedef struct AVLtreeType{
    AVLNode *rootNodePtr;//루트노드 포인터 
}AVLTree;

// 스택을 활용한 노드삽입, 제거, 피크 
int pushAVLNode(Stack* stackPtr, AVLNode* data){
    StackNode node = {0,};
    node.data = data;
    return pushStack(stackPtr, node);
}

AVLNode *popAVLNode(Stack* stackPtr){
    AVLNode *returnPtr = NULL;
    if(isStackEmpty(stackPtr) == FALSE){//삭제할 스택이 존재하는지 확인 
        StackNode* nodePtr = popStack(stackPtr);//스택POP
        if(nodePtr != NULL){
            returnPtr = nodePtr->data;
            free(nodePtr);//메모리 해제 
        }
    }
	return returnPtr;
}

AVLNode *peekAVLTreeNode(Stack* stackPtr){
    AVLNode* returnPtr = NULL;
    if(isStackEmpty(stackPtr) == FALSE){
        StackNode* nodePtr = peekStack(stackPtr);
        if(nodePtr != NULL){
            returnPtr = nodePtr->data;
        }
    }
    return returnPtr;
}
//트리 밸런싱, 회전연산 
void refreshHeightBalanceAVLTree(AVLNode* nodePtr){
    int leftHeight = 0;
    int rightHeight = 0;
    if(nodePtr != NULL){
        if(nodePtr->leftChildPtr != NULL){
            leftHeight = nodePtr->leftChildPtr->height;
        }
        if(nodePtr->rightChildPtr != NULL){
            rightHeight = nodePtr->rightChildPtr->height;
        }
        if(leftHeight > rightHeight){
            nodePtr->height = leftHeight + 1;
        }
        else{
            nodePtr->height = rightHeight + 1;
        }
        nodePtr->balance = leftHeight - rightHeight;
    }
}

AVLNode *rotate_LL(AVLNode *parentNodePtr){
    AVLNode *leftNodePtr = NULL;

    if(parentNodePtr != NULL){
        leftNodePtr = parentNodePtr->leftChildPtr;
        parentNodePtr->leftChildPtr = leftNodePtr->rightChildPtr;
        leftNodePtr->rightChildPtr = parentNodePtr;

        refreshHeightBalanceAVLTree(parentNodePtr);
        refreshHeightBalanceAVLTree(leftNodePtr);
    }
    return leftNodePtr;
}

AVLNode *rotate_RR(AVLNode *parentNodePtr){
    AVLNode *rightNodePtr = NULL;
    if(parentNodePtr != NULL){
        rightNodePtr = parentNodePtr->rightChildPtr;
        parentNodePtr->rightChildPtr = rightNodePtr->leftChildPtr;
        rightNodePtr->leftChildPtr = parentNodePtr;
        rightNodePtr->leftChildPtr = parentNodePtr;

        refreshHeightBalanceAVLTree(parentNodePtr);
        refreshHeightBalanceAVLTree(rightNodePtr);

    }
    return rightNodePtr;
}

AVLNode *rotate_LR(AVLNode *parentNodePtr){
    AVLNode *returnPtr = NULL;
    AVLNode *leftNodePtr = NULL;

    if(parentNodePtr != NULL){
        leftNodePtr = parentNodePtr->leftChildPtr;
        parentNodePtr->leftChildPtr = rotate_RR(leftNodePtr);
        returnPtr - rotate_LL(parentNodePtr);
    }
    return returnPtr;
}

AVLNode *rotate_RL(AVLNode *parentNodePtr){
    AVLNode *returnPtr = NULL;
    AVLNode *rightNodePtr = NULL;

    if(parentNodePtr !=NULL){
        rightNodePtr = parentNodePtr->rightChildPtr;
        parentNodePtr->rightChildPtr = rotate_LL(rightNodePtr);
        returnPtr = rotate_RR(parentNodePtr);
    }
    return returnPtr;
}





///새 트리 생성
AVLTree* newAVLTree(){
    AVLTree *returnPtr = NULL;
    returnPtr = (AVLTree*)malloc(sizeof(AVLTree)); //  AVL트리 메모리 할당
    if(returnPtr != NULL){
        memset(returnPtr,0,sizeof(AVLTree));//성공여부 확인 및 메모리 초기화
    }
    else{
        printf("memory allocation fail");
    }
    return returnPtr;
}

void balacnAVLTree(AVLTree* aVLTreePtr, Stack* stackPtr){
    AVLNode* parentNodePtr = NULL;
    AVLNode* nodePtr = NULL;
    AVLNode* childNodePtr = NULL;
    AVLNode* newNodePtr = NULL;

    if(aVLTreePtr == NULL || stackPtr == NULL){
        return;
    }

    while(isStackEmpty(stackPtr) == FALSE){
        nodePtr = popAVLNode(stackPtr);
        if(nodePtr !=NULL){
            refreshHeightBalanceAVLTree(nodePtr);
            if(nodePtr->balance >= -1 && nodePtr->balance <=1){
                continue;
            }
            if(nodePtr->balance > 1){
                childNodePtr = nodePtr->leftChildPtr;
                if(childNodePtr->balance > 0){
                    newNodePtr - rotate_LL(nodePtr);
                }
                else{
                    newNodePtr = rotate_LR(nodePtr);
                }
            }
            else if(nodePtr->balance < -1){
                childNodePtr = nodePtr->rightChildPtr;
                if(childNodePtr->balance < 0){
                    newNodePtr = rotate_RR(nodePtr);
                }
                else{
                    newNodePtr = rotate_RL(nodePtr);
                }
            }
            parentNodePtr = peekAVLTreeNode(stackPtr);
            if(parentNodePtr != NULL){
                if(parentNodePtr->leftChildPtr == nodePtr){
                    parentNodePtr->leftChildPtr = newNodePtr;
                }
                else{
                    parentNodePtr->rightChildPtr = newNodePtr;
                }
            }
            else{
                aVLTreePtr->rootNodePtr = newNodePtr;
            }
        }
    }
}

int addNodeAVL(AVLTree* aVLTreePtr, AVLtreeNodeData element){
    int outPut = TRUE;
    AVLNode* parentNodePtr = NULL;//루트노드의 포인터를 저장할 포인터 변수 
    AVLNode* newNodePtr = NULL; // 삽입할 노드의 포인터 변수
    Stack* stackPtr = NULL;//스택생성을 위한  포인터 변수 

    if(aVLTreePtr == NULL){
        outPut = FALSE;
        return outPut;
    }

    stackPtr = newStack();//스택생성
    if(stackPtr == NULL){
        outPut = FALSE;
        return outPut;
    }

    parentNodePtr = aVLTreePtr->rootNodePtr;//부모노드 포인터가 루트노드 포인터를 가리킴 
    while(parentNodePtr != NULL){//부모노드 포인터가 NULL 이면 루프 중단
        pushAVLNode(stackPtr, parentNodePtr);//부모노드를 포인터로 가지는 스택 삽입 
        if(element.key == parentNodePtr->data.key){//추가할 노드의 키값이 루트노드의 키값과 같은가?
            //printf("There is no removable node");
            outPut = FALSE;
            return outPut;
        }
        // 추가할 노드의 키값이 부모노드 키값이 루트노드 키값보다 작은가?
        else if(element.key < parentNodePtr->data.key){
            if(parentNodePtr->leftChildPtr == NULL){//루트노드의 왼쪽 자식노드가 리프노드인가?
                break;
            }
            else{//아니면 루트노드 주소를 왼쪽자식노드 주로소 변경한다. 
                parentNodePtr = parentNodePtr->leftChildPtr;//왼쪽 자식노드로 이동 
            } 
        }
        else{
            if(parentNodePtr->rightChildPtr == NULL){//루트노드의 왼쪽 자식노드가 리프노드인가?
                break;
            }
            else{
                parentNodePtr = parentNodePtr->rightChildPtr;//오른쪽 자식노드로 이동 
            }
        }
    }

    newNodePtr = (AVLNode*)malloc(sizeof(AVLNode));//삽입할 노드의 메모리 할당 
    if(newNodePtr != NULL){
        memset(newNodePtr,0,sizeof(AVLNode));//0으로 초기화
        newNodePtr->data = element;//노드에 데이터 삽입 
        newNodePtr->height = 1;//높이를 1로 지정
    }
    else{
        printf("memory allocation fail");
		deleteStack(stackPtr);

        return FALSE;
    }
    if(parentNodePtr == NULL){
        aVLTreePtr->rootNodePtr = newNodePtr;//루트노드
    }
    else{
        if(newNodePtr->data.key < parentNodePtr->data.key){
            parentNodePtr->leftChildPtr = newNodePtr;
        }
        else{
            parentNodePtr->rightChildPtr = newNodePtr;
        }
    }
    outPut = TRUE;
    balacnAVLTree(aVLTreePtr, stackPtr);
    deleteStack(stackPtr);
    return outPut;
//삽입 후 트리 밸런스 수정
}
//트리 밸런스 조정

int deleteAVLNode(AVLTree* aVLTreePtr, int key){
    int outPut = TRUE;
    AVLNode* deleteNodePtr = NULL;
    AVLNode* parentNodePtr = NULL;
    AVLNode* predecessorPtr = NULL;
    AVLNode* successorPtr = NULL;
    AVLNode* childPtr = NULL;
    Stack* mainStackPtr = NULL;
    Stack* subStackPtr = NULL;

    if(aVLTreePtr == NULL){
        outPut - FALSE;
        return outPut;
    }
    mainStackPtr = newStack();
    subStackPtr = newStack();
    if(mainStackPtr == NULL || subStackPtr == NULL){
        outPut = FALSE;
        return outPut;
    }

    parentNodePtr = NULL;
    deleteNodePtr = aVLTreePtr->rootNodePtr;
    while(deleteNodePtr != NULL){
        if(key == deleteNodePtr->data.key){
            break;
        }
        parentNodePtr = deleteNodePtr;
        pushAVLNode(mainStackPtr, parentNodePtr);

        if(key < deleteNodePtr->data.key){
            deleteNodePtr = deleteNodePtr->leftChildPtr;
        }
        else{
            deleteNodePtr = deleteNodePtr->rightChildPtr;
        }
    }
    if(deleteNodePtr == NULL){
        printf("There is no removable Node");
        outPut = FALSE;
        return outPut;
    }
    if(deleteNodePtr->leftChildPtr == NULL && deleteNodePtr->rightChildPtr == NULL){
        if(parentNodePtr != NULL){
            if(parentNodePtr->leftChildPtr = deleteNodePtr){
                parentNodePtr->leftChildPtr = NULL;
            }
            else {
                parentNodePtr->rightChildPtr = NULL;
            }
        }
        else{
            aVLTreePtr->rootNodePtr = NULL;
        }
    }
    else if(deleteNodePtr->leftChildPtr != NULL && deleteNodePtr->rightChildPtr != NULL){
        predecessorPtr = NULL;
        successorPtr = deleteNodePtr->leftChildPtr;
        pushAVLNode(subStackPtr, successorPtr);
        
        while(successorPtr->rightChildPtr != NULL){
            predecessorPtr = successorPtr;
            successorPtr = successorPtr->rightChildPtr;
            pushAVLNode(subStackPtr, successorPtr);
        }
        pushAVLNode(mainStackPtr, popAVLNode(subStackPtr));
        
        if(predecessorPtr != NULL){
            predecessorPtr->rightChildPtr = successorPtr->leftChildPtr;
            successorPtr->leftChildPtr = deleteNodePtr->leftChildPtr;
            pushAVLNode(subStackPtr, predecessorPtr->rightChildPtr);
        }
        successorPtr->rightChildPtr = deleteNodePtr->rightChildPtr;

        if(parentNodePtr != NULL){
            if(parentNodePtr->leftChildPtr == deleteNodePtr){
                parentNodePtr->leftChildPtr = successorPtr;
            }
            else{
                parentNodePtr->rightChildPtr = successorPtr;
            }
        }
        else{
            aVLTreePtr->rootNodePtr = successorPtr;
        }
    }
    else{
        if(deleteNodePtr->leftChildPtr != NULL){
            childPtr = deleteNodePtr->leftChildPtr;
        }
        else{
            childPtr = deleteNodePtr->rightChildPtr;
        }

        if(parentNodePtr != NULL){
            if(parentNodePtr->leftChildPtr == deleteNodePtr){
                parentNodePtr->leftChildPtr = childPtr;
            }
            else{
                parentNodePtr->rightChildPtr = childPtr;
            }
        }
        else{
            aVLTreePtr->rootNodePtr = childPtr;
        }
    }
    free(deleteNodePtr);
    balacnAVLTree(aVLTreePtr, subStackPtr);
    balacnAVLTree(aVLTreePtr, mainStackPtr);
    deleteStack(mainStackPtr);
    deleteStack(subStackPtr);

    return outPut;

}
//트리 출력 
void showAVLTree(AVLTree *treePtr)
{
	showAVLTreeIntrenal(treePtr->rootNodePtr, 0, ' ');
}

void showAVLTreeIntrenal(AVLNode *treeNodePtr, int level, char type){
	
   // for(int i=0;i<level;i++){
    //    printf("   ");
   // }
	if(treeNodePtr != NULL){
			//"-[%i,%i,%c],%i/%s\n"
    printf("%i\n", /*treeNodePtr->height, treeNodePtr->balance, type,*/ treeNodePtr->data.key/*, treeNodePtr->data.value*/);
    showAVLTreeIntrenal(treeNodePtr->leftChildPtr, level + 1, 'L');
    showAVLTreeIntrenal(treeNodePtr->rightChildPtr, level + 1, 'R');
	}
	else{
				printf("NULL\n");

	}

}


int main(void){
    AVLTree *newAVLTreePtr = NULL;
    AVLNode *travelsalPtr = NULL;
    int key = 0;
    int nodeNumber = 0;
	AVLtreeNodeData a = {9,"1"};
	AVLtreeNodeData b = {1,"2"};
	AVLtreeNodeData c = {0,"2"};
	AVLtreeNodeData d = {-1,"2"};
		newAVLTreePtr = newAVLTree();


	addNodeAVL(newAVLTreePtr,a);
		showAVLTree(newAVLTreePtr);

	addNodeAVL(newAVLTreePtr,b);
		showAVLTree(newAVLTreePtr);

	addNodeAVL(newAVLTreePtr,c);
		showAVLTree(newAVLTreePtr);

	addNodeAVL(newAVLTreePtr,d);
	showAVLTree(newAVLTreePtr);

//	AVLtreeNodeData b = {5,"2"};
	//addNodeAVL(newAVLTreePtr,b);


	
	//addNodeAVL(newAVLTreePtr,ab);
    //printf("Insert input node number under 100 : ");
    //scanf("%d",&nodeNumber);
    //AVLtreeNodeData dataarray[nodeNumber];
    //printf("Insert node to AVL tree : ");
    //for(int i=0;i<nodeNumber;i++){
    //    scanf("%d",&dataarray[i].key);
   // }
   //for(int i=0;i<nodeNumber;i++){
   //    addNodeAVL(newAVLTreePtr,dataarray[i]);
   // }
  //  showAVLTree(newAVLTreePtr);
	//printf("%d",)
    
}


