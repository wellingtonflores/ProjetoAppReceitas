#include "usuario.h"
#include <string>

Usuario::Usuario(string nomeCompleto, string dataNascimento, string username, string senha, string email, bool admin, int idBanco)
{
    this->nomeCompleto = nomeCompleto;
    this->dataNascimento = dataNascimento;
    this->username = username;
    this->senha = senha;
    this->email = email;
    this->admin = admin;
    this->idBanco = idBanco;
}

Usuario::Usuario()
{

}

string Usuario::getNomeCompleto()
{
    return nomeCompleto;
}
void Usuario::setNomeCompleto(string nomeCompleto)
{
    this->nomeCompleto = nomeCompleto;
}

string Usuario::getDataNascimento()
{
    return dataNascimento;
}

void Usuario::setDataNascimento(string dataNascimento)
{
    this->dataNascimento = dataNascimento;
}

string Usuario::getUsername()
{
    return username;
}

void Usuario::setUsername(string username)
{
    this->username = username;
}

string Usuario::getSenha()
{
    return senha;
}

void Usuario::setSenha(string senha)
{
    this->senha = senha;
}

string Usuario::getEmail()
{
    return email;
}

void Usuario::setEmail(string email)
{
    this->email = email;
}

bool Usuario::getAdmin()
{
    return admin;
}

void Usuario::setAdmin(bool admin)
{
    this->admin = admin;
}

int Usuario::getIdBanco()
{
    return idBanco;
}

void Usuario::setIdBanco(int idBanco)
{
    this->idBanco = idBanco;
}

vector<Favorito> Usuario::receitasFavoritas() 
{
    return favoritos;
}

void Usuario::favoritarReceita(Favorito receita)
{
    favoritos.push_back(receita);
}

void Usuario::excluirFavorito(int posicao)
{
    favoritos.erase(favoritos.begin() + posicao);
}

void Usuario::dados()
{
    cout << "Username: " << username << "\n";
    cout << "Senha: " << senha << "\n";
    cout << "Email: " << email << "\n";
    cout << "Nome completo: " << nomeCompleto << "\n";
    cout << "Data nascimento: " << dataNascimento << "\n";
}