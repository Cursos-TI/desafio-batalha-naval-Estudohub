#include <stdio.h>
#include <stdbool.h>

// --- Constantes do Tabuleiro ---
#define TAMANHO_TABULEIRO 10 // O tabuleiro é 10x10
#define TAMANHO_NAVIO 3       // Todos os navios terão 3 posições
#define AGUA 0                // Representação de Água no tabuleiro
#define NAVIO 3               // Representação de Navio no tabuleiro

// --- Protótipos de Funções ---
void inicializar_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
bool posicionar_navios(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha_inicial, int coluna_inicial, int orientacao);
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

/**
 * @brief Função principal para simular o posicionamento de navios.
 */
int main() {
    // Declaração da matriz do tabuleiro 10x10.
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa todo o tabuleiro com água (0).
    inicializar_tabuleiro(tabuleiro);
    
    // --- Configuração dos Navios ---
    
    // Navio 1: Horizontal
    int n1_linha = 1;
    int n1_coluna = 1;
    int n1_orientacao = 0; // 0 = Horizontal

    // Navio 2: Vertical
    int n2_linha = 5;
    int n2_coluna = 6;
    int n2_orientacao = 1; // 1 = Vertical

    printf("--- Batalha Naval - Posicionamento Novato ---\n\n");

    // 1. Posiciona o Navio Horizontal
    printf("Posicionando Navio 1 (Horizontal)... ");
    if (posicionar_navios(tabuleiro, n1_linha, n1_coluna, n1_orientacao)) {
        printf("SUCESSO!\n");
    } else {
        printf("FALHA: Coordenadas Inválidas ou Sobreposição.\n");
    }

    // 2. Posiciona o Navio Vertical
    printf("Posicionando Navio 2 (Vertical)... ");
    if (posicionar_navios(tabuleiro, n2_linha, n2_coluna, n2_orientacao)) {
        printf("SUCESSO!\n");
    } else {
        printf("FALHA: Coordenadas Inválidas ou Sobreposição.\n");
    }

    // 3. Exibe o tabuleiro final
    printf("\n--- Tabuleiro Final (%d = Agua, %d = Navio) ---\n", AGUA, NAVIO);
    exibir_tabuleiro(tabuleiro);

    return 0;
}

// -------------------------------------------------------------------
// --- Implementação das Funções ---
// -------------------------------------------------------------------

/**
 * @brief Inicializa todas as posições do tabuleiro com o valor de Água (0).
 * @param tabuleiro A matriz 10x10 a ser inicializada.
 */
void inicializar_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Loops aninhados para percorrer Linhas (i) e Colunas (j)
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA; // Define cada célula como ÁGUA (0)
        }
    }
}

/**
 * @brief Tenta posicionar um navio no tabuleiro, validando limites e sobreposição.
 * @param tabuleiro A matriz do tabuleiro.
 * @param linha_inicial Linha de início do navio.
 * @param coluna_inicial Coluna de início do navio.
 * @param orientacao 0 para Horizontal, 1 para Vertical.
 * @return true se o navio foi posicionado com sucesso, false caso contrário.
 */
bool posicionar_navios(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                       int linha_inicial, int coluna_inicial, int orientacao) 
{
    // Variáveis para iterar sobre as posições do navio
    int l, c;

    // --- 1. Validação de Limites ---
    
    // Para navio horizontal
    if (orientacao == 0) { 
        // Verifica se a linha inicial está ok E se o fim do navio está dentro dos limites da coluna
        if (linha_inicial < 0 || linha_inicial >= TAMANHO_TABULEIRO ||
            coluna_inicial < 0 || coluna_inicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
            return false; // Fora dos limites
        }
    } 
    // Para navio vertical
    else if (orientacao == 1) { 
        // Verifica se a coluna inicial está ok E se o fim do navio está dentro dos limites da linha
        if (coluna_inicial < 0 || coluna_inicial >= TAMANHO_TABULEIRO ||
            linha_inicial < 0 || linha_inicial + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
            return false; // Fora dos limites
        }
    } else {
        return false; // Orientação inválida
    }
    
    // --- 2. Validação de Sobreposição (Pré-verificação) ---
    
    // Loop para verificar se as posições necessárias já estão ocupadas por um navio (3)
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (orientacao == 0) { // Horizontal
            l = linha_inicial;
            c = coluna_inicial + i;
        } else { // Vertical
            l = linha_inicial + i;
            c = coluna_inicial;
        }

        // Se a posição já for um navio (3), há sobreposição
        if (tabuleiro[l][c] == NAVIO) {
            return false; // Sobreposição detectada
        }
    }

    // --- 3. Posicionamento (Se todas as validações passarem) ---
    
    // Loop para realmente marcar as posições do navio no tabuleiro
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (orientacao == 0) { // Horizontal: Aumenta a Coluna
            l = linha_inicial;
            c = coluna_inicial + i;
        } else { // Vertical: Aumenta a Linha
            l = linha_inicial + i;
            c = coluna_inicial;
        }
        
        tabuleiro[l][c] = NAVIO; // Marca a posição com o valor do Navio (3)
    }

    return true; // Navio posicionado com sucesso
}

/**
 * @brief Exibe o tabuleiro completo no console, formatado.
 * @param tabuleiro A matriz 10x10 a ser exibida.
 */
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Imprime o cabeçalho das colunas (0 a 9)
    printf("   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf(" %d", j);
    }
    printf("\n");
    
    // Imprime a linha separadora
    printf("  ");
    for (int j = 0; j < TAMANHO_TABULEIRO * 3; j++) {
        printf("-");
    }
    printf("\n");

    // Loops aninhados para percorrer e imprimir a matriz
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        // Imprime o número da linha
        printf("%d |", i); 
        
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            // Imprime o conteúdo da célula (0 ou 3) com um espaço separador
            printf(" %d", tabuleiro[i][j]); 
        }
        printf(" |\n"); // Quebra de linha no final de cada linha do tabuleiro
    }
    
    // Imprime a linha de rodapé
    printf("  ");
    for (int j = 0; j < TAMANHO_TABULEIRO * 3; j++) {
        printf("-");
    }
    printf("\n");
}


























