//
//  Linked.c
//
//  Simple Linked List
//  Created by 김용성 on 2015. 1. 9..
//

#include <stdio.h>
#include <stdlib.h>

//노드 구조체 선언
typedef struct Node{
    int data;           //값
    struct Node* next;  //다음노드 포인터
}Node;

//새로운 노드 생성
Node* newNode(int data){
    Node* node = (Node*)malloc(sizeof(Node));  //메모리에 동적할당을 받는다.
    node->data = data;                         //노드에 매개변수로 넘어온 값을 추가한다.
    node->next = NULL;                         //현재는 노드만 생성하는것 이기때문에 다음노드의 주소값은 NULL이다.
    
    return node;                               //새로생성한 노드의 주소값을 리턴해준다.
}

//리스트 사이즈 리턴
int getListSize(Node* head){
    int count = 0;                  //노드의 갯수를 표현하는 변수
    
    if(head == NULL){               //헤드가 NULL이면 노드가 1개도 없는것
        return 0;                   //0개를 리턴한다
    }else{                          //노드가 1개 이상 존재한다고 하면
        while(head->next != NULL){  //반복문을 돌려서 tail이 나올때까지 (노드에서 다음노드 주소값이 NULL이면 해당노드는 tail이다.)
            count++;                //갯수를 1씩 증가
            head = head->next;      //다음 노드로 이동
        }
        return count+1;             //맨 마지막노드(tail)는 반복문에 해당이 안되므로 반복문이 종료시 노드 1개를 추가해주고 리턴해줌.
    }
}

//맨뒤에 노드추가
void addNodeLast(Node** head, Node** tail, Node* node){
    if ((*head) == NULL){               //헤드가 NULL이면 현재 리스트에 아무것도 없는상태임.
        (*head) = node;                 //노드가 1개이므로 헤드가 됨.
        (*tail) = node;                 //노드가 1개이므로 헤드도 되고, 테일도 되는 상황.
    }
    else{                               //헤드에 노드가 1개 이상 존재한다면
        (*tail)->next = node;           //테일의 다음노드 포인터에 새로운 노드의 주소값을 연결하고.
        (*tail) = node;                 //새로운 노드를 테일로 만든다.
    }
}

//맨앞에 노드추가
void addNodeFirst(Node** head, Node** tail, Node* node){
    if((*head) == NULL){       //리스트에 노드가 하나도 없을경우
        (*head) = node;        //새로운 노드는 head가 됨.
        (*tail) = node;        //새로운 노드는 tail이 됨.(동시에 head와 tail이 되는거임)
    }
    else{                      //헤드가 1개이상 존재할경우
        node->next = *head;    //새노드가 가지고있는 다음노드의 주소값은 head의 주소값이 되고.
        (*head) = node;        //새노드를 head로 만든다.
    }
}

