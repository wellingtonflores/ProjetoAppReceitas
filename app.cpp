#include "app.h"
#include "usuario.h"
#include "receita.h"
#include "pais.h"
#include "ingrediente.h"
#include "metodo.h"
#include <string>

//*******************************************************
/* FUNCOES DE CONSTRUCAO DE CLASSE
 - App(): cria novo objeto da classe App
 - getUsuarioLogado(): retorna o objeto do usuario atualmente logado no sistema.
 - setUsuarioLogado(): especifica o usuario que esta logado no sistema.
 - getPaisSelecionado(): retorna o obejto do pais atualmente selecionado.
 - setPaisSelecionado(): especifica o pais que esta atualmente selecionado.
 - inserirReceita(): cadastra um novo objeto da classe Receita no vetor de receitas.
 - getReceitas(): retorna o vetor de receitas cadastradas no sistema.
 - getReceitaSelecionada(): retorna a receita atualmente selecionada.
 - setReceitaSelecionada(): especifica a receita selecionada no sistema.
 - getIngredientes(): retorna o vetor de ingredientes cadastrados no sistema.
 - inserirIngrediente(): cadastra um novo objeto da classe Ingrediente no vetor de ingredientes.
 - getIngredienteSelecionado(): retorna o ingrediente atualmente selecionado no sistema.
 - setIngredienteSelecionado(): especifica o ingrediente atualmente selecionado.
 - getMetodoSelecionado(): retorna o metodo atualmente selecionado no sistema.
 - setMetodoSelecionado(): especifica o metodo selecionado.
 - getConexaoDB(): retorna o objeto de conexao para interacao com banco de dados
 - setConexaoDB(): seta o objeto de Conexao com o DB
-------------------------------------------------------*/

App::App()
{
    // Construtor de objetos da classe
}

vector<Usuario> App::getUsuarios()
{
    // retorna o vetor de usuarios do sistema
    return usuarios;
}

void App::inserirUsuario(Usuario novoUsuario)
{
    //Insere uma novo objeto da classe Usuario no vetor de usuarios do sistema
    usuarios.push_back(novoUsuario);
}

Usuario App::getUsuarioLogado()
{
    //retorna valor do atributo para este objeto
    return usuarioLogado;
}

void App::setUsuarioLogado(Usuario usuarioLogado)
{
    //seta o valor do atributo para este objeto
    this->usuarioLogado = usuarioLogado;
}

vector<Pais> App::getPaises()
{
    // retorna o vetor de paises do sistema
    return paises;
}

void App::inserirPais(Pais novoPais)
{
    //Insere uma novo objeto da classe Usuario no vetor de usuarios do sistema
    paises.push_back(novoPais);
}

Pais App::getPaisSelecionado()
{
    //retorna valor do atributo para este objeto
    return paisSelecionado;
}

void App::setPaisSelecionado(Pais paisSelecionado)
{
    //seta o valor do atributo para este objeto
    this->paisSelecionado = paisSelecionado;
}

vector<Receita>	App::getReceitas()
{
    // retorna o vetor de receitas do sistema
    return receitas;
}

void App::inserirReceita(Receita novaReceita)
{
    //Insere uma novo objeto da classe Receita no vetor de receitas do sistema
    receitas.push_back(novaReceita);
}

Receita App::getReceitaSelecionada()
{
    //retorna o objeto da classe Receita atualmente selecionado no sistema
    return receitaSelecionada;
}

void App::setReceitaSelecionada(Receita receitaSelecionada)
{
    //seta o objeto da classe Receita atualmente selecionado no sistema
    this->receitaSelecionada = receitaSelecionada;
}

vector<Ingrediente>	App::getIngredientes()
{
    //retorna o vetor de ingredientes cadastrados no sistema
    return ingredientes;
}

void App::inserirIngrediente(Ingrediente novoIngrediente)
{
    //insere um novo objeto da classe Ingrediente no vetor de ingredientes do sistema
    ingredientes.push_back(novoIngrediente);
}

Ingrediente App::getIngredienteSelecionado()
{
    //retorna o objeto da classe Ingrediente atualmente selecionado no sistema
    return ingredienteSelecionado;
}

void App::setIngredienteSelecionado(Ingrediente ingredienteSelecionado)
{
    //seta o objeto da classe Ingrediente atualmente selecionado no sistema
    this->ingredienteSelecionado = ingredienteSelecionado;
}


//*******************************************************


//*******************************************************
/* FUNCOES DE CARREGAMENTO INICIAL E ENCERRAMENTO
 - executarApp(): Roda o menu inicial para login/cadastro/etc
 - encerrarApp(): Fecha o sistema
 - carregarDadosExistentes(): Popula objetos/vetores/etc com os dados existentes no banco de dados
-------------------------------------------------------*/

void App::executarApp()
{
    // Menu inicial do sistema
    system("cls");
    int escolha;

    cout << "**BEM VINDO AO APLICATIVO**\n";
    cout << "1 - Cadastrar\n";
    cout << "2 - Fazer login\n";
    cout << "3 - Fechar programa\n";

    do
    {
        cout << "Informe a opcao desejada: ";
        cin >> escolha;
        switch (escolha)
        {
        case 1:
            CadastroNovoUsuario(false);
            break;
        case 2:
            Login();
            break;
        case 3:
            encerrarApp();
            break;
        default:
            cout << "Escoha invalida.\n";
        }
    } while (escolha != 3);
}

void App::encerrarApp()
{
    //fecha o sistema
    cout << "Obrigado(a) por utilizar este aplicativo.";
    exit(0);
}

