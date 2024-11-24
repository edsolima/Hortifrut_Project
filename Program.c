#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h> 
#include <strings.h> 

#define TAM_DEPOSITO 1000 /*DEFINE A CAPACIDADE DE ARMAZENAMENTO NO DEPÓSITO*/

typedef struct {
    char usuario[100];
    int senha;
}Usuario;

typedef struct {/*Produtos*/
    int id;// identificacão dos produtos ex: macã id 1
    char nome[50];/*nome do produto ex: macã*/
    float precoKg;/* preco do produto ex: 1,99*/
    int quantidade;/*Define a quantidade de produtos*/
    char tipoKouG;  // 'K' para kg, 'G' para granel
    int quantidade_vendida;//quantidade de itens vendidos
} Produto;/*Caminho do produto*/

Produto produtos[TAM_DEPOSITO];//Lista de Array de produtos declarada já com o seu tamanho especificado pela variável TAM_DEPOSITO
int total_produtos = 0;// O total de produtos se inicia em 0, á medida que vai adicionando vai aumentando

void funcaoLimpaTela(){
    system("cls");// Limpa a tela
}
void autenticacaoUsuario(){
    Usuario user;
    char user1[] = "admin";
    int senha = 123;
    printf("\nOla querido colaborador, para prosseguir:\n");
    do{
        printf("Digite o Usuario:\n");
        scanf("%s", user.usuario);
        printf("Digite a Senha:\n");
        scanf("%d", &user.senha);
        if (strcmp(user.usuario, user1)== 0 && user.senha == senha){
            funcaoLimpaTela();
            opcFuncionario();
        }else{
            funcaoLimpaTela();
            printf("Usuario ou senha incorretos, tente novamente!\n");
        }
    } while (strcmp(user.usuario, user1)!= 0 || user.senha != senha);
}
void gravarTransacao(Produto product){
    // Gravação da transação no arquivo
    FILE *arquivo = fopen("transacoes.csv", "a");  // Abre o arquivo em modo append
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de transacoes.\n");
        return;
    }

     // Obtém a data e a hora atuais
    time_t agora;
    time(&agora);
    struct tm *dataHoraLocal = localtime(&agora);

    // Formata a data e hora para o padrão especificado, abaixo está em "dia, mes, ano, hora, minutos e segundos"
    char dateFormat[80];
    strftime(dateFormat, sizeof(dateFormat), "%d-%m-%Y %H:%M:%S", dataHoraLocal);//strftime formata a data/ hora, formatado em dia, mes, ano, hora, minuto e segundos

    // Grava no arquivo CSV
    fprintf(arquivo, "Data/Hora: %s\n", dateFormat);
    fprintf(arquivo, "ID: %d\n", product.id);
    fprintf(arquivo, "Produto: %s\n", product.nome);
    fprintf(arquivo, "Preco por Kg: %.2f\n", product.precoKg);
    fprintf(arquivo, "Quantidade: %d\n\n", product.quantidade);

    fclose(arquivo);  // Fecha o arquivo
}
void gravarTransacaoVenda(Produto product, int quantidade) {
    FILE *arquivo = fopen("transacoes_venda.csv", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de transacoes de venda.\n");
        return;
    }
    time_t agora;
    time(&agora);
    struct tm *dataHoraLocal = localtime(&agora);
    char dateFormat[80];
    strftime(dateFormat, sizeof(dateFormat), "%d-%m-%Y %H:%M:%S", dataHoraLocal);
    fprintf(arquivo, "Data/Hora: %s\n", dateFormat);
    fprintf(arquivo, "ID: %d\n", product.id);
    fprintf(arquivo, "Produto: %s\n", product.nome);
    fprintf(arquivo, "Quantidade: %d\n", quantidade);
    fprintf(arquivo, "Preco por Kg: %.2f\n", product.precoKg);
    fprintf(arquivo, "Total da Venda: %.2f\n\n", product.quantidade_vendida * product.precoKg);
    fclose(arquivo);
}
void flv(){
    int op;  
    funcaoLimpaTela();   
    printf("\x1b[38;5;46m==================================================================\n");  // Verde vibrante
    printf("\x1b[38;5;82m                ** MENU F-L-V **     \n");  // Verde claro
    printf("\x1b[38;5;46m==================================================================\n");  // Verde vibrante
    printf("\n\x1b[38;5;226m1. Frutas\n");  // Amarelo
    printf("\x1b[38;5;123m2. Legumes\n");  // Verde oliva
    printf("\x1b[38;5;39m3. Verduras\n");  // Azul claro
    printf("\x1b[38;5;82m4. Encerrar Sessao\n");  // Verde claro 
    printf("\x1b[38;5;46m==================================================================\n");  // Verde vibrante
    printf("\nEscolha uma opcao: ");
    scanf("%d", &op);
    printf("\x1b[38;5;105mCarregando sua escolha...\n");  // Cor Laranja
    sleep(1);  // Pausa antes de processar a escolha do usuário

        switch (op) {
        case 1:
            funcaoLimpaTela();
            listarProdutosPorTipo(1);  // Listar frutas
            break;
        case 2:
            funcaoLimpaTela();
            listarProdutosPorTipo(2);  // Listar legumes
            break;
        case 3:
            funcaoLimpaTela();
            listarProdutosPorTipo(3);  // Listar verduras
            break;
        case 4:
            funcaoLimpaTela();
            printf("\x1b[38;5;82m...\n");
            break;
        default:
            printf("\x1b[38;5;196mOpcao invalida! Tente novamente.\n");  // Vermelho
            break;
        }
}
void escolhaFLV(){
    int flv;
    do{
        funcaoLimpaTela();
        printf("\x1b[38;5;46m==================================================================\n");  // Verde vibrante
        printf("\x1b[38;5;82m                O QUE DESEJA ADICIONAR?     \n");  // Verde claro
        printf("\x1b[38;5;46m==================================================================\n");  // Verde vibrante
        printf("\n\x1b[38;5;226m1. Frutas\n");  // Amarelo
        printf("\x1b[38;5;123m2. Legumes\n");  // Verde oliva
        printf("\x1b[38;5;39m3. Verduras\n");  // Azul claro
        printf("\x1b[38;5;82m4. Sair\n");  // Verde claro 
        printf("\x1b[38;5;46m==================================================================\n");  // Verde vibrante
        printf("\nEscolha uma opcao: ");
        scanf("%d", &flv);
        printf("\x1b[38;5;105mCarregando sua escolha...\n");  // Cor Laranja
        sleep(1);  // Pausa antes de processar a escolha do usuário
        switch (flv){
            case 1:
                funcaoLimpaTela();
                listarProdutosPorTipo(1);
                adicionarProduto();
                break;
            case 2:
                funcaoLimpaTela();
                listarProdutosPorTipo(2);
                adicionarProduto();
                break;
            case 3:
                funcaoLimpaTela();
                listarProdutosPorTipo(3);
                adicionarProduto();
                break;
            case 4:
                printf("...\n");
                break;
            default:
                printf("Opcao incorreta!..\n");
                break;
        }
    } while (flv != 4);
}
void adicionarNovoProduto() {
    if (total_produtos >= TAM_DEPOSITO) {
        printf("\nLimite de produtos alcancado!\n");
        printf("\nPressione Enter para continuar...");
        getchar();
        getchar();
        return;
    }

    Produto novo_produto;
    char nome_temp[50];
    
    // Limpa o buffer do teclado
    while (getchar() != '\n');

    printf("\n============ CADASTRO DE PRODUTO ============\n");
    
    // Atribui um ID ao novo produto
    novo_produto.id = total_produtos + 1;
    
    printf("\nDigite o nome do produto: ");
    fgets(nome_temp, sizeof(nome_temp), stdin);
    nome_temp[strcspn(nome_temp, "\n")] = 0; // Remove o \n do final

    // Verifica se o produto já existe
    for (int i = 0; i < total_produtos; i++) {
        if (strcasecmp(produtos[i].nome, nome_temp) == 0) {
            printf("\nProduto ja cadastrado no sistema!\n");
            printf("\nPressione Enter para continuar...");
            getchar();
            return;
        }
    }

    // Se chegou aqui, o produto não existe
    strcpy(novo_produto.nome, nome_temp);
    
    printf("Digite o preco por Kg do produto: R$");
    while (scanf("%f", &novo_produto.precoKg) != 1 || novo_produto.precoKg <= 0) {
        printf("Preco invalido! Digite um valor positivo: R$");
        while (getchar() != '\n');
    }

    printf("Digite a quantidade do produto: ");
    while (scanf("%d", &novo_produto.quantidade) != 1 || novo_produto.quantidade < 0) {
        printf("Quantidade invalida! Digite um valor positivo: ");
        while (getchar() != '\n');
    }

    while (getchar() != '\n');
    do {
        printf("Escolha o tipo ('K' para kg, 'G' para granel): ");
        scanf(" %c", &novo_produto.tipoKouG);
        novo_produto.tipoKouG = toupper(novo_produto.tipoKouG);
    } while (novo_produto.tipoKouG != 'K' && novo_produto.tipoKouG != 'G');

    // Inicializa outros campos
    novo_produto.quantidade_vendida = 0;

    // Adiciona o produto à lista de produtos
    produtos[total_produtos] = novo_produto;
    total_produtos++;

    printf("\nProduto cadastrado com sucesso!\n");
    printf("\nPressione Enter para continuar...");
    getchar();
    getchar();
    funcaoLimpaTela();
}

