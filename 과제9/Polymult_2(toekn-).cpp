#include <iostream>
#include <vector>
#include <algorithm>
#define  printFunc(func)   std::cout<<func.size()<<endl;\
            for(auto f:func)std::cout<<f.first<<" "<<f.second<<endl;
using namespace std;

bool weight(const pair<int, int> &p1, const pair<int, int> &p2){
    return p1.second > p2.second;
}

vector<pair<int,int>> polyTwo(vector<pair<int, int>> &func1, vector<pair<int, int>> &func2){
    vector<pair<int, int>> temp;
    int tempFirst, tempSecond;
    for(auto f1:func1){
            for(auto f2:func2){
                tempFirst = f1.first*f2.first;
                tempSecond = f1.second+f2.second;

                auto itr = find_if(temp.begin(), temp.end(), [tempSecond](const pair<int, int> e){
                        return e.second == tempSecond;
                        });
                if(itr - temp.begin() == temp.size()){
                    temp.push_back(pair<int, int>(tempFirst, tempSecond));
                }//no element
                else{
                    temp.at(itr-temp.begin()).first += tempFirst;
                }
                //is in element
            }
    }
    /*
    for(int i = 0; i < temp.size(); i++){
        if(temp.at(i).first == 0) temp.erase(temp.begin() + i);
    }*/
    sort(temp.begin(), temp.end(), weight);
    //temp.shrink_to_fit();

    return temp;
}

vector<pair<int, int>> polyMany(vector<vector<pair<int, int>>> &funcs){
    vector<vector<pair<int, int>>> tempMany;
    vector<pair<int, int>> resultMany;

    tempMany.push_back(polyTwo(funcs.at(0), funcs.at(1)));
    for(int i=1;i<funcs.size()-1;i++){
        tempMany.push_back(polyTwo(*(tempMany.begin()+i-1), funcs.at(i+1)));
    }
    resultMany = tempMany.back();

    for(int i = 0; i < resultMany.size(); i++){
        if(resultMany.at(i).first == 0) resultMany.erase(resultMany.begin() + i);
    }

    return resultMany;
}
int main(){
    vector<pair<int, int>> func;
    vector<vector<pair<int, int>>> funcs;
    int n, termNum, e, s;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>termNum;
        for(int j=0;j<termNum;j++){
            cin>>s>>e;
            func.push_back(pair<int, int>(s, e));
        }
        sort(func.begin(), func.end(), weight);
        funcs.push_back(func);
        func.clear();
    }
    printFunc(polyMany(funcs));
return 0;
}
