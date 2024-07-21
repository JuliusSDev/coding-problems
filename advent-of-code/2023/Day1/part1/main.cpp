#include <iostream>
#include <fstream>
#include "string.h"
using namespace std;
int main(){
    string line = "";
    ifstream inputFile ("message.txt");
    long allNumbers = 0;
    if(inputFile.is_open()){
        while(getline(inputFile,line)){
            int first = -1;
            int last = -1;
            for(char c : line){
                if(isdigit(c)){
                    if(first != -1){
                        last = (int)c - 48;
                    }else{
                        first = (int)c - 48;
                    }
                    
                }
            }
            if((first != -1) && (last != -1)){
                allNumbers = allNumbers + first*10 + last;
            }  else if((first != -1) && (last == -1)){
                allNumbers = allNumbers + first*10 + first;
            }else{
                exit(1);
            }
        }
    }
    cout << allNumbers<<endl;
}