void App::carregarDadosExistentes()
{
    //Funcao para carregar os dados armazenados no banco no sistema.

    //parametros para conectar com o banco de dados
    Conexao conexaoDB("silly.db.elephantsql.com", "zecuhaus", "zecuhaus", "Beib7bJawWzoRjt-gaaRC6NGRUQum-X5"); 

    //carregar usuarios existentes no banco
    cout << "Carregando usuarios existentes no sistema... ";
    pqxx::result usuariosExistentes = conexaoDB.executarQuery("SELECT id_usuario, username, email, senha, nome_completo,  to_char(data_nascimento, 'DD/MM/YYYY') as data_nascimento, admin FROM dev.usuario;");
    cout << usuariosExistentes.size() << " usuarios encontrados." << endl;

    //criar um novo objeto da classe Usuario no vetor de usuarios do App para cada resultado do DB
    for (int i = 0; i < usuariosExistentes.size(); i++)
    {
        auto [id_usuario, username, email, senha, nome_completo, data_nascimento, admin] = usuariosExistentes[i].as<int, string, string, string, string, string, bool>();
        Usuario usuarioTemp(nome_completo, data_nascimento, username, senha, email, admin, id_usuario);

        pqxx::result receitasFavoritas = conexaoDB.executarQuery("SELECT id_favorito, dev.receita.id_receita, nome_receita, nome_pais FROM dev.favorito INNER JOIN dev.receita on dev.favorito.id_receita = dev.receita.id_receita INNER JOIN dev.pais on dev.receita.id_pais = dev.pais.id_pais WHERE id_usuario = " + to_string(id_usuario) + ";");
        
        //criar um novo objeto da classe Favorito no vetor de favoritos do Usuario para cada resultado do DB
        for (int j = 0; j < receitasFavoritas.size(); j++)
        {
            auto [id_favorito, id_receita, nome_receita, nome_pais] = receitasFavoritas[j].as<int, int, string, string>();
            Favorito favoritoTemp(id_receita, id_favorito, nome_receita, nome_pais);

            usuarioTemp.favoritarReceita(favoritoTemp);
        }
        inserirUsuario(usuarioTemp); 
    }
    //carregar paises
    cout << "Carregando paises existentes no sistema... ";
    pqxx::result paisesExistentes = conexaoDB.executarQuery("SELECT id_pais, nome_pais, resumo_pais FROM dev.pais;");
    cout << paisesExistentes.size() << " paises encontrados." << endl;

    //criar um novo objeto da classe Pais no vetor de paises do App para cada resultado do DB
    for (int i = 0; i < paisesExistentes.size(); i++)
    {
        auto [id_pais, nome_pais, resumo_pais] = paisesExistentes[i].as<int, string, string>();
        Pais paisTemp(nome_pais, resumo_pais, id_pais);
        inserirPais(paisTemp);
    }

    //carregar ingredientes
    cout << "Carregando ingredientes existentes no sistema... ";
    pqxx::result ingredientesExistentes = conexaoDB.executarQuery("SELECT id_ingrediente, nome_ingrediente FROM dev.ingrediente;");
    cout << ingredientesExistentes.size() << " ingredientes encontrados." << endl;

    //criar um novo objeto da classe Ingrediente no vetor de ingredientes do App para cada resultado do DB
    for (int i = 0; i < ingredientesExistentes.size(); i++)
    {
        auto [id_ingrediente, nome_ingrediente] = ingredientesExistentes[i].as<int, string>();
        Ingrediente ingredienteTemp(nome_ingrediente, id_ingrediente);
        inserirIngrediente(ingredienteTemp);
    }

    //carregar receitas, com seus metodos e ingredientes
    cout << "Carregando receitas com ingredientes e metodos... ";
    pqxx::result receitasExistentes = conexaoDB.executarQuery("SELECT id_receita, nome_receita, dev.pais.id_pais, nome_pais FROM dev.receita INNER JOIN dev.pais on dev.receita.id_pais = dev.pais.id_pais;");
    cout << receitasExistentes.size() << " receitas encontradas." << endl;

    //criar um novo objeto da classe Receita no vetor de receitas do App para cada resultado do DB
    for (int i = 0; i < receitasExistentes.size(); i++)
    {
        auto [id_receita, nome_receita, id_pais, nome_pais] = receitasExistentes[i].as<int, string, int, string>();
        Receita receitaTemp(nome_receita);
        receitaTemp.setIdBanco(id_receita);

        //cada receita possui determinados ingredientes
        pqxx::result ingredientesReceita = conexaoDB.executarQuery("SELECT dev.ingrediente.id_ingrediente, nome_ingrediente, quantidade_ingrediente from dev.receita INNER JOIN dev.ingredientes_receita on dev.receita.id_receita = ingredientes_receita.id_receita INNER JOIN dev.ingrediente on dev.ingredientes_receita.id_ingrediente = dev.ingrediente.id_ingrediente where nome_receita = '" + nome_receita + "';");
        
        //criar um novo objeto da classe QuantidadeIngredientesReceita no vetor de ingredientes da Receita para cada resultado do DB
        for (int j = 0; j < ingredientesReceita.size(); j++)
        {
            auto [id_ingrediente, nome_ingrediente, quantidade_ingrediente] = ingredientesReceita[j].as<int, string, string>();
            QuantidadeIngredientesReceita ingredientesDaReceita(nome_ingrediente, id_ingrediente, quantidade_ingrediente);
            receitaTemp.inserirIngrediente(ingredientesDaReceita);
        }

        //cada receita possui determinados metodos
        pqxx::result metodosReceita = conexaoDB.executarQuery("SELECT texto_metodo from dev.metodo INNER JOIN dev.receita on dev.metodo.id_receita = dev.receita.id_receita where nome_receita = '" + nome_receita + "' ORDER BY passo_cont ASC;");
        
        //criar um novo objeto da classe Metodo no vetor de metodos da Receita para cada resultado do DB
        for (int k = 0; k < metodosReceita.size(); k++)
        {
            auto [texto_metodo] = metodosReceita[k].as<string>();
            Metodo metodoDaReceita(texto_metodo);
            receitaTemp.inserirMetodo(metodoDaReceita);
        }

        //cada receita possui avaliacoes
        pqxx::result avaliacoesReceita = conexaoDB.executarQuery("SELECT comentario, avaliacao, id_comentario, username FROM dev.comentario INNER JOIN dev.usuario on dev.comentario.id_usuario = dev.usuario.id_usuario where dev.comentario.id_receita = " + to_string(id_receita) + ";");

        //criar um novo struct Comentario no vetor de comentarios da Receita para cada resultado do DB
        for (int l = 0; l < avaliacoesReceita.size(); l++)
        {
            auto [comentario, avaliacao, id_comentario, username] = avaliacoesReceita[l].as<string, int, int, string>();
            receitaTemp.inserirComentario(comentario, avaliacao, id_comentario, username);
        }

        //Objetos da classe Pais tb possuem um vetor de Receitas. Portanto, precisamos popular a receita no vetor de receitas do pais correspondente
        for (int m = 0; m < paises.size(); m++) 
        {
            if (paises[m].getNomePais() == nome_pais)  
            {
                paises[m].inserirReceita(receitaTemp); 
            }
        }
        //inserir Receita no vetor de receitas do sistema
        inserirReceita(receitaTemp);
    } 
    executarApp(); 
}

//*******************************************************


//*******************************************************
/* FUNCOES DE MENU/INTERFACE/ETC
 - menuInicial(): menu inicial para usuario logado.
 - menuAdmin(): menu disponvel para administradores. Funcoes elevadas no sistema.
 - listaUsuarios(): lista todos os usuarios cadastrados no sistema.
 - CadastroNovoUsuario(): cadastrar um novo usuario no sistema
 - UsuarioDisponivel(): verifica se o username & email nao estao em uso, durante o cadastro de novo usuario.
 - UsuarioDisponivel(): verifica se o username nao esta em uso, durante alteracao de cadastro existente.
 - Login(): loga usuario no sistema.
 - menuPerfil(): mostra informacoes de perfil.
 - verCadastro(): mostra dados cadastrais do usuario.
 - alterarCadastro(): alterar informacoes de cadastro.
 - mostrarFavoritos(): mostrar receitas favoritadas no sistema.
 - logout(): encerrar sessao.
 - mostrarPaises(): mostrar paises cadastrados no sistema.
 - adicionarPais(): adicionar um novo pais no sistema.
 - PaisDisponivel(): valida se o pais informado ja esta cadastrado no sistema.
 - menuPais(): menu de opcoes do pais selecionado.
 - listarReceitas(): listar receitas.
 - adicionarReceita(): cadastrar nova receita.
 - removerReceita(): apagar receita.
 - menuReceita(): menu de opcoes da receita selecionada.
 - verComentariosReceita(): ver comentarios da receita.
 - verIngredienteseMetodosReceita(): ver ingredientes e metodo de preparo da receita.
 - listarIngredientes(): listar ingredientes cadsatrados no sistema.
 - menuBusca(): buscar receita.
 - aplicarFiltros(): ??
 - removerFavorito(): ??
 - removerComentario(): ??
-------------------------------------------------------*/

