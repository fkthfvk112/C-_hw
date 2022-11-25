#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
//1. �� ����ֱ� 2. set�Լ��� 3.
using namespace std;


//���Ϳ� node����
//nodeŬ���������� �����ͷ� ���

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
        cout << name << "�� �ڽ� " << endl;
        for (auto n : children) {
            cout << n->name << endl;
        }
    }

    void pushChildren(Node* n) { //���� �缳�� �ؾ��ؿ�!!
        children.emplace_back(n);
    }
    int setAllChildrenNumber() {
        cout << name << "���� ȣ��" << endl;
        for (auto c : children) {
            childrenNum += c->setAllChildrenNumber();
            childrenNum++;
            cout << c->name << "�� ĥ�己 �� " << c->childrenNum << endl;
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

/*�����ͷ� �ϴϱ� ���� �̻�������.... �ذ�å�� �������?*/
//1���� ���� ���ϱ�, 2���������κ��� ����Լ��� �� �Ҵ�,3sort�� ���� �־ �Ǵ� 4, ���
//nodelist�� �����ͷ� ���ϴϱ� ������ ����.......��??