void adicionarProduto() {
    
    int idp, quantidade;
    if (total_produtos >= TAM_DEPOSITO) {
        printf("Numero maximo de produtos atingido. Nao e possivel adicionar mais produtos.\n");

    }
    printf("\n\nDigite o ID do produto que deseja adicionar: ");
    scanf("%d", &idp);
    for (int i = 0; i < total_produtos; i++){
        if (produtos[i].id == idp){
            printf("\nDigite a quantidade que deseja adicionar: ");
            scanf("%d", &quantidade);
            produtos[i].quantidade += quantidade ;
            printf("\n\nProduto adicionado com sucesso!\n\n.\n");
            printf("\nResultados da adicao:\n");
            for (int i = 0; i < total_produtos; i++) {
                if (produtos[i].id == idp) {// validação caso exista o produto com o id informado
                    printf("ID: %d | Nome: %s | Preco: %.2f | Quantidade: %d\n",
                    produtos[i].id, produtos[i].nome, produtos[i].precoKg, produtos[i].quantidade);
                    printf("\nPressione qualquer tecla para voltar ao menu...\n");
                    getchar();  // Função para aguardar  pressionar qualquer tecla
                    getchar();
                }
            }
        }  
    }
    
}
void produtosNoEstoque(){
        // Definindo os produtos pré-cadastrados em um array de structs
    Produto produtosPreCadastrados[45] = {
        // Frutas
        {1, "Banana", 5.0, 10}, 
        {2, "Abacaxi", 3.0, 14}, 
        {3, "Maca", 1.2, 6}, 
        {4, "Pera", 2.0, 12},
        {5, "Laranja", 3.5, 20}, 
        {6, "Melancia", 6.0, 8}, 
        {7, "Melao", 4.5, 10}, 
        {8, "Morango", 8.0, 15},
        {9, "Uva", 12.0, 10},
        {10, "Coco", 7.0, 5},
        {11, "Limao", 2.5, 11},
        {12, "Mamao", 3.0, 9},
        {13, "Acerola", 4.2, 13},
        {14, "Pessego", 5.0, 6},
        {15, "Caju", 3.8, 7},

        // Legumes
        {16, "Abobrinha", 2.5, 12}, 
        {17, "Cenoura", 2.0, 18}, 
        {18, "Beterraba", 3.0, 10},
        {19, "Pepino", 1.5, 9}, 
        {20, "Tomate", 4.0, 16}, 
        {21, "Pimentao", 5.5, 10},
        {22, "Brocolis", 6.5, 10},
        {23, "Alho", 10.0, 5},
        {24, "Batata", 2.5, 17},
        {25, "Cebola", 3.5, 12},
        {26, "Chuchu", 2.0, 14},
        {27, "Rabanete", 3.0, 8},
        {28, "Gengibre", 8.0, 4},
        {29, "Mandioca", 3.0, 15},
        {30, "Batata-doce", 2.8, 10},

        // Verduras
        {31, "Alface", 1.8, 13}, 
        {32, "Rucula", 3.0, 7},
        {33, "Abobora", 4.0, 15},
        {34, "Ervilha", 3.2, 12},
        {35, "Jilo", 3.8, 8},
        {36, "Quiabo", 4.5, 6},
        {37, "Espinafre", 2.7, 9},
        {38, "Couve", 3.3, 11},
        {39, "Agriao", 2.5, 5},
        {40, "Chicoria", 1.9, 6},
        {41, "Salsa", 2.0, 13},
        {42, "Manjericao", 3.2, 8},
        {43, "Acelga", 3.0, 10},
        {44, "Cebolinha", 2.3, 7},
        {45, "Salsao", 4.1, 5}

    };
    // Adicionar os produtos pré-cadastrados ao array global de produtos e gravar as transações
    for (int i = 0; i < 45; i++) {
        produtos[total_produtos++] = produtosPreCadastrados[i];   
    }
}
void listarProdutosPorTipo(int tipo) {
    int encontrou = 0;
    int inicioID, fimID;
    const char* categoriaNome;
    
    // Define o range de IDs e nome da categoria baseado no tipo
    switch(tipo) {
        case 1: // Frutas
            inicioID = 1;
            fimID = 15;
            categoriaNome = "FRUTAS";
            break;
        case 2: // Legumes
            inicioID = 16;
            fimID = 30;
            categoriaNome = "LEGUMES";
            break;
        case 3: // Verduras
            inicioID = 31;
            fimID = 45;
            categoriaNome = "VERDURAS";
            break;
        default:
            printf("Tipo invalido!\n");
            return;
    }

    // Cabeçalho
    printf("\x1b[38;5;82m========================================================\n");
    printf("                  LISTAGEM DE %s                     \n", categoriaNome);
    printf("========================================================\x1b[0m\n");
    
    // Cabeçalho da tabela
    printf("\x1b[38;5;226m%-5s %-20s %-10s %-10s\x1b[0m\n",
           "ID", "Nome", "Preco/Kg", "Estoque");
    printf("--------------------------------------------------------\n");

    // Lista os produtos
    for (int i = 0; i < total_produtos; i++) {
        if (produtos[i].id >= inicioID && produtos[i].id <= fimID) {
            encontrou = 1;
            
            // Define cor baseada no nível de estoque
            if (produtos[i].quantidade <= 5) {
                printf("\x1b[38;5;196m"); // Vermelho para estoque crítico
            } else if (produtos[i].quantidade <= 10) {
                printf("\x1b[38;5;208m"); // Laranja para estoque baixo
            } else {
                printf("\x1b[38;5;46m"); // Verde para estoque normal
            }

            // Imprime informações do produto
            printf("%-5d %-20s R$%-8.2f %-10d %c\n",
                   produtos[i].id,
                   produtos[i].nome,
                   produtos[i].precoKg,
                   produtos[i].quantidade,
                   produtos[i].tipoKouG);
            
            printf("\x1b[0m"); // Reset cor

        }
    }

    if (!encontrou) {
        printf("\x1b[38;5;196mNenhum produto encontrado nesta categoria.\x1b[0m\n");
        return;
    }
}
void listarProdutosDeposito(){
    int flv;
    do{
        funcaoLimpaTela();
        printf("\x1b[38;5;46m==================================================================\n");  // Verde vibrante
        printf("\x1b[38;5;82m               DEPOSITO FLV     \n");  // Verde claro
        printf("\x1b[38;5;46m==================================================================\n");  // Verde vibrante
        printf("\n\x1b[38;5;226m1. Frutas\n");  // Amarelo
        printf("\x1b[38;5;123m2. Legumes\n");  // Verde oliva
        printf("\x1b[38;5;39m3. Verduras\n");  // Azul claro
        printf("\x1b[38;5;82m4. Sair\n");  // Verde claro 
        printf("\x1b[38;5;46m==================================================================\n");  // Verde vibrante
        printf("\nEscolha uma opcao: ");
        scanf("%d", &flv);
        printf("\x1b[38;5;105mCarregando sua escolha...\n");  // Cor Laranja
        sleep(1);  // Pausa antes de processar a escolha do usuário
        switch (flv){
            case 1:
                funcaoLimpaTela();
                listarProdutosDepTipo(1);
                
                break;
            case 2:
                funcaoLimpaTela();
                listarProdutosDepTipo(2);
                
                break;
            case 3:
                funcaoLimpaTela();
                listarProdutosDepTipo(3);
                
                break;
            case 4:
                printf("...\n");
                break;
            default:
                printf("Opcao incorreta!..\n");
                break;
        }
    } while (flv != 4);
}
void listarProdutosDepTipo(int tipo) {
    int encontrou = 0;
    float valorTotalEstoque = 0;
    int quantidadeTotalItens = 0;
    int inicioID, fimID;
    const char* categoriaNome;
    
    // Define o range de IDs e nome da categoria baseado no tipo
    switch(tipo) {
        case 1: // Frutas
            inicioID = 1;
            fimID = 15;
            categoriaNome = "FRUTAS";
            break;
        case 2: // Legumes
            inicioID =16;
            fimID = 30;
            categoriaNome = "LEGUMES";
            break;
        case 3: // Verduras
            inicioID = 31;
            fimID = 45;
            categoriaNome = "VERDURAS";
            break;
        default:
            printf("Tipo invalido!\n");
            return;
    }

    // Cabeçalho
    printf("\x1b[38;5;82m========================================================\n");
    printf("                  LISTAGEM DE %s                     \n", categoriaNome);
    printf("========================================================\x1b[0m\n");
    
    // Cabeçalho da tabela
    printf("\x1b[38;5;226m%-5s %-20s %-10s %-10s %-8s\x1b[0m\n",
           "ID", "Nome", "Preco/Kg", "Estoque", "Tipo");
    printf("--------------------------------------------------------\n");

    // Lista os produtos
    for (int i = 0; i < total_produtos; i++) {
        if (produtos[i].id >= inicioID && produtos[i].id <= fimID) {
            encontrou = 1;
            
            // Define cor baseada no nível de estoque
            if (produtos[i].quantidade <= 5) {
                printf("\x1b[38;5;196m"); // Vermelho para estoque crítico
            } else if (produtos[i].quantidade <= 10) {
                printf("\x1b[38;5;208m"); // Laranja para estoque baixo
            } else {
                printf("\x1b[38;5;46m"); // Verde para estoque normal
            }

            // Imprime informações do produto
            printf("%-5d %-20s R$%-8.2f %-10d %c\n",
                   produtos[i].id,
                   produtos[i].nome,
                   produtos[i].precoKg,
                   produtos[i].quantidade,
                   produtos[i].tipoKouG);
            
            printf("\x1b[0m"); // Reset cor

            valorTotalEstoque += produtos[i].quantidade * produtos[i].precoKg;
            quantidadeTotalItens += produtos[i].quantidade;
        }
    }

    if (!encontrou) {
        printf("\x1b[38;5;196mNenhum produto encontrado nesta categoria.\x1b[0m\n");
        return;
    }

    // Rodapé com informações totais
    printf("--------------------------------------------------------\n");
    printf("\x1b[38;5;39mResumo da Categoria:\n");
    printf("Total de Itens em Estoque: %d\n", quantidadeTotalItens);
    printf("Valor Total em Estoque: R$ %.2f\x1b[0m\n", valorTotalEstoque);

    // Legenda
    printf("\n\x1b[38;5;246mLegenda:\n");
    printf("\x1b[38;5;196m\x1b[0m Estoque Critico (<= 5 unidades)\n");
    printf("\x1b[38;5;208m\x1b[0m Estoque Baixo (<= 10 unidades)\n");
    printf("\x1b[38;5;46m\x1b[0m Estoque Normal (> 10 unidades)\n");
    printf("K - Vendido por Quilo | G - Vendido por Granel\x1b[0m\n");

    // Opções pós-listagem
    printf("\n\x1b[38;5;105mOpcoes:\n");
    printf("1. Voltar ao menu anterior\n");
    printf("2. Atualizar estoque\n");
    printf("3. Ver detalhes de um produto\n");
    printf("Escolha uma opcao: \x1b[0m");

    int opcao;
    scanf("%d", &opcao);

    switch(opcao) {
        case 1:
            return;
        case 2:
            printf("Digite o ID do produto para atualizar: ");
            int idAtualizar;
            scanf("%d", &idAtualizar);
            atualizarEstoque(idAtualizar);
            break;
        case 3:
            printf("Digite o ID do produto para ver detalhes: ");
            int idDetalhes;
            scanf("%d", &idDetalhes);
            mostrarDetalhesProduto(idDetalhes);
            printf("\nPressione qualquer tecla para voltar ao menu...\n");
            getchar();  // Função para aguardar  pressionar qualquer tecla
            getchar();
            break;
        default:
            printf("\x1b[38;5;196mOpcao invalida!\x1b[0m\n");
    }
}
// Função auxiliar para atualizar estoque
void atualizarEstoque(int id) {
    for (int i = 0; i < total_produtos; i++) {
        if (produtos[i].id == id) {
            printf("Quantidade atual: %d\n", produtos[i].quantidade);
            printf("Digite a nova quantidade: ");
            scanf("%d", &produtos[i].quantidade);
            printf("\x1b[38;5;82mEstoque atualizado com sucesso!\x1b[0m\n");
            gravarTransacao(produtos[i]);
            return;
        }
    }
    printf("\x1b[38;5;196mProduto nao encontrado!\x1b[0m\n");
}

