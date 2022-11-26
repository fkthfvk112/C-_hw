#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string data;
    Node* child1, * child2, * parent;
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
        if (willDeletedChild->child1 != NULL) {//¿ÞÂÊ Æ®¸® Á¸Àç
            replaceData = child1->maxValue();
            Node* changedData = getNodePointerByData(replaceData);
            free(changedData);
            willDeletedChild->data = replaceData;//»ðÀÔ
        }

        else {//¿ÞÂÊ Æ®¸® Á¸Àç X
            replaceData = child2->minValue();
            Node* changedData = getNodePointerByData(replaceData);
            free(changedData);
            willDeletedChild->data = replaceData;//»ðÀÔ
        }
    }

    string maxValue() {
        string maxData = "";
        if (child1 != NULL) maxData = child1->maxValue();
        if (child2 != NULL) maxData = child2->maxValue();
        if (maxData <= data) maxData = data;

        return maxData;
    }

    string minValue() {
        string minData = "";
        if (child1 != NULL) minData = child1->minValue();
        if (child2 != NULL) minData = child2->minValue();
        if (minData > data) minData = data;

        return minData;
    }

    Node* getNodePointerByData(string _data) {
        Node* searchedPointer = NULL;
        if (data == _data) searchedPointer = this;
        if (child1 != NULL && searchedPointer == NULL)searchedPointer = child1->getNodePointerByData(_data);
        if (child2 != NULL && searchedPointer == NULL)searchedPointer = child2->getNodePointerByData(_data);

        return searchedPointer;
    }

    void printDepthN(int goalDepth, int nowSearchingDepth = 1) {
        if (goalDepth == nowSearchingDepth) cout << this->data << " ";
        if (child1 != NULL) {
            child1->printDepthN(goalDepth, nowSearchingDepth++);
        }
        if (child2 != NULL) {
            child2->printDepthN(goalDepth, nowSearchingDepth++);

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

};

int main() {
    Node* root = new Node("phone");
    root->addChild("banana");
    root->addChild("chip");
    root->addChild("pizza");
    root->addChild("soccer");
    //cout << root->maxValue();
    //root->printAll();
    root->deleteChild("phone");
    //cout << root->child1->data;
    //root->printDepthN(3);
    root->printAll();
    return 0;
}