void App::menuInicial()
{
    //menu inicial exibido para usuarios logados.
    system("cls");
    int escolha;

    cout << "**MENU INICIAL**\n";
    cout << "1 - Perfil\n";
    cout << "2 - Paises \n";
    cout << "3 - Receitas favoritas \n";
    cout << "4 - Adicionar receita \n";
    cout << "5 - Logout \n";
    cout << "6 - Fechar programa \n";
    if (usuarioLogado.getAdmin())
    {
        cout << "7 - Menu Administrativo\n";
    }
    
    do
    {
        cout << "\nInforme o numero da opcao desejada: ";
        cin >> escolha;

        switch (escolha)
        {
        case 1:
            menuPerfil();
            break;
        case 2:
            mostrarPaises();
            break;
        case 3:
            mostrarFavoritos();
            break;
        case 4:
            adicionarReceita();
            break;
        case 5:
            logout();
            break;
        case 6:
            encerrarApp();
            break;
        case 7:
            // caso um usuario non admin aperte 7, vamos validar que ele eh um admin antes de mostrar as devidas opcoes
            if (usuarioLogado.getAdmin())
            {
                menuAdmin();
            }
            else
            {
                cout << "Escoha invalida.\n"; 
            } 
            break;
        default:
            cout << "Escoha invalida.\n";
        }
    } while (escolha != 6 || (escolha == 7 && !usuarioLogado.getAdmin()));
};

void App::menuAdmin() //** FAZER
{
    //opcoes administrativas do sistema
    system("cls");
    int escolha;
    vector<Receita> receitasCadastradas = getReceitas();

    cout << "MENU ADMINISTRATIVO\n";
    cout << "1 - Listar usuarios\n";
    cout << "2 - Listar todas as receitas cadastradas no sistema\n";
    cout << "3 - Listar todos os ingredientes cadastrados no sistema\n";
    cout << "4 - Adicionar pais\n";
    cout << "5 - Remover uma avaliacao\n";
    cout << "6 - Remover uma receita \n";
    cout << "6 - Criar administrator\n";
    cout << "7 - Retornar ao menu inicial\n";
    cout << "8 - Fechar programa\n";

    do
    {
        cout << "\nInforme a opcao desejada: ";
        cin >> escolha;

        switch (escolha)
        {
        case 1:
            listaUsuarios();
            break;
        case 2:
            listarTodasReceitas();
            break;
        case 3:
            listarIngredientes();
            break;
        case 4:
            adicionarPais();
            break;
        case 5:
            removerAvaliacao();
            break;
        case 6:
            removerReceita();
            break;
        case 7:
            CadastroNovoUsuario(true);
            break;
        case 8:
            menuInicial();
            break;
        case 9:
            encerrarApp();
            break;
        default:
            cout << "Escoha invalida.\n";

        }
    } while (escolha != 9);
}

void App::listaUsuarios()
{
    //listar usuarios cadastrados no sistema
    system("cls");
    int escolha;

    if (usuarios.size() > 0)
    {
        for (int i = 0; i < usuarios.size(); i++)
        {
            cout << "Username: " << usuarios[i].getUsername() << endl; 
            cout << "Nome completo: " << usuarios[i].getNomeCompleto() << endl; 
            cout << "Data de Nascimento: " << usuarios[i].getDataNascimento() << endl; 
            cout << "Email: " << usuarios[i].getEmail() << endl; 
            cout << "Admin: " << usuarios[i].getAdmin() << endl; 
            
            if (i + 1 < usuarios.size())
            {
                cout << "\n";
            }
        }
    }
    else
    {
        cout << "Nenhum usuario cadastrado no sistema. \n";
    }

    cout << "\nMenu de opcoes: " << endl; 
    cout << "1 - Retornar ao menu adiministrativo\n";
    cout << "2 - Retornar ao menu inicial\n";
    cout << "3 - Fechar programa\n\n";
    do
    {
        cout << "Informe a opcao desejada: ";
        cin >> escolha;

        switch (escolha)
        {
        case 1:
            menuAdmin();
            break;
        case 2:
            menuInicial();
            break;
        case 3:
            encerrarApp();
            break;
        default:
            cout << "Escoha invalida.\n";

        }
    } while (escolha != 3);

}

void App::CadastroNovoUsuario(bool admin)
{
    //cadastra novo usuario no sistema
    system("cls");
    int escolha;
    string nomeCompleto, email, dataNascimento, username, senha;

    cout << "CADASTRO DE NOVO USUARIO:\n";
    cout << "Nome Completo: ";
    cin.ignore();
    getline(cin, nomeCompleto);
    cout << "Data de nascimento, no formato (DD/MM/AAAA): ";
    getline(cin, dataNascimento);
    cout << "E-mail: ";
    getline(cin, email);
    cout << "Username(sera o seu login): ";
    getline(cin, username);
    cout << "Senha: ";
    getline(cin, senha);

    if (UsuarioDisponivel(username, email))
    {
        cout << "\nUsername e email disponiveis para uso.\n";

        //cadastrar usuario no sistema
        Conexao conexaoDB("silly.db.elephantsql.com", "zecuhaus", "zecuhaus", "Beib7bJawWzoRjt-gaaRC6NGRUQum-X5");
        
        //cadastrar novo usuario no banco
        if (admin)
        {
            pqxx::result armazenaUsuario = conexaoDB.executarQuery("INSERT INTO dev.usuario (username, senha, nome_completo, email, data_nascimento, admin) VALUES('" + username + "', '" + senha + "', '" + nomeCompleto + "', '" + email + "', TO_DATE('" + dataNascimento + "', 'DD/MM/YYYY'), true)");
            
        }
        else
        {
            pqxx::result armazenaUsuario = conexaoDB.executarQuery("INSERT INTO dev.usuario (username, senha, nome_completo, email, data_nascimento, admin) VALUES('" + username + "', '" + senha + "', '" + nomeCompleto + "', '" + email + "', TO_DATE('" + dataNascimento + "', 'DD/MM/YYYY'), false)");

        }
        
        //buscar o ID recebido no banco para utilizar na criacao do objeto
        pqxx::result idUsuario = conexaoDB.executarQuery("SELECT id_usuario from dev.usuario where username = '" + username + "'");
        auto [id_usuario] = idUsuario[0].as<int>();

        Usuario usuarioLogado(nomeCompleto, dataNascimento, username, senha, email, admin, id_usuario); 
        setUsuarioLogado(usuarioLogado);

        if (admin)
        {
            cout << "Administrador cadastrado com sucesso. Pressione qualquer tecla para retornar ao menu inicial.\n";
        }
        else
        {
            cout << "Usuario cadastrado com sucesso. Pressione qualquer tecla para retornar ao menu inicial.\n";
        }
        system("pause");
        menuInicial();
    }
    else
    {
        cout << "\nNome de usuario e/ou email nao disponivel.\n";
        cout << "1 - Tentar novamente\n";
        cout << "2 - Retornar ao menu inicial\n";
        cout << "3 - Fechar programa\n";
        do
        {
            cout << "Informe a opcao desejada: ";
            cin >> escolha;
            switch (escolha)
            {
            case 1:
                CadastroNovoUsuario(admin);
                break;
            case 2:
                executarApp();
                break;
            case 3:
                encerrarApp();
                break;
            default:
                cout << "Escoha invalida.\n";
            }
        } while (escolha != 3);
    }
}

bool App::UsuarioDisponivel(string tempUsername, string tempEmail)
{
    // funcao para validar se email e/ou username ja estao em uso - novo cadastro
    for (int i = 0; i < usuarios.size(); i++)
    {
        if (tempUsername == usuarios[i].getUsername() || tempEmail == usuarios[i].getEmail())
        {
            return false;
        }
    }
    return true;
}

bool App::UsuarioDisponivel(string tempUsername)
{
    // funcao para validar se username ja esta em uso - alterar cadastro existente
    for (int i = 0; i < usuarios.size(); i++)
    {
        if (tempUsername == usuarios[i].getUsername())
        {
            return false;
        }
    }
    return true; // username disponivel pra uso
}

