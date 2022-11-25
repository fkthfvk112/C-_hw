#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
//1. 다 집어넣기 2. set함수들 3.
using namespace std;


//벡터에 node저장
//node클래스에서는 포인터로 사용

class Node {
public:
    string name;
    int childrenNum = 0;
    int level = 0;
    int isBoss = 1;
    vector<Node*> children;
public:
    Node(string _name) {
        name = _name;
        children.reserve(100000);
    }
    void isNotBoss() {
        isBoss = 0;
    }
    void showAdd() {
        for (auto itr = children.begin(); itr != children.end(); itr++) {
            cout << &(*itr) << endl;
        }
    }
    void showMyChildren() {
        cout << name << "의 자식 " << endl;
        for (auto n : children) {
            cout << n->name << endl;
        }
    }

    void pushChildren(Node* n) { //레벨 재설정 해야해요!!
        children.emplace_back(n);
    }
    int setAllChildrenNumber() {
        cout << name << "에서 호출" << endl;
        for (auto c : children) {
            childrenNum += c->setAllChildrenNumber();
            childrenNum++;
            cout << c->name << "의 칠드런 수 " << c->childrenNum << endl;
        }

        return childrenNum;
    }

    string getName() {
        return name;
    }
};
vector<Node> nodeList;
vector<string> nodeNames;

int main() {
    nodeList.reserve(1000000);//for prevent rearrange of address
    int nodeNumber;
    cin >> nodeNumber;
    string p, b;
    for (int i = 0; i < nodeNumber - 1; i++) {
        cin >> p >> b;
        auto pItr = find(nodeNames.begin(), nodeNames.end(), p);
        auto bItr = find(nodeNames.begin(), nodeNames.end(), b);

        bool pIsInList = (pItr != nodeNames.end());
        bool bIsInList = (bItr != nodeNames.end());
        int pInx = pItr - nodeNames.begin();
        int bInx = bItr - nodeNames.begin();

        if (bIsInList) {
            if (pIsInList) {
                nodeList.at(pInx).isNotBoss();
                nodeList.at(bInx).pushChildren(&nodeList.at(pInx));
                //nodeList.at(bInx).showMyChildren();

            }
            else {
                Node* temp = new Node(p);
                temp->isNotBoss();
                nodeList.emplace_back(*temp);
                nodeNames.emplace_back(p);
                nodeList.at(bInx).pushChildren(temp);
                nodeList.at(bInx).showMyChildren();

            }
        }

        else if (!bIsInList) {
            Node* temp = new Node(b);
            nodeList.emplace_back(*temp);
            nodeNames.emplace_back(b);
            bInx = nodeNames.end() - 1 - nodeNames.begin();

            if (pIsInList) {
                nodeList.at(pInx).isNotBoss();
                nodeList.back().pushChildren(&nodeList.at(pInx));
                nodeList.at(bInx).showMyChildren();

            }
            else {
                //Node* tempBoss = &nodeList.back();
                Node* tempP = new Node(p);
                tempP->isNotBoss();
                nodeList.emplace_back(*tempP);
                nodeNames.emplace_back(p);
                //tempBoss->pushChildren(&nodeList.back()); why error?
                nodeList.at(bInx).pushChildren(tempP);
                nodeList.at(bInx).showMyChildren();

            }
        }
    }


    for (auto n : nodeList) {
        if (n.isBoss) {
            n.setAllChildrenNumber();
        }
    }
    for (auto n : nodeList) {
        cout << n.name << " : level : " << n.level << endl;
    }


    return 0;
}

/*포인터로 하니까 값이 이상해진다.... 해결책이 있을까요?*/
//1최종 보스 구하기, 2최종보스로부터 재귀함수로 값 할당,3sort에 조건 넣어서 판단 4, 출력
//nodelist를 포인터로 안하니까 오류가 난다.......왜??
