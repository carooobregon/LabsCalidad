#include <iostream>

using namespace std;

class Archivo {
    public:
        Archivo();
       void setName(string);
       void setType(char);
       char getType();
       int getTotal();
       int getItems();
       int getBase();
       int getDeleted();
       int getModified();
       void addTotal(int);
       void addItems();
       void addBase(int);
       void addDeleted(int);
       void addModified();
       void incrementarLineasBlanco();
        void incrementarLineasCodigo();
        void print();
        void calculateAgregadas();
        int getLDC();
        void classify();

    private:
        char defineType();
        string name;
        char type;
        int total;
        int items;
        int base;
        int deleted;
        int modified;
        int LDC;
        int agregadas;
        char classification;
};

Archivo::Archivo(){
    total = 0;
    items = 0;
    base = 0;
    deleted = 0;
    modified = 0;
    LDC = 0;
    agregadas = 0;
}

void Archivo::print(){
    calculateAgregadas();
    classify();
    cout << "T: " << LDC << endl;
    cout << "I: " << items << endl;
    cout << "B: " << base << endl;
    cout << "D: " << deleted << endl;
    cout << "M: " << modified << endl;
    cout << "A: " << agregadas << endl;
    cout << "Clasificacion: " << classification << endl;
}
void Archivo::setName(string name) {
	name = name;
}

char Archivo::getType() {
	return type;
}

void Archivo::setType(char t) {
	type = t;
}

int Archivo::getTotal() {
	return total;
}

void Archivo::addTotal(int t) {
	total += t;
    
}

int Archivo::getItems() {
	return items;
}

void Archivo::addItems() {
	items++;
}

int Archivo::getBase() {
	return base;
}

void Archivo::addBase(int b) {
	base += b;
    
}

int Archivo::getDeleted() {
	return deleted;
}

void Archivo::addDeleted(int d) {
	deleted = deleted + d;
    
}

int Archivo::getModified() {
	return modified;
}

void Archivo::addModified() {
	modified++;
}

void Archivo::incrementarLineasCodigo(){
    LDC++;
}

int Archivo:: getLDC(){
    return LDC;
}
void Archivo::incrementarLineasBlanco(){
    return;
}

void Archivo::calculateAgregadas(){
    agregadas = LDC - base + deleted;
}

void Archivo::classify(){
    if(base > 0 && ( modified > 0 || deleted > 0 || agregadas >0))
        classification = 'b';
    else if(base == 0 && modified == 0 && deleted == 0 & agregadas == 0)
        classification = 'n';
    else if(base > 0 && modified == 0 & deleted == 0 && agregadas ==0 )
        classification = 'r';
}