#pragma once
#ifndef METODO_H
#define METODO_H
#include <iostream>
#include <string>

using namespace std;

/* CLASSE METODO
Cada receita contem um vetor de metodos, ou seja, de objetos desta classe. 
Atributos:
 - texto: explicacao de um passo de preparo de uma receita.
*/

class Metodo {
public:
    //funcoes de contrucao da classe e de atributos
    Metodo();
    Metodo(string texto);
    string getTexto();
    void setTexto(string texto);
private:
    string texto;
};

#endif