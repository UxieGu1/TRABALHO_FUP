#include <stdio.h>

int main(){
    FILE *arquivo = fopen("../data/palavras.txt", "a");

    if(arquivo == NULL){
        printf("Erro ao criar arquivo!\n");
        return 1;
    }

    char p1[100], p2[100], p3[100];

    printf("Digite 3 palavras: \n");
    scanf("%99s %99s %99s", p1, p2, p3);

    fprintf(arquivo, " %s\n %s\n %s\n", p1, p2, p3);
    fclose(arquivo);

    printf("Palavras salvas no palavras.txt com sucesso!\n");
    return 0;
}