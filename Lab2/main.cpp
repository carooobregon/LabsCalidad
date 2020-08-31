#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "Assigner.h"

using namespace std;

bool isComment(string currString, Archivo &myArch, bool &currComment){

    for(int i = currString.length()-1; i >= 0; i-- ){
        if(currString[i] == '*'){
            if(i+1 <= currString.length()-1 && currString[i+1] == '/'){
                currComment = 0;
                return true;
            }
            else{
                currComment = 1;
                return true;
            }
        }
    }

    bool inString = 0;
    for(int i = 0; i<currString.length(); i++){
        if(currString[i] == '"' && !inString)
            inString =1;
        else if(currString[i] == '"' && inString)
            inString = 0;
        if(currString[i] == '.'){
            if(currString[i+1] == 'm' && !inString){
                myArch.addModified();
                return false;
            }
        }
    }
    return false;
}

void handleComment(string currString, Assigner myAssigner, Archivo &myArch){
    char currComment = myAssigner.defComment(currString);
    string currNum;
    switch(currComment){
        case 'd':
            currNum = currString.substr(5,currString.length()-5);
            myArch.addDeleted(stoi(currNum));
            break;
        case 'b':
            currNum = currString.substr(5,currString.length()-5);
            myArch.addBase(stoi(currNum));
            break;
        case 'i':
            myArch.addItems();
            break;
        case 'm':
            myArch.addModified();
            break;
    }
}

int main(){
    Assigner myAssigner;
    Archivo myArch;
    ifstream archEnt;
    string nombreArch, currString;
    bool multiLine = 0;
    
    int cont =0;
    int handler = 1;
    int globalLDC = 0;
    bool rep = 0;
    cin >> nombreArch;
    
    while(handler == 1){
        archEnt.open(nombreArch);
        string shortName = nombreArch.substr(0,nombreArch.length()-4);
        myArch.setName(shortName);
        
        bool hasLineStarted = 0;

        if(!archEnt.good()){
            cout << "Archivo no existe" << endl;
            return 0;
        }
        
        while (!archEnt.eof()) {
            getline(archEnt, currString);
            for(int i = 0; i < currString.length(); i++){
                if(currString[i] == '/' || currString[i] == '*'){
                    currString = currString.substr(i,currString.length()-i);
                    handleComment(currString, myAssigner, myArch);
                    bool temp = isComment(currString, myArch, multiLine);
                    hasLineStarted = 1;
                    break;
                }
                if(isalpha(currString[i]) || currString[i] == '+'){
                    if(isComment(currString, myArch, multiLine)){
                        currString = currString.substr(i,currString.length()-i);
                        handleComment(currString, myAssigner, myArch);
                    }
                    else {
                        if(!multiLine){
                            myArch.incrementarLineasCodigo();
                        }
                    }
                    hasLineStarted = 1;
                    break;
                }
                if(currString[i] == '{' || currString[i] == '}'){
                    if( !multiLine && (i+1 <= currString.length() && (currString[i+1] == ')' || currString[i+1] == '('))){
                        myArch.incrementarLineasCodigo();
                    }
                }

            }
            if(!hasLineStarted){
                myArch.incrementarLineasBlanco();
            }
            hasLineStarted = 0;
            cont++;
        }
        cout << "Presiona 1 para agregar otro archivo" << endl;
        cin >> handler;
        if(handler == 1){
            cin >> nombreArch;
            shortName = nombreArch.substr(0,nombreArch.length()-4);
            if(shortName != myArch.getName()){
                myAssigner.addArchivos(myArch);
                globalLDC += myArch.getLDC();
                myArch.clearAll();
                rep = 0;
            } else
                rep = 1;
        }
        archEnt.close();
    }
    myAssigner.addArchivos(myArch);
    globalLDC += myArch.getLDC();
    
    myAssigner.printArchivos();
    myAssigner.writeFile();
    cout << "Total de LDC=" << globalLDC << endl;
    return 0;
}