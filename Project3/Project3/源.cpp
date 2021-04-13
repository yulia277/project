#include <stdio.h>
#include<malloc.h>
#define ElemType char

//�ڵ�����������������ָ�롢�Һ���ָ��

typedef struct BiTNode {

    char data;

    struct BiTNode* lchild, * rchild;

}BiTNode, * BiTree;

//������������

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

    return T;//���ظ��ڵ�

}

//�������������

void PreOrderTraverse(BiTree T) {

    if (T) {

        printf("%c", T->data);

        PreOrderTraverse(T->lchild);

        PreOrderTraverse(T->rchild);

    }

}



//�������

void InOrderTraverse(BiTree T) {

    if (T) {

        PreOrderTraverse(T->lchild);

        printf("%c", T->data);

        PreOrderTraverse(T->rchild);

    }

}

//�������

void PostOrderTraverse(BiTree T) {

    if (T) {

        PreOrderTraverse(T->lchild);

        PreOrderTraverse(T->rchild);

        printf("%c", T->data);

    }

}

void main() {

    BiTree T;

    T = CreateBiTree();//����

    PreOrderTraverse(T);//���
    printf("\n");
    InOrderTraverse(T);
    printf("\n");
    PostOrderTraverse(T);
}