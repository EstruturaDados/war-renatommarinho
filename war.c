#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// =====================================
// Struct dos territórios
// =====================================

typedef struct
{
    char nome[30];
    char cor[10];
    int tropas;

} Territorio;

// =====================================
// Cadastro dos territórios
// =====================================

void cadastrarTerritorios(Territorio *territorios, int quantidade)
{
    for (int i = 0; i < quantidade; i++)
    {
        printf("\n--- Cadastro do Territorio %d ---\n", i + 1);

        printf("Digite o nome do territorio: ");
        fgets((territorios + i)->nome, 30, stdin);
        (territorios + i)->nome[strcspn((territorios + i)->nome, "\n")] = '\0';

        printf("Digite a cor do exercito: ");
        fgets((territorios + i)->cor, 10, stdin);
        (territorios + i)->cor[strcspn((territorios + i)->cor, "\n")] = '\0';

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &(territorios + i)->tropas);

        getchar();
    }
}

// =====================================
// Exibe os territórios
// =====================================

void exibirTerritorios(Territorio *territorios, int quantidade)
{
    printf("\n========== TERRITORIOS ==========\n");

    for (int i = 0; i < quantidade; i++)
    {
        printf("\nTerritorio %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
    }
}

// =====================================
// Sorteia missão
// =====================================

void atribuirMissao(char *destino, char *missoes[], int totalMissoes)
{
    int sorteio = rand() % totalMissoes;

    strcpy(destino, missoes[sorteio]);
}

// =====================================
// Exibe missão
// =====================================

void exibirMissao(char *missao)
{
    printf("\n========== MISSAO ==========\n");
    printf("%s\n", missao);
}

// =====================================
// Verifica missão
// =====================================

int verificarMissao(char *missao,
                    Territorio *mapa,
                    int tamanho,
                    char corJogador[])
{
    // Missão: conquistar 5 territórios
    if (strcmp(missao, "Conquistar 5 territorios") == 0)
    {
        int contador = 0;

        for (int i = 0; i < tamanho; i++)
        {
            if (strcmp(mapa[i].cor, corJogador) == 0)
            {
                contador++;
            }
        }

        if (contador >= 5)
        {
            return 1;
        }
    }

    // Missão: possuir 20 tropas
    else if (strcmp(missao, "Possuir 20 tropas no total") == 0)
    {
        int soma = 0;

        for (int i = 0; i < tamanho; i++)
        {
            if (strcmp(mapa[i].cor, corJogador) == 0)
            {
                soma += mapa[i].tropas;
            }
        }

        if (soma >= 20)
        {
            return 1;
        }
    }

    // Missão: eliminar vermelhos
    else if (strcmp(missao, "Eliminar exercitos vermelhos") == 0)
    {
        int encontrou = 0;

        for (int i = 0; i < tamanho; i++)
        {
            if (strcmp(mapa[i].cor, "Vermelho") == 0)
            {
                encontrou = 1;
            }
        }

        if (!encontrou)
        {
            return 1;
        }
    }

    // Missão: conquistar território azul
    else if (strcmp(missao, "Conquistar um territorio azul") == 0)
    {
        for (int i = 0; i < tamanho; i++)
        {
            if (strcmp(mapa[i].cor, "Azul") == 0 &&
                strcmp(mapa[i].cor, corJogador) == 0)
            {
                return 1;
            }
        }
    }

    return 0;
}

// =====================================
// Sistema de ataque
// =====================================

void atacar(Territorio *atacante, Territorio *defensor)
{
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n========== ATAQUE ==========\n");

    printf("%s atacou %s\n", atacante->nome, defensor->nome);

    printf("Dado atacante: %d\n", dadoAtacante);
    printf("Dado defensor: %d\n", dadoDefensor);

    // Vitória do atacante
    if (dadoAtacante > dadoDefensor)
    {
        printf("\nO atacante venceu!\n");

        // Território muda de cor
        strcpy(defensor->cor, atacante->cor);

        // Calcula tropas transferidas
        int tropasTransferidas = atacante->tropas / 2;

        if (tropasTransferidas < 1)
        {
            tropasTransferidas = 1;
        }

        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;
    }

    // Vitória do defensor
    else
    {
        printf("\nO defensor venceu!\n");

        atacante->tropas--;

        if (atacante->tropas < 0)
        {
            atacante->tropas = 0;
        }
    }
}

// =====================================
// Libera memória
// =====================================

void liberarMemoria(Territorio *territorios, char *missao)
{
    free(territorios);
    free(missao);
}

// =====================================
// MAIN
// =====================================

int main()
{
    int quantidade;

    srand(time(NULL));

    // =====================================
    // Vetor de missões
    // =====================================

    char *missoes[] =
    {
        "Conquistar 5 territorios",
        "Possuir 20 tropas no total",
        "Eliminar exercitos vermelhos",
        "Conquistar um territorio azul"
    };

    int totalMissoes = 4;

    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &quantidade);

    getchar();

    // =====================================
    // Alocação dinâmica dos territórios
    // =====================================

    Territorio *territorios;

    territorios = (Territorio *)calloc(quantidade, sizeof(Territorio));

    // =====================================
    // Alocação dinâmica da missão
    // =====================================

    char *missaoJogador;

    missaoJogador = (char *)malloc(100 * sizeof(char));

    // =====================================
    // Cadastro dos territórios
    // =====================================

    cadastrarTerritorios(territorios, quantidade);

    // =====================================
    // Sorteia missão
    // =====================================

    atribuirMissao(missaoJogador, missoes, totalMissoes);

    // =====================================
    // Exibe missão inicial
    // =====================================

    exibirMissao(missaoJogador);

    int opcao = 1;

    // =====================================
    // Loop principal do jogo
    // =====================================

    while (opcao == 1)
    {
        int atacante;
        int defensor;

        // Exibe territórios
        exibirTerritorios(territorios, quantidade);

        // Exibe missão atual
        exibirMissao(missaoJogador);

        printf("\nEscolha o territorio atacante (1 a %d): ", quantidade);
        scanf("%d", &atacante);

        printf("Escolha o territorio defensor (1 a %d): ", quantidade);
        scanf("%d", &defensor);

        atacante--;
        defensor--;

        // =====================================
        // Validação
        // =====================================

        if (atacante < 0 || atacante >= quantidade ||
            defensor < 0 || defensor >= quantidade)
        {
            printf("\nTerritorio invalido!\n");
        }

        else if (strcmp(territorios[atacante].cor,
                         territorios[defensor].cor) == 0)
        {
            printf("\nNao e permitido atacar territorios da mesma cor!\n");
        }

        else if (territorios[atacante].tropas <= 1)
        {
            printf("\nTropas insuficientes para atacar!\n");
        }

        // =====================================
        // Realiza ataque
        // =====================================

        else
        {
            atacar(&territorios[atacante],
                    &territorios[defensor]);

            // =====================================
            // Verifica missão no final do turno
            // =====================================

            if (verificarMissao(missaoJogador,
                                territorios,
                                quantidade,
                                territorios[atacante].cor))
            {
                printf("\n=================================\n");
                printf("MISSAO CUMPRIDA!\n");
                printf("Jogador venceu o jogo!\n");
                printf("Missao: %s\n", missaoJogador);
                printf("=================================\n");

                break;
            }
            else
            {
                printf("\nMissao ainda nao cumprida!\n");
                printf("O jogo continua...\n");
            }
        }

        // =====================================
        // Continua jogo
        // =====================================

        printf("\nDeseja realizar outro ataque?\n");
        printf("1 - Sim\n");
        printf("0 - Nao\n");
        printf("Opcao: ");

        scanf("%d", &opcao);
    }

    // =====================================
    // Estado final
    // =====================================

    printf("\n========== ESTADO FINAL ==========\n");

    exibirTerritorios(territorios, quantidade);

    // =====================================
    // Libera memória
    // =====================================

    liberarMemoria(territorios, missaoJogador);

    return 0;
}