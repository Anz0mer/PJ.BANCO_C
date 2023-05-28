// Bibliotecas que serão utilizadas.
#include <stdio.h>
#include <string.h>
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
int escolhaMenu() {
  int escolha;
  printf("Digite sua escolha: ");
  scanf("%d", &escolha);
  return escolha;
}

// Função que adiciona um novo cliente.
void novocliente() {
  FILE *conta = fopen("clientes.txt", "a");
  if (conta == NULL) {
    printf("Erro ao abrir o arquivo!\n");
    return;
  }

  char nome[100];
  int cpf;
  char tipoConta[10];
  float saldo;
  int senha;
  int milhas;

  printf("Nome: ");
  scanf("%s", nome);
  printf("CPF: ");
  scanf("%d", &cpf);
  printf("Tipo de conta (comum ou plus): ");
  scanf("%s", tipoConta);
  printf("Valor inicial da conta: R$");
  scanf("%f", &saldo);
  printf("Senha do usuário: ");
  scanf("%d", &senha);
  milhas = 0;

  fprintf(conta, "%s %d %s %.2f %d %d\n", nome, cpf, tipoConta, saldo, senha,
          milhas);
  fclose(conta);

  printf("\n");
  printf("Cliente cadastrado com sucesso!!\n");
}

// Função que apaga um cliente.
void apagacliente() {
  int cpf;
  int senha;
  printf("CPF: ");
  scanf("%d", &cpf);
  printf("Senha: ");
  scanf("%d", &senha);

  FILE *f = fopen("clientes.txt", "r");
  FILE *temp = fopen("temp.txt", "w");

  if (f == NULL || temp == NULL) {
    printf("Erro ao abrir o arquivo!!\n");
    return;
  }

  char linha[100];
  // Variável de controle para verificar se o CPF foi encontrado
  int cpfEncontrado = 0;

  while (fgets(linha, sizeof(linha), f)) {
    int cpf_arquivo;
    sscanf(linha, "%*s %d", &cpf_arquivo);

    // Verifica se o CPF é igual ao CPF fornecido e se a senha está correta.
    if (cpf_arquivo == cpf) {
      cpfEncontrado = 1;
      // Verifica se a senha está correta
      int senha_arquivo;
      sscanf(linha, "%*s %*d %*s %*f %d", &senha_arquivo);
      if (senha_arquivo != senha) {
        printf("Erro!\n");
        fclose(f);
        fclose(temp);
        remove("temp.txt");
        return;
      }
    } else {
      // Escreve a linha atual no arquivo temporário.
      fputs(linha, temp);
    }
  }

  fclose(f);
  fclose(temp);

  if (!cpfEncontrado) {
    printf("CPF não encontrado!\n");
    remove("temp.txt");
    return;
  }

  if (remove("clientes.txt") != 0) {
    printf("Erro ao apagar o arquivo!\n");
    return;
  }

  if (rename("temp.txt", "clientes.txt") != 0) {
    printf("Erro ao renomear o arquivo!\n");
    return;
  }

  printf("Conta Apagada!!\n");
}

// Função que realiza o débito.
void debito() {
  int cpf;
  int senha;
  float valor;
  printf("CPF: ");
  scanf("%d", &cpf);
  printf("Senha: ");
  scanf("%d", &senha);
  printf("Qual valor deseja debitar? R$ ");
  scanf("%f", &valor);

  FILE *f = fopen("clientes.txt", "r+");
  if (f == NULL) {
    printf("Arquivo não aberto! Erro!\n");
    return;
  }

  FILE *temp = fopen("temp.txt", "w");
  if (temp == NULL) {
    printf("Arquivo temporário não criado! Erro!\n");
    fclose(f);
    return;
  }

  int cpf_arquivo;
  char nome[100];
  char tipoConta[10];
  float saldo;
  int senha_arquivo;
  int milhas;

  int encontrou = 0;

  while (fscanf(f, "%s %d %s %f %d %d", nome, &cpf_arquivo, tipoConta, &saldo,
                &senha_arquivo, &milhas) == 6) {
    if (cpf_arquivo == cpf && senha_arquivo == senha) {
      encontrou = 1;
      if (valor > saldo) {
        printf("Saldo insuficiente para realizar o débito!\n");
      } else {
        saldo -= valor;
        fprintf(temp, "%s %d %s %.2f %d %d\n", nome, cpf_arquivo, tipoConta,
                saldo, senha_arquivo, milhas);
        printf("Débito realizado!\n");
      }
    } else {
      fprintf(temp, "%s %d %s %.2f %d %d\n", nome, cpf_arquivo, tipoConta,
              saldo, senha_arquivo, milhas);
    }
  }

  fclose(f);
  fclose(temp);

  if (encontrou) {
    if (remove("clientes.txt") != 0) {
      printf("Não foi possível apagar o arquivo original!\n");
      return;
    }

    if (rename("temp.txt", "clientes.txt") != 0) {
      printf("Não foi possível renomear o arquivo temporário!\n");
      return;
    }
  } else {
    remove("temp.txt");
    printf("CPF e/ou senha incorretos!\n");
  }
}

