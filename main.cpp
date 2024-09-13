#include <iostream>
#include <time.h> //nao usei ainda -> talvez dê pra calendários :)
#include <unistd.h> // biblioteca para sleep, é unix-like mas vem com o gcc
#include <chrono>
#include <fstream>
#include <sstream> // biblioteca que tá convertento de string pra float

// As funções estão em ordem de execução

// limpar a tela do terminal em qualquer sistema
    #ifdef _WIN32 // caso windows
    #define clear "cls"
    #else // caso não
    #define clear "clear";
    #endif


//----------------- início do programa -----------------------------------------------------------

int RetornoInteiroSwitch(std:: string x, int limite);
void Cadastro();
void Carrinho();
void Pagamentos();


// Caracteriza os produtos
struct Produto{
    std:: string nome;
    float quantidade;
    float valor;
};

//função de abrir arquivinhos
void CriarArquivos(){

    std:: ofstream temp("temp.txt", std:: ios_base:: app);
    std:: ofstream carrinho("carrinho.txt", std:: ios_base:: app);
    std:: ofstream produtos("produtos.txt", std:: ios_base:: app); 

    temp.close();
    carrinho.close();
    produtos.close();
}

//escreve as informações enviadas por Cadastro()
void Escritor(std:: string nomeProduto, float quantidadeProduto, float valorProduto){

    std:: ofstream escritor;
    escritor.open ("produtos.txt", std::ios::app);//app é para append mode, onde ele começa a escrever do fim do arquivo

    if(quantidadeProduto != 0){
        escritor << nomeProduto << " ";
        escritor << quantidadeProduto << " ";
        escritor << valorProduto << " \n";
    }
    else std:: cout << "Erro! O produto possui 0 quantidades, logo, não foi salvo em 'pagamentos.txt'";
    sleep(2);

    escritor.close();
}

//lê as informações já presentes no arquivo
bool Leitor(std:: string nome){

    std:: string nomeProduto;

    std:: ifstream leitor;
    leitor.open ("produtos.txt");

    while(leitor.eof() == false){

        leitor >> nomeProduto;

        if(nomeProduto == nome){
            return true;
        }
    }

    leitor.close();
    return false;
}

void Apagador(std:: string nomeProduto){

    std:: ifstream leitor;
    std:: ofstream escritor;
    std:: string produto;
    float quantidade;
    float valor;

    leitor.open("produtos.txt");
    escritor.open("temp.txt");

    while(leitor >> produto && leitor >> quantidade && leitor >> valor){
        if(nomeProduto != produto && quantidade != 0){
            escritor << produto    << " ";
            escritor << quantidade << " ";
            escritor << valor << std::endl;
        }
    }

    leitor.close();
    escritor.close();
    std:: remove ("produtos.txt");
    std:: rename ("temp.txt", "produtos.txt");

    CriarArquivos();
}

// função para printar o menu inicial na tela do usuário
void MostreMenu(){
    system(clear);

    std:: cout << "Bem-Vindo ao Mercadinho!\n" << std:: endl;

    std:: cout << "......1- Cadastro/Consulta......" << std:: endl;
    std:: cout << "......2- Carrinho..............." << std:: endl;
    std:: cout << "......3- Pagamentos............." << std:: endl;
    std:: cout << "......4- Sobre.................." << std:: endl;
    std:: cout << "......5- Sair..................." << std:: endl;


    std:: cout << "Digite a opção desejada: ";
}

bool JaCadastrado (std:: string nomeProduto){

    std:: string resposta;

    if (Leitor(nomeProduto) == true){

        return true;
    }

    return false;
}

// função de leitor de quantidade e escritor no arquivo carrinho.txt
void LeitorQuantidade(std:: string nomeProduto, float quantidadeProduto){

        std::ofstream carrinho("carrinho.txt", std:: ios_base:: app);
        std::fstream produtos("produtos.txt");

        std:: string produto;
        float quantidade;
        float valor;
        int i = 0;
        
        while( produtos >> produto && produtos >> quantidade && produtos >> valor){

            if( produto == nomeProduto && i == 0){
                if(quantidadeProduto == 0){
                    std:: cout << "A quantidade digitada foi nula! Digite novamente...";
                    sleep(1);
                    Carrinho();
                }
                else if (quantidade >= quantidadeProduto){
                    carrinho << produto << " ";
                    carrinho << quantidadeProduto << " ";
                    carrinho << (valor*quantidadeProduto) << std:: endl;
                    
                    produtos.close();
                    Apagador(nomeProduto);
                    Escritor(nomeProduto, (quantidade - quantidadeProduto), valor);
                    i++;
                }
                else{
                    std:: string resposta;
                    std:: cout << "A quantidade digitada não é válida! " << std:: endl; 
                    std:: cout << "Gostaria de cadastrar uma nova quantidade? sim(s) não(): " << std:: endl;
                    std:: cin >> resposta;
                    if(resposta == "S" || resposta == "s" || resposta == "sim" || resposta == "Sim"){
                        std:: cout << "Você será redirecionado para a aba de cadastros...";
                        sleep(2);
                        Cadastro();
                    }
                    else {
                        std:: cout << "Carrinho não atualizado, voltando para o menu...";
                        sleep(2);
                    }
                }
            }
        }
        carrinho.close();
}

