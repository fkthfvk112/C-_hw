#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

list<char> sapiens;
int maxN= 0;

void chrom_front(int p1, int p2){
    stack<char> tempS;
    cout<<p2;
    auto itr = sapiens.begin();
    for(int i=0;i<p2;i++,itr++){
        if(i >= p1-1){
            tempS.push(*itr);
            itr = sapiens.erase(itr);
            itr--;
        }
    }


    while(!tempS.empty()){
        sapiens.push_front(tempS.top());
        tempS.pop();
    }
}

void chrom_back(int p1, int p2){
    vector<char> tempV;
    auto itr = sapiens.begin();
    for(int i=0;i<p2;i++,itr++){
        if(i >= p1-1){
            tempV.push_back(*itr);
            itr = sapiens.erase(itr);
            itr--;
        }
    }

    for(auto v:tempV){
        sapiens.push_back(v);
    }
}

void chrom_cut(int p1, int p2){
    if(p2-p1>0)maxN -= (p2-p1+1);
    cout<<"ÄÆ¿¡¼­ Å©±â"<<maxN<<endl;
    auto itr = sapiens.begin();
    for(int i=0;i < p2;i++,itr++){
        if(i >= p1-1){
            itr=sapiens.erase(itr);
            itr--;
        }
    }
}
void chrom_double(int p1, int p2){
    if(p2-p1>0) maxN += (p2-p1+1);
    vector<char> tempV;
    auto itr = sapiens.begin();
    int psize = p2-p1;
    for(int i=0;i < p2;i++, itr++){
        if(i >= p1-1){
            tempV.push_back(*itr);
        }
    }
    for(auto v:tempV){
        itr = sapiens.insert(itr, v);
        itr++;
    }
}

void chrom_flip(int p1, int p2){
    stack<int> tempS;
    auto itr = sapiens.begin();
    for(int i=0;i<p2;i++,itr++){
        if(i >= p1-1){
            tempS.push(*itr);
            itr = sapiens.erase(itr);
            itr--;
        }
    }
    while(!tempS.empty()){
        itr = sapiens.insert(itr, tempS.top());
        tempS.pop();
        itr++;
    }
}

void chrom_report(int p1, int p2){
    stack<int> tempS;
    auto itr = sapiens.begin();
    for(int i=0;i<p2;i++,itr++){
        if(i >= p1-1){
            cout<<*itr;
        }
    }
    cout<<endl;
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
        if(p2>maxN) p2 = maxN;
        if(command == "front")
            chrom_front(p1, p2);
        if(command == "back")
            chrom_back(p1, p2);
        if(command == "cut")
            chrom_cut(p1, p2);
        if(command == "double")
            chrom_double(p1, p2);
        if(command == "flip")
            chrom_flip(p1, p2);
        if(command =="report")
            chrom_report(p1, p2);
                    cout<<"ÃÑ Å©±â"<<maxN<<endl;

    }


return 0;
}
