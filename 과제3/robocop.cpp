#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define TOP 0
#define RIGHT 1
#define BOTTOM 2
#define LEFT 3

using namespace std;


class Point{
public:
    int pX, pY;
public:
    Point(int x= -1, int y = -1):pX(x), pY(y){};
};

class Node{
private:
    int nodeNumber, direction;
    vector <Point> nodeList;
    Point currentNode, nextNode, location;
public:
    Node(int _nodeNumber){
        nodeNumber = _nodeNumber;
    };
    void addNode(Point p){
        nodeList.push_back(p);
    };
    void setNodeLocation(){
        if(nodeList.size()>1){
            currentNode = location = nodeList[0];
            nextNode = nodeList[1];
            setDirection();
        }
    }

    void setDirection(){
        int dx = nextNode.pX - currentNode.pX;
        int dy = nextNode.pY - currentNode.pY;
        if(dx == 0 && dy > 0)
            direction = TOP;
        else if(dx == 0 && dy < 0)
            direction = BOTTOM;
        else if(dx < 0 && dy == 0)
            direction = LEFT;
        else if(dx > 0 && dy == 0)
            direction = RIGHT;
    }

    void inTheNode(){
        for(int i = 0; i < nodeNumber; i++){
            if(location.pX == nodeList[i].pX &&
               location.pY == nodeList[i].pY){
            currentNode = nodeList[i%nodeNumber];
            nextNode = nodeList[(i+1)%nodeNumber];
            setDirection();
            break;
            }
        }
    }

    void move(queue <int> times, int maxtime){
        int cnt = 0;
        while(cnt < maxtime){
            if(direction == TOP)location.pY ++;
            if(direction == RIGHT)location.pX ++;
            if(direction == BOTTOM)location.pY --;
            if(direction == LEFT)location.pX --;
            inTheNode();
            if(cnt+1 == times.front()){
                cout<<location.pX<<" "<<location.pY<<endl;
                times.pop();
                setNodeLocation();
                cnt = -1;
            }
            if(times.empty()) break;
            cnt++;
        }
    }
};


int main(void){
    int nodeNum = 0, maxtime = 0, tempTime[5];
    queue <int> time;
    cin>>nodeNum;
    Node node = Node(nodeNum);
    for(int i = 0; i < nodeNum; i++){
        int x, y;
        cin>>x>>y;
        node.addNode(Point(x, y));
    }
    node.setNodeLocation();

    maxtime = *max_element(tempTime, tempTime+6);
    for(int i= 0; i<5;i++){
        cin>>tempTime[i];
        time.push(tempTime[i]);
    }
    node.move(time, maxtime);

    return 0;
}
