#include <iostream>
#include <random>
#include <math.h>
#include <queue>

#define DEBUG 0

using namespace std;

#define START_TIME 0
#define FINISH_TIME 10000
#define K 50

double lambd = 1.0;
double mu = 1.0;
int global_pkt_id = 0;

typedef struct _wait_Packet{
    double w_arrival_time;
    int w_packet_id;
} wait_Packet;

queue<wait_Packet> pkt_queue;

int arrival_cnt = 0;    // Packet Arrival Count
int departure_cnt = 0;  // Packet Departure Count
int loss_cnt = 0;       // Packet Loss Count
double interval_x_queue_sum = 0.0;
double stay_time_sum = 0.0;

// Uniform Random Number [0, 1) (一様乱数)
double uni_rand(){
    random_device rand_dev;
    mt19937 mt32(rand_dev());
    uniform_real_distribution<double> uni_distribution(0, 1);
    double uni_rnd = uni_distribution(mt32);
    return uni_rnd;
}

// Exponential Random Number (指数乱数)
double exp_rand(double x){
    double exp_rnd = -log(1.0 - uni_rand()) / x;
    return exp_rnd;
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
    Event new_event = {s_time, e_type, pkt_id};
    event_table.push(new_event);
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
        while(!event_table.empty()){
            cout << "    arrival_time = " << event_table.top().arrival_time << endl;
            cout << "    event_type = " << static_cast<int>(event_table.top().event_type) << endl;
            cout << "    packet_id = " << event_table.top().packet_id << endl;
            cout << "    pkt_queue = " << pkt_queue.size() << endl << endl;
            delete_head_event();
        }
#endif
            break;

        }
        else if (head_e_type == EVENT_TYPE::ARRIVAL){
#if DEBUG
            cout << "  event_type = Arrival" << endl;
#endif
            register_event(sim_time + exp_rand(lambd), EVENT_TYPE::ARRIVAL, global_pkt_id);

            if (pkt_queue.size() < K){
                if (pkt_queue.size() == 0){
                    register_event(sim_time + exp_rand(mu), EVENT_TYPE::DEPARTURE, event_table.top().packet_id);
                }
                pkt_queue.push({sim_time, global_pkt_id++});
            }else{
                loss_cnt++;
            }
            arrival_cnt++;
        }
        else if (head_e_type == EVENT_TYPE::DEPARTURE){
#if DEBUG
            cout << "  event_type = Departure" << endl;
#endif
            if (pkt_queue.size() > 1){
                register_event(sim_time + exp_rand(mu), EVENT_TYPE::DEPARTURE, pkt_queue.front().w_packet_id);
            }
            
            stay_time_sum += sim_time - pkt_queue.front().w_arrival_time;
            pkt_queue.pop();
            departure_cnt++;

        }
#if DEBUG
        cout << "    arrival_time = " << event_table.top().arrival_time << endl;
        cout << "    packet_id = " << event_table.top().packet_id << endl;
        cout << "    pkt_queue = " << pkt_queue.size() << endl;
#endif

        delete_head_event();
        interval_x_queue_sum += (event_table.top().arrival_time - sim_time) * pkt_queue.size();

        sim_time = event_table.top().arrival_time;
#if DEBUG
        cout << "\n[sim_time] = " << sim_time << endl;
#endif
    }

    cout << "Average Packet Count = " << interval_x_queue_sum/(FINISH_TIME-START_TIME) << endl;
    cout << "Average Stay Time = " << stay_time_sum/departure_cnt << endl;
    cout << "Loss Rate = " << (double)loss_cnt/arrival_cnt << endl;
    return 0;
}
