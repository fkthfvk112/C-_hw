#include <iostream>
#include <queue>

using namespace std;

class Client {
public:
    int arrival_time;
    int ID;
    int counseling_time;

    Client(int arrival, int id, int ct) :arrival_time(arrival), ID(id), counseling_time(ct) {};
};

struct cmp {
    bool operator()(Client a, Client b) {
        if (a.counseling_time < b.counseling_time) return true;
        else if (a.counseling_time == b.counseling_time) {
            if (a.ID > b.ID) return true;
            return false;
        }
        return false;
    }
};

int main() {
    priority_queue<Client, vector<Client>, cmp> pq;
    vector<Client> clientTable;
    int n, nowTime = 30;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int arrivalT, id, cT;
        cin >> arrivalT >> id >> cT;
        clientTable.push_back(Client(arrivalT, id, cT));
    }

    while (1) {
        if (clientTable.empty() && pq.empty()) break;
        if (pq.empty()) nowTime += 1;
        for (auto it = clientTable.begin(); it != clientTable.end();) {
            if (it->arrival_time <= nowTime) {
                pq.push(*it);
                it = clientTable.erase(it);
            }
            else it++;
        }//insert to priority queue at time
        if (!pq.empty()) {
            if (pq.top().counseling_time <= 10) {
                cout << pq.top().ID <<endl;
                nowTime += pq.top().counseling_time;
                pq.pop();
            }
            else {
                pq.push(Client(pq.top().arrival_time, pq.top().ID, pq.top().counseling_time - pq.top().counseling_time / 2));
                nowTime += pq.top().counseling_time / 2;
                pq.pop();
            }
        }
    }

    return 0;
}
