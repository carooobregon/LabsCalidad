#include <iostream>
#include <vector>
#include <fstream>

#include "Archivo.h"

using namespace std;

bool isComment(string currString){
    for(int i = 0; i<currString.length(); i++){
        if(currString[i] == '*')
            return true;
    }
    return false;
}

int main(){
    Archivo myArch;
    ifstream archEnt;
    string nombreArch, currString;
    int cont =0;
    cin >> nombreArch;
    archEnt.open(nombreArch);

    bool hasLineStarted = 0;

    if(!archEnt.good()){
        cout << "Archivo no existe" << endl;
        return 0;
    }

    myArch.setName(nombreArch);
    
    while (!archEnt.eof()) {
        getline(archEnt, currString);
        for(int i = 0; i < currString.length(); i++){
            if(currString[i] == '/' || currString[i] == '*'){
                myArch.incrementarLineasComentario();
                hasLineStarted = 1;
                break;
            }
            if(isalpha(currString[i]) || currString[i] == '{' || currString[i] == '}'){
                if(isComment(currString)){
                    myArch.incrementarLineasComentario();
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
    return 0;
}