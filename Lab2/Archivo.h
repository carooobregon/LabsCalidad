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
        char classify();
        string getName();
        int getAgregadas();

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
    cout << name << ": ";
    cout << "T=" << LDC << ", ";
    cout << "I=" << items << ", ";
    cout << "B=" << base <<", ";
    if(deleted > 0)
        cout << "D=" << deleted << ", ";
    if(modified > 0)
        cout << "M=" << modified <<", ";
    if(agregadas > 0)
    cout << "A=" << agregadas;

    cout << endl;
}
void Archivo::setName(string n) {
	name = n;
}

string Archivo::getName() {
	return name;
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

char Archivo::classify(){
    if(base > 0 && ( modified > 0 || deleted > 0 || agregadas >0))
        return 'b';
    else if(base == 0 && modified == 0 && deleted == 0 & agregadas == 0)
        return 'n';
    else if(base > 0 && modified == 0 & deleted == 0 && agregadas ==0 )
        return 'r';
        
    return 'n';
}

int Archivo::getAgregadas(){
    return agregadas;
}