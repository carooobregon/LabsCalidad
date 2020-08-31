#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "Assigner.h"

using namespace std;

bool isComment(string currString, Archivo &myArch){
    for(int i = 0; i<currString.length(); i++){
        if(currString[i] == '*')
            return true;
    }
    for(int i = 0; i<currString.length(); i++){
        if(currString[i] == '.'){
            if(currString[i+1] == 'm'){
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
    ifstream archEnt;
    string nombreArch, currString;
    int cont =0;
    int handler = 1;
    int globalLDC = 0;

    while(handler == 1){
        Archivo myArch;
        cin >> nombreArch;
        cout << nombreArch << endl;
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
                    hasLineStarted = 1;
                    break;
                }
                if(isalpha(currString[i]) || currString[i] == '{' || currString[i] == '}' || currString[i] == '+'){
                    if(isComment(currString, myArch)){
                        currString = currString.substr(i,currString.length()-i);
                        currString = currString.substr(i,currString.length()-i);
                        handleComment(currString, myAssigner, myArch);
                    }
                    else {
                        myArch.incrementarLineasCodigo();
                    }
                    hasLineStarted = 1;
                    break;
                }
            }
            if(!hasLineStarted){
                myArch.incrementarLineasBlanco();
            }
            hasLineStarted = 0;
            cont++;
        }
        myAssigner.addArchivos(myArch);
        cout << "Presiona 1 para agregar otro archivo" << endl;
        cin >> handler;
        archEnt.close();
        globalLDC += myArch.getLDC();
    }
    myAssigner.printArchivos();
    cout << "Total de LDC=" << globalLDC << endl;
    return 0;
}