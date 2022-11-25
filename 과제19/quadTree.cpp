#include <iostream>
#include <array>
#include <cmath>
using namespace std;


class QuadTree {
public:
    string data = "";
    QuadTree* first, * second, * third, * fourth;

public:
    QuadTree() {
        first = second = third = fourth = NULL;
    }
    void setTreeByQTS(string qts) {
        if (qts[0] != '(') {
            data = qts[0];
            return;
        }
        string temp = "";
        for (int i = 1; i < qts.size() - 1; i++) {
            temp += qts[i];
        }//cut front back

        int leftBrace = 0, rightBrace = 0, inx = 0;
        string seperatedQts = "";
        bool isSubQts = 0;
        for (auto t : temp) {
            seperatedQts += t;
            if (t == '(') {
                leftBrace++;
                continue;
            }
            else if (t == ')') {
                rightBrace++;
                if (leftBrace == rightBrace) {
                    leftBrace = rightBrace = 0;
                    isSubQts = 1;
                }
            }
            else if (leftBrace == 0 && rightBrace == 0 && t != '(') {
                isSubQts = 1;
            }
            if (isSubQts) {
                switch (inx) {
                case 0: {
                    QuadTree* temp = new QuadTree();
                    first = temp;
                    first->setTreeByQTS(seperatedQts);
                    break;
                }
                case 1: {
                    QuadTree* temp = new QuadTree();
                    second = temp;
                    second->setTreeByQTS(seperatedQts);
                    break;
                }
                case 2: {
                    QuadTree* temp = new QuadTree();
                    third = temp;
                    third->setTreeByQTS(seperatedQts);
                    break;
                }
                case 3: {
                    QuadTree* temp = new QuadTree();
                    fourth = temp;
                    fourth->setTreeByQTS(seperatedQts);
                    break;
                }
                }
                inx++;
                isSubQts = 0;
                seperatedQts = "";
            }
        }
    }

    void setImage(bool** img, int rs, int cs, int length) {
        if (data == "1") {
            for (int i = rs; i < rs + length; i++) {
                for (int j = cs; j < cs + length; j++) {
                    img[i][j] = 1;
                }
            }
            return;
        }
        bool isReaf = (first == NULL && second == NULL && third == NULL && fourth == NULL);
        if (isReaf) {
            return;
        }
        first->setImage(img, rs, cs + length / 2, length / 2);
        second->setImage(img, rs, cs, length / 2);
        third->setImage(img, rs + length / 2, cs, length / 2);
        fourth->setImage(img, rs + length / 2, cs + length / 2, length / 2);
    }
};
int main() {
    int n, imgSize;
    string selectImgOrQts;
    cin >> n >> selectImgOrQts;
    imgSize = pow(n, 2);
    bool** img = new bool* [imgSize]; //n*n array
    for (int i = 0; i < imgSize; i++) {
        img[i] = new bool[imgSize];
    }

    if (selectImgOrQts == "Img") {
        int element;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> element;
                img[i][j] = element;
            }
        }
        //setTreeByImg(img, n);
    }
    if (selectImgOrQts == "QTS") {
        QuadTree root = QuadTree();
        string qts;
        cin >> qts;
        for (int i = 0; i < imgSize; i++) {
            for (int j = 0; j < imgSize; j++) {
                img[i][j] = 0;
            }
        }
        root.setTreeByQTS(qts);
        root.setImage(img, 0, 0, imgSize);
        for (int i = 0; i < imgSize; i++) {
            for (int j = 0; j < imgSize; j++) {
                cout << img[i][j];
            }
            cout << endl;
        }
    }


    return 0;
}