void App::Login()
{
    // logar usuario no sistema
    system("cls");
    bool userAutenticado = false;
    int escolha;
    string tempUsername, tempSenha;

    cout << "REALIZE O SEU LOGIN:\n";
    cout << "Informe o seu username: ";
    cin.ignore();
    cin >> tempUsername;
    cout << "Informe a sua senha: ";
    cin >> tempSenha;

    for (int i = 0; i < usuarios.size(); i++)
    { 
        if (usuarios[i].getUsername() == tempUsername && usuarios[i].getSenha() == tempSenha)
        {
            userAutenticado = true;
            cout << "\nUsuario autenticado. " << endl;

            Usuario usuarioLogado(usuarios[i].getNomeCompleto(), usuarios[i].getDataNascimento(), usuarios[i].getUsername(), usuarios[i].getSenha(), usuarios[i].getEmail(), usuarios[i].getAdmin(), usuarios[i].getIdBanco());
            //carregar favoritos
            vector<Favorito> favoritos = usuarios[i].receitasFavoritas();
            for (int j = 0; j < favoritos.size(); j++)
            {
                usuarioLogado.favoritarReceita(favoritos[j]);
            }
            setUsuarioLogado(usuarioLogado); 
            menuInicial();
        }
    }
    if (!userAutenticado)
    {
        cout << "\nDados incorretos. Falha no login.\n";
        cout << "1 - Tentar novamente\n";
        cout << "2 - Retornar ao menu inicial\n";
        cout << "3 - Fechar programa\n";
        do
        {
            cout << "Informe a opcao desejada: ";
            cin >> escolha;
            switch (escolha)
            {
            case 1:
                Login();
                break;
            case 2:
                executarApp();
                break;
            case 3:
                encerrarApp();
                break;
            default:
                cout << "Escoha invalida.\n";

            }
        } while (escolha != 3);
    }
}

void App::menuPerfil()
{
    //mostrar perfil do usuario
    system("cls");
    int escolha;

    cout << "*****MEU PERFIL*****\n\n";
    cout << "Username: " << usuarioLogado.getUsername() << endl;
    cout << "1 - Ver/Alterar dados \n";
    cout << "2 - Favoritos \n";
    cout << "3 - Logout \n";
    cout << "4 - Voltar ao menu inicial \n";
    cout << "5 - Fechar programa \n";

    do
    {
        cout << "\nInforme o numero da opcao desejada ";
        cin >> escolha;

        switch (escolha)
        {
        case 1:
            verCadastro();
            break;
        case 2:
            mostrarFavoritos();
            break;
        case 3:
            logout();
            break;
        case 4:
            menuInicial();
            break;
        case 5:
            encerrarApp();
            break;
        default:
            cout << "Escoha invalida.\n";
        }
    } while (escolha != 5);
};

void App::verCadastro()
{
    //mostrar dados de cadastro do usuario
    system("cls");
    int escolha;

    cout << "DADOS DO SEU CADASTRO: \n";
    usuarioLogado.dados();

    cout << "\nDeseja editar seu username e/ou senha?\n";
    cout << "1 - Sim\n";
    cout << "2 - Nao, retornar ao perfil\n";
    cout << "3 - Retornar ao menu inicial\n";
    cout << "4 - Fechar programa\n";
    do
    {
        cout << "\nInforme a opcao desejada: ";
        cin >> escolha;
        switch (escolha)
        {
        case 1:
            alterarCadastro();
            break;
        case 2:
            menuPerfil();
            break;
        case 3:
            menuInicial();
            break;
        case 4:
            encerrarApp();
            break;
        default:
            cout << "Escolha invalida.\n";
        }
    } while (escolha != 4);
};

void App::alterarCadastro()
{
    //alterar informacoes de cadastro do usuario
    system("cls");
    int escolha;
    string novoUsername, novaSenha;

    cout << "EDITAR DADOS: \n";
    cout << "Username(sera o seu login): ";
    cin.ignore();
    getline(cin, novoUsername);
    cout << "Senha: ";
    getline(cin, novaSenha);

    if (UsuarioDisponivel(novoUsername))
    {
        usuarioLogado.setUsername(novoUsername);
        usuarioLogado.setSenha(novaSenha);

        Conexao newCon("silly.db.elephantsql.com", "zecuhaus", "zecuhaus", "Beib7bJawWzoRjt-gaaRC6NGRUQum-X5");
        pqxx::result atualizarUsuario = newCon.executarQuery("UPDATE dev.usuario SET username = '" + novoUsername + "', senha = '" + novaSenha + "' WHERE id_usuario = " + to_string(usuarioLogado.getIdBanco()) + ";");

        for (int i = 0; i < usuarios.size(); i++)
        {
            if (usuarioLogado.getIdBanco() == usuarios[i].getIdBanco())
            {
                usuarios[i].setUsername(novoUsername);
                usuarios[i].setSenha(novaSenha);
            }
        }

        cout << "\nInformacoes atualizadas com sucesso. Pressione qualquer tecla para retornar a pagina incial e faca login novamente.\n";
        system("pause");
        executarApp();
    }
    else
    {
        cout << "\nNome de usuario nao disponivel.\n";
        cout << "Informe a opcao desejada: \n";
        cout << "1 - Tentar novamente.\n";
        cout << "2 - Retornar ao perfil.\n";
        cout << "3 - Retornar ao menu inicial\n";
        cout << "4 - Fechar programa\n";

        do
        {
            cout << "\nInforme a opcao desejada: ";
            cin >> escolha;
            switch (escolha)
            {
            case 1:
                alterarCadastro();
                break;
            case 2:
                menuPerfil();
                break;
            case 3:
                menuInicial();
                break;
            case 4:
                encerrarApp();
                break;
            default:
                cout << "Opcao invalida.\n";
            }
        } while (escolha != 4);
    }
}

void App::mostrarFavoritos()
{
    //mostrar receitas favoritadas do usuario
    system("cls");
    int escolha, receitaEscolhida;
    cout << "RECEITAS FAVORITAS\n";

    if (usuarioLogado.receitasFavoritas().size() > 0)
    {
        for (int i = 0; i < usuarioLogado.receitasFavoritas().size(); i++)
        {
            cout << " " << i + 1 << " - " << usuarioLogado.receitasFavoritas()[i].getNomeReceita() << endl;
        }

        cout << "\nO que deseja fazer? \n";
        cout << "1 - Acessar receita \n";
        cout << "2 - Remover receita dos favoritos \n";
        cout << "3 - Voltar ao menu inicial\n";
        cout << "4 - Fechar programa\n";
        do
        {
            cout << "\nInforme o numero da opcao desejada: ";
            cin >> escolha;
            switch (escolha)
            {
            case 1:

                do {
                    cout << "Informe o numero da receita: ";
                    cin >> receitaEscolhida;

                    if (receitaEscolhida < 1 || receitaEscolhida > usuarioLogado.receitasFavoritas().size())
                    {
                        cout << "Escoha invalida.\n";
                    }
                    else
                    {
                        for (int i = 0; i < receitas.size(); i++)
                        {
                            if (usuarioLogado.receitasFavoritas()[receitaEscolhida - 1].getIdReceita() == receitas[i].getIdBanco())
                            {
                                setReceitaSelecionada(receitas[i]);
                                menuReceita();
                            }
                        }
                    }
                } while (receitaEscolhida < 1 || receitaEscolhida > receitas.size());

                break;
            case 2:

                do {
                    cout << "Informe o numero da receita: ";
                    cin >> receitaEscolhida;

                    if (receitaEscolhida < 1 || receitaEscolhida > usuarioLogado.receitasFavoritas().size())
                    {
                        cout << "Escoha invalida.\n";
                    }
                    else
                    {
                        removerFavorito(receitaEscolhida - 1);
                    }
                } while (receitaEscolhida < 1 || receitaEscolhida > receitas.size());

                break;
            case 3:
                menuInicial();
                break;
            case 4:
                encerrarApp();
                break;
            default:
                cout << "Escoha invalida.\n";
            }
        } while (escolha != 3);
    }
    else
    {
        cout << "Voce nao possui nenhuma receita favorita. Pressione qualquer tecla para retornar ao menu inicial\n";
        system("pause");
        menuInicial();
    }
};