//특정위치에 노드추가
void addNode(Node** head, Node** tail, Node* node, int position){ //position은 사용자가 노드를 추가하길 원하는 index번호다.
                                                                  //position은 무조건 0이상의 정수이다(음수는 입력시 걸러냄.)
    int size = getListSize(*head);                      //현재 리스트의 크기를 가지고온다.
    
    if(size < position){                                //리스트의 크기보다 사용자가 노드를 추가하길 원하는 위치가 클경우 리스트의 맨 마지막에 노드를 추가한다.
        printf("리스트의 맨 마지막에 노드를 추가하겠습니다.\n");     //(ex. 리스트에 노드가 2개가 존재해서 index가 0,1일때 position값이 2이상일경우 맨마지막에 노드를 추가)
        addNodeLast(head, tail, node);                  //addNodeLast함수를 이용해 리스트 맨 마지막에 노드를 추가
    }
    else if(position == 0){                             //position이 0일경우 리스트 맨 앞에 노드를 추가
        addNodeFirst(head, tail, node);                 //addNodeFirst함수를 이용.
    }
    else{                                               //position값이 list크기 보다 작거나 같을때(ex. 리스트에는 노드가 2개 존재.(size = 2), position값은 1 or 2)
        if((*head) == NULL){                            //먼저 리스트에 노드가 하나도 없을때.
            printf("리스트가 비어있으므로 노드를 추가하겠습니다\n");
            addNodeLast(head, tail, node);              //리스트가 비어있으므로 position값과 상관없이 노드를 추가한다.(맨앞에 추가하던, 맨뒤에 추가하던 상관없음)
        }else{                                          //노드에 값이 존재한다면.
            Node* tmp = (*head);                        //head의 주소값을 가진 tmp 노드를 만든다.
            Node* previous = NULL;                      //현재 노드의 앞에있는 노드의 주소값을 가진 previous노드를 만든다(현재 노드에서 다음노드의 주소값은 알수있지만, 이전 노드의 주소값은 알수가 없기때문)
            
            for(int i=position; i>0; i--){              //반복문을 이용해서 position값에 해당하는 위치로 노드를 이동함.
                previous = tmp;                         //다음노드로 이동하기전 현재 노드를 previous에 넣음.
                tmp = tmp->next;                        //tmp를 다음노드로 이동시킴.
            }
            
            previous->next = node;                      //이전 노드가 가지고있는 다음노드의 주소값을 새로운 노드의 주소값으로 대입시킨다.
            node->next = tmp;                           //새로운 노드가 가지고있는 다음노드의 주소값은 tmp노드의 주소값으로 대입한다.
        }
    }
}


//노드 삭제
void deleteNode(Node** head, Node** tail, int position){    //position값은 삭제를 원하는 노드의 index.
    Node* previous = NULL;                                  //삭제 노드의 앞 노드에 해당하는 previous노드를 만든다.
    Node* tmp = *head;                                      //head의 주소값을 가진 tmp를 만든다. (head의 주소값을 직접적으로 건드리면 문제가 생기므로 따로 복사해서 사용함)
    
    int size = getListSize(*head);                          //리스트의 사이즈 가져옴
    
    if(size <= position || (head) == NULL){                  //삭제를 원하는 노드의 index값이 리스트의 크기보다 크거나 같을경우 || head가 NULL일 경우
        printf("해당위치에 노드가 존재하지 않습니다\n");             //삭제가 안됨.
    }
    else{
        if(size == 1 ){                                      //리스트에 노드가 1개만 있을경우
            free(*head);                                    //head를 동적할당 해제를 해준다. 리스트에는 노드가 하나도 존재하지 않게된다.
            *head = NULL;                                   //head를 NULL로 바꿔준다. (동적할당 해제를 한다고 NULL이 되는건 아니다)
        }
        else{
            if(position == 0){                              //맨 앞의 노드를 삭제하고 싶으면
                previous = *head;                           //head를 previous에 대입후에
                *head = (*head)->next;                      //head의 다음 노드를 head로 만들어준다
                free(previous);                             //previous를 해제해준다. (이때는 NULL로 만들어줄필요는 없다.)
            }
            else{
                for(int i=position; i>0; i--){              //삭제를 원하는 노드로 이동할때까지 반복함.
                    previous = tmp;                         //삭제하려는 노드의 앞 노드를 previous에 넣어두기 위함
                    tmp = tmp->next;                        //노드를 한칸씩 이동
                }
                
                previous->next = tmp->next;                 //삭제하려는 노드의 이전노드와, 다음노드를 연결한다.
                if(tmp->next == NULL){                      //만약 삭제하려는 노드가 tail일경우에
                    *tail = previous;                       //삭제하려는 노드의 이전노드를 tail 로 만들고
                }
                free(tmp);                                  //동적할당 해제를 해준다.
            }
        }
    }
}