// Função auxiliar para mostrar detalhes do produto
void mostrarDetalhesProduto(int id) {
    for (int i = 0; i < total_produtos; i++) {
        if (produtos[i].id == id) {
            printf("\n\x1b[38;5;82m=== Detalhes do Produto ===\x1b[0m\n");
            printf("ID: %d\n", produtos[i].id);
            printf("Nome: %s\n", produtos[i].nome);
            printf("Preco por Kg: R$ %.2f\n", produtos[i].precoKg);
            printf("Quantidade em estoque: %d\n", produtos[i].quantidade);
            printf("Tipo de venda: %s\n", produtos[i].tipoKouG == 'K' ? "Quilo" : "Granel");
            printf("Valor total em estoque: R$ %.2f\n", produtos[i].quantidade * produtos[i].precoKg);
            return;
        }
    }
    printf("\x1b[38;5;196mProduto nao encontrado!\x1b[0m\n");
}
void pesquisarProduto() {
    int opcaoPesquisa, id;
    char stringPesquisa[50];
    int encontrou = 0; // verificação se encontrou algum produto
    
    while (1) {
        printf("\n=== Pesquisa de Produtos ===\n");
        printf("Pesquisar por:\n");
        printf("1. Nome do Produto\n");
        printf("2. ID do Produto\n");
        printf("3. Voltar ao menu anterior\n");
        printf("\nDigite sua escolha: ");
        
        // Validação da entrada
        if (scanf("%d", &opcaoPesquisa) != 1) {
            funcaoLimpaTela();
            printf("Erro: Digite apenas numeros!\n");
            while (getchar() != '\n'); // Limpa o buffer
            continue;
        }

        if (opcaoPesquisa >= 1 && opcaoPesquisa <= 3) {
            break;
        } else {
            funcaoLimpaTela();
            printf("Erro: Opcao invalida! Escolha entre 1 e 3.\n");
            while (getchar() != '\n');
        }
    }

    // Verifica se há produtos cadastrados
    if (total_produtos == 0) {
        printf("\nNao ha produtos cadastrados no sistema!\n");
        printf("Pressione ENTER para continuar...");

        getchar();
    }

    switch(opcaoPesquisa) {
        case 1: // Pesquisa por nome
            printf("Digite o nome do produto: ");
            while (getchar() != '\n'); // Limpa o buffer
            if (fgets(stringPesquisa, sizeof(stringPesquisa), stdin) != NULL) {
                // Remove o \n do final da string
                stringPesquisa[strcspn(stringPesquisa, "\n")] = 0;
                
                // Valida se o nome não está vazio
                if (strlen(stringPesquisa) == 0) {
                    printf("Erro: Nome nao pode estar vazio!\n");
                    break;
                }

                printf("\nResultados da pesquisa:\n");
                printf("----------------------------------------\n");
                
                for (int i = 0; i < total_produtos; i++) {
                    if (strstr(produtos[i].nome, stringPesquisa) != NULL) {
                        printf("ID: %d\nNome: %s\nPreco: R$ %.2f\nQuantidade: %d\n",
                               produtos[i].id, produtos[i].nome, 
                               produtos[i].precoKg, produtos[i].quantidade);
                        printf("----------------------------------------\n");
                        encontrou = 1;
                    }
                }
            }
            break;

        case 2: // Pesquisa por ID
            printf("Digite o ID do produto: ");
            while (getchar() != '\n'); // Limpa o buffer
            
            if (scanf("%d", &id) != 1 || id < 0) {
                printf("Erro: ID invalido! Digite um numero positivo.\n");
                break;
            }

            printf("\nResultados da pesquisa:\n");
            printf("----------------------------------------\n");
            
            for (int i = 0; i < total_produtos; i++) {
                if (produtos[i].id == id) {
                    printf("ID: %d\nNome: %s\nPreco: R$ %.2f\nQuantidade: %d\n",
                           produtos[i].id, produtos[i].nome, 
                           produtos[i].precoKg, produtos[i].quantidade);
                    printf("----------------------------------------\n");
                    encontrou = 1;
                    break; // Como ID é único, podemos sair do loop
                }
            }
            break;

        case 3: // Voltar ao menu anterior
            return;
    }

    if (!encontrou) {
        printf("\nNenhum produto encontrado!\n");
    }

    printf("\nPressione ENTER para continuar...");
    while (getchar() != '\n');
    getchar();
}
void atualizarProduto() {
    int id, opcao;
    char novoNome[50];
    float novoPreco;
    int novaQuantidade;
    int encontrado = 0; 

    printf("Digite o ID do produto que deseja atualizar: ");
    scanf("%d", &id);

    for (int i = 0; i < total_produtos; i++) {
        if (produtos[i].id == id) {
            encontrado = 1;

            printf("Produto encontrado:\n");
            printf("ID: %d | Nome: %s | Preco: %.2f | Quantidade: %d\n",
                   produtos[i].id, produtos[i].nome, produtos[i].precoKg, produtos[i].quantidade);
            printf("\nO que deseja atualizar?\n");
            printf("1. Preco por Kg\n");
            printf("2. Quantidade\n");
            printf("3. Sair\n");
            printf("Digite sua escolha: ");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    printf("Digite o novo preco por Kg: ");
                    scanf("%f", &novoPreco);
                    if (novoPreco <= 0){
                        printf("o valor deve ser maior que 0!\n");
                        printf("\nPressione qualquer tecla para voltar ao menu...\n");
                        getchar();  // Função para aguardar pressionar qualquer tecla
                        getchar();
                    }else{produtos[i].precoKg = novoPreco;
                        printf("Preco atualizado com sucesso!\n\n");
                        printf("ID: %d | Nome: %s | Preco: %.2f | Quantidade: %d\n",
                        produtos[i].id, produtos[i].nome, produtos[i].precoKg, produtos[i].quantidade);
                        printf("\nPressione qualquer tecla para voltar ao menu...\n");
                        getchar();
                        getchar();
                    }
                    break;

                case 2:
                    printf("Digite a nova quantidade em estoque: ");
                    scanf("%d", &novaQuantidade);
                     if (novaQuantidade <= 0){
                        printf("o valor deve ser maior que 0!\n");
                        printf("\nPressione qualquer tecla para voltar ao menu...\n");
                        getchar();  // Função para aguardar pressionar qualquer tecla
                        getchar();
                    }else{produtos[i].quantidade = novaQuantidade;
                        printf("Quantidade atualizada com sucesso!\n\n");
                        printf("ID: %d | Nome: %s | Preco: %.2f | Quantidade: %d\n",
                        produtos[i].id, produtos[i].nome, produtos[i].precoKg, produtos[i].quantidade);
                        printf("\nPressione qualquer tecla para voltar ao menu...\n");
                        getchar();
                        getchar();
                    }
                    break;
                case 3:
                    printf("\nSaindo...\n");
                    break;
                default:
                    printf("Opcao invalida. Operacao cancelada.\n");
                    break;
            }
            return;
        }
    }

    if (!encontrado) {
        printf("Produto com ID %d nao encontrado.\n", id);
    }
}
void excluirProduto() {// funcão de exclusão de produtos
  int idEncontrado = 0;  
  int id, qtd;
    printf("Digite o ID do produto a ser excluido: ");
    scanf("%d", &id);
    for (int i = 0; i < total_produtos; i++) {
        if (produtos[i].id == id) {// validação caso exista o produto com o id informado
            printf("ID: %d | Nome: %s | Preco: %.2f | Quantidade: %d\n",
            produtos[i].id, produtos[i].nome, produtos[i].precoKg, produtos[i].quantidade);
        }
    }
    for (int i = 0; i < total_produtos; i++) {//for para percorrer o total de produtos e exclusão do produto localizado pelo id informado
        if (produtos[i].id == id) {//validacão "se o id na casa 'i' for igual a o id informado" significa que o id foi localizado
            printf("\nDigite a quantidade a ser excluida: ");
            scanf("%d", &qtd);
            if (produtos[i].quantidade >= qtd) {
                produtos[i].quantidade -= qtd;
                funcaoLimpaTela();
                printf("\nResultados da exclusao:\n");
                for (int i = 0; i < total_produtos; i++) {
                    if (produtos[i].id == id) {// validação caso exista o produto com o id informado
                        printf("ID: %d | Nome: %s | Preco: %.2f | Quantidade: %d\n",
                        produtos[i].id, produtos[i].nome, produtos[i].precoKg, produtos[i].quantidade);
                        printf("\nPressione qualquer tecla para voltar ao menu...\n");
                        getchar();  // Função para aguardar  pressionar qualquer tecla
                        getchar();
                        funcaoLimpaTela();
                    }
                }
            } else {
                printf("Erro! Quantidade a ser excluida maior que a disponivel.\n");
            }
            idEncontrado = 1;
        }
    }
    if (!idEncontrado) {
        printf("Produto nao encontrado.\n");
    }

}
void comprarProduto() {
    int idProduto, quantidade;
    int encontrado = 0;
    flv();
    printf("Digite o ID do produto a ser vendido: ");
    scanf("%d", &idProduto);
    printf("Digite a quantidade a ser vendida: ");
    scanf("%d", &quantidade);

    for (int i = 0; i < total_produtos; i++) {
        if (produtos[i].id == idProduto) {
            if (produtos[i].quantidade >= quantidade) {
                produtos[i].quantidade -= quantidade;
                produtos[i].quantidade_vendida += quantidade;
                printf("Produto vendido com sucesso.\n");
                relatorioVendas();
            } else {
                printf("Quantidade insuficiente em estoque.\n");
            }
            encontrado = 1;
            
        }
    }

    if (!encontrado) {
        printf("Produto nao encontrado.\n");
    }
}
void doarSemanalmente() {
    int quantidadeDoada; // Quantidade a ser doada para cada produto
    printf("Realizando doacao semanal de 10%% do estoque...\n\n");

    for (int i = 0; i < total_produtos; i++) {
        if (produtos[i].quantidade > 0) { // Apenas produtos com quantidade > 0 podem ser doados
            quantidadeDoada = produtos[i].quantidade / 10; // Calcula 10% arredondado para baixo
            if (quantidadeDoada > 0) {
                produtos[i].quantidade -= quantidadeDoada; // Atualiza o estoque
                printf("Produto doado: %s | Quantidade: %d\n", produtos[i].nome, quantidadeDoada);
                FILE *arquivo = fopen("C:\\Transacoes\\relatorio_doacoes.csv", "w");
                if (arquivo != NULL) {
                    fprintf(arquivo, "Produto: %s | Quantidade doada: %d\n", produtos[i].nome, quantidadeDoada);
                }
                fclose(arquivo);
            }
        }
    }
    printf("Doacao semanal concluida com sucesso.\n");
}
void doarProdutos() { 
    char nomeProduto[50];
    int quantidade;
    
    printf("Informe o nome do produto/item que deseja doar: ");
    scanf("%s", nomeProduto);
    printf("Informe a quantidade que deseja doar: ");
    scanf("%d", &quantidade);

    FILE *arquivo = fopen("C:\\Transacoes\\relatorioDoacao.csv", "a");
    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo de doacoes.\n");
    }

    fprintf(arquivo, "Produto/item: %s, Quantidade: %d\n", nomeProduto, quantidade);
    fclose(arquivo);

    printf("Voce doou %d unidades de %s.\n", quantidade, nomeProduto);
}

