#include <iostream>
#include <vector>
#include <algorithm>
#define ROW 1
#define COL 2

using namespace std;


class Tree{
    public:
    int val, lineN;
    int state = ROW;

    Tree(int _rowVal, int _rowN){
        val = _rowVal;
        lineN = _rowN;
    }
    void convertToCol(){
        state = COL;
        int temp;
        temp = val;
        val = lineN;
        lineN = temp;
    }
};


bool weight(const Tree &t1, const Tree &t2){
    return t1.lineN < t2.lineN;
}

class Trees{
    private:
    vector <Tree> trees;
    int space;

    public:
    Trees(int n){
        space = n;
    }
    void pushToTrees(Tree t){
        trees.push_back(t);
    }

    void sorting(){
        sort(trees.begin(), trees.end(), weight);
    }


    void printTreesLocation(){
        sorting();
        int gap = 0, cnt = 0;
        cout<<space<<endl;
        if(trees.at(0).lineN > 1){
            cout<<"0 "<<trees.at(0).lineN -1<<endl;
        }
        for(int i= 0;i<trees.size();i++){
            gap = trees.at((i+1)%trees.size()).lineN - trees.at(i).lineN -1;
            if(gap == -1){
                cout<<trees.at(i).val<<" ";
            }
            else if(gap == 0 || gap < -1){
                cout<<trees.at(i).val<<" 0"<<endl;
            }
            else{
                cout<<trees.at(i).val<<" 0"<<endl;
                cout<<"0 "<<gap<<endl;
            }
        }
        if(trees.back().lineN < space){
            cout<<"0 "<<space - trees.back().lineN<<endl;
        }

    }
};


int main(){

int n, rowVal, rowN, endOrNot, lineN = 0, space;
cin>>n;
Trees trees(n);

while(lineN<n){
    lineN++;
    cin>>rowVal;
    if(rowVal == 0){
        cin>>space;
        lineN += space-1;
    }
    else{
        Tree t = Tree(Tree(rowVal, lineN));
        t.convertToCol();
        trees.pushToTrees(t);

        for(int i = 0; i<n;i++){
            cin>>rowVal;
            if(rowVal ==0) break;
            Tree t = Tree(Tree(rowVal, lineN));
            t.convertToCol();
            trees.pushToTrees(t);

        }
    }
}

trees.printTreesLocation();

return 0;
}
