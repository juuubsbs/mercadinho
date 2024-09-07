#include <iostream>

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

struct Produto{
    std:: string nome;
    float quantidade;
    float valor;

};

int RetornoInteiro(std:: string x, int limite){
    int inteiro = x[0] - 48;

    if((x[1] > 0 || x[1] < 0 ) && inteiro > limite){
        std:: cout << "Opção inválida, tente novamente" << std:: endl;
        return inteiro = limite + 1; // para cair em default
    }
     else return inteiro;
}

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

        //código para correção do input de string -> int, iniciou como string para não quebrar
        int numero = numeroMenu[0] - 48;
        if(numeroMenu[1] > 0 || numeroMenu[1] < 0){
            std:: cout << "Opção inválida, tente novamente" << std:: endl;
            return main();
        }

        //switch para a posição escolhida
        switch (numero){
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