//리스트 출력
void printAllNode(Node* head){
    int count = 0;                                      //index번호를 출력하기위한 변수
    
    while(head != NULL){                                //head가 노드를 하나씩 이동해서 tail까지 이동후 반복문 종료
        int val = head->data;                           //값 출력을 위한 int형 변수 val에 현재 노드의 data를 대입
        printf("list[%d]의 값은 : %d\n", count, val);     //index번호와 값 출력
        count++;                                        //index번호 증가
        head = head->next;                              //다음노드로 이동
    }
    
    if(count == 0){                                     //반복문이 한번도 동작하지 않았을때 count가 0이됨. 즉, 리스트에 노드가 존재하지 않을경우.
        printf("리스트가 현재 비어있습니다.\n");
    }
}

//노드 탐색
void searchNode(Node* head, int position){
    int value = -1;                                         //node의 data값을 담을 변수(printf함수에서는 node->data가 안되는데 왠지는 모름;;)
    int size = getListSize(head);                           //리스트 사이즈 가져옴
    Node* tmp = head;                                       //head 주소값을 가지는 tmp만듬.
    
    if(tmp == NULL || size < position){                     //tmp가 NULL이거나, 사이즈보다 찾는 노드가 클경우
        printf("해당 위치에 노드가 존재하지 않습니다.\n");
    }else{
        for(int i = position; i>0; i--){                    //해당 인덱스값 만큼 반복
            tmp = tmp->next;                                //노드이동
        }
        value = tmp->data;                                  //노드의 값을 변수에 담음
        printf("index %d번의 값은 %d입니다.\n",position, value);
    }
}

int main(){
    
    Node* head = NULL;
    Node* tail = NULL;
    Node* temp;

    int choice;
    int data;
    int position;
    
    do
    {
        printf("\n기능선택 : 1. 맨뒤에 노드추가, 2. 맨앞에 노드추가, 3. 특정부분 노드추가, 4. 노드 삭제, 5. 노드 출력, 6. 노드 탐색, 7. 사이즈 출력  // 999. 종료\n");
        
        scanf("%d", &choice);
        
        switch (choice){
            case 1:
                printf("1. 맨뒤에 노드추가\n");
                printf("노드에 추가할 값을 입력하세요 : ");
                scanf("%d", &data);
                temp = newNode(data);
                addNodeLast(&head, &tail, temp);
                break;
            case 2:
                printf("2. 맨앞에 노드추가\n");
                printf("노드에 추가할 값을 입력하세요 : ");
                scanf("%d", &data);
                temp = newNode(data);
                addNodeFirst(&head, &tail, temp);
                break;
            case 3:
                printf("3. 특정부분 노드추가");
                printf("노드에 추가할 값을 입력하세요 : ");
                scanf("%d", &data);
                printf("노드를 추가할 위치를 입력하세요 : ");
                scanf("%d", &position);
                if(position < 0){
                    printf("음수는 입력 불가능합니다\n");
                }else{
                    temp = newNode(data);
                    addNode(&head, &tail, temp, position);
                }
                break;
            case 4:
                printf("4. 노드삭제\n");
                printf("삭제할 노드의 index를 입력하세요 : ");
                scanf("%d", &position);
                if(position < 0){
                    printf("음수는 입력 불가능합니다\n");
                }else{
                    deleteNode(&head, &tail, position);
                }
                break;
            case 5:
                printf("5. 노드 출력\n");
                printAllNode(head);
                break;
            case 6:
                printf("6. 노드 탐색\n");
                printf("검색할 노드의 값을 입력하세요 : ");
                scanf("%d", &position);
                if(position < 0){
                    printf("음수는 입력 불가능합니다\n");
                }else{
                    searchNode(head, position);
                }
                break;
            case 7:
                printf("7. 사이즈 출력\n");
                printf("리스트의 크기는 : %d\n", getListSize(head));
                break;
                
        }
    } while (choice != 999);
    
    getchar();
    
    return 0;
}