#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <deque>

#define TOP 1
#define RIGHT 2
#define BOTTOM -1
#define LEFT -2
#define CLOCKWISE 1
#define ANTICLOCKWISE -1

using namespace std;

class Point{
public:
    int pX, pY;
    Point(int x= -1, int y = -1):pX(x), pY(y){};
};

class Node{
public:
    int nodeNumber, direction, lotate;
    deque <Point> nodeList;
    Point currentNode, nextNode, location;
    Node(int _nodeNumber, int _lotate){
        nodeNumber = _nodeNumber;
        lotate = _lotate;
    };
    void addNode(Point p){
        if(lotate == CLOCKWISE)
            nodeList.push_back(p);
        if(lotate == ANTICLOCKWISE)
            nodeList.push_front(p);
    };
    void setNodeLocation(){
        if(nodeList.size()>=1){
            if(lotate == CLOCKWISE){
                currentNode = location = nodeList[0];
                nextNode = nodeList[1];
                setDirection();
                }
            if(lotate == ANTICLOCKWISE){
                currentNode = location = nodeList[nodeNumber/2];
                nextNode = nodeList[nodeNumber/2 + 1];
                setDirection();
            }
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

    bool isCrush(Node& object){
        if(object.location.pX == location.pX && abs(object.location.pY - location.pY)<=1) return 1;
        else if(object.location.pY == location.pY && abs(object.location.pX - location.pX)<=1) return 1;
        return 0;
    }

    void move(){
        int cnt = 0;
            if(direction == TOP)location.pY ++;
            if(direction == RIGHT)location.pX ++;
            if(direction == BOTTOM)location.pY --;
            if(direction == LEFT)location.pX --;
            inTheNode();
    }

    void printLocation(){
        cout<<location.pX<<" "<<location.pY<<endl;
    }
};


int main(void){
    int nodeNum = 0, maxtime = 0, tempTime[5];
    int time;
    cin>>nodeNum;
    Node cop1 = Node(nodeNum, CLOCKWISE);
    Node cop2 = Node(nodeNum, ANTICLOCKWISE);
    Node temp = Node(0, 0);


    for(int i = 0; i < nodeNum; i++){
        int x, y;
        cin>>x>>y;
        cop1.addNode(Point(x, y));
        cop2.addNode(Point(x, y));
    }
    cop1.setNodeLocation();
    cop2.setNodeLocation();

    cin>>time;
    for(int i = 0; i < time; i++){
        if(cop1.isCrush(cop2)){
            temp = cop1;
            cop1 = cop2;
            cop2 = temp; //swap
        }
        cop1.move();
        cop2.move();

    }
    cop1.printLocation();
    cop2.printLocation();

    return 0;
}
