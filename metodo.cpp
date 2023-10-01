#include "metodo.h"
#include <iostream>


Metodo::Metodo(string texto) {
	this->texto = texto;
}

Metodo::Metodo() {
}

string Metodo::getTexto() {
	return texto;
}

void Metodo::setTexto(string texto) {
	this->texto = texto;
}