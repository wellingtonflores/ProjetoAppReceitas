#pragma once
#ifndef RECEITA_H
#define RECEITA_H
#include "ingrediente.h"
#include "metodo.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

// apaguei as composicoes(pq tava como heranca mas n eh heranca, e como vamos fazer o menu pro usuario escolher o que ele quer ver, ele adiciona so o nome da receita)

/* CLASSE RECEITA
Cada receita cadastrado no sistema resulta em um objeto desta classe.
Atributos:
 - nomeReceita: nome da receita.
 - ingredientes: vetor de objetos da classe QuantidadeIngredientesReceita. Contem todos os ingredientes e quantidades utilizada na receita.
 - metodos: vetor de objetos da classe metodo. Contem todos os metodos de preparo da receita
*/
struct Comentario 
{
    string comentario;
    int estrelas;
    int idBanco;
    string username;
};

class Receita {
public:
    //funcoes de contrucao da classe e de atributos
    Receita();
    Receita(string nomeReceita);
    string getNomeReceita();
    void setNomeReceita(string nomeReceita);
    int getIdBanco();
    void setIdBanco(int idBanco);
    vector<QuantidadeIngredientesReceita>getIngredientes();
    void inserirIngrediente(QuantidadeIngredientesReceita novoIngrediente);
    vector<Metodo>getMetodos();
    void inserirMetodo(Metodo novoMetodo); 
    void inserirComentario(string texto, int estrelas, int idBanco, string username);
    vector<Comentario>getComentarios();
    void apagarComentario(int indice);
private:
    string nomeReceita;
    int idBanco;
    vector<QuantidadeIngredientesReceita> ingredientes;
    vector<Metodo> metodos; 
    vector<Comentario>comentarios;
};

#endif