#include <iostream>

using namespace std;

enum class EVENT_TYPE {
    ARRIVAL,
    DEPARTURE,
    TERMINATOR
};

int main(){

    // the 1st way
    EVENT_TYPE event_type = EVENT_TYPE::TERMINATOR;
    int e1 =  static_cast<int>(event_type);  // 明示的なキャストのみ可能
    cout << e1 << endl;

    // the 2nd way
    int e2 =  static_cast<int>(EVENT_TYPE::TERMINATOR);
    cout << e2 << endl;

    return 0;
}

