# Projeto_Banco_C

Trabalho prático - Banco QuemPoupaTem
O novo banco QuemPoupaTem vai iniciar a sua operação em breve, mas não tem um sistema bancário estabelecido. Para desenvolver o sistema que controla os clientes, o banco decidiu contratar você.

O seu programa deve ser todo desenvolvido em C.

*Requisitos*

O banco trabalha com dois tipos de conta:
Comum:
Cobra taxa de 5% a cada débito realizado
Permite um saldo negativo de até (R$ 1.000,00)
Plus:
Cobra taxa de 3% a cada débito realizado
Permite um saldo negativo de até (R$ 5.000,00)
O sistema criado por você deve funcionar em loop infinito até que se deseje sair.

Um menu de opções deve ser sempre apresentado ao operador, contendo as seguintes operações:

Novo Cliente
Apaga Cliente
Débito
Depósito
Extrato
Transferência Entre Contas
‘Operação Livre’
Sair
Cada opção deve ser implementada como uma função!

*IMPORTANTE:* Não se esqueça de que o banco não pode perder as informações se o programa terminar, fechar, parar de funcionar, ou o computador desligar. Todos os dados devem ser salvos de maneira permanente utilizando arquivos binários.

Opção 1 - Usada para criar novos clientes.
Dados solicitados:

Nome
CPF
Tipo de conta (são dois: comum e plus)
Valor inicial da conta
Senha do usuário
Opção 2 - Apaga o cliente pelo CPF
Opção 3 - Serve para debitar um valor da conta do cliente
Dados solicitados:
CPF
Senha
Valor
O débito somente pode ser feito se o CPF e a senha estiverem corretos.

Opção 4 - Deposita um valor na conta do cliente
Dados solicitados:

CPF
Valor
Opção 5 - Extrato - exibe o histórico de todas as operações realizadas na conta, com datas e valores, incluindo as tarifas.
Dados solicitados:

CPF
Senha
O extrato só pode ser exibido se o CPF e senha estiverem corretos!

Opção 6 - Transferência - realiza a transferência de uma valor determinado de uma conta (Origem) para outra conta (Destino)
Dados solicitados:

CPF (Origem)
Senha (Origem)
CPF (Destino)
Valor
O transferência só pode ser realizada se o CPF e a senha da conta de origem estiverem corretos!

Opção 7 - Livre!
Crie você mesmo uma operação útil para o sistema bancário
