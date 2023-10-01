#include "pais.h"
#include <iostream>

Pais::Pais(){

}

Pais::Pais(string nomePais, string resumo, int idBanco) 
{
	this->nomePais = nomePais;
	this->resumo = resumo;
	this->idBanco = idBanco;
}

string Pais::getNomePais() {
	return nomePais;
}

void Pais::setNomePais(string nomePais) 
{
	this->nomePais = nomePais;
}

string Pais::getResumo() 
{
	return resumo;
}

void Pais::setResumo(string resumo) 
{
	this->resumo = resumo;
}

vector<Receita> Pais::getReceitas() //vetor de receitas que vao ficar salvas no pais onde elas for cadastradas
{
	return receitasDoPais;
}

void Pais::inserirReceita(Receita novaReceita) // aqui sempre que uma nova receita for cadastrada ela vai ser inserida no vetor de receitas que ta na classe pais
{
	receitasDoPais.push_back(novaReceita);
}

int Pais::getIdBanco()
{
	return idBanco;
}
void Pais:: setIdBanco(int idBanco)
{
	this->idBanco = idBanco;
}