#pragma once
#ifndef CONEXAO_H
#define CONEXAO_H
#include <string>
#include <iostream>
#include <pqxx/pqxx>

using namespace std;

/* CLASSE CONEXAO
Classe criada para a conexao com o banco de dados, para persistir valores.

Principal material utilizado: https://www.youtube.com/watch?v=qDiC1Wja6Og&ab_channel=Instituteofmarxism-leninism
O video ensina como instalar PostgreSQL, e tambem a biblioteca que estamos utilizando para conectar com o banco (libpqxx)
Durante a instalacao, tive alguns problemas e notei que precisava instalar tambem o OpenSSL no Windows, que foi bastante trabalhoso. 
	Econtrei alguns instaladores na web mas fiquei com medo de ser virus. Segui os passos do Github: https://github.com/openssl/openssl/blob/master/NOTES-WINDOWS.md
	Que exigiu a instalacao de algumas coisas extras como perl, nasm e etc

O proprio video contem um codigo de exemplo de conexao, e as seguintes paginas tb ajudaram como referencias adicionais:
https://www.tutorialspoint.com/postgresql/postgresql_c_cpp.htm
https://www.instaclustr.com/support/documentation/postgresql/using-postgresql/connecting-to-postgresql-with-c-plus-plus/
Atributos:
 - hostName: endereco do servidor do banco de dados.
 - databaseName: nome do banco de dados no servidor.
 - userName: usuario para conectar com o banco de dados.
 - password: senha para conexao.
*/

class Conexao
{
public:
	//funcoes de contrucao da classe e de atributos
	Conexao();
	Conexao(string hostName, string databaseName, string userName, string password);
	pqxx::connection criarConexao();
	pqxx::result executarQuery(string query);
private:
	string hostName;
	string databaseName;
	string userName;
	string password;
};

#endif