void relatorioDoacao(){
    
    FILE *arquivo = fopen("C:\\Transacoes\\relatorioDoacao.csv", "r");
    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo..\n");
    }
    char linha[256];
    printf("\nRelatorio de doacoes:\n\n");

    while (fgets(linha, sizeof(linha), arquivo)) {
        printf("%s", linha);  // Exibe cada linha do arquivo
    }

    fclose(arquivo);
}
void relatorioVendas() {
    float totalVendas = 0.0;
    int totalItensVendidos = 0;
    Produto prod;
    int quant; 
    printf("\x1b[38;5;82m");  // Verde escuro
    printf("\n=====================================================\n");
    printf("==               Relatorio de Vendas             ==\n");
    printf("=====================================================\n");
    printf("\n\x1b[38;5;46m");  // Verde claro 
    printf("=====================================================\n");
    printf("  ID   ==    Nome     == Preco (R$) == Qtd. Vendida\n");
    printf("=====================================================\n");
    printf("\x1b[0m");  // Resetando a cor

    for (int i = 0; i < total_produtos; i++) {
        if (produtos[i].quantidade_vendida > 0) {
            printf("ID: %d | Nome: %s | Preco: %.2f | Quantidade Vendida: %d\n",
            produtos[i].id, produtos[i].nome, produtos[i].precoKg, produtos[i].quantidade_vendida);
            totalVendas += produtos[i].precoKg * produtos[i].quantidade_vendida;
            totalItensVendidos += produtos[i].quantidade_vendida;
            prod = produtos[i];
            quant = produtos[i].quantidade_vendida;
        }
    }
    gravarTransacaoVenda(prod, quant);
    printf("\nTotal de Vendas: R$ %.2f\n", totalVendas);
    printf("Total de Itens Vendidos: %d\n", totalItensVendidos);
}


