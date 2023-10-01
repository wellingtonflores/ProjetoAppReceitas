#include "receita.h"
//#include "metodo.h"
//#include "ingrediente.h"
#include <iostream>


//*******************************************************
/* FUNCOES DE CONSTRUCAO DE CLASSE
* Receita(): Cria novo objeto da classe.	
 getNomeReceita():
 setNomeReceita():
 getIngredientes():
 setIngredientes():
 inserirIngrediente():
 getMetodos():
 inserirMetodo:
-------------------------------------------------------*/

Receita::Receita(string nomeReceita)
{
	this->nomeReceita = nomeReceita;
}

Receita::Receita() {

}

string Receita::getNomeReceita() {
	return nomeReceita;
}

int Receita::getIdBanco()
{
	return idBanco;
}

void Receita::setIdBanco(int idBanco)
{
	this->idBanco = idBanco;
}

void Receita::setNomeReceita(string nomeReceita) {
	this->nomeReceita = nomeReceita;
}

vector<QuantidadeIngredientesReceita> Receita::getIngredientes() //vetor de receitas que vao ficar salvas no pais onde elas for cadastradas
{
	return ingredientes;
}

void Receita::inserirIngrediente(QuantidadeIngredientesReceita novoIngrediente) // aqui sempre que uma nova receita for cadastrada ela vai ser inserida no vetor de receitas que ta na classe pais
{
	ingredientes.push_back(novoIngrediente);
}

vector<Metodo>	Receita::getMetodos() //vetor de receitas que vao ficar salvas no pais onde elas for cadastradas
{
	return metodos;
}

void Receita::inserirMetodo(Metodo novoMetodo) // aqui sempre que uma nova receita for cadastrada ela vai ser inserida no vetor de receitas que ta na classe pais
{
	metodos.push_back(novoMetodo);
}

void Receita::inserirComentario(string comentario, int estrelas, int idBanco, string username)
{
	Comentario comentario1;
	comentario1.comentario = comentario;
	comentario1.estrelas = estrelas;
	comentario1.idBanco = idBanco;
	comentario1.username = username;

	comentarios.push_back(comentario1);
}

vector<Comentario> Receita::getComentarios()
{
	return comentarios;
}

void Receita::apagarComentario(int indice)
{
	comentarios.erase(comentarios.begin() + indice);
}