void App::logout()
{
    //encerrar sessao do usuario logado
    system("cls");
    int escolha;

    cout << "DESEJA REALMENTE SAIR?\n";
    cout << "1 - Sim\n";
    cout << "2 - Nao, retornar ao menu incial\n";
    cout << "3 - Fechar programa\n";
    do {
        cout << "\nInforme a opcao desejada: ";
        cin >> escolha;

        switch (escolha)
        {
        case 1:
            cout << "\nObrigado(a) por usar nosso aplicativo.\n";
            executarApp();
            break;
        case 2:
            menuInicial();
            break;
        case 3:
            encerrarApp();
            break;
        default:
            cout << "Escolha invalida.\n";
        }
    } while (escolha != 3);
}

void App::mostrarPaises()
{
    //listar paises cadastrados no sistema e selecionar pais para ver informacoes
    system("cls");
    int paisEscolhido;

    //aqui vai imprimir os paises ja cadastrados por admins
    if (paises.size() > 0)
    {
        cout << "LISTA DE PAISES:\n";

        for (int i = 0; i < paises.size(); i++) 
        {
            cout << " " << i + 1 << " - " << paises[i].getNomePais() << " (" << paises[i].getReceitas().size() << " receitas cadastradas)." << endl;
        }

        do {
            cout << "Informe o numero do pais: ";
            cin >> paisEscolhido;

            if (paisEscolhido < 1 || paisEscolhido > paises.size())
            {
                cout << "Escoha invalida.\n";
            }
            else
            {
                setPaisSelecionado(paises[paisEscolhido - 1]);
                menuPais();
            }
        } while (paisEscolhido < 1 || paisEscolhido > paises.size());
    }
    else
    {
        cout << "Nenhum pais cadastrado no sistema. Pressione qualquer tecla para retornar ao menu inicial\n";
        system("pause");
        menuInicial();
    }
}

void App::adicionarPais()
{
    //cadastrar novo pais no sistema- disponivel para admins
    system("cls");
    int escolha;
    string nomePais, resumo;

    cout << "Qual pais voce deseja adicionar ao aplicativo?\n";
    getline(cin, nomePais);

    if (PaisDisponivel(nomePais))
    {
        cout << "Informe o resumo contendo informacoes sobre a cultura do pais adicionado: \n";
        getline(cin, resumo);

        Conexao newCon("silly.db.elephantsql.com", "zecuhaus", "zecuhaus", "Beib7bJawWzoRjt-gaaRC6NGRUQum-X5");
        pqxx::result inserirPais = newCon.executarQuery("INSERT INTO dev.pais (nome_pais, resumo_pais) VALUES ('" + nomePais + "', '" + resumo + "');");
        pqxx::result idPais = newCon.executarQuery("SELECT id_pais from dev.pais where nome_pais = '" + nomePais + "';");
        auto [id_pais] = idPais[0].as<int>();

        Pais paisTemp(nomePais, resumo, id_pais);
        paises.push_back(paisTemp);
        cout << "\nPais cadastrado com sucesso. Pressione qualquer tecla para retornar ao menu adiministrativo.\n";
        system("pause");
        menuAdmin();
    }
    else
    {
        cout << "\nO pais ja esta cadastrado.\n";
        cout << "Menu de opcoes: \n";
        cout << "1 - Tentar novamente.\n";
        cout << "2 - Retornar ao menu administrativo.\n";
        cout << "3 - Retornar ao menu inicial\n";
        cout << "4 - Fechar programa\n";
        do
        {
            cout << "\nInforme a opcao desejada: ";
            cin >> escolha;
            switch (escolha)
            {
            case 1:
                adicionarPais();
                break;
            case 2:
                menuAdmin();
                break;
            case 3:
                menuInicial();
                break;
            case 4:
                encerrarApp();
                break;
            default:
                cout << "Opcao invalida.\n";
            }
        } while (escolha != 4);
    }
}

bool App::PaisDisponivel(string nomePais)
{
    //valida se o pais ja esta cadastrado no sistema
    for (int i = 0; i < paises.size(); i++) 
    {
        if (paises[i].getNomePais() == nomePais) 
            return false;
    }
    return true;
};

void App::menuPais()
{
    //menu de opcoes do pais selecionado
    system("cls");
    int escolha;

    cout << "*****" + paisSelecionado.getNomePais() + "*****\n";
    cout << paisSelecionado.getResumo() << endl;
    cout << "1 - Ver as receitas tradicionais do pais \n";
    cout << "2 - Pesquisar receita \n";
    cout << "3 - Adicionar receita \n";
    cout << "4 - Retornar ao menu inicial \n";
    cout << "5 - Fechar programa \n";

    do
    {
        cout << "\nInforme o numero da opcao desejada ";
        cin >> escolha;
        switch (escolha)
        {
        case 1:
            listarReceitas();
            break;
        case 2:
            menuBusca();
        case 3:
            adicionarReceita();
            break;
        case 4:
            menuInicial();
            break;
        case 5:
            encerrarApp();
            break;
        default:
            cout << "Escolha invalida.\n";
        }
    } while (escolha != 5);
}

void App::listarReceitas()
{
    //listar receitas cadastradas para o pais selecionado
    system("cls");
    int receitaEscolhida;

    cout << "LISTA DE RECEITAS.\n";
    cout << "Pais selecionado: " << paisSelecionado.getNomePais() << "\n\n";

    if (paisSelecionado.getReceitas().size() > 0)
    {
        for (int i = 0; i < paisSelecionado.getReceitas().size(); i++)
        {
            cout << " " << i + 1 << " - " << paisSelecionado.getReceitas()[i].getNomeReceita() << endl;
        }

        do {

            cout << "\nInforme o numero da receita: ";
            cin >> receitaEscolhida;

            if (receitaEscolhida < 1 || receitaEscolhida > paisSelecionado.getReceitas().size())
            {
                cout << "\nEscoha invalida.\n";
            }
            else
            {
                setReceitaSelecionada(paisSelecionado.getReceitas()[receitaEscolhida - 1]);
                menuReceita();
            }
        } while (receitaEscolhida < 1 || receitaEscolhida > receitas.size());
    }
    else
    {
        cout << "\nAinda nao ha receitas cadastradas para este pais.\n";
    }
};

