#include <iostream>
#include <stdlib.h>

using namespace std;

typedef struct _Node{
    int data;
    struct _Node *next;
} Node;

int main(){
    Node *pre_p = (Node*)malloc(sizeof(Node));
    pre_p->next = NULL;
    pre_p->data = 33;

    Node *p = (Node*)malloc(sizeof(Node));
    pre_p->next = p;
    p->next = NULL;
    p->data = 77;

    for (int i=0;i<2;i++){
        cout << pre_p[i].data << endl;
    }

    return 0;
}