void relatorioCaixa() {
    FILE *arquivo = fopen("transacoes_venda.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de transacoes de venda.\n");
        return;
    }
    char linha[256];
    float totalVendas = 0.0;
    while (fgets(linha, sizeof(linha), arquivo)) {
        if (strncmp(linha, "Total da Venda:", 15) == 0) {
            float valorVenda;
            sscanf(linha + 15, "%f", &valorVenda);
            totalVendas += valorVenda;
        }
        printf("%s", linha);
    }
    printf("Total de Vendas: %.2f\n", totalVendas);
    fclose(arquivo);
}
void cliente(){
    int opc ;
    do{
        funcaoLimpaTela();
        printf("\x1b[32m==============================================\n"); // Verde
        printf("\x1b[33m            ** Ola Cliente **                \n"); // Amarelo
        printf("\x1b[32m==============================================\n"); // Verde
        printf("\n\x1b[34mComo posso ajudar hoje?\n"); // Azul
        printf("\x1b[32m==============================================\n"); // Verde
        printf("\x1b[35m1. Comprar Produtos\n");  // Roxo
        printf("\x1b[36m2. Doar produtos para a campanha beneficente\n");  // Ciano
        printf("\x1b[31m3. Sair\n");  // Vermelho
        printf("\x1b[32m==============================================\n"); // Verde
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opc);
        printf("\x1b[38;5;105mCarregando sua escolha...\n");  // Cor Laranja
        sleep(1);  // Pausa antes de processar a escolha do usuário
        switch (opc){
            case 1:
                funcaoLimpaTela();
                comprarProduto();
                printf("\nPressione qualquer tecla para voltar ao menu...\n");
                getchar();  // Função para aguardar pressionar qualquer tecla
                getchar();
                break;
            case 2:
                funcaoLimpaTela();
                doarProdutos();
                printf("\nPressione qualquer tecla para voltar ao menu...\n");
                getchar();  // Função para aguardar pressionar qualquer tecla
                getchar();
                break;
            case 3:
                funcaoLimpaTela();
                printf("Obrigado por usar nosso sistema! Ate logo.\n");
                break;
            default:
                funcaoLimpaTela();
                printf("\x1b[38;5;196m[ERRO] Opcao incorreta! Tente novamente.\n\x1b[0m");
                printf("\nPressione qualquer tecla para voltar ao menu...\n");
                getchar();  // Função para aguardar pressionar qualquer tecla
                getchar();
                break;
        }
    } while (opc != 3);
}
void menuHortifruti(){
    int opc1;
    do {
        funcaoLimpaTela();
        printf("\x1b[38;5;46m==============================================\n");  // Verde vibrante
        printf("\x1b[38;5;82m            Cadastro de Produto               \n");  // Verde claro
        printf("\x1b[38;5;46m==============================================\n");  // Verde vibrante
        printf("\n\x1b[38;5;39mEscolha uma opcao para o cadastro de produtos:\n");  // Azul claro
        printf("\x1b[38;5;46m==============================================\n");  // Verde vibrante
        printf("\x1b[38;5;226m1. Repor Produto\n");  // Amarelo dourado
        printf("\x1b[38;5;123m2. Excluir Produto\n");  // Verde oliva
        printf("\x1b[38;5;166m3. Atualizar Produto\n");  // laranja
        printf("\x1b[38;5;36m4. Adicionar novo Produto\n"); //ciano
        printf("\x1b[38;5;196m5. Sair\n");  // Vermelho fogo
        
        printf("\x1b[38;5;46m==============================================\n");  // Verde vibrante
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opc1);
        printf("\x1b[38;5;105mCarregando sua escolha...\n");  // Cor Laranja
        sleep(1);  // Pausa antes de processar a escolha do usuário
        switch (opc1) {
            case 1:
                funcaoLimpaTela();
                escolhaFLV();
                break;
            case 2:
                funcaoLimpaTela();
                excluirProduto();
                break;
            case 3:
                funcaoLimpaTela();
                atualizarProduto();
                break;
            case 4:
                funcaoLimpaTela();
                adicionarNovoProduto();
                break;
            case 5:
                funcaoLimpaTela();
                printf("...");
                break;
            default:
                funcaoLimpaTela();
                printf("\x1b[38;5;196m[ERRO] Opcao incorreta! Tente novamente.\n\x1b[0m");
                printf("\nPressione qualquer tecla para voltar ao menu...\n");
                getchar();  // Função para aguardar  pressionar qualquer tecla
                getchar();
                break;
        }
    } while (opc1 != 5);
}
void opcFuncionario() {
    int menu;
      printf("\x1b[38;5;82mAutenticacao bem-sucedida! Bem-vindo(a)!\n\x1b[0m");
    
    do {
        funcaoLimpaTela();
        printf("\x1b[38;5;46m==================================================================\n");  // Verde vibrante
        printf("\x1b[38;5;82m                ** MENU PRINCIPAL - HORTIFRUTI **     \n");  // Verde claro
        printf("\x1b[38;5;46m==================================================================\n");  // Verde vibrante
        printf("\x1b[38;5;46m>> Bem-vindo, voce esta no menu de gerenciamento de Hortifruti. <<\n"); 
        printf("\n\x1b[38;5;226m1. Cadastro de Produto\n");  // Amarelo
        printf("\x1b[38;5;123m2. Pesquisar Produto\n");  // Verde oliva
        printf("\x1b[38;5;39m3. Ver Estoque\n");  // Azul claro
        printf("\x1b[38;5;196m4. Relatorio de Doacoes campanha\n");  // Vermelho
        printf("\x1b[38;5;36m5. Relatorio semanal de produtos doados do estoque\n"); //ciano
        printf("\x1b[38;5;166m6. Relatorio de Caixa\n");  // Laranja
        printf("\x1b[38;5;82m7. Encerrar Sessao\n");  // Verde claro 
        printf("\x1b[38;5;46m==================================================================\n");  // Verde vibrante
        printf("\nEscolha uma opcao: ");
        scanf("%d", &menu);
        printf("\x1b[38;5;105mCarregando sua escolha...\n");  // Cor Laranja
        sleep(1);  // Pausa antes de processar a escolha do usuário
        switch (menu) {
            case 1:
                funcaoLimpaTela();
                menuHortifruti();
                break;
            case 2:
                funcaoLimpaTela();
                pesquisarProduto();
                break;
            case 3:
                funcaoLimpaTela();
                listarProdutosDeposito();
                printf("\nPressione qualquer tecla para voltar ao menu...\n");
                getchar();  // Função para aguardar  pressionar qualquer tecla
                getchar();
                break;
            case 4:
                funcaoLimpaTela();
                relatorioDoacao();
                printf("\nPressione qualquer tecla para voltar ao menu...\n");
                getchar();  // Função para aguardar  pressionar qualquer tecla
                getchar();
                break;
            case 5 :
                funcaoLimpaTela();
                doarSemanalmente();
                printf("\nPressione qualquer tecla para voltar ao menu...\n");
                getchar();  // Função para aguardar pressionar qualquer tecla
                getchar();
                break;
            case 6:
                funcaoLimpaTela();
                relatorioCaixa();
                printf("\nPressione qualquer tecla para voltar ao menu...\n");
                getchar();  // Função para aguardar pressionar qualquer tecla
                getchar();
                break;
            case 7:
                funcaoLimpaTela();
                printf("\n...\n");
                sleep(1); 
                break;
            default:
                funcaoLimpaTela();
                printf("\x1b[38;5;196m[ERRO] Opcao incorreta! Tente novamente.\n\x1b[0m");
                printf("\nPressione qualquer tecla para voltar ao menu...\n");
                getchar();  // Função para aguardar  pressionar qualquer tecla
                getchar();
                break;
        }
    } while (menu != 7);
}

