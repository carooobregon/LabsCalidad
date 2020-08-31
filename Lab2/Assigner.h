#include <iostream>
#include <vector>
#include "Archivo.h"

using namespace std;

class Assigner {
    public:
        int defLOC();
        char defComment(string);
        int defNumberInComment();
        Archivo getArchivo();
        void handleComment(string);
        void addArchivos(Archivo);
        void printArchivos();
        
    private:
        vector<Archivo> archivosBase;
        vector<Archivo> archivosNuevos;
        vector<Archivo> archivosReusados;
};

char Assigner::defComment(string comment){
    if(comment.length() < 2 || comment[2] != '.')
        return 'c';

    switch(comment[3]){
        case 'i':
            return 'i';
            break;
        case 'b':
            return 'b';
            break;
        case 'd':
            return 'd';
        case 'm':
            return 'm';
    }

    return 'c';
}

void Assigner::addArchivos(Archivo curr){
    curr.calculateAgregadas();
    switch(curr.classify()){
        case 'b':
            archivosBase.push_back(curr);
            break;
        
        case 'n':
            archivosNuevos.push_back(curr);
            break;
        
        case 'r':
            archivosReusados.push_back(curr);
        
    }
}

void Assigner::printArchivos(){
    cout << "CLASES BASE:" << endl;
    for(int i =0 ; i < archivosBase.size(); i++){
        cout << '\t';
        archivosBase[i].print();
    }
    cout << "-------------------------------------------" << endl;
    cout << "CLASES NUEVAS:" << endl;
    for(int i =0 ; i < archivosNuevos.size(); i++){
        cout << '\t';
        archivosNuevos[i].print();
    }
    cout << "-------------------------------------------" << endl;
    cout << "CLASES REUSADAS:" << endl;
    for(int i =0 ; i < archivosReusados.size(); i++){
        cout << '\t';
        archivosReusados[i].print();
    }
    cout << "-------------------------------------------" << endl;
}