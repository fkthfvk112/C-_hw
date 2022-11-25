#include <iostream>
#include <list>
#include <string>
using namespace std;
int v, totalSize;
list<int> fileSpace ;
list<string> fileName ;


void compactFile(){
    auto itS = fileSpace.begin();
    string preFileName;
    for(auto it = fileName.begin(); it != fileName.end(); it++, itS++){
        if(*it == "empty_space"){
            it = fileName.erase(it);
            itS =fileSpace.erase(itS);
            it--;
            itS--;
        }
        else{
            if(*it == preFileName){
                int temp = *itS;
                it = fileName.erase(it);
                itS = fileSpace.erase(itS);
                it--;
                *(--itS) += temp;
            }
        }
        preFileName = *it;
    }
}

void showFile(string &n){
    bool isIn = 0;
    int startingAdress = 0;
    auto itS = fileSpace.begin();
    for(auto it = fileName.begin(); it != fileName.end(); it++, itS++){
        if(*it == n){
            cout<<startingAdress<<" ";
            isIn = 1;
        }
        startingAdress += *itS;
    }
    if(isIn == 0) cout<<"error"<<endl;
    else cout<<endl;
}

void deleteFile(string &n){
    bool isIn = 0;
    auto itS = fileSpace.begin();
    for(auto it = fileName.begin(); it != fileName.end(); it++, itS++){
        if(*it == n){
            isIn = 1;
            *it = "empty_space";
            totalSize -= *itS;
        }
    }
    if(isIn == 0) cout<<"error"<<endl;
}

int totalSpaceIncludeEmpty(){
    int result = 0;
    for(auto n:fileSpace){
        result+=n;
    }
    return result;
}
bool writeFile(string &n, int &filesize){
    for(auto f:fileName){
        if(f == n){
            cout<<"error"<<endl;
            return 0;
        }
    }

    if(totalSize + filesize > v){
        cout<<"diskfull"<<endl;
        return 0;
    }
    int tempSize;

    totalSize += filesize;


    if(v - totalSpaceIncludeEmpty() > 0){
        fileName.push_back("empty_space");
        fileSpace.push_back(v-totalSpaceIncludeEmpty());
    }

    //can be inserted whole
    auto it = fileName.begin();
    for(auto itS = fileSpace.begin(); itS != fileSpace.end(); itS++, it++){
        if(*it == "empty_space" && *itS >= filesize){
            tempSize = *itS - filesize;
            *itS = filesize;
            *it = n;
            if(tempSize>0){
                fileName.insert(++it, "empty_space");
                fileSpace.insert(++itS, tempSize);
                it--;
                itS--;
            }
            return 1;
        }
    }


    //can't be inserted whole
    auto itS = fileSpace.begin();
    for(auto it = fileName.begin(); it != fileName.end(); it++, itS++){
        if(filesize == 0) break;//check for empty space(Advance)
        if(*it == "empty_space"){
            *it = n;
            tempSize = filesize - *itS;
            if(tempSize < 0){//empty space > filesize
                int emptySpace = -tempSize;
                *itS = filesize;
                it++;
                itS++;
                fileName.insert(it, "empty_space");
                fileSpace.insert(itS, emptySpace);
                filesize = 0;
            }
            else{//filesize > empty space
                filesize = filesize - *itS;
            }
        }
    }
    if(filesize > 0){
        fileName.push_back(n);
        fileSpace.push_back(filesize);
    }

    return 1;
}

int main(){
    cin>>v;
    string func, n;
    while(1){
        cin>>func;
        if(func == "write"){
            int filesize;
            cin>>n>>filesize;
            writeFile(n, filesize);
        }
        else if(func == "delete"){
            cin>>n;
            deleteFile(n);
        }
        else if(func == "show"){
            cin>>n;
            showFile(n);
        }
        else if(func == "compact"){
            compactFile();
        }
        else break;
        //cout<<endl;
        //cout<<"name"<<endl;
/*

        for(auto f:fileName){
            cout<<f<<" ";
        }

        cout<<endl;
        cout<<"space"<<endl;
        for(auto f:fileSpace){
            cout<<f<<" ";
        }
        cout<<endl;
        cout<<endl;
*/
    }

}
