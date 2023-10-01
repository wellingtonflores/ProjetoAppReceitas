#pragma once
#ifndef FAVORITO_H
#define FAVORITO_H
#include <iostream>
#include <string>

using namespace std;

/* CLASSE FAVORITO
Cada usuario contem um vetor de receitas favoritas, ou seja, de objetos desta classe.
Atributos:

*/

class Favorito {
public:
    //funcoes de contrucao da classe e de atributos
    Favorito();
    Favorito(int idReceita, int idBanco, string nomeReceita, string nomePais);
    int getIdReceita();
    int getIdBanco();
    string getNomeReceita();
    string getNomePais();
private:
    int idReceita;
    int idBanco;
    string nomeReceita;
    string nomePais;
};

#endif
