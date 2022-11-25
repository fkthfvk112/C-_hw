#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <string>
#define ENDFUNC '@';
#define DEADLOCK '^'
using namespace std;

vector <vector<string>> functions;
stack <pair<int, char>>funcTable;
int cnt = 0;
int k1, k2;
string k1Val, k2Val, k1c, k2c;

char runCode(char codeName, int startInx){
    vector<string> tempString;
    for(auto fs:functions){
        if(fs.at(0).at(0) == codeName){
            tempString = fs;
        }
    }
   for(int i = startInx; i < tempString.size(); i++){
    if(isupper(tempString[i].at(0))){
        char next = tempString[i].at(0);
        funcTable.push(pair<int, char>(i+1, codeName));
        return next;//next funcname
    }
    if(tempString[i].at(0) == '$'){
        if(funcTable.top().second == 'M') return '&';//end of main
        if(funcTable.top().second == codeName){
            funcTable.pop();
        }
        return ENDFUNC;
    }

    cnt++;
    //cout<<cnt<<" "<<tempString[i]<<endl;
    if(cnt >= 100000){
        k1 = -2;
        k2 = -2;
    return DEADLOCK;
   }
    if(k1 == cnt){
        k1Val = tempString[i];
        k1c = codeName;
        k1 = -1;
    }
    if(k2 == cnt){
        k2Val = tempString[i];
        k2c = codeName;
        k2 = -1;
    }
   }

}

int main(){
    int n;
    cin>>n>>k1>>k2;

    vector<string> tempV;
    for(int i=0;i<n;i++){
        tempV.clear();
        while(1){
            string tempChar;
            cin>>tempChar;
            tempV.push_back(tempChar);
            if(tempChar.back() == '$'){
                functions.push_back(vector<string>(tempV));
                break;
            }
        };
    }

    char after = runCode('M', 1);
    while(after != '&' && after != DEADLOCK){
        if(after != '@')
            after = runCode(after, 1);
        else
            after = runCode(funcTable.top().second, funcTable.top().first);
    }

    if(k1 != -2 && k2 != -2){
        if(k1 == -1) cout<<k1c<<"-"<<k1Val<<endl;
        else cout<<"NONE"<<endl;

        if(k2 == -1)cout<<k2c<<"-"<<k2Val<<endl;
        else cout<<"NONE"<<endl;
    }

    if(k1 == -2 || k2 == -2){
        cout<<"DEAD LOCK"<<endl;
    }


return 0;
}
