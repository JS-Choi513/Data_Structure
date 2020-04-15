#include <stdio.h>
#include <stdlib.h>

int main(){
    int arraySize,elementPosition,newElement ; 
    
    scanf("%d",&arraySize);
    int *array = malloc(sizeof(int) * arraySize);//01234 5
    printf("element in array: ");
    for(int i=0 ; i<arraySize ; i++){
        scanf("%d",&array[i]);
    }
     printf("Stored data in array: ");
    for(int j=0 ; j<arraySize ; j++){
        printf(" %d",array[j]);    
    }
    printf("\n");    
    printf("Enter position for element: ");
    scanf("%d",&elementPosition);
    printf("Enter New element: ");
    scanf("%d",&newElement);
    arraySize = arraySize+1;//01 2 3 4 5 6
    realloc(array,sizeof(int) * (arraySize));//추가된 원소만큼 배열크기 재할당 
    memmove(array+elementPosition,array+(elementPosition-1),(sizeof(array)-elementPosition-1) * sizeof(int));
	// 배열 쉬프트, 끼워넣을 인덱스+1 인덱스 부터 끝가지의 원소를 1칸씩 쉬프트하여 새 원소를 넣을 공간 확보
    array[elementPosition-1] = newElement;//
    printf("Stored data in array: ");
       for(int m=0 ; m<arraySize ; m++){
        printf(" %d",array[m]);    
    }
//0 1 2 3 4 5 6
//3 5 7 6 1
//3 5 8 7 6 1
}
