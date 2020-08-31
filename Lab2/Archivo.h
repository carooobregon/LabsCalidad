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
       void addItems(int);
       void addBase(int);
       void addDeleted(int);
       void addModified(int);
       void incrementarLineasBlanco();
        void incrementarLineasCodigo();

    private:
        char defineType();
        string name;
        char type;
        int total;
        int items;
        int base;
        int deleted;
        int modified;
};

Archivo::Archivo(){
    total = 0;
    items = 0;
    base = 0;
    deleted = 0;
    modified = 0;
}

void Archivo::setName(string name) {
	name = name;
}

char Archivo::getType() {
	return type;
}

void Archivo::setType(char type) {
	type = type;
}

int Archivo::getTotal() {
	return total;
}

void Archivo::addTotal(int total) {
	total += total;
}

int Archivo::getItems() {
	return items;
}

void Archivo::addItems(int items) {
	items += items;
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

void Archivo::addModified(int modified) {
	modified += modified;
}

void Archivo::incrementarLineasCodigo(){
    return;
}
void Archivo::incrementarLineasBlanco(){
    return;
}