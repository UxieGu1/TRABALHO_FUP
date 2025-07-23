#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int main() {
    FILE *arquivo = fopen("../data/palavras.txt", "a+");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return 1;
    }

    char palavraAnterior[150];
    char palavraAtual[150];
    char dica[150];
    int i, rodada;

    // Palavra inicial:
    while (true){
    
    printf("Digite a palavra inicial (minimo 3 letras): ");
    scanf("%s", palavraAnterior);

    // Validação da palavra inicial:
    if (strlen(palavraAnterior) < 3) {
        printf("ERRO: A palavra inicial precisa ter pelo menos 3 letras!\n");
        fclose(arquivo);
        return 1;
    }

    for (i = 0; palavraAnterior[i] != '\0'; i++) {
        if (!isalpha(palavraAnterior[i])) {
            printf("ERRO: Palavra inicial deve conter apenas letras!\n");
            fclose(arquivo);
            return 1;
        }
    }

    fprintf(arquivo, "%s\n", palavraAnterior);

    // Loop de 4 rodadas
    for (rodada = 1; rodada <= 4; rodada++) {
        printf("\n--- Rodada %d ---\n", rodada);

        printf("Digite a dica: ");
        scanf(" %[^\n]", dica);

        printf("Digite a nova palavra (1 letra diferente de '%s'): ", palavraAnterior);
        scanf("%s", palavraAtual);

        // Validação:
        int valido = 1;
        if (strlen(palavraAtual) != strlen(palavraAnterior)) {
            printf("ERRO: As palavras devem ter o mesmo tamanho!\n");
            valido = 0;
        }

        int diferencas = 0;
        for (i = 0; palavraAtual[i] != '\0'; i++) {
            if (!isalpha(palavraAtual[i])) {
                printf("ERRO: A palavra deve conter apenas letras!\n");
                valido = 0;
                break;
            }
            if (tolower(palavraAtual[i]) != tolower(palavraAnterior[i])) {
                diferencas++;
            }
        }

        if (valido && diferencas != 1) {
            printf("A nova palavra deve ter exatamente 1 letra diferente da anterior!\n");
            valido = 0;
        }

        if (valido && strcasecmp(palavraAtual, palavraAnterior) == 0) {
            printf("ERRO: A nova palavra não pode ser igual à anterior!\n");
            valido = 0;
        }
        //Caso tudo seja válido, executará:
        if (valido) {
            fprintf(arquivo, "%s\n", dica);
            fprintf(arquivo, "%s\n", palavraAtual);
            strcpy(palavraAnterior, palavraAtual);
        } else {
            printf("Repetindo a rodada...\n");
            rodada--; 
        }
    }

    fclose(arquivo);
    printf("\nDados salvos com sucesso em palavras.txt!\n");

    char repetir;
    printf("Deseja jogar novamente(S/n)?\n");
    scanf(" %c", &repetir);

    if (repetir == 'S' || repetir == 's'){
        continue;
    }else{
        printf("Obrigado por jogar, volte sempre!");
        break;
    }
    }
    return 0;
}