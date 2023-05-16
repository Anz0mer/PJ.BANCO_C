#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Exibir menu.
void menu() {
    printf("Digite o número da ação solicitada:\n");
    printf("1 - Novo Cliente\n");
    printf("2 - Apagar Cliente\n");
    printf("3 - Débito\n");
    printf("4 - Depósito\n");
    printf("5 - Extrato\n");
    printf("6 - Transferência entre contas\n");
    printf("7 - Conversão em Milhas\n");
    printf("0 - Sair\n");
    printf("\n");
}

// Leitura da escolha do menu.
int escolhaMenu(){
    int x;
    printf("Digite sua escolha: ");
    scanf("%d", &x);
    return x;
}

// Função que adicona um novo cliente.

// Função que apaga um cliente.

// Função que realiza o débito.

// Função que realiza o depósito.

// Função que mostra o extrato.

// Função que realiza as tranferências.

// Função que realiza a conversão.

// Execução do menu.
int main (){
    int escolha;

    do {
        menu();
        escolha = escolhaMenu();

        // Executar menu com base na escolha do usuário.
        switch (escolha){
            case 1:
                printf("Opção escolhida: Novo Cliente!\n");
                break;

            case 2:
                printf("Opção escolhida: Apaga Cliente! \n");
                break;

            case 3:
                printf("Opção escolhida: Débito!\n");
                break;

            case 4:
                printf("Opção escolhida: Depósito!\n");
                break;

            case 5:
                printf("Opção escolhida: Extrato!\n");
                break;

            case 6:
                printf("Opção escolhida: Transferência entre contas!\n");
                break;

            case 7:
                printf("Opção escolhida: Conversão entre milhas!\n");
                break;

            case 0:
                printf("Opção escolhida: Sair!\n");
                break;

            // Se o usuário escolher uma opção inválida, ou seja, um valor diferente de 0 a 7, será acionado a mensagem do printf.
            default: 
                printf("Opção Inválida! Por favor, escolha novamente.\n");
                break;
        }
        
        printf("\n");
    } while (escolha != 0);

    return 0;
}