// Função que realiza o depósito.
void deposito() {
  int cpf3;
  int senha;
  float valor3;
  float saldo = 0;
  char linha[100];
  char cpf_str[12];
  FILE *clientes;
  FILE *extrato;
  time_t agora;
  struct tm *data_hora;
  char data_hora_str[20];
  int encontrado = 0;

  printf("CPF: ");
  scanf("%d", &cpf3);
  printf("Qual o valor que deseja depositar? R$ ");
  scanf("%f", &valor3);

  snprintf(cpf_str, sizeof(cpf_str), "%d", cpf3);

  clientes = fopen("clientes.txt", "r+");
  if (clientes == NULL) {
    printf("Erro ao abrir o arquivo clientes.txt\n");
    return;
  }

  while (fgets(linha, sizeof(linha), clientes) != NULL) {
    int cpf_arquivo;
    char nome[100];
    char tipoConta[10];
    float saldo_arquivo;
    int senha_arquivo;
    int milhas;

    sscanf(linha, "%s %d %s %f %d %d", nome, &cpf_arquivo, tipoConta,
           &saldo_arquivo, &senha_arquivo, &milhas);

    if (cpf_arquivo == cpf3) {
      printf("Senha: ");
      scanf("%d", &senha);
      if (senha != senha_arquivo) {
        printf("Erro!\n");
        fclose(clientes);
        return;
      }

      saldo_arquivo += valor3;
      saldo = saldo_arquivo;

      fseek(clientes, -(strlen(linha)), SEEK_CUR);
      fprintf(clientes, "%s %d %s %.2f %d %d\n", nome, cpf_arquivo, tipoConta,
              saldo_arquivo, senha_arquivo, milhas);

      agora = time(NULL);
      data_hora = localtime(&agora);
      strftime(data_hora_str, sizeof(data_hora_str), "%d/%m/%Y %H:%M:%S",
               data_hora);

      extrato = fopen("extrato.txt", "a");
      if (extrato == NULL) {
        printf("Erro ao abrir o arquivo extrato.txt\n");
        fclose(clientes);
        return;
      }

      fprintf(extrato, "%d Data: %s %.2f Tarifa: 0 Saldo: %.2f\n", cpf3,
              data_hora_str, valor3, saldo);

      fclose(extrato);
      encontrado = 1;
      break;
    }
  }

  fclose(clientes);

  if (!encontrado) {
    printf("CPF não encontrado!\n");
    return;
  }

  printf("Depósito realizado!\n");
}

// Função que mostra o extrato.

// Função que realiza as transferências.

// Função que realiza a conversão de milhas.

// Execução do menu.
int main() {
  int escolha;

  do {
    menu();
    escolha = escolhaMenu();

    // Executar o menu com base na escolha do usuário
    switch (escolha) {
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
      printf("\n");
      deposito();
      break;

    case 5:
      printf("Opção escolhida: Extrato!\n");
      printf("\n");
      //extrato();
      break;

    case 6:
      printf("Opção escolhida: Transferência entre contas!\n");
      //tranferencia();
      break;

    case 7:
      printf("Opção escolhida: Conversão entre milhas!\n");
      //milhas();
      printf("\n");
      break;

    case 0:
      printf("Opção escolhida: Sair!\n");
      printf("\n");
      break;

    // Se o usuário escolher uma opção inválida, ou seja, um valor diferente de
    // 0 a 7, será acionado a mensagem do printf.
    default:
      printf("Opção Inválida! Por favor, escolha novamente.\n");
      printf("\n");
      break;
    }

    printf("\n");
  } while (escolha != 0);

  return 0;
}
