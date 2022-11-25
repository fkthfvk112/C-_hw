#include <iostream>
#include <vector>

using namespace std;

class Point{
int x;
int y;
public:
    Point(const int &_x,const int &_y) : x(_x), y(_y) {}
    int getX()   {return x;}
    int getY()   {return y;}
    int getSum() {return x+y;}
};

int main(){
    int until;
    int x, y;
    vector<Point> points;
    cin >> until;
    while (until--){
        cin >> x >> y;
        points.push_back(Point(x, y));
    }
    points.push_back(points[0]);

    vector<int> distances;
    for (int i = 0; i < points.size() - 1; i++){
        distances.push_back(abs(points[i].getSum() - points[i + 1].getSum()));
    }

    for (int j = 0; j < 5; j++){
        int timePoint;
        cin >> timePoint;
        long tempSum = 0;
        int pointIndex = 0;
        while (timePoint >= tempSum+distances[pointIndex]){
            tempSum += distances[pointIndex++];
            if (pointIndex == distances.size()) pointIndex = 0;
        }
        int distance = timePoint - tempSum;
        int answerX = points[pointIndex].getX();
        int answerY = points[pointIndex].getY();
        Point nextPoint = points[pointIndex+1];

        if(answerX < nextPoint.getX())      answerX += distance;
        else if(answerX > nextPoint.getX()) answerX -= distance;
        else if(answerY < nextPoint.getY()) answerY += distance;
        else if(answerY > nextPoint.getY()) answerY -= distance;

        cout << answerX << ' ' << answerY << endl;
    }
}