// função para converter uma string em int no switch-case do menu
int RetornoInteiroSwitch(std:: string x, int limite){
    int inteiro = x[0] - 48;

    if((x[1] - 48) >= 0 || inteiro > limite){
        system(clear);
        std:: cout << "Opção inválida, tente novamente" << std:: endl;
        sleep(1);
        return inteiro = limite + 1; // para cair em default
    }

    else return inteiro;
}

//função para converter a string quantidade em float
float RetornoFloatQuantidade(std :: string quantidadeProduto){
    float quantidade;
    std:: stringstream quantidadess;

    quantidadess << quantidadeProduto;
    quantidadess >> quantidade;

    return quantidade;
}

//função para converter a string valor em float
float RetornoFloatValor(std:: string valorProduto){
    float valor;
    std:: stringstream valorss;

    valorss << valorProduto;
    valorss >> valor;


    return valor;
}

// função para cadastrar os produtos
void Cadastro(){
    system(clear);

    Produto produto;
    std:: string resposta;

    std:: cout << "Olá, vamos cadastrar seu produto! \n";
    std:: cout << "Primeiro, você irá digitar o nome de seu produto,\ninformaremos a você caso ele já esteja cadastrado :)" << std:: endl;
    
    std:: cout << "Nome do produto: ";
    std:: cin >> produto.nome;

    if(JaCadastrado(produto.nome) == false){

        std:: string quantidade;
        std:: string valor;

        std:: cout << "Quantidade do produto: ";
        std:: cin >> quantidade;

        std:: cout << "Valor da unidade: R$ "; 
        std:: cin >> valor;

        produto.quantidade = RetornoFloatQuantidade(quantidade);
        produto.valor = RetornoFloatValor(valor);

        Escritor(produto.nome, produto.quantidade, produto.valor);
    }

    else{

        std:: cout << "O produto digitado já foi cadastrado!" << std:: endl;
        std:: cout << "Gostaria de alterá-lo? " << std:: endl;
        std:: cout << "sim(s) não(): ";
        std:: cin >> resposta;

        if(resposta == "s" || resposta == "S" || resposta == "sim" || resposta == "Sim" || resposta == "dã"){
            Apagador(produto.nome);

            std:: string quantidade;
            std:: string valor;
            
            std:: cout << "Quantidade do produto: ";
            std:: cin >> quantidade;

            std:: cout << "Valor da unidade: R$ "; 
            std:: cin >> valor;

            produto.quantidade = RetornoFloatQuantidade(quantidade);
            produto.valor = RetornoFloatValor(valor);

            Escritor(produto.nome, produto.quantidade, produto.valor);
        }
    }
} 



void Carrinho(){
    system(clear);

    Produto produto;

    std:: cout << "Olá, vamos adicionar produtos ao carrinho!" << std:: endl;
    std:: cout << "Digite o nome do produto e a quantidade para adicionarmos :)" << std:: endl;

    std:: cout << "Nome do produto: ";
    std:: cin >> produto.nome;

    if(JaCadastrado(produto.nome) == true){

        std:: string quantidade;

        std:: cout << "Quantidade do produto: ";
        std:: cin >> quantidade;

        produto.quantidade = RetornoFloatQuantidade(quantidade);

        LeitorQuantidade(produto.nome, produto.quantidade);
        sleep(1);
    }

    else{
        std:: string resposta;
        std:: cout << "Produto não cadastrado!" << std:: endl;
        std:: cout << "Gostaria de ser redirecionado para a página de cadastro? " << std:: endl;
        std:: cout << "sim(s) nao(): ";
        std:: cin >> resposta;
        if(resposta == "s" || resposta == "S" || resposta == "sim" || resposta == "Sim" || resposta == "dã"){
            std:: cout << "Redirecionando...";
            sleep(1);
            Cadastro();
        }
    }

}

