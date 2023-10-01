#pragma once
#ifndef USUARIO_H
#define USUARIO_H
#include <iostream>
#include "favorito.h"
#include <vector>

using namespace std;

/* CLASSE USUARIO
Cada usuario cadastrado no sistema resulta em um objeto desta classe.
Atributos:
 - nomeCompleto: nome completo do usuario.
 - dataNascimento: data de nascimento (no formato DD/MM/YYYY).
 - username: username do usuario.
 - email: email do usuario.
 - senha: senha do usuario.
 - admin: indicador se o usuario tem permissao de administrador no sistema.
*/

class Usuario {
public:
    //funcoes de contrucao da classe e de atributos
    Usuario();
    Usuario(string nomeCompleto, string dataNascimento, string username, string senha, string email, bool admin, int idBanco);
    string getNomeCompleto();
    void setNomeCompleto(string nomeCompleto);
    string getDataNascimento();
    void setDataNascimento(string dataNascimento);
    string getUsername();
    void setUsername(string username);
    string getEmail();
    void setEmail(string email);
    string getSenha();
    void setSenha(string senha);
    bool getAdmin();
    void setAdmin(bool admin);
    int getIdBanco();
    void setIdBanco(int idBanco);
    void favoritarReceita(Favorito receita);
    vector<Favorito> receitasFavoritas();
    void excluirFavorito(int posicao);
    //funcao de listagem de informacoes do objeto
    void dados();
private:
    string nomeCompleto;
    string dataNascimento;
    string username;
    string email;
    string senha;
    bool admin;
    int idBanco;
    vector<Favorito> favoritos;
};

#endif 
