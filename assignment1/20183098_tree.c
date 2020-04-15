#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct BinaryTreeNode{
    char data;

    struct BinaryTreeNode* leftChildPtr;
    struct BinaryTreeNode* rightChildPtr;
}BinTreeNode;

typedef struct BinaryTree{
    struct BinaryTreeNode* rootNodePtr;// 이거 선언할 때 BinaryTreeNode 라고 안하고 구조체 선언변수 BindTreeNode 라고 하면 '불완전한 클래스 형식에 대한 포인터는 사용할 수 없습니다라고 오류남 
}BinaryTree;

BinaryTree* newBinaryTree(BinTreeNode rootNode){
    BinaryTree* returnPtr = NULL;
    returnPtr = (BinaryTree*)malloc(sizeof(BinaryTree));
    if(returnPtr != NULL){
        returnPtr->rootNodePtr = (BinTreeNode*)malloc(sizeof(BinTreeNode));
        if(returnPtr -> rootNodePtr != NULL){
            *(returnPtr->rootNodePtr) = rootNode;
            returnPtr->rootNodePtr->leftChildPtr = NULL;
            returnPtr->rootNodePtr->rightChildPtr = NULL;
        }
        else printf("tree memory allocation fail");
    }
    else printf("tree memory allocation fail");
    return returnPtr;
}

BinTreeNode* addLeftChildNode(BinTreeNode* parentNodePtr, BinTreeNode element){
    BinTreeNode* returnNodePtr = NULL;
    if(parentNodePtr->leftChildPtr == NULL){
        parentNodePtr->leftChildPtr = (BinTreeNode*)malloc(sizeof(BinTreeNode));
        if(parentNodePtr->leftChildPtr != NULL){
            *(parentNodePtr->leftChildPtr) = element;
            parentNodePtr->leftChildPtr->leftChildPtr = NULL;
            parentNodePtr->rightChildPtr->rightChildPtr = NULL;
            returnNodePtr = parentNodePtr->leftChildPtr;
        }
        else("leftnode memory allocation fail");
    }
    else("leftnode is already exist");
    return returnNodePtr;
}

BinTreeNode* addRightChildNode(BinTreeNode* parentNodePtr, BinTreeNode element){
    BinTreeNode* returnNodePtr = NULL;
    if(parentNodePtr->rightChildPtr == NULL){
        parentNodePtr->rightChildPtr = (BinTreeNode*)malloc(sizeof(BinTreeNode));
        if(parentNodePtr->rightChildPtr != NULL){
            *(parentNodePtr->rightChildPtr) = element;
            parentNodePtr->rightChildPtr->rightChildPtr = NULL;
            parentNodePtr->leftChildPtr->leftChildPtr = NULL;
            returnNodePtr = parentNodePtr->rightChildPtr;
        }
        else("leftnode memory allocation fail");
    }
    else("rightnode is already exist");
    return returnNodePtr;
}

BinTreeNode* ReturnRootNode(BinaryTree* bintreePtr){
    BinTreeNode* returnPtr = NULL;
    if(bintreePtr != NULL){
        returnPtr = bintreePtr->rootNodePtr;
    }
    else printf("unknown value");
    return returnPtr;
}

BinTreeNode* ReturnRightNode(BinTreeNode* bintreePtr){
    BinTreeNode* returnPtr = NULL;
    if(bintreePtr != NULL){
        returnPtr = bintreePtr->rightChildPtr;
    }
    else printf("unknown value");
    return returnPtr;
}

BinTreeNode* ReturnLeftNode(BinTreeNode* bintreePtr){
    BinTreeNode* returnPtr = NULL;
    if(bintreePtr != NULL){
        returnPtr = bintreePtr->leftChildPtr;
    }
    else printf("unknown value");
    return returnPtr;
}

void deleteBinTreeNode(BinTreeNode* binNodePtr){
    if(binNodePtr != NULL){
        deleteBinTreeNode(binNodePtr->leftChildPtr);
        deleteBinTreeNode(binNodePtr->rightChildPtr);
        free(binNodePtr);
    }
}









