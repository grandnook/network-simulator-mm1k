#include <iostream>
#include <random>
#include <math.h>
#include <queue>

#define DEBUG 0

using namespace std;

#define START_TIME 0
#define FINISH_TIME 10

double lambd = 1.0;
int global_pkt_id = 0;
queue<int> pkt_queue;

// Uniform Random Number [0, 1) (一様乱数)
double uni_rand(){
    random_device rand_dev;
    mt19937 mt32(rand_dev());
    uniform_real_distribution<double> uni_distribution(0, 1);
    return uni_distribution(mt32);    
}

// Exponential Random Number (指数乱数)
double exp_rand(){
    return -log(1.0 - uni_rand()) / lambd;
}

enum class EVENT_TYPE{
    ARRIVAL,
    DEPARTURE,
    TERMINATOR
};

typedef struct _Event{
    double arrival_time;    // Arrival Time of Event (イベント発生時刻)
    EVENT_TYPE event_type;  // Event Type (イベントタイプ)
    int packet_id;          // Sequence Number of Packet (パケットのシーケンス番号)
} Event;

// In `priority_queue<Event> event_table`, Sort in Ascending Order by `arrival_time`.
// (イベント追加時に，イベント発生時刻の昇順でソートする．)
bool operator<(const Event &left, const Event &right){
    return left.arrival_time > right.arrival_time;
};

priority_queue<Event> event_table;

void register_event(double s_time, EVENT_TYPE e_type, int pkt_id){
    Event e = {s_time, e_type, pkt_id};
    event_table.push(e);
}

void delete_head_event(){
    event_table.pop();
}

int main(){
    double sim_time = START_TIME;
#if DEBUG
    cout << "[sim_time] = " << sim_time << endl;
#endif

    register_event(START_TIME, EVENT_TYPE::ARRIVAL, global_pkt_id++);
    register_event(FINISH_TIME, EVENT_TYPE::TERMINATOR, -1);

    while (1)
    {
        EVENT_TYPE head_e_type = event_table.top().event_type;
        if (head_e_type == EVENT_TYPE::TERMINATOR){
#if DEBUG
            cout << "  event_type = Terminator" << endl;
#endif
            return 0;

        }
        else if (head_e_type == EVENT_TYPE::ARRIVAL){
#if DEBUG
            cout << "  event_type = Arrival" << endl;
#endif
            if (pkt_queue.size() == 0){
                register_event(sim_time + exp_rand(), EVENT_TYPE::DEPARTURE, event_table.top().packet_id);
            }

            register_event(sim_time + exp_rand(), EVENT_TYPE::ARRIVAL, global_pkt_id);

            pkt_queue.push(global_pkt_id++);

        }
        else if (head_e_type == EVENT_TYPE::DEPARTURE){
#if DEBUG
            cout << "  event_type = Departure" << endl;
#endif
            if (pkt_queue.size() > 1){
                register_event(sim_time + exp_rand(), EVENT_TYPE::DEPARTURE, pkt_queue.front());
            }            

            pkt_queue.pop();

        }
#if DEBUG
        cout << "    arrival_time = " << event_table.top().arrival_time << endl;
        cout << "    packet_id = " << event_table.top().packet_id << endl;
        cout << "    pkt_queue = " << pkt_queue.size() << endl;
#endif

        delete_head_event();
        sim_time = event_table.top().arrival_time;

#if DEBUG
        cout << "\n[sim_time] = " << sim_time << endl;
#endif
    }
}
