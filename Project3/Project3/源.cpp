#include <stdio.h>
#include<malloc.h>
#define ElemType char

//节点声明，数据域、左孩子指针、右孩子指针

typedef struct BiTNode {

    char data;

    struct BiTNode* lchild, * rchild;

}BiTNode, * BiTree;

//先序建立二叉树

BiTree CreateBiTree() {

    char ch;

    BiTree T;

    scanf("%c", &ch);

    if (ch == '#')T = NULL;

    else {

        T = (BiTree)malloc(sizeof(BiTNode));

        T->data = ch;

        T->lchild = CreateBiTree();

        T->rchild = CreateBiTree();

    }

    return T;//返回根节点

}

//先序遍历二叉树

void PreOrderTraverse(BiTree T) {

    if (T) {

        printf("%c", T->data);

        PreOrderTraverse(T->lchild);

        PreOrderTraverse(T->rchild);

    }

}



//中序遍历

void InOrderTraverse(BiTree T) {

    if (T) {

        PreOrderTraverse(T->lchild);

        printf("%c", T->data);

        PreOrderTraverse(T->rchild);

    }

}

//后序遍历

void PostOrderTraverse(BiTree T) {

    if (T) {

        PreOrderTraverse(T->lchild);

        PreOrderTraverse(T->rchild);

        printf("%c", T->data);

    }

}

void main() {

    BiTree T;

    T = CreateBiTree();//建立

    PreOrderTraverse(T);//输出
    printf("\n");
    InOrderTraverse(T);
    printf("\n");
    PostOrderTraverse(T);
}