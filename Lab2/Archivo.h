#include <iostream>

using namespace std;

class Archivo {
    public:
       Archivo(string);
       char defineType();
       
    private:
        string name;
        char type;
        int total;
        int items;
        int base;
        int deleted;
        int modified;

};

void Archivo::setName(string name) {
	this.name = name;
}

char Archivo::getType() {
	return this.type;
}

void Archivo::setType(char type) {
	this.type = type;
}

int Archivo::getTotal() {
	return this.total;
}

void Archivo::setTotal(int total) {
	this.total = total;
}

int Archivo::getItems() {
	return this.items;
}

void Archivo::setItems(int items) {
	this.items = items;
}

int Archivo::getBase() {
	return this.base;
}

void Archivo::setBase(int base) {
	this.base = base;
}

int Archivo::getDeleted() {
	return this.deleted;
}

void Archivo::setDeleted(int deleted) {
	this.deleted = deleted;
}

int Archivo::getModified() {
	return this.modified;
}

void Archivo::setModified(int modified) {
	this.modified = modified;
}