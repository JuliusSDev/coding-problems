#include <fstream>
#include <iostream>
using namespace std;

struct lineData
{
    string lastLine;
    string currentLine;
    string nextLine;
};


bool checkForFirstSymbol(lineData lines, int i){
    //  _ _ _
    //  _ 1 
    //
    bool returnVal = false;
    if(i > 0){
        if (lines.currentLine[i-1] != '.' && !isdigit(lines.currentLine[i-1])){
            cout << "before ";
            returnVal = true;
        }

        if(!isdigit(lines.lastLine[i-1]) && lines.lastLine[i-1] != '.'){
            cout << "upperLeft ";
            returnVal = true;
        }

        if(!isdigit(lines.nextLine[i-1]) && lines.nextLine[i-1] != '.'){
            cout << "lowerLeft ";
            returnVal = true;
        }
    }
    if(!isdigit(lines.lastLine[i]) && lines.lastLine[i] != '.'){
        cout << "upperMiddle ";
        returnVal = true;
    }
    if(!isdigit(lines.nextLine[i]) && lines.nextLine[i] != '.'){
        cout << "lowerMiddle ";
        returnVal = true;
    }
    if(i < (lines.currentLine.size() - 1)){
        if (lines.currentLine[i+1] != '.' && !isdigit(lines.currentLine[i+1])){
            cout << "next ";
            returnVal = true;
        }

        if(!isdigit(lines.lastLine[i+1]) && lines.lastLine[i+1] != '.'){
            cout << "upperRight ";
            returnVal = true;
        }
        
        if(!isdigit(lines.nextLine[i+1]) && lines.nextLine[i+1] != '.'){
            cout << "lowerRight ";
            returnVal = true;
        }
    }
    cout << endl;
    return returnVal;
}

int handleLine(lineData lines){
    int i = 0;
    int whichNumber = 0;
    bool oneNumber = false;
    string numString = "";
    bool hasSymbol = false;

    int wholeNumber = 0;
        // cout << lines.currentLine<<endl;
    for (char c : lines.currentLine){
            cout << "----" << endl;
        cout << c << endl;
        cout << "wholeNumber:" <<wholeNumber << endl;
        cout << "numString:" <<numString << endl;
        cout << "hasSymbol: " << hasSymbol << " oneNumber: " << oneNumber << endl;
        if(c == '.'){
        
        if(hasSymbol && oneNumber){
            cout << "change to int" << endl;
            wholeNumber += stoi(numString);
            oneNumber = false;
            hasSymbol = false;
            numString = "";
        }
        hasSymbol = false;
        oneNumber = false;
        numString = "";
            
            i++;
        } 
        else if (isdigit(c) && !oneNumber)
        {
            oneNumber = true;
            numString += c;
            if(checkForFirstSymbol(lines, i)){
                // cout << "first " << endl;
                hasSymbol = true;
            }
            i++;
        }
        else if (isdigit(c) && oneNumber){
            numString += c;
            if(checkForFirstSymbol(lines, i)){
                // cout << "Mitte oder last" << endl;
                hasSymbol = true;
            }
            i++;
        }else{
            i++;
        }
        
    }
    if(hasSymbol && oneNumber){
        cout << "change to int" << endl;
        wholeNumber += stoi(numString);
        oneNumber = false;
        hasSymbol = false;
        numString = "";
    } //9541962,11277277
    return wholeNumber;
}
int main(){
    ifstream inputFile ("data.txt");
    if(inputFile.is_open()){
        lineData lines = {.lastLine = "", .currentLine = "", .nextLine = ""};
        bool first = true;
        bool second = false;
        string line = "";
        int wholeNumber = 0;
        int size = 0;
        while(getline(inputFile, line)){
            size = line.size();
            if(first){
                for(char c : line){
                    lines.lastLine += '.';
                    lines.nextLine += '.';
                }
            }
            cout <<"NewLine: "<< line << endl;
            if(first){
                first = false;
                second = true;
                cout << "first" << endl;
                lines.currentLine = line;
            }else if (second){
                second = false;
                cout << "second" << endl;
                lines.nextLine = line;
                wholeNumber += handleLine(lines);
            }else{
                cout << "else" << endl;
                lines.lastLine = lines.currentLine;
                lines.currentLine = lines.nextLine;
                lines.nextLine = line;
                wholeNumber += handleLine(lines);
            }

            cout << "_________________________" << endl;
            cout << lines.lastLine << endl;
            cout << lines.currentLine << endl;
            cout << lines.nextLine << endl;
            cout << "=========================" << endl;
        }
        cout << "last" << endl;
        lines.lastLine = lines.currentLine;
        lines.currentLine = lines.nextLine;
        lines.nextLine = "";
        for(int j = 0; j < size; j++){
            lines.nextLine += '.';
        }
        cout << "_________________________" << endl;
        cout << lines.lastLine << endl;
        cout << lines.currentLine << endl;
        cout << lines.nextLine << endl;
        cout << "=========================" << endl;
        wholeNumber += handleLine(lines);
        cout << wholeNumber << endl;
    }
    return 0;
}