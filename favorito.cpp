#include "favorito.h"


Favorito::Favorito() {

}

Favorito::Favorito(int idReceita, int idBanco, string nomeReceita, string nomePais)
{
	this->idReceita = idReceita;
	this->idBanco = idBanco;
	this->nomeReceita = nomeReceita;
	this->nomePais = nomePais;
}

int Favorito::getIdReceita()
{
	return idReceita;
}

int Favorito::getIdBanco()
{
	return idBanco;
}

string Favorito::getNomeReceita()
{
	return nomeReceita;
}

string Favorito::getNomePais()
{
	return nomePais;
}