int main() {//funcão principal do programa
    int aut;// número int a ser armazenado para a escolha das opcões
    produtosNoEstoque();
        do {
        printf("\x1b[38;5;82m");
        printf("=====================================================\n");
        printf("\x1b[38;5;46m             ** HORTIFRUTI ECOLOGIC **            \n");
        printf("\x1b[38;5;82m");
        printf("=====================================================\n");
        printf("\x1b[38;5;39m");  // Cor Azul para a próxima linha
        printf("\n\t\tComo podemos te ajudar hoje?\n");
        sleep(1);  // Pequena pausa antes de mostrar as opções para criar uma sensação de transição
        printf("\x1b[38;5;226m1. Funcionario\n");  // Amarelo
        printf("\x1b[38;5;123m2. Cliente\n");  // Verde oliva
        printf("\x1b[38;5;196m3. Sair\n");  // Vermelho
        printf("\x1b[38;5;82m=====================================================\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &aut);
        printf("\x1b[38;5;105mCarregando sua escolha...\n");  // Cor Laranja
        sleep(1);  // Pausa antes de processar a escolha do usuário

        switch (aut) {
            case 1:
                funcaoLimpaTela();
                autenticacaoUsuario();
                break;
            case 2:
                funcaoLimpaTela();
                cliente();
                break;
            case 3:
                funcaoLimpaTela();
                printf("\x1b[38;5;196mEncerrando o sistema...\n\x1b[0m");
                break;
            default:
                funcaoLimpaTela();
                printf("\x1b[38;5;196m[ERRO] Opcao incorreta! Tente novamente.\n\x1b[0m");
                printf("\nPressione qualquer tecla para voltar ao menu...\n");
                getchar();  // Função para aguardar  pressionar qualquer tecla
                getchar();
                break;
        }
    }while (aut !=3);
    
    return 0;
}
