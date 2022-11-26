#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string data;
    Node* parent, *child1, * child2;
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

    void deleteChild(string _data) {
        Node* willDeletedChild = getNodePointerByData(_data);
        if (willDeletedChild == NULL) return;

        string replaceData = "";

        if (willDeletedChild->child1 == NULL && willDeletedChild->child2 == NULL) {
            if (willDeletedChild->parent->data < willDeletedChild->data) willDeletedChild->parent->child2 = NULL;
            else willDeletedChild->parent->child1 = NULL;
            free(willDeletedChild);
            return;
        }
        if (willDeletedChild->child1 != NULL) {//왼쪽 트리 존재
            replaceData = willDeletedChild->child1->maxValue();
            if (replaceData == "a(minimal)") replaceData = child1->data;
            Node* changedData = getNodePointerByData(replaceData);
            //추가


            //삭제
            if (changedData->parent->data < changedData->data) changedData->parent->child2 = NULL;
            else changedData->parent->child1 = NULL;
            free(changedData);
            willDeletedChild->data = replaceData;//교체
        }

        else {//왼쪽 트리 존재 X
            replaceData = willDeletedChild->child2->minValue();
            if (replaceData == "z(maximum)") replaceData = child2->data;
            Node* changedData = getNodePointerByData(replaceData);
            if (changedData->parent->data < changedData->data) changedData->parent->child2 = NULL;
            else changedData->parent->child1 = NULL;
            free(changedData);
            willDeletedChild->data = replaceData;//삽입
        }
    }

    void deleteChild(string inputString) {
        if (this->child1 == NULL, this->child2 == NULL) {
            if (this->parent->child1 != NULL && this->parent->child1->data == inputString) {
                this->parent->child1->data = "";
                this->parent->child1 = NULL;
            }
            if(this->parent->child2 != NULL && this->parent->child2->data == inputString) {
                this->parent->child2->data = "";
                this->parent->child2 = NULL;
            }
            free(this);

            return;
        }
        if (this->child1 != NULL) {
            swapTwoNodeData(this, this->child1);
            this->child1->deleteChild(inputString);
        }
        else {
            swapTwoNodeData(this, this->child2);
            this->child2->deleteChild(inputString);
        }
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

    void printAll() {
        cout << this->data << endl;
        if (child1 != NULL) {
            child1->printAll();
        }
        if (child2 != NULL) {
            child2->printAll();
        }

        //cout << this->data << endl;

    }

    void printLeaf() {
        if (child1 != NULL) child1->printLeaf();
        if (this->child1 == NULL && this->child2 == NULL)cout << this->data << " ";
        if (child2 != NULL) child2->printLeaf();
    }

    void swapTwoNodeData(Node* n1, Node* n2) {
        string tempData;

        tempData = n1->data;

        n1->data = n2->data;
        n2->data = tempData;
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
            deletNode->deleteChild(inputString);
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


    /*

    Node* root = new Node("", NULL);
    root->addChild("phone");
    root->addChild("banana");
    root->addChild("chip");
    root->addChild("pizza");
    root->addChild("soccer");
    //cout << root->maxValue();
    //root->printAll();
    root->deleteChild("phone");
    root->printDepthN(3);
    cout << endl;
    root->addChild("machine");
    cout << endl;
    root->printDepthN(2);
    root->deleteChild("pizza");
    //cout << root->child1->data;
    root->printReaf();
    //root->printAll();
    */
    return 0;
}
