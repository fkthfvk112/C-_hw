#include <iostream>
#include <array>
#include <vector>
#define printAll(vec) for(auto v:vec) std::cout<<v.first<<" "<<v.second<<endl;
#define printAll2(vec) for(auto v:vec) std::cout<<v<<" ";\
            cout<<endl;
using namespace std;
int n;
vector <pair<int, int>> seats; // first = number of people, second == seat number
vector <int> distanceTable;



void pushBack_to_DistanceTable(int dis){
    if(distanceTable.size() >=2){
        distanceTable.at(distanceTable.size()-2) = abs(seats.back().second - seats.at(seats.size()-2).second);
    }
    distanceTable.push_back(abs(dis));
}

void setSeat(int pn){
    int seatIndex = 0, maxDistance = 0;
    int distanceBeween;
    for(int i =0;i<distanceTable.size();i++){
        //printAll2(distanceTable);
        if(maxDistance < distanceTable[i]){
            if(maxDistance == distanceTable[i]){
                int tempS1 = (seats.at(seatIndex).second + maxDistance/2)%n;
                int tempS2 = (seats.at(i).second + maxDistance/2)%n;
                if(tempS1 < tempS2) continue;
            }
            maxDistance = distanceTable[i];
            seatIndex = i;
        }
    }
    int resultSeat;
    if((seats.at(seatIndex).second + maxDistance/2)%n < ((seats.at(seatIndex).second + maxDistance/2)%n)+1){
        resultSeat = (seats.at(seatIndex).second + maxDistance/2)%n;
        distanceBeween = maxDistance/2;
    }
    else{
        resultSeat = (seats.at(seatIndex).second + maxDistance/2)%n + 1;
        distanceBeween = maxDistance/2+1;
    }

    seats.push_back(pair<int, int> (pn, resultSeat));
    cout<<"µð½ºÅÁ½º Å×ÀÌºí : ";
    printAll2(distanceTable);
    cout<<"½Ë ¹øÈ£ : ";
    for(auto k:seats){
        cout<<k.second<<" ";
    }
    cout<<endl;
    pushBack_to_DistanceTable(distanceBeween);
}

using namespace std;
int main(){
    int k, u;
    cin>>n>>k;
    for(int i = 0; i < k; i++){
        cin>>u;
        if(i == 0){
            distanceTable.push_back(n-1);
            seats.push_back(pair<int, int>(u, 1));
            continue;
        }
        setSeat(u);
    }
    printAll(seats);
return 0;}
