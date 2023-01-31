#include <iostream>
#include <vector>

using namespace std;

typedef struct _Node{
    int data;
} Node;

int main(){
    vector<Node> v;
    Node n1 = {1};
    Node n2 = {2};
    Node n3 = {3};

    v.push_back(n1);
    v.push_back(n2);
    v.push_back(n3);

    for (auto i=v.begin(); i!=v.end();i++){
        cout << i->data << endl;
    }

    return 0;
}
