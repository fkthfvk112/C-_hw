#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string data;
    Node* parent, * child1, * child2;
public:
    Node(string _data, Node* _parent) {
        data = _data;
        parent = _parent;
        child1 = NULL;
        child2 = NULL;
    }

    void addChild(string _data) {
        bool inputIsBigger = (data < _data);
        bool inputIsSmaller = (data >= _data);

        if (inputIsSmaller && child1 == NULL) {
            child1 = new Node(_data, this);
            return;
        }
        else if (inputIsBigger && child2 == NULL) {
            child2 = new Node(_data, this);
            return;
        }
        if (inputIsSmaller) child1->addChild(_data);
        if (inputIsBigger) child2->addChild(_data);
    }

    string deleteChild(string inputString) {
        string replaceData = "";
        if (this->child1 == NULL, this->child2 == NULL) {
            Node* parent = this->parent;
            if (parent->child1 != NULL) {
                replaceData = parent->child1->data;
                parent->child1->data = "";
                parent->child1 = NULL;
            }
            if (parent->child2 != NULL) {
                replaceData = parent->child2->data;
                parent->child2->data = "";
                parent->child2 = NULL;
            }
            free(this);
        }
        if (replaceData == "") {
            if (this->child1 != NULL) {
                replaceData = this->child1->deleteChild(inputString);
            }
            else {
                replaceData = this->child2->deleteChild(inputString);
            }
        }
        return replaceData;
    }

    Node* getNodePointerByData(string _data) {
        Node* searchedPointer = NULL;
        if (data == _data) searchedPointer = this;
        if (child1 != NULL && searchedPointer == NULL)searchedPointer = child1->getNodePointerByData(_data);
        if (child2 != NULL && searchedPointer == NULL)searchedPointer = child2->getNodePointerByData(_data);

        return searchedPointer;
    }

    void printDepthN(int goalDepth, int nowSearchingDepth = 0) {
        if (goalDepth == nowSearchingDepth) cout << this->data << " ";
        nowSearchingDepth++;
        if (child1 != NULL) {
            child1->printDepthN(goalDepth, nowSearchingDepth);
        }
        if (child2 != NULL) {
            child2->printDepthN(goalDepth, nowSearchingDepth);

        }
    }
    void printLeaf() {
        if (child1 != NULL) child1->printLeaf();
        if (this->child1 == NULL && this->child2 == NULL)cout << this->data << " ";
        if (child2 != NULL) child2->printLeaf();
    }
};

int main() {
    string inputString;
    Node* root = new Node("", NULL);
    while (inputString != "quit") {
        cin >> inputString;
        if (inputString == "+") {
            cin >> inputString;
            root->addChild(inputString);
        }
        if (inputString == "-") {
            cin >> inputString;
            Node* deletNode = root->getNodePointerByData(inputString);
            if (deletNode == NULL) continue;
            else if (deletNode->child1 == NULL && deletNode->child2 == NULL) {
                if (deletNode->parent->data < deletNode->data)deletNode->parent->child2 = NULL;
                else deletNode->parent->child1 = NULL;
                free(deletNode);
                continue;
            }
            deletNode->data = deletNode->deleteChild(inputString);
        }
        if (inputString == "leaf") {
            root->printLeaf();
            cout << endl;
        }
        if (inputString == "depth") {
            int depthNumer;
            cin >> depthNumer;
            root->printDepthN(depthNumer);
            cout << endl;
        }
    }

    return 0;
}
