#pragma once
#ifndef PAIS_H
#define PAIS_H
#include <iostream>
#include <string>
#include "receita.h"
#include <vector>

using namespace std;

/* CLASSE PAIS
Cada pais cadastrado no sistema resulta em um objeto desta classe.
Atributos:
 - nomePais: nome do pais.
 - resumo: resumo da cultura do pais.
 - receitas: vetor de objetos da classe Receita. Contem todas as receitas cadastradas no sistema deste pais.
 - idBanco: O ID (PK) deste pais no banco. Armazenar esta informacao no objeto permite referencia-lo no banco diretamente.
*/

class Pais {
public:
    //funcoes de contrucao da classe e de atributos
    Pais();
    Pais(string nomePais, string resumo, int idBanco);
    string getNomePais();
    void setNomePais(string nomePais);
    string getResumo();
    void setResumo(string resumo);
    vector<Receita>getReceitas();
    void inserirReceita(Receita novaReceita); // a funcao que vai inserir a receita no pais
    int getIdBanco();
    void setIdBanco(int idBanco);
private:
    string nomePais;
    string resumo;
    vector<Receita>receitasDoPais; // aqui eu adicionei um vetor de receitas que vai estar dentro da classe pais!! ou seja, toda vez que adicionarmos uma receita dentro do pais, ela vai ficar salva dentro DAQUELE pais, ou seja, nesse vetor
    int idBanco;
};

#endif