void App::adicionarReceita() 
{
    //cadastrar nova receita no sistema
    system("cls");
    bool ingredienteExistente = false;
    int escolha, contMetodo = 1;
    string nomeReceita, nomeIngrediente, textoMetodo, quantidade;

    Conexao newCon("silly.db.elephantsql.com", "zecuhaus", "zecuhaus", "Beib7bJawWzoRjt-gaaRC6NGRUQum-X5");

    cout << " ***** " + paisSelecionado.getNomePais() + " *****\n\n";
    cout << "Informe o nome da receita que deseja adicionar: ";
    cin.ignore();
    getline(cin, nomeReceita);
    Receita receita(nomeReceita);

    cout << "\nAdicionar ingredientes" << endl;
    do
    {
        cout << "Informe o nome do ingrediente: ";
        getline(cin, nomeIngrediente);
        cout << "Informe a quantidade deste ingrediente: ";
        getline(cin, quantidade);

        for (int i = 0; i < ingredientes.size(); i++)
        {
            if (ingredientes[i].getNomeIngrediente() == nomeIngrediente)
            {

                QuantidadeIngredientesReceita ingredienteReceita(nomeIngrediente, ingredientes[i].getIdBanco(), quantidade);
                receita.inserirIngrediente(ingredienteReceita);
                ingredienteExistente = true;
                break;
            }
        }
        if (!ingredienteExistente)
        {
            pqxx::result inserirNovoIngrediente = newCon.executarQuery("INSERT INTO dev.ingrediente (nome_ingrediente) VALUES ('" + nomeIngrediente + "')");
            pqxx::result idNovoIngrediente = newCon.executarQuery("SELECT id_ingrediente from dev.ingrediente WHERE nome_ingrediente = '" + nomeIngrediente + "'");
            auto [id_ingrediente] = idNovoIngrediente[0].as<int>();
            int idIngrediente = id_ingrediente;

            Ingrediente novoIngrediente(nomeIngrediente, id_ingrediente);
            QuantidadeIngredientesReceita ingredienteReceita(nomeIngrediente, id_ingrediente, quantidade);

            receita.inserirIngrediente(ingredienteReceita);
            ingredientes.push_back(novoIngrediente);
        }

        cout << "\nDeseja adicionar mais um ingrediente na receita? \n";
        cout << "1 - Sim\n";
        cout << "2 - Nao\n";
        cout << "\nInforme a opcao desejada: ";
        cin >> escolha;
        cin.ignore();
        switch (escolha)
        {
        case 1:
            break;
        case 2:
            break;
        default:
            cout << "Opcao invalida.\n";
        }

    } while (escolha != 2);

    //--------------------------
    escolha = 1;
    cout << "\nAdicionar metodo de preparo: \n";
    do
    {
        cout << "Passo " << contMetodo << ": ";
        getline(cin, textoMetodo);
        Metodo metodo(textoMetodo);
        receita.inserirMetodo(metodo);
        cout << "\nDeseja adicionar mais um metodo na receita? \n";
        cout << "1 - Sim\n";
        cout << "2 - Nao\n";
        cout << "\nDigite o numero da opcao desejada: ";
        cin >> escolha;
        cin.ignore();
        contMetodo++;
    } while (escolha == 1);

    pqxx::result novaReceita = newCon.executarQuery("INSERT INTO dev.receita(nome_receita,id_pais) VALUES ('" + nomeReceita + "', " + to_string(paisSelecionado.getIdBanco()) + ")");
    pqxx::result idReceitaQuery = newCon.executarQuery("SELECT id_receita FROM dev.receita WHERE nome_receita = '" + nomeReceita + "'");

    auto [id_receita] = idReceitaQuery[0].as<int>();
    int idReceita = id_receita;

    vector<QuantidadeIngredientesReceita> ingredientesUtilizados = receita.getIngredientes();

    cout << "Armazenando dados no sistema...\n\n";

    for (int i = 0; i < ingredientesUtilizados.size(); i++)
    {
        pqxx::result inserirIngredientesReceita = newCon.executarQuery("INSERT INTO dev.ingredientes_receita (id_ingrediente, id_receita, quantidade_ingrediente) VALUES (" + to_string(ingredientesUtilizados[i].getIdBanco()) + ", " + to_string(idReceita) + ", '" + ingredientesUtilizados[i].getQuantidade() + "')");
    }

    vector<Metodo> metodosReceita = receita.getMetodos();

    for (int i = 0; i < metodosReceita.size(); i++)
    {
        pqxx::result inserirMetodosReceita = newCon.executarQuery("INSERT INTO dev.metodo (passo_cont, texto_metodo, id_receita) VALUES (" + to_string(i + 1) + ", '" + metodosReceita[i].getTexto() + "', " + to_string(idReceita) + ")");
    }

    paisSelecionado.inserirReceita(receita);
    cout << "\nReceita cadastrada com sucesso. Digite qualquer tecla para retornar ao menu do pais selecionado.\n";
    system("pause");
    menuPais();
}

void App::removerReceita() 
{
    //FUNCAO ADMIN -- remove alguma receita do pais E do sistema
    system("cls");
    int removerReceita;
    Conexao conexaoDB("silly.db.elephantsql.com", "zecuhaus", "zecuhaus", "Beib7bJawWzoRjt-gaaRC6NGRUQum-X5");
    pqxx::result deletarReceitaDB; 
    cout << "RECEITAS DO SISTEMA\n";
    for (int i = 0; i < receitas.size(); i++)
    {
        cout << " " << i + 1 << " - " << "Nome receita: " << receitas[i].getNomeReceita() << endl;
    }
    do
    {
        cout << "Digite o numero da receita que voce deseja apagar: ";
        cin >> removerReceita;

        if (removerReceita < 1 || removerReceita > receitas.size())
        {
            cout << "Escoha invalida.\n";
        }
        else
        {
            //deletar receita do DB
            deletarReceitaDB = conexaoDB.executarQuery("DELETE FROM dev.receita WHERE id_receita = " + to_string(receitas[removerReceita - 1].getIdBanco()) + ";");

            //deletar receita do vetor de receita do pais
            for (int j=0;j<paises.size();j++)
            {
                for (int k=0; k<paises[j].getReceitas().size();k++)
                {
                    if (receitas[removerReceita-1].getIdBanco()==paises[j].getReceitas()[k].getIdBanco())
                    {
                        paises[j].getReceitas().erase(paises[j].getReceitas().begin() + k);
                    }
                }
            }

            //deletar receita do vetor de receita do sistema
            receitas.erase(receitas.begin() + removerReceita - 1);

            cout << "\Receita removida com sucesso, pressione qualquer tecla para voltar ao menu administrador\n";
            system("pause");
            menuAdmin();
        }
    } while (removerReceita < 1 || removerReceita > receitas.size());
};

void App::menuReceita()
{
    //menu de opcoes da receita
    system("cls");
    int escolha;
    cout << "*****RECEITA*****\n\n";
    cout << receitaSelecionada.getNomeReceita() << endl;
    cout << "1 - Ver os ingredientes e metodo de preparo \n";
    cout << "2 - Ver avaliacoes \n";
    cout << "3 - Adicionar receita aos favoritos \n";
    cout << "4 - Avaliar receita \n";
    cout << "5 - Voltar ao pais \n";
    cout << "6 - Voltar ao menu inicial \n";
    cout << "7 - Fechar programa\n";
    do
    {
        cout << "\nInforme o numero da opcao desejada: ";
        cin >> escolha;
        switch (escolha)
        {
        case 1:
            verIngredienteseMetodosReceita();
            break;
        case 2:
            verAvaliacaoReceita();
            break;
        case 3:
            adicionarFavorito();
            break;
        case 4:
            avaliarReceita();
            break;
        case 5:
            menuPais();
            break;
        case 6:
            menuInicial();
            break;
        case 7:
            encerrarApp();
            break;
        default:
            cout << "Escolha invalida.";
        }
    } while (escolha != 7);
}

void App::verAvaliacaoReceita()
{
    system("cls");
    cout << "AVALIACOES\n";
    
    if (receitaSelecionada.getComentarios().size() > 0)
    {
        for (int i = 0; i < receitaSelecionada.getComentarios().size(); i++) 
        {
            cout << " - Avaliacao " << i + 1 << ":\n";
            cout << "   - " << receitaSelecionada.getComentarios()[i].comentario << "." << endl; 
            cout << "   - " << receitaSelecionada.getComentarios()[i].estrelas << "/5 estrelas." << endl; 
            cout << "   - Criado por " << receitaSelecionada.getComentarios()[i].username << "." << endl; 
            cout << "\n";
        }
    }
    else
    {
        cout << "\nReceita ainda nao possui nenhum comentario.";
    }
    cout << "\nDigite qualquer tecla para retornar ao menu da receita.\n";
    system("pause");
    menuReceita(); 
}

