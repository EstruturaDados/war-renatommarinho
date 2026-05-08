#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Struct do território
struct Territorio
{
    char nome[30];
    char cor[10];
    int tropas;
};

// Função para cadastrar territórios
void cadastrarTerritorios(struct Territorio *territorios, int quantidade)
{
    for (int i = 0; i < quantidade; i++)
    {
        printf("\n--- Cadastro do Territorio %d ---\n", i + 1);

        // Nome do território
        printf("Digite o nome do territorio: ");
        fgets((territorios + i)->nome, 30, stdin);
        (territorios + i)->nome[strcspn((territorios + i)->nome, "\n")] = '\0';

        // Cor do exército
        printf("Digite a cor do exercito: ");
        fgets((territorios + i)->cor, 10, stdin);
        (territorios + i)->cor[strcspn((territorios + i)->cor, "\n")] = '\0';

        // Quantidade de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &(territorios + i)->tropas);

        getchar(); // limpa o ENTER do buffer
    }
}

// Função para exibir os territórios
void exibirTerritorios(struct Territorio *territorios, int quantidade)
{
    printf("\n=== TERRITORIOS ===\n");

    for (int i = 0; i < quantidade; i++)
    {
        printf("\nTerritorio %d\n", i + 1);
        printf("Nome: %s\n", (territorios + i)->nome);
        printf("Cor: %s\n", (territorios + i)->cor);
        printf("Tropas: %d\n", (territorios + i)->tropas);
    }
}

// Função de ataque
void atacar(struct Territorio *atacante, struct Territorio *defensor)
{
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n=== ATAQUE ===\n");

    printf("%s atacou %s\n", atacante->nome, defensor->nome);

    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    // Vitória do atacante
    if (dadoAtacante > dadoDefensor)
    {
        printf("\nO atacante venceu!\n");

        // Defensor muda de cor
        strcpy(defensor->cor, atacante->cor);

        // Metade das tropas vai para o território conquistado
        defensor->tropas = atacante->tropas / 2;

        // Atacante perde metade das tropas
        atacante->tropas = atacante->tropas / 2;
    }
    else
    {
        printf("\nO defensor venceu!\n");

        // Atacante perde 1 tropa
        atacante->tropas--;

        // Evita tropas negativas
        if (atacante->tropas < 0)
        {
            atacante->tropas = 0;
        }
    }
}

// Função para liberar memória
void liberarMemoria(struct Territorio *territorios)
{
    free(territorios);
}

int main()
{
    int quantidade;

    // Inicializa números aleatórios
    srand(time(NULL));

    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &quantidade);

    getchar();

    // Alocação dinâmica de memória
    struct Territorio *territorios;

    territorios = (struct Territorio *)calloc(quantidade, sizeof(struct Territorio));

    // Cadastro dos territórios
    cadastrarTerritorios(territorios, quantidade);

    int opcao = 1;

    // Loop principal do jogo
    while (opcao == 1)
    {
        int atacante;
        int defensor;

        // Mostra os territórios
        exibirTerritorios(territorios, quantidade);

        printf("\nEscolha o territorio atacante (1 a %d): ", quantidade);
        scanf("%d", &atacante);

        printf("Escolha o territorio defensor (1 a %d): ", quantidade);
        scanf("%d", &defensor);

        // Ajusta para índice do vetor
        atacante--;
        defensor--;

        // Validação de posições inválidas
        if (atacante < 0 || atacante >= quantidade ||
            defensor < 0 || defensor >= quantidade)
        {
            printf("\nTerritorio invalido!\n");
        }

        // Não pode atacar território da mesma cor
        else if (strcmp(territorios[atacante].cor,
                         territorios[defensor].cor) == 0)
        {
            printf("\nNao e permitido atacar territorios da mesma cor!\n");
        }

        // Verifica tropas suficientes
        else if (territorios[atacante].tropas <= 1)
        {
            printf("\nO territorio atacante nao possui tropas suficientes!\n");
        }

        // Realiza ataque
        else
        {
            atacar(&territorios[atacante],
                    &territorios[defensor]);
        }

        // Pergunta se deseja continuar
        printf("\nDeseja realizar outro ataque?\n");
        printf("1 - Sim\n");
        printf("0 - Nao\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
    }

    // Exibe resultado final
    printf("\n=== ESTADO FINAL DOS TERRITORIOS ===\n");

    exibirTerritorios(territorios, quantidade);

    // Libera memória
    liberarMemoria(territorios);

    return 0;
}