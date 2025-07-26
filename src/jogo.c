#include <stdio.h>
#include <string.h>

#define MAX_RODADAS 100

typedef struct {
    char dica[200];
    char proxima[200];
} Rodada;

typedef struct {
    char inicial[200];
    Rodada rodadas[MAX_RODADAS];
    int totalRodadas;
} Jogo;

int main(void) {
    FILE *arquivo = fopen("../data/palavras.txt", "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo.");
        return 1;
    }

    char linha[200];
    char chute[200];
    char escolha;
    int acertou;
    int introduzir = 1;

    while (1) {
        Jogo game;
        game.totalRodadas = 0;

        while (fgets(linha, sizeof(linha), arquivo)) {
            linha[strcspn(linha, "\n")] = '\0';
            if (strcasecmp(linha, "###") != 0) {
                strcpy(game.inicial, linha);
                break;
            }
        }

        if (feof(arquivo) || strlen(game.inicial) == 0)
            break;

        while (game.totalRodadas < MAX_RODADAS && fgets(linha, sizeof(linha), arquivo)) {
            linha[strcspn(linha, "\n")] = '\0';
            if (strcasecmp(linha, "###") == 0)
                break;

            strcpy(game.rodadas[game.totalRodadas].dica, linha);

            if (!fgets(linha, sizeof(linha), arquivo))
                break;
            linha[strcspn(linha, "\n")] = '\0';
            strcpy(game.rodadas[game.totalRodadas].proxima, linha);

            game.totalRodadas++;
        }

        if (introduzir) {
            printf("========================================\n");
            printf("   Bem‑vindo ao Cladder em C!\n");
            printf("Neste jogo, você verá uma palavra e\n");
            printf("receberá uma dica para descobrir a\n");
            printf("próxima palavra mudando apenas uma\n");
            printf("letra. Boa sorte!\n");
            printf("========================================\n\n");
            introduzir = 0;
        }

        acertou = 0;
        int total = game.totalRodadas;
        char atual[200];
        strcpy(atual, game.inicial);

        for (int i = 0; i < game.totalRodadas; i++) {
            printf("Palavra atual: %s\n", atual);
            printf("Dica: %s\n", game.rodadas[i].dica);
            printf("Qual é a próxima palavra? ");
            scanf("%s", chute);

            if (strcmp(chute, game.rodadas[i].proxima) == 0) {
                printf("Correto!\n\n");
                acertou++;
            } else {
                printf("Errado! Era \"%s\".\n\n", game.rodadas[i].proxima);
            }
            strcpy(atual, game.rodadas[i].proxima);
        }

        printf("Fim do jogo! Você acertou %d de %d.\n", acertou, total);
        printf("Deseja continuar para o próximo jogo? (S/N): ");
        scanf(" %c", &escolha);
        printf("\n");

        if (escolha != 'S' && escolha != 's')
            break;
    }

    printf("Programa concluído. Até mais.\n");
    fclose(arquivo);
    return 0;
}
