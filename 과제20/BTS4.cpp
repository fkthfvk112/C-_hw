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

    void swapTwoData(Node* node1, Node* node2) {
        string tempString;
        tempString = node1->data;
        node1->data = node2->data;
        node2->data = tempString;
    }

    void topToBottom() {
        if (this->child1 != NULL) { //from bottom
            //cout << "swap : " << this->data << this->child1->data << endl;
            swapTwoData(this, this->child1);
            this->child1->topToBottom();
        }
        else if (this->child2 != NULL) {
            //cout << "swap : " << this->data << this->child2->data << endl;
            swapTwoData(this, this->child2);
            this->child2->topToBottom();
        }
    }

    void bottomToUp() {//to private
        if (this->child1 != NULL) { //from bottom
            this->child1->bottomToUp();
            //cout << "swap : " << this->data << this->child1->data << endl;
            swapTwoData(this, this->child1);
        }
        else if (this->child2 != NULL) {
            this->child2->bottomToUp();
            //cout << "swap : " << this->data << this->child2->data << endl;
            swapTwoData(this, this->child2);
        }
    }

    void deleteChild(string deleteString) {
        if (this == NULL) return;
        if (this->child1 == NULL && this->child2 == NULL && this->data != deleteString) {
            swapTwoData(this, this->parent);
        }
        if (this->child1 == NULL && this->child2 == NULL && this->data == deleteString) {
            Node* parent = this->parent;
            if (parent->child1 != NULL && parent->child1->data == deleteString) {
                parent->child1 = NULL;
                free(this);
            }
            else if(parent->child2 != NULL && parent->child2->data == deleteString) {
                parent->child2 = NULL;
                free(this);
            }
            return;
        }
        if (this->child1 != NULL) {
            this->bottomToUp();
            child1->deleteChild(deleteString);
        }
        else if(this->child2 != NULL){
            this->topToBottom();
            child2->deleteChild(deleteString);
        };
    }


    Node* getNodePointerByData(string _data) {
        Node* searchedPointer = NULL;
        if (child1 == NULL && child2 == NULL) return searchedPointer;
        if (data == _data) searchedPointer = this;
        if (child1 != NULL && searchedPointer == NULL)searchedPointer = child1->getNodePointerByData(_data);
        if (child2 != NULL && searchedPointer == NULL)searchedPointer = child2->getNodePointerByData(_data);

        return searchedPointer;
    }

    void printDepthN(int goalDepth, int nowSearchingDepth = 0) {
        if (goalDepth == nowSearchingDepth) cout << this->data << " ";
        if (child1 == NULL && child2 == NULL) return;
        nowSearchingDepth++;
        if (this->child1 != NULL) {
            child1->printDepthN(goalDepth, nowSearchingDepth);
        }
        if (this->child2 != NULL) {
            child2->printDepthN(goalDepth, nowSearchingDepth);

        }
    }
    int depth(){
        int dn;
        int dl = 0;
        int dr = 0;
        if(child1 != NULL){
            dl += child1->depth();
        }
        if(child1 != NULL){
            dr += child2->depth();
        }
        if(dl>dr) dn = dl;
        else dn = dr;
        dn++;
        return dn;
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
            Node* searchingData = root->getNodePointerByData(inputString);
            searchingData->deleteChild(inputString);
        }
        if (inputString == "leaf") {
            root->printLeaf();
            cout << endl;
        }
        if (inputString == "depth") {
            int depthNumer;
            cin >> depthNumer;
            root->printDepthN(depthNumer);
            cout<<"µ¥"<<root->depth()<<endl;
            cout << endl;
        }
    }

    return 0;
}
