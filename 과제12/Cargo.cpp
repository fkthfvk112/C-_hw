#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector<int> weightTable;
vector<vector<int>> container;

bool insertIntoContainer(int w, int n){
    int cnt = 0;
    for(auto i = weightTable.begin(); i!=weightTable.end(); i++){
        if((weightTable.at(cnt)+ w) <= 100){
            weightTable.at(cnt) += w;
            container.at(cnt).push_back(n);

            return 0;//no new one
        }
        cnt++;
    }
    weightTable.push_back(w);
    vector<int> newStack;
    newStack.push_back(n);
    container.push_back(newStack);

    return 1;// new
}

bool compare(int a, int b){
    return a > b;
}
int main(){

    int n, w;
    cin>>n;
    for(int i=0; i<n; i++){
        cin>>w;
        insertIntoContainer(w, i+1);
    }
    for(auto v:container){
        sort(v.begin(), v.end(), compare);
        while(!v.empty()){
            cout<<v.back()<<" ";
            v.pop_back();
        }
        cout<<endl;
    }
    return 0;
}
