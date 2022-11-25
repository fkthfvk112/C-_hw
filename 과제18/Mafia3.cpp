#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;


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

    void setAllLevel(int l = 0){
        l++;
        for(auto c:children){
            c->setAllLevel(l);
        }
        level = l;
    }

    void pushChildren(Node* n) {
        children.emplace_back(n);
    }
    int setAllChildrenNumber() {
        for (auto c : children) {
            childrenNum += c->setAllChildrenNumber();
            childrenNum++;
        }

        return childrenNum;
    }
/*will write getter and setter, public->private
    string getName() {
        return name;
    }
*/
};
vector<Node*> nodeList;
vector<string> nodeNames;
bool weight(Node* a, Node* b){
    if(!(a->childrenNum == b->childrenNum))return  a->childrenNum > b->childrenNum;;
    if(!(a->level == b->level))return a->level < b->level;
    else return a->name < b->name;
}
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
                nodeList.at(pInx)->isNotBoss();
                nodeList.at(bInx)->pushChildren(nodeList.at(pInx));
            }
            else {
                Node* temp = new Node(p);
                temp->isNotBoss();
                nodeList.emplace_back(temp);
                nodeNames.emplace_back(p);
                nodeList.at(bInx)->pushChildren(temp);
            }
        }

        else if (!bIsInList) {
            Node* temp = new Node(b);
            nodeList.emplace_back(temp);
            nodeNames.emplace_back(b);
            bInx = nodeNames.end() - 1 - nodeNames.begin();

            if (pIsInList) {
                nodeList.at(pInx)->isNotBoss();
                nodeList.back()->pushChildren(nodeList.at(pInx));
            }
            else {
                Node* tempP = new Node(p);
                tempP->isNotBoss();
                nodeList.emplace_back(tempP);
                nodeNames.emplace_back(p);
                nodeList.at(bInx)->pushChildren(tempP);
            }
        }
    }

    for (auto n : nodeList) {
        if (n->isBoss) {//boss is root
            n->setAllChildrenNumber();
            n->setAllLevel();
        }
    }

    sort(nodeList.begin(), nodeList.end(), weight);
    for (auto n : nodeList) {
        cout << n->name<<endl;
    }


    return 0;
}
