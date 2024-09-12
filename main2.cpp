#include <iostream>
#include <time.h> //nao usei ainda -> talvez dê pra calendários :)
#include <unistd.h> // biblioteca para sleep, é unix-like mas vem com o gcc
#include <fstream>

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

// Caracteriza os produtos
struct Produto{
    std:: string nome;
    float quantidade;
    float valor;
};

//função de abrir arquivinhos
void CriarArquivos(){
    std:: ofstream temp("temp.txt");
    std:: fstream carrinho("carrinho.txt");
    temp.close();
    carrinho.close();
}

//escreve as informações enviadas por Cadastro()
void Escritor(std:: string nomeProduto, float quantidadeProduto, float valorProduto){

    std:: ofstream escritor;
    escritor.open("produtos.txt", std::ios::app);//app é para append mode, onde ele começa a escrever do fim do arquivo

    escritor << nomeProduto << " ";
    escritor << quantidadeProduto << " ";
    escritor << valorProduto << " \n";

    escritor.close();
}

//lê as informações já presentes no arquivo
bool Leitor(std:: string nome){

    std:: string nomeProduto;

    std:: ifstream leitor;
    leitor.open("produtos.txt");

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
    std:: string quantidade;
    std:: string valor;

    leitor.open("produtos.txt");
    escritor.open("temp.txt");

    while(leitor >> produto && leitor >> quantidade && leitor >> valor){
        if(nomeProduto != produto){
            escritor << produto << " ";
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


bool JaCadastrado (std:: string nomeProduto){

    std:: string resposta;

    if (Leitor(nomeProduto) == true){
        std:: cout << "O produto informado já foi cadastrado!" << std:: endl;
        return true;

    }

    return false;
}

// função de leitor de quantidade
void LeitorQuantidade( std:: string nomeProduto, float quantidadeProduto){

        std::ofstream carrinho("carrinho.txt", std:: ios_base:: app);
        std::fstream produtos("produtos.txt");

        std:: string produto;
        float quantidade;
        float valor;
        int i = 0;
        
        while( produtos >> produto && produtos >> quantidade && produtos >> valor){

            if( produto == nomeProduto && i == 0){
                if (quantidade >= quantidadeProduto){
                    carrinho << produto << " ";
                    carrinho << quantidadeProduto << " ";
                    carrinho << (valor*quantidadeProduto) << std:: endl;
                    
                    produtos.close();
                    Apagador(nomeProduto);
                    Escritor(nomeProduto, (quantidade - quantidadeProduto), valor);
                    i++;
                }
                else {
                    std:: string resposta;
                    std:: cout << "A quantidade digitada não é válida! "; 
                    std:: cout << "Gostaria de cadastrar uma nova quantidade? sim(s) não(): " << std:: endl;
                    std:: cin >> resposta;
                    if(resposta == "S" || resposta == "s" || resposta == "sim" || resposta == "Sim"){
                        std:: cout << "Você será redirecionado para a aba de cadastros...";
                        sleep(2);
                        Cadastro();


                    }
                }

            }
        }
        carrinho.close();
}

//função para printar a tela de pagamentos e mostrar as condições e as datas
void Pagamentos(){
    system(clear);

    std:: ifstream carrinho;
    std:: string produto;
    float quantidade;
    float valor;
    float valorTotal;

    std:: string formaPagamento;

    carrinho.open("carrinho.txt");

    std:: cout << "Bem-Vindo a tela de pagamentos! Aqui está o que você salvou no carrinho até agora:  " << std:: endl << std:: endl;

    while( carrinho >> produto && carrinho >> quantidade && carrinho >> valor){
        std:: cout << "Nome do Produto: " << produto << std:: endl;
        std:: cout << "Quantidade: " << quantidade << std:: endl;
        std:: cout << "Valor: R$ " << valor << std:: endl << std:: endl;
        valorTotal+= valor;
    }

    std:: cout << "Total da compra: R$" << valorTotal; 

    std:: cin >> formaPagamento;

    carrinho.close();
    
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

// função para converter uma string em int nos switch-case
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

        std:: cout << "Quantidade do produto: ";
        std:: cin >> produto.quantidade;

        std:: cout << "Valor da unidade: R$ "; 
        std:: cin >> produto.valor;

        Escritor(produto.nome, produto.quantidade, produto.valor);
    }

    else{

        std:: cout << "Gostaria de alterá-lo? "
                   << "sim(s) não (n): ";
        std:: cin >> resposta;

        if(resposta == "s" || resposta == "S" || resposta == "sim" || resposta == "Sim" || resposta == "dã"){
            Apagador(produto.nome);
            
            std:: cout << "Quantidade do produto: ";
            std:: cin >> produto.quantidade;

            std:: cout << "Valor da unidade: R$ "; 
            std:: cin >> produto.valor;

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
        std:: cout << "Quantidade do produto: ";
        std:: cin >> produto.quantidade;

        LeitorQuantidade(produto.nome, produto.quantidade);
    }

    else{
        std:: cout << "Produto não cadastrado, você será redirecionado para a página de cadastro...";
        sleep(2);
        Cadastro();
    }
}


//MAIN
int main(){

    setlocale(LC_ALL, "pt_BR.UTF-8");

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
            //sobre();
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