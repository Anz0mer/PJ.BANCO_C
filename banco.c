//Blibliotas que serão utilizadas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Exibir menu
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

//Leitura da escolha do menu.
int escolhaMenu(){
    int x;
    printf("Digite sua escolha: ");
    scanf("%d", &x);
    return x;
}

//Função que adicona um novo cliente.
void novocliente() {
    //Armazén dos dados do cliente.
    FILE *conta = fopen("clientes.txt", "a");

    char nome[100];
    int cpf;
    char conta1 [10];
    float valor;
    int senha;
    int milhas = 0;

    //Dados do novo cliente.
    printf("Nome: ");
    scanf("%s", nome);
    printf("CPF: ");
    scanf("%s", &cpf);
    printf("Tipo de conta (comum ou plus): ");
    scanf("%s", conta1);
    printf("Valor incial da conta: R$");
    scanf("%s", &valor);
    printf("Senha do usuário: ");
    scanf("%s", &senha);

    //Armazenar os dados no arquivo.
    fprintf(conta, "%s %d %s %.2f %d %d\n", nome, cpf, conta1, valor, senha, milhas);
    fclose(conta);

    printf("\n");
    printf("Cliente cadastrado com sucesso!!\n");
}

//Função que apaga um cliente.
void apagacliente(){
    int cpf;
    int senha;
    printf("CPF: ");
    scanf("%d", &cpf);
    printf("Senha: ");
    scanf("%d", &senha);

    FILE *f = fopen("clientes.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (f == NULL || temp == NULL){
        printf("Erro ao abrir o arquivo!!\n");
        return;
    }

    char linha[100];
    while (fgets(linha, sizeof(linha), f)) {
        int cpf_arquivo;
        sscanf(linha, "%*s %d", &cpf_arquivo);
        //Verifica se o CPF é diferente do CPF fornecido
        if(cpf_arquivo != cpf) {
            //Escreve a linha atual no arquivo temporário
            fputs(linha, temp);
        }
    }

    fclose(f);
    fclose(temp);
    
    //Remove o arquivo "clientes.txt"
    if (remove("clientes.txt") != 0) {
        printf("Erro ao apagar o arquivo!\n");
        return;
    }

    printf("Conta Apagada!!\n");
}

//Função que realiza o débito.
void debito() {
    int cpf, senha;
    float valor;
    printf("CPF: ");
    scanf("%d", &cpf);
    printf("Senha: ");
    scanf("%d", &senha);
    printf("Qual valor deseja debitar?: ");
    scanf("%f", &valor);

    //Calcula a tarifa 1 (5% do valor a ser debitado)
    float tarifa1 = valor * 0.05;

    //Calcula a tarifa 2 (3% do valor a ser debitado)
    float tarifa2 = valor * 0.03;

    FILE *f = fopen("clientes.txt", "r+");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
}
//Função que realiza o depósito.

//Função que mostra o extrato.

//Função que realiza as tranferências.

//Função que realiza a conversão.

//Execução do menu.
int main (){
    int escolha;

    do {
        menu();
        escolha = escolhaMenu();

        //Executar menu com base na escolha do usuário.
        switch (escolha){
            case 1:
                printf("Opção escolhida: Novo Cliente!\n");
                printf("\n");
                novocliente();
                break;

            case 2:
                printf("Opção escolhida: Apaga Cliente! \n");
                printf("\n");
                apagacliente();
                break;

            case 3:
                printf("Opção escolhida: Débito!\n");
                printf("\n");
                debito();
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
