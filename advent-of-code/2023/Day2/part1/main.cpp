#include <iostream>
#include <fstream>
#include "string.h"
using namespace std;

const int RED = 12;
const int GREEN = 13;
const int BLUE = 14;

int handleNumber(string smallerSegment){
    string numStr = "";
    while (smallerSegment[0] == ' '){
        smallerSegment.erase(0,1);
    }
    for(char c: smallerSegment){
        if(c == ' '){
            return stoi(numStr);
        }else{
            numStr += c;
        }
    }
    exit(1);
}
struct rgb
{
    int red;
    int blue;
    int green;
};

void handleSmallerSegment(string smallerSegment, rgb *rgbs){
    if(smallerSegment.find("green") != string::npos){
        int number = handleNumber(smallerSegment);
        cout << "green: " << number << endl;
        if(number > rgbs->green){
            rgbs->green = number;
        }
    }else if(smallerSegment.find("blue") != string::npos){
        int number = handleNumber(smallerSegment);
        cout << "blue: " << number << endl;
        if(number > rgbs->blue){
            rgbs->blue = number;
        }
    }else if(smallerSegment.find("red") != string::npos){
        int number = handleNumber(smallerSegment);
        cout << "red: " << number << endl;
        if(number > rgbs->red){
            rgbs->red = number;
        }
    }
}

void handleSegment(string segment, rgb *rgbs){
    string smallerSegment;
    // cout << "Segment: " << segment <<endl;
    for (char c: segment){
        if(c != ','){
            smallerSegment +=c;
        }else{
            handleSmallerSegment(smallerSegment, rgbs);
            smallerSegment = "";
        }
    }
    handleSmallerSegment(smallerSegment, rgbs);


}

bool handleLine(string line, int id){
    cout << "Line: " << line <<endl;
    rgb rgbs = {.red = 0, .blue = 0, .green = 0};
    string segment = "";
    for(char c: line){
        if(c == ';'){
            handleSegment(segment, &rgbs);
            segment = "";
        }else if(c == ':'){
            segment = "";
        }else{
            segment += c;
        }
        // cout << "Segment1: " << c << " " << segment << endl;
    }
    handleSegment(segment, &rgbs);

    if((rgbs.blue <= BLUE) && (rgbs.red <= RED) && (rgbs.green <= GREEN)){
        return true;
    }else{
        return false;
    }
}
int main(){
    
    ifstream inputFile ("data.txt");
    int sum = 0;
    if(inputFile.is_open()){
        int id = 0;
        string line = "";
        while(getline(inputFile,line)){
            id++;
            
            if(handleLine(line, id)){
                sum += id;
            }
        }
    }
    cout << sum << endl;
}