#include <iostream>
#include <string>

using namespace std;
class Music{
public:
    Music(string _T  = "NoMusic", string _G = "NoMusic", int _B  = 0, double _S = 0, int _D = 0){
        T = _T;
        G = _G;
        B = _B;
        S = _S;
        D = _D;
    }
        string T, G;
        int B, D;
        double S;
};

class Jamong{
    int size;
    Music *musics;
    int addI= 0;
    bool isSeqG(Music pre, Music now){
        if(pre.G == now.G) return 1;
        return 0;
    }

    bool isOnlyG(Music now, int index){
        if(index +1 < size)
            for(int i= index+1; i<size;i++){
                if(now.G == musics[i].G) return 0;
            }
        return 1;
    }

    void arrange(){
        for(int i = 0; i<size;i++){
            for(int j=1;j<size-1-i;j++){
                if(isSeqG(musics[j-1], musics[j])){
                    if(isOnlyG(musics[j], j)) continue;
                    else{
                        Music temp;
                        temp = musics[j];
                        musics[j] = musics[j+1];
                        musics[j+1] = temp;
                    }
                }
            }
        }
    }
    public:
    Jamong(int _size){
        size = _size;
        musics = new Music[size];
    }

    void add(Music m){
        musics[addI] = m;
        addI++;
    };

    void sort(){
        for(int j =0;j<size;j++){
            for(int i=0;i<size-1-j;i++){ //bubble sort
                if(musics[i].B < musics[i+1].B){
                    Music temp;
                    temp = musics[i];
                    musics[i] = musics[i+1];
                    musics[i+1] = temp;
                }

                else if(musics[i].B == musics[i+1].B){
                    if(musics[i].D < musics[i+1].D){
                        Music temp;
                        temp = musics[i];
                        musics[i] = musics[i+1];
                        musics[i+1] = temp;
                    }
                    else if(musics[i].D == musics[i+1].D){
                        if(musics[i].S > musics[i+1].S){
                            Music temp;
                            temp = musics[i];
                            musics[i] = musics[i+1];
                            musics[i+1] = temp;
                        }
                    }
                }
            }
        }
        arrange();
    }
    void printN(int& n){
        cout<<musics[n-1].T<<endl;
    }

};

int main(){
    int musicSize;
    int searchingNum;
    cin>>musicSize;
    cin>>searchingNum;

    Jamong jamong = Jamong(musicSize);

    string T, G;
    int B, D;
    double S;
    for(int i = 0; i < musicSize; i++){
            cin>>T>>G>>B>>S>>D;
        jamong.add(Music(T, G, B, S, D));
    }
    jamong.sort();
    jamong.printN(searchingNum);
return 0;
}
