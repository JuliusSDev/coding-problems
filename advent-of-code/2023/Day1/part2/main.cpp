#include <iostream>
#include <fstream>
#include "string.h"
using namespace std;

bool isWrittenDigit(string input, int* digit){
    // cout << input <<endl;
    if(input == "" || input.length() < 3){
        return false;
    }
    int maxIndex = input.length()-1;
    if(input[maxIndex] == 'e'){
        if((input[maxIndex-1] == 'n') && (input[maxIndex-2] == 'o')){
            *digit = 1;
            return true;
        } else if((input[maxIndex-1] == 'e') && (input[maxIndex-2] == 'r') && (input[maxIndex-3] == 'h') && (input[maxIndex-4] == 't')){
            *digit = 3;
            return true;
        } else if((input[maxIndex-1] == 'v') && (input[maxIndex-2] == 'i') && (input[maxIndex-3] == 'f')){
            *digit = 5;
            return true;
        }else if((input[maxIndex-1] == 'n') && (input[maxIndex-2] == 'i') && (input[maxIndex-3] == 'n')){
            *digit = 9;
            return true;
        }else{
            return false;
        }
    } else if((input[maxIndex] == 'o')&& (input[maxIndex-1] == 'w') && (input[maxIndex-2] == 't')){
        *digit = 2;
        return true;
    } else if((input[maxIndex] == 'x')&& (input[maxIndex-1] == 'i') && (input[maxIndex-2] == 's')){
        *digit = 6;
        cout << "6 erkannt" << endl;
        return true;
    }else if((input[maxIndex] == 'r')&& (input[maxIndex-1] == 'u') && (input[maxIndex-2] == 'o') && (input[maxIndex-3] == 'f')){
        *digit = 4;
        return true;
    }else if((input[maxIndex] == 'n')&& (input[maxIndex-1] == 'e') && (input[maxIndex-2] == 'v') && (input[maxIndex-3] == 'e')&& (input[maxIndex-4] == 's')){
        *digit = 7;
        return true;
    }else if((input[maxIndex] == 't')&& (input[maxIndex-1] == 'h') && (input[maxIndex-2] == 'g') && (input[maxIndex-3] == 'i')&& (input[maxIndex-4] == 'e')){
        *digit = 8;
        return true;
    }
    return false;
}

int main(){
    string line = "";
    ifstream inputFile ("message.txt");
    long allNumbers = 0;
    if(inputFile.is_open()){
        while(getline(inputFile,line)){
            int first = -1;
            int last = -1;
            string checkForWrittenDigit = "";
            for(char c : line){
                // cout << c << endl;
                if(isalpha(c)){
                    if(checkForWrittenDigit.length() >=5){
                        checkForWrittenDigit.erase(0,1);
                        checkForWrittenDigit += c;
                    }else{
                        checkForWrittenDigit += c;
                    }
                }else{
                    checkForWrittenDigit = "";
                }
                int digitWasWritten = -1;
                cout << checkForWrittenDigit << endl;
                if(isdigit(c)){
                    if(first != -1){
                        last = (int)c - 48;
                    }else{
                        first = (int)c - 48;
                    }
                }else if(isWrittenDigit(checkForWrittenDigit, &digitWasWritten)){
                    if(first != -1){
                        last = digitWasWritten;
                    }else{
                        first = digitWasWritten;
                    }
                }
                // cout << first << " " << last << endl;
            }
            if((first != -1) && (last != -1)){
                allNumbers = allNumbers + first*10 + last;
                cout << first*10 + last << endl;
            }  else if((first != -1) && (last == -1)){
                allNumbers = allNumbers + first*10 + first;
                cout << first*10 + first << endl;
            }else{
                exit(1);
            }
        }
    }
    cout << allNumbers<<endl;
}