#include <stdio.h>
#include <string.h>

// Definição da struct
struct Territorio
{
    char nome[30];
    char cor[10];
    int tropas;
};

int main()
{
    struct Territorio territorios[5];

    // Cadastro dos territórios
    for (int i = 0; i < 5; i++)
    {
        printf("\n--- Cadastro do Territorio %d ---\n", i + 1);

        // Nome do território
        printf("Digite o nome do territorio: ");
        fgets(territorios[i].nome, 30, stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

        // Cor do exército
        printf("Digite a cor do exercito: ");
        fgets(territorios[i].cor, 10, stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';

        // Tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        getchar(); // limpa o ENTER do buffer
    }

    // Exibição dos dados
    printf("\n=== Territorios cadastrados ===\n");

    for (int i = 0; i < 5; i++)
    {
        printf("\nTerritorio %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exercito: %s\n", territorios[i].cor);
        printf("Quantidade de tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}