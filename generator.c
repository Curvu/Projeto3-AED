#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INPUT "input.txt"
#define OUTPUT "output.txt"
#define MAX 100

// detect if is linux or windows
#ifdef _WIN32
    #define OS 0
#else
    #define OS 1
#endif

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
    char command[100];
    if (OS) { // linux
        sprintf(command, "./main 0 1 < %s > %s", INPUT, OUTPUT);
        system(command); // 0 = without time, 1 = merge sort
        system("exec 1>&-"); // stop printing to out.txt
    } else { // windows
        sprintf(command, "Get-Content %s | ./main 0 1 > %s", INPUT, OUTPUT); // 0 = without time, 1 = merge sort
        system(command);
    }
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

        char command[100];
        if (OS) { // linux
            sprintf(command, "./main 0 3 < %s > %s", INPUT, OUTPUT);
            system(command); // 0 = without time, 3 = reverse
            system("exec 1>&-"); // stop printing to out.txt
        } else { // windows
            sprintf(command, "Get-Content %s | ./main 0 3 > %s", INPUT, OUTPUT);
            system(command); // 0 = without time, 3 = reverse
        }

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