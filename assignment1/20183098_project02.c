#include <stdio.h>
#include <stdlib.h>

int main(){
    int arraySize,deletePosition; 
    
    scanf("%d",&arraySize);
    int *array = malloc(sizeof(int) * arraySize);
    printf("element in array: ");
    for(int i=0 ; i<arraySize ; i++){
        scanf("%d",&array[i]);
    }
     printf("Stored data in array: ");
    for(int j=0 ; j<arraySize ; j++){
        printf(" %d",array[j]);    
    }
    printf("\n");    
    printf("Enter  Delete position : ");
    scanf("%d",&deletePosition);
    arraySize = arraySize-1;//01 2 3 4 5 6
    realloc(array,sizeof(int) * (arraySize));//추가된 원소만큼 배열크기 재할당 
    memmove(array+(deletePosition-1),array+deletePosition,(sizeof(array)-deletePosition) * sizeof(int));
	// 제거할 원소의 인덱스 어드레스+1 만큼의 원들의 어드레스를 왼쪽으로 1칸식 쉬프트
    printf("Stored data in array: ");
       for(int m=0 ; m<arraySize ; m++){
        printf(" %d",array[m]);    
    }
//0 1 2 3 4 5 6
//3 5 7 6 1
//3 5 8 7 6 1
}