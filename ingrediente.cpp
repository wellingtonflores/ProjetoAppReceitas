#include "ingrediente.h"
#include <iostream>

//*******************************************************
/* FUNCOES DE CONSTRUCAO DE CLASSE
 Ingrediente(): Cria novo objeto da classe.	
 getNomeIngrediente(): Retorna o valor desse atributo para o objeto da classe ingrediente.
 setNomeIngrediente(): Seta o valor desse atributo para o objeto da classe ingrediente.
 getIdBanco(): Retorna o valor desse atributo para o objeto da classe ingrediente.
 setIdBanco(): Seta o valor desse atributo para o objeto da classe ingrediente.
 QuantidadeIngredientesReceita(): construtor da subclasse.
 getQuantidade: Retorna o valor desse atributo para o objeto da classe ingrediente.
 setQuantidade: Seta o valor desse atributo para o objeto da classe ingrediente.
-------------------------------------------------------*/



Ingrediente::Ingrediente(string nomeIngrediente, int idBanco)
{
	this->nomeIngrediente = nomeIngrediente;
	this->idBanco = idBanco;

}

Ingrediente::Ingrediente() 
{

}

string Ingrediente::getNomeIngrediente() 
{
	return nomeIngrediente;
}

void Ingrediente::setNomeIngrediente(string nomeIngrediente) 
{
	this->nomeIngrediente = nomeIngrediente;
}

int Ingrediente::getIdBanco()
{
	return idBanco;
}

void Ingrediente::setIdBanco(int idBanco)
{
	this->idBanco = idBanco;
}

//aqui eu declarei a heranca da subClasse

QuantidadeIngredientesReceita::QuantidadeIngredientesReceita (string nomeIngrediente, int idBanco, string quantidade): Ingrediente(nomeIngrediente, idBanco)
{
	this->quantidade = quantidade;
}

string QuantidadeIngredientesReceita::getQuantidade()
{
	return quantidade;
}

void QuantidadeIngredientesReceita::setQuantidade(string quantidade)
{
	this->quantidade = quantidade;
}