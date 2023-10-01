#include "conexao.h"

//Cria um novo objeto de conexao, recebendo a info do db
Conexao::Conexao()
{
}

Conexao::Conexao(string hostName, string databaseName, string userName, string password)
{
    this->hostName = hostName;
    this->databaseName = databaseName;
    this->userName = userName;
    this->password = password;
}

//Utiliza o objeto criado para conectar com o DB, retornando uma conexao aberta, ou mostrando um erro de conexao
pqxx::connection Conexao::criarConexao()
{
    string dadosConexao = "host=" + this->hostName + " port=5432 dbname=" + databaseName + " user=" + userName + " password=" + password;

    try
    {
        pqxx::connection connectionObject(dadosConexao.c_str());
        return connectionObject;
    }
    catch (const std::exception& e)
    {
        cerr << e.what() << endl;
        system("pause");
    }
}

// Executa um SQL query no DB, realizando um commit ao final da query (necessario para alteracoes de dados)
pqxx::result Conexao::executarQuery(string query)
{
    pqxx::connection conexao = this->criarConexao();
    pqxx::work worker(conexao);

    pqxx::result resposta = worker.exec(query);
    worker.commit();
    return resposta;
}