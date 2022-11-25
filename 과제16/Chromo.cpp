#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

list<char> sapiens;
int maxN= 0;

bool chrom_func(int p1, int p2, string command){
    stack<char> tempS;
    vector<char> tempV;
    if(p1>maxN && command == "report"){
        cout<<"NONE"<<endl;
        return 0;
    }
    if(p2>maxN) p2 = maxN;

    if(p2-p1>0){
        if(command =="cut")
            maxN -= (p2-p1+1);
        if(command =="double")
            maxN += (p2-p1+1);
    }

    auto itr = sapiens.begin();
    for(int i=0;i<p2;i++,itr++){
        if(i >= p1-1){
            if(command =="front"){
                tempS.push(*itr);
                itr = sapiens.erase(itr);
                itr--;
            }
            else if(command == "back"){
                tempV.push_back(*itr);
                itr = sapiens.erase(itr);
                itr--;
            }
            else if(command =="cut"){
                itr=sapiens.erase(itr);
                itr--;
            }
            else if(command =="double"){
                tempV.push_back(*itr);
            }
            else if(command == "flip"){
                tempS.push(*itr);
                itr = sapiens.erase(itr);
                itr--;
            }
            else if(command == "report"){
                    cout<<*itr;
            }
        }
    }
    if(command == "front"){
        while(!tempS.empty()){
        sapiens.push_front(tempS.top());
        tempS.pop();
        }
    }
    else if(command == "back"){
        for(auto v:tempV){
            sapiens.push_back(v);
        }
    }
    else if(command == "double"){
        for(auto v:tempV){
            itr = sapiens.insert(itr, v);
            itr++;
        }
    }
    else if(command == "flip"){
        while(!tempS.empty()){
            itr = sapiens.insert(itr, tempS.top());
            tempS.pop();
            itr++;
        }
    }
    else if(command == "report"){
        cout<<endl;
    }
    return 1;
}

int main(void){
    ifstream in("sapiens.txt");
    int n, p1, p2, fcnt = 0;
    string command, tempS;
    while(getline(in, tempS)){
        if(fcnt > 0){
            for(int i = 0; i < tempS.size(); i++){
                sapiens.push_back(tempS[i]);
                maxN ++;
            }
        }
        fcnt++;
    }
    cin>>n;
    for(int i = 0; i<n;i++){
        cin>>command>>p1>>p2;
        if(command == "front" || command == "back" || command == "cut" ||command == "double"||command =="flip"||command=="report")
            chrom_func(p1, p2, command);
    }


return 0;
}