//função para printar a tela de pagamentos e mostrar as condições e as datas
void Pagamentos(){
    system(clear);

    std:: ifstream carrinho;
    std:: string produto;
    float quantidade = 0;
    float valor = 0;
    float valorTotal = 0;

    std:: string formaPagamento;

    carrinho.open("carrinho.txt");

    std:: cout << "Bem-Vindo a tela de pagamentos! Aqui está o que você salvou no carrinho até agora:  " << std:: endl << std:: endl;

    while( carrinho >> produto && carrinho >> quantidade && carrinho >> valor){
        std:: cout << "Nome do Produto: " << produto      << std:: endl;
        std:: cout << "Quantidade: " << quantidade        << std:: endl;
        std:: cout << "Valor Total: R$ " << valor << std:: endl << std:: endl;
        valorTotal+= valor;
    }

    std:: cout << "Total da compra: R$" << valorTotal << std:: endl; 

    std:: cout << "Escolha a forma de pagamento... " << std:: endl;
    std:: cout << "...1- A vista (5% de desconto)................" << std:: endl;
    std:: cout << "...2- Parcelado em até 3x sem juros..........." << std:: endl;
    std:: cout << "...3- Parcelado em até 12x com 10% de juros..." << std:: endl << std:: endl;
    std:: cout << "Digite aqui: ";

    std:: cin >> formaPagamento;

    //para setar a saída correta da data do sistema
    auto now = std::chrono::system_clock::now();
    std::time_t hora_hoje = std::chrono::system_clock::to_time_t(now);
    std::tm* tm_ptr = std::localtime(&hora_hoje);

    std:: string sair;
    switch (RetornoInteiroSwitch(formaPagamento, 3)){

        case 1:
            std:: cout << "O pagamento será realizado hoje, dia: "
                       << (tm_ptr->tm_mday) << "/"
                       << (tm_ptr->tm_mon + 1) << "/"
                       << (tm_ptr->tm_year + 1900) << std::endl;
            std:: cout << "O valor a ser pago é dê: " << valorTotal - (valorTotal*0.05) << std:: endl;
            std:: cout << "Digite um caractere e Enter para voltar ao menu...";
            std:: cin >> sair;
            break;

        case 2: 
            std:: cout << "O pagamento será realizados nos dias: " << std:: endl;
            for( int i = 0; i < 3; i++){
            std:: cout << (tm_ptr->tm_mday) << "/"
                       << (tm_ptr->tm_mon + 1 + i) << "/"
                       << (tm_ptr->tm_year + 1900 ) << std::endl;
            }

            std:: cout << "O valor a ser pago por parcela é dê: " << valorTotal/3 << std:: endl;
            std:: cout << "Digite um caractere e Enter para voltar ao menu...";
            std:: cin >> sair;
            break;

        case 3:
            std:: cout << "O pagamento será realizado nos dias: " << std:: endl;
            for( int i = 0; i < 12; i++){
            std:: cout << (tm_ptr->tm_mday) << "/"
                       << (tm_ptr->tm_mon + 1 + i) << "/"
                       << (tm_ptr->tm_year + 1900) << std::endl;
            }
            std:: cout << "O valor a ser pago por parcela é dê: " << (valorTotal/12) + (valorTotal*0.1) << std:: endl;
            std:: cout << "Digite um caractere e Enter para voltar ao menu...";
            std:: cin >> sair;
            break;

        default:
            system(clear);
            std:: cout << "A opção digitada não é válida!";
            sleep(1);

            Pagamentos();


    }

    carrinho.close();
    
}

//Função para contar um pouquinho sobre o trabalho
void Sobre(){
    system(clear);

    std:: string sair;
    std:: cout << "Oiê! Este trabalho foi feito pela aluna Juliana do 2° Período de Ciência da Computação.\n";
    std:: cout << "Ele utiliza das bibliotecas <time.h> para lidar com datas e horários e <unistd.h> para a função ";
    std:: cout << "de sleep(). Para o código de cores temos o padrão ANSI." << std:: endl;
    std:: cout << "Digite qualquer tecla e pressione Enter para voltar ao menu.";
    std:: cin >> sair;
}

//MAIN
int main(){
    setlocale(LC_ALL, "pt_BR.UTF-8");

    CriarArquivos();

    // bool para controlar a duração do loop
    bool rodando = true;

    do{

        MostreMenu(); // chamada da função do menu
        std:: string numeroMenu;
        std:: cin >> numeroMenu;

        //switch para a posição escolhida
        switch (RetornoInteiroSwitch(numeroMenu, 5)){
        case 1 :
            Cadastro();
            break;
        case 2 :
            Carrinho();
            break;
        case 3 :
            Pagamentos();
            break;
        case 4 : 
            Sobre();
            break;
        case 5 :
            std:: cout << "Saindo...";
            sleep(1);
            system(clear);
            rodando = false;
            break;
        default:
            std:: cout << "Opção inválida, tente novamente";
            return main();
        }
    }
    while(rodando == true);

    return 0;
}