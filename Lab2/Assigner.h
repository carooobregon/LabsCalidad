#include <iostream>
#include <vector>
#include <fstream>
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
        void replaceArchivo(Archivo);
        void writeFile();

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
            break;
        
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

void Assigner::replaceArchivo(Archivo curr){
    curr.calculateAgregadas();
    switch(curr.classify()){
        case 'b':
            archivosReusados.pop_back();
            break;
        case 'n':
            archivosNuevos.pop_back();
            break;
        case 'r':
            archivosReusados.pop_back();
            break;
    }
    addArchivos(curr);
}

void Assigner::writeFile(){
    ofstream myFile ("example.txt");
        myFile << "CLASES BASE:" << endl;
    for(int i =0 ; i < archivosBase.size(); i++){
        myFile << '\t';
            archivosBase[i].calculateAgregadas();
            archivosBase[i].classify();
            myFile << archivosBase[i].getName() << ": ";
            myFile << "T=" << archivosBase[i].getLDC() << ", ";
            myFile << "I=" << archivosBase[i].getItems() << ", ";
            myFile << "B=" << archivosBase[i].getBase() <<", ";
            myFile << "D=" << archivosBase[i].getDeleted() << ", ";
                myFile << "M=" << archivosBase[i].getModified() <<", ";
            myFile << "A=" << archivosBase[i].getAgregadas();
            myFile << endl;

    }
    myFile << "-------------------------------------------" << endl;
    myFile << "CLASES NUEVAS:" << endl;
    for(int i =0 ; i < archivosNuevos.size(); i++){
        myFile << '\t';
            archivosNuevos[i].calculateAgregadas();
            archivosNuevos[i].classify();
            myFile << archivosNuevos[i].getName() << ": ";
            myFile << "T=" << archivosNuevos[i].getLDC() << ", ";
            myFile << "I=" << archivosNuevos[i].getItems() << ", ";
            myFile << "B=" << archivosNuevos[i].getBase() <<", ";
                myFile << "D=" << archivosNuevos[i].getDeleted() << ", ";
                myFile << "M=" << archivosNuevos[i].getModified() <<", ";
            myFile << "A=" << archivosNuevos[i].getAgregadas();
            myFile << endl;
    }
    cout << "-------------------------------------------" << endl;
    cout << "CLASES REUSADAS:" << endl;
    for(int i =0 ; i < archivosReusados.size(); i++){
        myFile << '\t';
            archivosReusados[i].calculateAgregadas();
            archivosReusados[i].classify();
            myFile << archivosReusados[i].getName() << ": ";
            myFile << "T=" << archivosReusados[i].getLDC() << ", ";
            myFile << "I=" << archivosReusados[i].getItems() << ", ";
            myFile << "B=" << archivosReusados[i].getBase() <<", ";
                myFile << "D=" << archivosReusados[i].getDeleted() << ", ";
                myFile << "M=" << archivosReusados[i].getModified() <<", ";
            myFile << "A=" << archivosReusados[i].getAgregadas();
            myFile << endl;
    }
    myFile << "-------------------------------------------" << endl;

}