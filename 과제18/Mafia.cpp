#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
//1. 다 집어넣기 2. set함수들 3.
using namespace std;


//벡터에 node저장
//node클래스에서는 포인터로 사용

class Node{
public:
    string name;
    int childrenNum = 0;
    int level = 0;
    vector<Node*> children;
public:
    Node(string _name){
        name = _name;
    }
    void showAdd(){
        for(auto itr = children.begin(); itr!=children.end();itr++){
            cout<<&(*itr)<<endl;
        }
    }
    void showMyChildren(){
        cout<<name<<"의 자식 "<<endl;

        for(auto n:children){
            cout<<n->name<<endl;
        }
    }

    void pushChildren(Node* n){ //레벨 재설정 해야해요!!
        children.push_back(n);
    }
    int setAllChildrenNumber(){
        cout<<name<<"에서 실행중"<<endl;
        for(auto c:children){
            childrenNum += c->setAllChildrenNumber();
            childrenNum ++;
        }

        return childrenNum;
    }

    string getName(){
        return name;
    }
};
vector<Node> nodeList;
vector<string> nodeNames;

int main(){
    int nodeNumber;
    cin>>nodeNumber;
    string p, b;
    for(int i = 0; i < nodeNumber-1; i++){
        cin>>p>>b;
        auto pItr = find(nodeNames.begin(), nodeNames.end(), p);
        auto bItr = find(nodeNames.begin(), nodeNames.end(), b);

        bool pIsInList = (pItr != nodeNames.end());
        bool bIsInList = (bItr != nodeNames.end());
        int pInx = pItr - nodeNames.begin();
        int bInx = bItr - nodeNames.begin();

//nodeList에 할당하는 과정에서 capacity초과시 재할당이 일어남, 그러므로 기존의 주소는 쓰레기 값이 됨(Children에 할당한 값)그러므로 미리 reserve이
        if(bIsInList){
            if(pIsInList){
                cout<<"조건1"<<endl;
                nodeList.at(bInx).pushChildren(&nodeList.at(pInx));
                cout<<nodeList.at(bInx).name<<"의 자식에 "<<nodeList.at(pInx).name<<" 추가"<<endl;
                                nodeList.at(bInx).showMyChildren();

            }
            else{
                cout<<"조건2"<<endl;
                nodeList.push_back(Node(p));
                nodeNames.push_back(p);
                nodeList.at(bInx).pushChildren(&nodeList.back());
                cout<<nodeList.at(bInx).name<<"의 자식에 "<<nodeList.back().name<<" 추가"<<endl;
                nodeList.at(bInx).showMyChildren();

            }
        }

        else if(!bIsInList){
            nodeList.push_back(Node(b));
            nodeNames.push_back(b);
            bInx = nodeNames.end()-1 - nodeNames.begin();

            if(pIsInList){
                    cout<<"조건3"<<endl;
                nodeList.back().pushChildren(&nodeList.at(pInx));
                cout<<nodeList.back().name<<"의 자식에 "<<nodeList.at(pInx).name<<" 추가"<<endl;
                nodeList.at(bInx).showMyChildren();

            }
            else{
                cout<<"조건4"<<endl;
                //Node* tempBoss = &nodeList.back();
                nodeList.push_back(Node(p));
                nodeNames.push_back(p);
                cout<<"마지막 요소"<<nodeList.back().name;
                //tempBoss->pushChildren(&nodeList.back()); why error?
                nodeList.at(bInx).pushChildren(&nodeList.back());
                cout<<nodeList.at(bInx).name<<"의 자식에 "<<nodeList.back().name<<" 추가"<<endl;
                nodeList.at(bInx).showMyChildren();

            }
        }
    }
    for(auto n:nodeList){
        n.showMyChildren();
    }
    cout<<"노드리스트 주소값"<<endl;
    for(auto a:nodeList){
        cout<<&(a.name)<<endl;
        cout<<a.name<<endl;
    }
    cout<<endl;
    cout<<"첫 요소의자식들 주소값"<<endl;
    nodeList[0].showAdd();


return 0;
}

/*포인터로 하니까 값이 이상해진다.... 해결책이 있을까요?*/
