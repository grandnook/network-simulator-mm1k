#include <iostream>
#include <queue>

using namespace std;

typedef struct _Node{
    int data1;
    int data2;
    string name;
} Node;

// Ascending Order Sort by `data2`
bool operator<(const Node &left, const Node &right) {
    return left.data2 > right.data2;
};

int main(){

    Node n1 = {1, 30, "n1"};
    Node n2 = {2, 60, "n2"};
    Node n3 = {3, 10, "n3"};

    priority_queue<Node> p_que;
    p_que.push(n1);
    p_que.push(n2);
    p_que.push(n3);

    while(!p_que.empty()){
        cout << p_que.top().data1 << " " << p_que.top().data2 << " " << p_que.top().name << endl;
        p_que.pop();
    }

    return 0;
}
