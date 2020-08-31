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
    bool inString = 0;
    for(int i = 0; i<currString.length(); i++){
        if(currString[i] == '"' && !inString)
            inString =1;
        else if(currString[i] == '"' && inString)
            inString = 0;
        if(currString[i] == '.'){
            if(currString[i+1] == 'm' && !inString){
                cout << "Modified" << " " << currString << endl;
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
            cout << "Deleted" << " " << currString << endl;
            myArch.addDeleted(stoi(currNum));
            break;
        case 'b':
            currNum = currString.substr(5,currString.length()-5);
            cout << "Base" << " " << currString << endl;
            myArch.addBase(stoi(currNum));
            break;
        case 'i':
            cout << "Item" << " " << currString << endl;
            myArch.addItems();
            break;
        case 'm':
            cout << "Modified" << " " << currString << endl;
            myArch.addModified();
            break;
    }
}

void handleFile(Archivo &myArch, string nombreArch, Assigner &myAssigner){
        ifstream archEnt;
        string currString;
        int cont;
        archEnt.open(nombreArch);

        bool hasLineStarted = 0;

        cout << "iN";
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
}


int main(){
    Assigner myAssigner;
    ifstream archEnt;
    string nombreArch, currString;
    int cont =0;
    int handler = 1;
    int globalLDC = 0;
    
    cin >> nombreArch;
    
    while(handler == 1){
        Archivo myArch;
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
                if(isalpha(currString[i]) || currString[i] == '+'){
                    if(isComment(currString, myArch)){
                        currString = currString.substr(i,currString.length()-i);
                        handleComment(currString, myAssigner, myArch);
                    }
                    else {
                        cout << "Linea #" << myArch.getLDC() << " " <<  currString << endl;
                        myArch.incrementarLineasCodigo();
                    }
                    hasLineStarted = 1;
                    break;
                }
                if(currString[i] == '{' || currString[i] == '}'){
                    if( i+1 <= currString.length() && (currString[i+1] == ')' || currString[i+1] == '(')){
                        cout << "Linea #" << myArch.getLDC() << " " <<  currString << endl;
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
        archEnt.close();
        if(handler == 1){
            cout << "Teclee nombre de archivo" << endl;
            cin >> nombreArch;
            string shortName = nombreArch.substr(0,nombreArch.length()-4);
            if(shortName == myArch.getName()){
                handleFile(myArch, nombreArch, myAssigner);
                cout << "Presiona 1 para agregar otro archivo" << endl;
                cin >> handler;
            }
        }
        myAssigner.addArchivos(myArch);

        globalLDC += myArch.getLDC();
    }
    myAssigner.printArchivos();
    myAssigner.writeFile();
    cout << "Total de LDC=" << globalLDC << endl;
    return 0;
}