void App::verIngredienteseMetodosReceita()
{
    // listar ingredientes e metodo de preparo da receita
    system("cls");
    int escolha;

    cout << "INGREDIENTES:\n";

    vector<QuantidadeIngredientesReceita> ingredientesDaReceitaSelecionada = receitaSelecionada.getIngredientes();

    for (int i = 0; i < ingredientesDaReceitaSelecionada.size(); i++)
    {
        cout << ingredientesDaReceitaSelecionada[i].getNomeIngrediente() << " - " << ingredientesDaReceitaSelecionada[i].getQuantidade() << endl;
    }

    cout << "\nMETODO: \n";
    vector<Metodo> metodoDaReceita = receitaSelecionada.getMetodos();
    for (int i = 0; i < metodoDaReceita.size(); i++)
    {
        cout << "Passo " << i + 1 << " - " << metodoDaReceita[i].getTexto() << endl;
    }

    cout << "\n\nInforme a opcao desejada:\n";
    cout << "1 - Retornar ao menu da receita\n";
    cout << "2 - Retornar ao menu inicial\n";
    cout << "3 - Fechar programa\n";
    do
    {
        cout << "\nInforme o numero da opcao desejada ";
        cin >> escolha;
        switch (escolha)
        {
        case 1:
            menuReceita();
            break;
        case 2:
            menuInicial();
        case 3:
            encerrarApp();
            break;
        default:
            cout << "Escolha invalida.\n";
        }
    } while (escolha != 3);
}

void App::listarIngredientes()
{
    //listar todos os ingredientes do sistema
    if (ingredientes.size() > 0)
    {
        for (int i = 0; i < ingredientes.size(); i++)
        {
            cout << "Ingrediente: " << ingredientes[i].getNomeIngrediente() << endl;

            if (i + 1 < ingredientes.size())
            {
                cout << "\n";
            }
        }
    }
    else
    {
        cout << "Nenhum ingrediente cadastrado no sistema. \n";
    }
}

void App::menuBusca() //***FAZER
{/*
    //acho que o melhor eh as restricoes serem colocadas no banco de dados pelo adm.
    //eai aparecem na busca por algum bool ou sei la..
 
    //menu de busca e filtro de receitas
    int escolha;
    int num, num2, num3;
    cout << "**PESQUISAR RECEITA**\n";
    cout << "1 - Restricoes \n";
    cout << "2 - Pimenta \n";
    cout << "3 - Tipo de refeicao \n";
    cout << "4 - Clasificacao: \n";
    cout << "5 - Busca pelo nome \n";
    cout << "6 - Voltar ao Pais \n";
    cout << "7 - Voltar ao menu inicial \n";
    cout << "8 - Encerrar programa \n";
    cout << "Informe o numero da opcao desejada: ";





    cout << "\nInforme agora caracteristicas sobre esta receita\n";
    cout << "Sobre restricoes alimentares: \n";
    do
    {
        escolha = 1;
        cout << "1 - Sem gluten" << endl;
        cout << "2 - Sem lactose" << endl;
        cout << "3 - Vegano" << endl;
        cout << "4 - +18 (contem bebida alcoolica)" << endl;
        cout << "Digite o numero que corresponde: ";
        cin >> num;
        cout << "Deseja informar mais uma restricao sobre esta receita?\n";
        cout << "1 - Sim\n";
        cout << "2 - Nao\n";

    } while (escolha != 2);
    
    

   
    cout << "Agora informe a quantidade de pimenta:" << endl;
    cout << "1 - Sem pimenta" << endl;
    cout << "2 - Pouco apimentado" << endl;
    cout << "3 - Apimentado" << endl;
    cout << "4 - Muito apimentado" << endl;
    cout << "Digite o numero que corresponde: ";
    cin >> num2;
    

    cout << "Tipo de refeicao:" << endl;
    cout << "1 - Refeicao completa" << endl;
    cout << "2 - Pratos salgados" << endl;
    cout << "3 - Agridoce/Doce" << endl;
    cout << "4 - Lanche" << endl;
    cout << "5 - Sobremesa" << endl;
    cout << "Digite o numero que corresponde: ";
    cin >> num3;
    cout << "Esta refeicao se encaixa em mais um tipo?\n";
    cout << "1 - Sim\n";
    cout << "2 - Nao\n";

    


    //falta criar o switch .
    cin >> escolha;
    */
};

void App::aplicarFiltros()//***FAZER
{
    int num, num2, num3, num4;
    cout << "Restricoes:" << endl;
    cout << "1 - Sem gluten" << endl;
    cout << "2 - Sem lactose" << endl;
    cout << "3 - Vegano" << endl;
    cout << "4 - +18 (contem bebida alcoolica)" << endl;
    cin >> num;
    cout << "Pimenta:" << endl;
    cout << "1 - Sem pimenta" << endl;
    cout << "2 - Pouco apimentado" << endl;
    cout << "3 - Apimentado" << endl;
    cout << "4 - Muito apimentado" << endl;
    cin >> num2;
    cout << "Tipo de refeicao:" << endl;
    cout << "1 - Refeicao completa" << endl;
    cout << "2 - Pratos salgados" << endl;
    cout << "3 - Agridoce/Doce" << endl;
    cout << "4 - Lanche" << endl;
    cout << "5 - Sobremesa" << endl;
    cin >> num3;
    cout << "Classificacao:" << endl;
    cout << "1 - 1 estrela" << endl;
    cout << "2 - 2 estrelas" << endl;
    cout << "3 - 3 estrelas" << endl;
    cout << "4 - 4 estrelas" << endl;
    cout << "5 - 5 estrelas" << endl;
    cin >> num4;

};

void App::adicionarFavorito()
{
    system("cls");
    int idReceita = receitaSelecionada.getIdBanco();
    int idUsuario = usuarioLogado.getIdBanco();

    Conexao newCon("silly.db.elephantsql.com", "zecuhaus", "zecuhaus", "Beib7bJawWzoRjt-gaaRC6NGRUQum-X5");
    pqxx::result inserirFavorito = newCon.executarQuery("INSERT INTO dev.favorito (id_usuario, id_receita) VALUES (" + to_string(idUsuario) + ", " + to_string(idReceita) + ");");
    pqxx::result idNovoFavorito = newCon.executarQuery("SELECT id_favorito, nome_receita, nome_pais FROM dev.favorito INNER JOIN dev.receita on dev.favorito.id_receita = dev.receita.id_receita INNER JOIN dev.pais on dev.receita.id_pais = dev.pais.id_pais WHERE id_usuario = " + to_string(idUsuario) + " and dev.favorito.id_receita =  " + to_string(idReceita) + ";");
    auto [id_banco, nome_receita, nome_pais] = idNovoFavorito[0].as<int, string, string>();
    
    Favorito novoFavorito(idReceita, id_banco, nome_receita, nome_pais);
    
    usuarioLogado.favoritarReceita(novoFavorito);
    
    for (int i = 0; i < usuarios.size(); i++)
    {
        if (usuarioLogado.getIdBanco() == usuarios[i].getIdBanco())
        {
            usuarios[i].favoritarReceita(novoFavorito);
        }
    }
    
    cout << "\nReceita adicionada aos favoritos com sucesso. Pressione qualquer tecla para retornar ao menu da receita.\n";
    system("pause");
    menuReceita();
}

void App::removerFavorito(int indice)
{
    //deletar favorito do DB
    Conexao conexaoDB("silly.db.elephantsql.com", "zecuhaus", "zecuhaus", "Beib7bJawWzoRjt-gaaRC6NGRUQum-X5");
    pqxx::result deletarFavoritoDB = conexaoDB.executarQuery("DELETE FROM dev.favorito WHERE id_favorito = " + to_string(usuarioLogado.receitasFavoritas()[indice].getIdBanco()) + ";");
    
    //deletar favorito do vetor de objetos
    usuarioLogado.excluirFavorito(indice);

    cout << "\nA receita foi removida dos seus favoritos.\n";
    cout << "Digite qualquer tecla para voltar as receitas favoritas.\n";
    system("pause");
    mostrarFavoritos();
}

