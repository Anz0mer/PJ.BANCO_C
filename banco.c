//Blibliotas que serão utilizadas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura para armazenar os dados do cliente
typedef struct {
    char nome[100];
    int cpf;
    char tipoConta[10];
    float saldo;
    int senha;
    int milhas;
} Cliente;

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
    FILE *conta = fopen("clientes.txt", "a");
    if (conta == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    Cliente cliente;
    printf("Nome: ");
    scanf("%s", cliente.nome);
    printf("CPF: ");
    scanf("%d", &cliente.cpf);
    printf("Tipo de conta (comum ou plus): ");
    scanf("%s", cliente.tipoConta);
    printf("Valor inicial da conta: R$");
    scanf("%f", &cliente.saldo);
    printf("Senha do usuário: ");
    scanf("%d", &cliente.senha);
    cliente.milhas = 0;

    fprintf(conta, "%s %d %s %.2f %d %d\n", cliente.nome, cliente.cpf, cliente.tipoConta, cliente.saldo, cliente.senha, cliente.milhas);
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

    float tarifa;

    FILE *f = fopen("clientes.txt", "r+");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Cliente cliente;
    int encontrado = 0;
    while (fscanf(f, "%s %d %s %f %d %d", cliente.nome, &cliente.cpf, cliente.tipoConta, &cliente.saldo, &cliente.senha, &cliente.milhas) != EOF) {
        if (cliente.cpf == cpf && cliente.senha == senha) {
            encontrado = 1;
            if (strcmp(cliente.tipoConta, "comum") == 0) {
                tarifa = valor * 0.05;
                if (cliente.saldo >= -1000) {
                    cliente.saldo -= valor + tarifa;
                    printf("Novo saldo: R$%.2f\n", cliente.saldo);
                } else {
                    printf("Saldo insuficiente!\n");
                    fclose(f);
                    return;
                }
            } else if (strcmp(cliente.tipoConta, "plus") == 0) {
                tarifa = valor * 0.03;
                if (cliente.saldo >= -5000) {
                    cliente.saldo -= valor + tarifa;
                    printf("Novo saldo: R$%.2f\n", cliente.saldo);
                } else {
                    printf("Saldo insuficiente!\n");
                    fclose(f);
                    return;
                }
            }

            fseek(f, -sizeof(Cliente), SEEK_CUR);
            fprintf(f, "%s %d %s %.2f %d %d\n", cliente.nome, cliente.cpf, cliente.tipoConta, cliente.saldo, cliente.senha, cliente.milhas);
            break;
        }
    }

    fclose(f);

    if (encontrado) {
        printf("Débito realizado!\n");
    } else {
        printf("Cliente não encontrado!\n");
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
