#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Node{
private:
    int level;
    string data;
    vector<Node> childs;
    bool isReaf = 0;
public:
    Node(string _data, int _level){
        data = _data;
        level = _level;
        addChild();
    }
    void addChild(){
        if(data =="{}" || data==""){
            isReaf = 1;
        }
        else{
            int leftBrace = 0;
            int rightBrace = 0;
            string temp = "";
            for(int i = 1; i<data.size()-1; i++){
                if(data[i] == '{') leftBrace++;
                if(data[i] == '}') rightBrace++;
                temp += data[i];
                if(leftBrace == rightBrace){
                    childs.push_back(Node(temp, level+1));
                    leftBrace = 0;
                    rightBrace =0;
                    temp = "";
                }
            }
        }
    }

    int addAllChildsLevel(){
        int sum = 0;
        sum += level;
        for(auto c:childs){
            sum += c.addAllChildsLevel();
        }
        return sum;
    }

};

string getBrace(){
    string temp, brace = "{";
    int leftBrace = 0;
    int rightBrace = 0;
    bool isMainFunc = 0, startMainbrace = 0;
    while(1){
        getline(cin, temp);
        if(temp.find("main")!=temp.npos){
                isMainFunc = 1;
        }

        /*
        for main()
        {
         */
        if(isMainFunc == 1&& temp.find("{")!=temp.npos)
            startMainbrace = 1;

        for(int i = 0;i<temp.size();i++){
            if(temp[i] == '{'){
                brace += '{';
                leftBrace += 1;
            }
            if(temp[i] == '}'){
                brace += '}';
                rightBrace +=1;
            }
        }
        if(startMainbrace && leftBrace == rightBrace)
            break;
    }
    brace += '}';
    return brace;
}

int main(){
    string brace, temp;
    brace = getBrace();

    Node root = Node(brace, 0);
    cout<<root.addAllChildsLevel();
return 0;
};
