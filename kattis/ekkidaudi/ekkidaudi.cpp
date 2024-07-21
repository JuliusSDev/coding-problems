#include <iostream>
#include <string.h>
using namespace std;

int main(){
    string inputLine1 = "";
    string inputLine2 = "";
    getline(cin, inputLine1);
    getline(cin, inputLine2);
    string subresult[4];
    
    int whichLine = 0;
    for(char c : inputLine1){
        if(c == '|'){
            whichLine++;
        } else {
            subresult[whichLine] += c;
        }
    }
    whichLine++;
    for(char c : inputLine2){
        if(c == '|'){
            whichLine++;
        } else {
            subresult[whichLine] += c;
        }
    }
    cout << subresult[0] << subresult[2] << " " <<subresult[1] << subresult[3] << endl;
}