void App::avaliarReceita()
{
    system("cls");
    string comentario; 
    int estrelas;
    cout << "Adicione um comentario nesta receita: \n";
    cin.ignore();
    getline(cin, comentario);

    cout << "\nQuantas estrelas voce da para esta receita?: \n";
    cout << "1 estrela\n";
    cout << "2 estrelas\n";
    cout << "3 estrelas\n";
    cout << "4 estrelas\n";
    cout << "5 estrelas\n";
    cout << "Digite o numero: ";
    cin >> estrelas;

    Conexao newCon("silly.db.elephantsql.com", "zecuhaus", "zecuhaus", "Beib7bJawWzoRjt-gaaRC6NGRUQum-X5");
    pqxx::result inserirAvaliacao = newCon.executarQuery("INSERT INTO dev.comentario (id_usuario, id_receita, comentario, avaliacao) VALUES (" + to_string(usuarioLogado.getIdBanco()) + ", " + to_string(receitaSelecionada.getIdBanco()) + ", '" + comentario + "', " + to_string(estrelas) + ");");
    pqxx::result idNovoComentario = newCon.executarQuery("SELECT id_comentario FROM dev.comentario WHERE id_usuario = " + to_string(usuarioLogado.getIdBanco()) + " and dev.receita.id_receita =  " + to_string(receitaSelecionada.getIdBanco()) + ";");
    auto [id_banco] = idNovoComentario[0].as<int>();

    receitaSelecionada.inserirComentario(comentario, estrelas, id_banco, usuarioLogado.getUsername());
    for (int i=0; i<receitas.size();i++)
    {
        if (receitaSelecionada.getNomeReceita()==receitas[i].getNomeReceita())
        {
            receitas[i].inserirComentario(comentario, estrelas, id_banco, usuarioLogado.getUsername());
        }
    }
    for (int i = 0; i < paises.size(); i++)
    {
        for (int j=0; j<paises[i].getReceitas().size();j++)
        {
            if (paises[i].getReceitas()[j].getNomeReceita() == receitaSelecionada.getNomeReceita())
            {
                paises[i].getReceitas()[j].inserirComentario(comentario, estrelas, id_banco, usuarioLogado.getUsername());
            }
        }
       
    }

    cout << "Avaliacao realizada com sucesso\n";
    cout << "Pressione qualquer tecla para voltar ao menu da receita.\n";
    system("pause");
    menuReceita();
}

void App::removerAvaliacao()
{
    //FUNCAO ADMIN -- remove avaliacao de alguma receita do sistema
    int tempAvaliacao, escolha, receitaEscolhida; 
    Conexao conexaoDB("silly.db.elephantsql.com", "zecuhaus", "zecuhaus", "Beib7bJawWzoRjt-gaaRC6NGRUQum-X5");
    pqxx::result deletarAvaliacaoDB;
    system("cls");
    cout << "AVALIACOES DO SISTEMA\n";
    for (int i=0; i<receitas.size();i++)
    {
        cout << " " << i + 1 << " - " << "Nome receita: " << receitas[i].getNomeReceita() << " - Quantidade de comentarios: " << receitas[i].getComentarios().size() << endl;
    }
    do {
        cout << "Digite o numero da receita que voce deseja apagar algum comentario: ";
        cin >> receitaEscolhida; 

        if (receitaEscolhida < 1 || receitaEscolhida > receitas.size())
        {
            cout << "Escoha invalida.\n";
        }
        else
        {
            if (receitas[receitaEscolhida - 1].getComentarios().size()>0)
            {
                cout << "\nAVALIACOES DA RECEITA SELECIONADA\n";
                for (int j = 0; j < receitas[receitaEscolhida - 1].getComentarios().size(); j++)
                {
                    cout << " - Avaliacao " << j + 1 << ":\n";
                    cout << "   - " << receitas[receitaEscolhida - 1].getComentarios()[j].comentario << "." << endl;
                    cout << "   - " << receitas[receitaEscolhida - 1].getComentarios()[j].estrelas << "/5 estrelas." << endl;
                    cout << "   - Criado por " << receitas[receitaEscolhida - 1].getComentarios()[j].username << "." << endl;
                    cout << "\n";
                }

                cout << "Voce deseja remover uma destas avaliacoes?\n";
                cout << "1 - Sim\n";
                cout << "2 - Nao, desejo voltar ao menu de administrador\n";
                do
                {
                    cout << "\nInforme a opcao desejada: ";
                    cin >> escolha;
                    switch (escolha)
                    {
                    case 1:


                        cout << "Informe o numero da avaliacao que voce deseja remover: ";
                        cin >> tempAvaliacao;

                        //deletar comentario do DB
                        deletarAvaliacaoDB = conexaoDB.executarQuery("DELETE FROM dev.comentario WHERE id_comentario = " + to_string(receitas[receitaEscolhida - 1].getComentarios()[tempAvaliacao - 1].idBanco) + ";");

                        //deletar comentario do vetor de comentarios da receita
                        receitas[receitaEscolhida - 1].apagarComentario(tempAvaliacao - 1);
                        cout << "\nAvaliacao removida com sucesso, pressione qualquer tecla para voltar ao menu administrador\n";
                        system("pause");
                        menuAdmin();
                        break;
                    case 2:
                        menuAdmin();
                        break;
                    default:
                        cout << "\nOpcao invalida.\n";
                    }
                } while (escolha != 2);
            }
            else
            {
                cout << "\nA receita selecionada nao possui nenhuma avaliacao. Pressione qualquer tecla para voltar ao menu administrativo.\n";
                system("pause");
                menuAdmin();
            }
        }
    } while (receitaEscolhida < 1 || receitaEscolhida > paises.size());
};

void App::listarTodasReceitas()
{
    //FUNCAO ADMIN -- listar todas as receitas cadastradas no sistema
    system("cls");
    cout << "LISTA DE RECEITAS.\n";
    int escolha, receitaEscolhida;

    if (receitas.size() > 0)
    {
        for (int i = 0; i < receitas.size(); i++)
        {
            cout << " " << i+1 << " - " << receitas[i].getNomeReceita() << endl;
        }
        cout << "\nMenu de opcoes: " << endl;
        cout << "1 - Acessar receita\n";
        cout << "2 - Excluir receita\n";
        cout << "3 - Retornar ao menu administrativo\n";
        cout << "4 - Retornar ao meu incial\n";

        do
        {
            cout << "\nEscolha a opcao desejada: ";
            cin >> escolha;
            switch (escolha)
            {
            case 1:

                do {
                    cout << "Informe o numero da receita: ";
                    cin >> receitaEscolhida;

                    if (receitaEscolhida < 1 || receitaEscolhida > receitas.size())
                    {
                        cout << "Escoha invalida.\n";
                    }
                    else
                    {
                        setReceitaSelecionada(receitas[receitaEscolhida - 1]);
                        menuReceita();
                    }
                } while (receitaEscolhida < 1 || receitaEscolhida > receitas.size());

                break;
            case 2:
                removerReceita();
                break;
            case 3:
                menuAdmin();
                break;
            case 4:
                menuInicial();
                break;
            default:
                cout << "Escoha invalida.\n";
            }
        } while (escolha != 4);
    }
    else
    {
        cout << "Ainda nao ha receitas cadastradas no sistema. Pressione qualquer tecla para retornar ao menu administrativo.\n";
        system("pause");
        menuAdmin();
    }
}

