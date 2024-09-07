#include <iostream>
#include <time.h> //nao usei ainda
#include <unistd.h> // biblioteca para sleep, é unix-like mas vem com gcc

// limpar a tela do terminal
    #ifdef _WIN32 // caso windows
    #define clear "cls"
    #else // caso não
    #define clear "clear";
    #endif

// função para printar o menu inicial na tela do usuário
void MostreMenu(){
    system(clear);

    std:: cout << "......1- Cadastro......" << std:: endl;
    std:: cout << "......2- Venda........." << std:: endl;
    std:: cout << "......3- Pagamentos...." << std:: endl;
    std:: cout << "......4- Sair.........." << std:: endl;

}

// função para converter uma string
int RetornoInteiro(std:: string x, int limite){
    int inteiro = x[0] - 48;

    if((x[1] - 48) >= 0 || inteiro > limite){
        system(clear);
        std:: cout << "Opção inválida, tente novamente" << std:: endl;
        sleep(1);
        return inteiro = limite + 1; // para cair em default
    }
     else return inteiro;
}

struct Produto{
    std:: string nome;
    float quantidade;
    float valor;

};

void Cadastro(){
    system(clear);

    Produto produto;

    std:: cout << "Olá, vamos cadastrar seu produto! \n";
    std:: cout << "Primeiro, você irá digitar o nome de seu produto, informaremos a você caso ele já esteja cadastrado";
    std:: cin >> produto.nome;

    //if (JaCadastrado(produto.nome) == true)

}

bool JaCadastrado (){

    

    return false;
}



int main(){

    setlocale(LC_ALL, "pt_BR.UTF-8");

    // bool para controlar a duração do loop
    bool rodando = true;

    do{

        MostreMenu(); // chamada da função do menu
        std:: string numeroMenu;
        std:: cin >> numeroMenu;

        //switch para a posição escolhida
        switch (RetornoInteiro(numeroMenu, 4)){
        case 1 :
            Cadastro();
            break;
        case 2 :
            //venda();
            break;
        case 3 :
            //pagamentos();
            break;
        case 4 : 
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