#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INPUT "inp.txt"
#define OUTPUT "out.txt"
#define MAX 100

// generate a random_matricula : A-Z, 0-9, 6 characters
char *generate_matricula() {
    char *chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    char *matricula = malloc(7 * sizeof(char));
    for (int i = 0; i < 6; i++) matricula[i] = chars[rand() % strlen(chars)];
    matricula[6] = '\0';
    return matricula;
}

// generate a random_name : {"Joao Rodrigues", "Maria Antonia", "Antonio Miguel", "Ana Pereira", "Rui Gomes"};
char *generate_name() {
    char *names[] = {"Joao Rodrigues", "Maria Antonia", "Antonio Miguel", "Ana Pereira", "Rui Gomes"};
    return names[rand() % 5];
}

// generate a random_num : 1-5
int generate_num() {
    return rand() % 5 + 1;
}

// generate a random_infracao : {"Velocidade", "Estacionamento", "Transito", "Alcool", "Drogas"};
char *generate_infracao() {
    char *infracoes[] = {"Velocidade", "Estacionamento", "Transito", "Alcool", "Drogas"};
    return infracoes[rand() % 5];
}

void sortFile(int dim, int flag) {
    system("./main 0 1 < inp.txt > out.txt"); // 0 = without time, 1 = merge sort
    system("exec 1>&-"); // stop printing to out.txt
    FILE *fp = fopen(INPUT, "w");
    FILE *fp2 = fopen(OUTPUT, "r");
    // ignore first and last line
    char input[MAX];
    fgets(input, MAX, fp2);
    fprintf(fp, "DIM_BD %d\n", dim);
    while (fgets(input, MAX, fp2) != NULL) {
        if (strcmp(input, "FIM\n") == 0) break;
        fprintf(fp, "%s", input);
    }
    if (flag == 1) fprintf(fp, "CONSULTA_BD\n");
    fprintf(fp, "TCHAU\n");
    fclose(fp);
    fclose(fp2);
}

int main(int argc, char** argv) { // ./gerar <dim> <flag {0 = random, 1 = sorted, 2 = reversed}>
    int dim = atoi(argv[1]), flag = atoi(argv[2]);
    srand(time(NULL));

    FILE *fp = fopen(INPUT, "w");
    fprintf(fp, "DIM_BD %d\n", dim);
    for (int i = 0; i < dim; i++) fprintf(fp, "%s %s %d %s\n", generate_matricula(), generate_infracao(), generate_num(), generate_name());
    if (flag == 1 || flag == 2) {
        fprintf(fp, "CONSULTA_BD\n");
        FILE *fp2 = fopen(OUTPUT, "w");
        fclose(fp2);
    }
    fprintf(fp, "TCHAU\n");
    fclose(fp);

    if (flag == 1) { // sort
        sortFile(dim, 0);
    } else if (flag == 2) { // decrescente
        sortFile(dim, 1);

        system("./main 0 3 < inp.txt > out.txt"); // 0 = without time, 3 = reverse
        system("exec 1>&-"); // stop printing to out.txt
        FILE *fp = fopen(INPUT, "w");
        FILE *fp2 = fopen(OUTPUT, "r");
        // ignore first and last line
        char input[MAX];
        fgets(input, MAX, fp2);
        fprintf(fp, "DIM_BD %d\n", dim);
        while (fgets(input, MAX, fp2) != NULL) {
            if (strcmp(input, "FIM\n") == 0) break;
            fprintf(fp, "%s", input);
        }
        fprintf(fp, "TCHAU\n");
        fclose(fp);
        fclose(fp2);
    }
    return 0;
}