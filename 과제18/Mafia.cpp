#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
//1. �� ����ֱ� 2. set�Լ��� 3.
using namespace std;


//���Ϳ� node����
//nodeŬ���������� �����ͷ� ���

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
        cout<<name<<"�� �ڽ� "<<endl;

        for(auto n:children){
            cout<<n->name<<endl;
        }
    }

    void pushChildren(Node* n){ //���� �缳�� �ؾ��ؿ�!!
        children.push_back(n);
    }
    int setAllChildrenNumber(){
        cout<<name<<"���� ������"<<endl;
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

//nodeList�� �Ҵ��ϴ� �������� capacity�ʰ��� ���Ҵ��� �Ͼ, �׷��Ƿ� ������ �ּҴ� ������ ���� ��(Children�� �Ҵ��� ��)�׷��Ƿ� �̸� reserve��
        if(bIsInList){
            if(pIsInList){
                cout<<"����1"<<endl;
                nodeList.at(bInx).pushChildren(&nodeList.at(pInx));
                cout<<nodeList.at(bInx).name<<"�� �ڽĿ� "<<nodeList.at(pInx).name<<" �߰�"<<endl;
                                nodeList.at(bInx).showMyChildren();

            }
            else{
                cout<<"����2"<<endl;
                nodeList.push_back(Node(p));
                nodeNames.push_back(p);
                nodeList.at(bInx).pushChildren(&nodeList.back());
                cout<<nodeList.at(bInx).name<<"�� �ڽĿ� "<<nodeList.back().name<<" �߰�"<<endl;
                nodeList.at(bInx).showMyChildren();

            }
        }

        else if(!bIsInList){
            nodeList.push_back(Node(b));
            nodeNames.push_back(b);
            bInx = nodeNames.end()-1 - nodeNames.begin();

            if(pIsInList){
                    cout<<"����3"<<endl;
                nodeList.back().pushChildren(&nodeList.at(pInx));
                cout<<nodeList.back().name<<"�� �ڽĿ� "<<nodeList.at(pInx).name<<" �߰�"<<endl;
                nodeList.at(bInx).showMyChildren();

            }
            else{
                cout<<"����4"<<endl;
                //Node* tempBoss = &nodeList.back();
                nodeList.push_back(Node(p));
                nodeNames.push_back(p);
                cout<<"������ ���"<<nodeList.back().name;
                //tempBoss->pushChildren(&nodeList.back()); why error?
                nodeList.at(bInx).pushChildren(&nodeList.back());
                cout<<nodeList.at(bInx).name<<"�� �ڽĿ� "<<nodeList.back().name<<" �߰�"<<endl;
                nodeList.at(bInx).showMyChildren();

            }
        }
    }
    for(auto n:nodeList){
        n.showMyChildren();
    }
    cout<<"��帮��Ʈ �ּҰ�"<<endl;
    for(auto a:nodeList){
        cout<<&(a.name)<<endl;
        cout<<a.name<<endl;
    }
    cout<<endl;
    cout<<"ù ������ڽĵ� �ּҰ�"<<endl;
    nodeList[0].showAdd();


return 0;
}

/*�����ͷ� �ϴϱ� ���� �̻�������.... �ذ�å�� �������?*/
