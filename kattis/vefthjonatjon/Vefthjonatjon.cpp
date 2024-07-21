#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

int main(){
    int n = 0;
    cin >> n;
    vector<string> in ;
    for(int i = 0; i<= n; i++){
        string input;
        getline(cin, input);
        in.push_back(input);
    }
    int cpu = 0;
    int mem = 0;
    int hdd = 0;
    for(int i = 0; i < in.size(); i++){
        for (int c = 0; c < in[i].size(); c++)
        {
            string line = in[i];
            if (line[c] == 'J')
            {
                if(c == 0) cpu++;
                if(c == 2) mem++;
                if(c == 4) hdd++;
            } 
        }
    }
    if(cpu <= mem && cpu <= hdd){
        cout << cpu << endl;
    } else if(mem <= cpu && mem <= hdd){
        cout << mem << endl;
    }
    else if(hdd <= cpu && hdd <= mem){
        cout << hdd << endl;
    } 
    else{
        cout << "ERROR" << endl;
    }
}