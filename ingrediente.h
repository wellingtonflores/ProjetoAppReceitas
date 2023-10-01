#pragma once
#ifndef INGREDIENTE_H
#define INGREDIENTE_H
#include <iostream>
#include <string>

using namespace std;

/* CLASSE INGREDIENTE
Cada ingrediente cadastrado no sistema resulta em um objeto desta classe.
Atributos:
 - nomeIngrediente: nome de um ingrediente utilizado em receitas.
 - idBanco: O ID (PK) deste ingrediente no banco. Armazenar esta informacao no objeto permite referencia-lo no banco diretamente.
*/

class Ingrediente {
public:
    //funcoes de contrucao da classe e de atributos
    Ingrediente();
    Ingrediente(string nomeIngrediente, int idBanco);
    string getNomeIngrediente();
    void setNomeIngrediente(string nomeIngrediente);
    int getIdBanco();
    void setIdBanco(int idBanco);
private:
    string nomeIngrediente;
    int idBanco;
};

/* SUBCLASSE QuantidadeIngredientesReceita
Cada receita contem ingrededientes, e tambem a quantidade do mesmo. Portanto, cada receita contem um vetor de objetos desta subclasse.
Portanto, criamos uma classe que herda Ingrediente, com um atributo adicional.
Atributos:
 - quantidade: quantidade do ingrediente utilizado na receita.
*/
class QuantidadeIngredientesReceita : public Ingrediente
{
public:
    //funcoes de contrucao da classe e de atributos
    QuantidadeIngredientesReceita(string nomeIngrediente, int idBanco, string quantidade);
    string getQuantidade();
    void setQuantidade(string quantidade);
private:
    string quantidade;
};

#endif
