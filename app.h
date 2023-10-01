#pragma once
#ifndef APP_H
#define APP_H
#include "usuario.h"
#include "receita.h"
#include "pais.h"
#include "conexao.h"
#include <iostream>
#include <vector>

using namespace std;

/* CLASSE APP
Classe principal do sistema. Contem metodos de menu/interface/execucao etc.
Atributos:
 - usuarios: vetor de objetos da classe Usuario. Contem todos os usuarios cadastrados no sistema.
 - usuarioLogado: objeto da classe Usuario com informacoes do usuario atualmente logado.
 - paises: vetor de objetos da classe Pais. Contem todos os paises cadastrados no sistema.
 - paisSelecionado: objeto da classe Pais com informacoes do pais atualmente selecionado.
 - receitas: vetor de objetos da classe Receitas. Contem todas as receitas cadastradas no sistema.
 - receitaSelecionada: objeto da classe Receita com informacoes da receita atualmente selecionada.
 - ingredientes: vetor de objetos da classe Ingredientes. Contem todos os ingredientes cadastrados no sistema.
 - ingredienteSelecionado: objeto da classe Ingrediente com informacoes do ingrediente atualmente selecionado.
 - metodoSelecionado: objeto da classe Metodo com informacoes do metodo atualmente selecionado.
*/

class App : public Usuario, public Receita, public Pais, public Ingrediente, public Metodo {
public:
    //funcoes de contrucao da classe e de atributos
    App();
    vector<Usuario> getUsuarios();
    void inserirUsuario(Usuario novoUsuario);
    Usuario getUsuarioLogado();
    void setUsuarioLogado(Usuario usuarioLogado);
    vector<Pais> getPaises();
    void inserirPais(Pais novoPais);
    Pais getPaisSelecionado();
    void setPaisSelecionado(Pais paisSelecionado);
    vector<Receita> getReceitas();
    void inserirReceita(Receita novaReceita);
    Receita getReceitaSelecionada();
    void setReceitaSelecionada(Receita receitaSelecionada);
    vector<Ingrediente> getIngredientes();
    void inserirIngrediente(Ingrediente novoIngrediente);
    Ingrediente getIngredienteSelecionado();
    void setIngredienteSelecionado(Ingrediente ingredienteSelecionado);
    // CRIAR FUNCOES DO VETOR DE METODOS

    //funcoes de carregamento inicial e encerramento
    void executarApp();
    void encerrarApp();
    void carregarDadosExistentes();

    //funcoes de menu/interface/gerenciamento de objetos
    void menuInicial();
    void menuAdmin();
    void listaUsuarios();
    void CadastroNovoUsuario(bool admin);
    bool UsuarioDisponivel(string tempUsername, string tempEmail);
    bool UsuarioDisponivel(string tempUsername);
    void Login();
    void menuPerfil();
    void verCadastro();
    void alterarCadastro();
    void mostrarFavoritos();
    void logout();
    void mostrarPaises();
    void adicionarPais();
    bool PaisDisponivel(string nomePais); 
    void menuPais();
    void listarReceitas();
    void listarTodasReceitas();
    void adicionarReceita();
    void removerReceita();
    void menuReceita();
    void verAvaliacaoReceita(); 
    void verIngredienteseMetodosReceita();
    void listarIngredientes();
    void menuBusca();
    void aplicarFiltros();
    void adicionarFavorito();
    void removerFavorito(int indice);
    void avaliarReceita();
    void removerAvaliacao();

private:
    vector<Usuario> usuarios; 
    Usuario usuarioLogado;
    vector<Pais> paises;
    vector<Ingrediente>ingredientes;
    vector<Receita>receitas;
    Pais paisSelecionado;
    Receita receitaSelecionada;
    Ingrediente ingredienteSelecionado;
    Metodo metodoSelecionado;
};

#endif 