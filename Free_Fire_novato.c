#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definição da capacidade máxima do inventário
#define MAX_ITENS 10


typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Variáveis globais
Item inventario[MAX_ITENS]; // Vetor de itens (mochila do jogador)
int totalItens = 0;         // Contador de itens cadastrados

// Protótipos das funções
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();
void limparBuffer();
void exibirMenu();

/**
 * Função principal: controla o fluxo do programa
 */
int main() {
    int opcao;
    
    printf("===========================================\n");
    printf("   SISTEMA DE INVENTARIO - MODO SURVIVAL\n");
    printf("===========================================\n\n");
    
    do {
        exibirMenu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        printf("\n");
        
        switch(opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 5:
                printf("Saindo do sistema...\n");
                printf("Boa sorte na sua jornada de sobrevivencia!\n");
                break;
            default:
                printf("[ERRO] Opcao invalida! Tente novamente.\n\n");
        }
        
    } while(opcao != 5);
    
    return 0;
}

/**
 * Exibe o menu principal do sistema
 */
void exibirMenu() {
    printf("-------------------------------------------\n");
    printf("MENU PRINCIPAL\n");
    printf("-------------------------------------------\n");
    printf("1. Cadastrar item\n");
    printf("2. Remover item\n");
    printf("3. Listar todos os itens\n");
    printf("4. Buscar item por nome\n");
    printf("5. Sair\n");
    printf("-------------------------------------------\n");
    printf("Itens no inventario: %d/%d\n", totalItens, MAX_ITENS);
    printf("-------------------------------------------\n");
}

/**
 * Insere um novo item no inventário
 * Verifica se há espaço disponível e valida os dados
 */
void inserirItem() {
    // Verifica se o inventário está cheio
    if(totalItens >= MAX_ITENS) {
        printf("[AVISO] Inventario cheio! Remova itens antes de adicionar novos.\n\n");
        return;
    }
    
    Item novoItem;
    
    printf("=== CADASTRAR NOVO ITEM ===\n");
    
    // Leitura do nome do item
    printf("Nome do item: ");
    fgets(novoItem.nome, 30, stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = '\0'; // Remove o '\n'
    
    // Validação: nome não pode estar vazio
    if(strlen(novoItem.nome) == 0) {
        printf("[ERRO] Nome invalido! Operacao cancelada.\n\n");
        return;
    }
    
    // Leitura do tipo do item
    printf("Tipo (arma/municao/cura/ferramenta): ");
    fgets(novoItem.tipo, 20, stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = '\0';
    
    // Leitura da quantidade
    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);
    limparBuffer();
    
    // Validação: quantidade deve ser positiva
    if(novoItem.quantidade <= 0) {
        printf("[ERRO] Quantidade deve ser maior que zero!\n\n");
        return;
    }
    
    // Adiciona o item ao inventário
    inventario[totalItens] = novoItem;
    totalItens++;
    
    printf("\n[SUCESSO] Item '%s' cadastrado com sucesso!\n\n", novoItem.nome);
    listarItens();
}

/**
 * Remove um item do inventário com base no nome
 * Utiliza busca sequencial para localizar o item
 */
void removerItem() {
    if(totalItens == 0) {
        printf("[AVISO] Inventario vazio! Nao ha itens para remover.\n\n");
        return;
    }
    
    char nomeBusca[30];
    int encontrado = 0;
    
    printf("=== REMOVER ITEM ===\n");
    printf("Nome do item a remover: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    // Busca sequencial pelo item
    for(int i = 0; i < totalItens; i++) {
        if(strcmp(inventario[i].nome, nomeBusca) == 0) {
            encontrado = 1;
            
            // Desloca os itens seguintes para preencher o espaço
            for(int j = i; j < totalItens - 1; j++) {
                inventario[j] = inventario[j + 1];
            }
            
            totalItens--;
            printf("\n[SUCESSO] Item '%s' removido do inventario!\n\n", nomeBusca);
            listarItens();
            break;
        }
    }
    
    if(!encontrado) {
        printf("\n[ERRO] Item '%s' nao encontrado no inventario.\n\n", nomeBusca);
    }
}

/**
 * Lista todos os itens cadastrados no inventário
 * Exibe informações formatadas de cada item
 */
void listarItens() {
    printf("===========================================\n");
    printf("   ITENS NO INVENTARIO\n");
    printf("===========================================\n");
    
    if(totalItens == 0) {
        printf("  [Inventario vazio]\n");
    } else {
        printf("%-20s %-15s %s\n", "NOME", "TIPO", "QUANTIDADE");
        printf("-------------------------------------------\n");
        
        for(int i = 0; i < totalItens; i++) {
            printf("%-20s %-15s %d\n", 
                   inventario[i].nome, 
                   inventario[i].tipo, 
                   inventario[i].quantidade);
        }
    }
    
    printf("===========================================\n");
    printf("Total: %d/%d itens\n", totalItens, MAX_ITENS);
    printf("===========================================\n\n");
}

/**
 * Busca um item específico pelo nome usando busca sequencial
 * Exibe os detalhes do item se encontrado
 */
void buscarItem() {
    if(totalItens == 0) {
        printf("[AVISO] Inventario vazio! Nao ha itens para buscar.\n\n");
        return;
    }
    
    char nomeBusca[30];
    int encontrado = 0;
    
    printf("=== BUSCAR ITEM ===\n");
    printf("Nome do item: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    // Busca sequencial pelo nome do item
    for(int i = 0; i < totalItens; i++) {
        if(strcmp(inventario[i].nome, nomeBusca) == 0) {
            encontrado = 1;
            
            printf("\n=== ITEM ENCONTRADO ===\n");
            printf("Nome.......: %s\n", inventario[i].nome);
            printf("Tipo.......: %s\n", inventario[i].tipo);
            printf("Quantidade.: %d\n", inventario[i].quantidade);
            printf("Posicao....: %d\n", i + 1);
            printf("========================\n\n");
            break;
        }
    }
    
    if(!encontrado) {
        printf("\n[ERRO] Item '%s' nao foi encontrado no inventario.\n\n", nomeBusca);
    }
}

/**
 * Limpa o buffer de entrada para evitar leituras indesejadas
 */
void limparBuffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}
