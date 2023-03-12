#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int main(int argc, char* argv[]) {
    srand(time(NULL));
    int dim = atoi(argv[1]);
    printf("DIM_BD %d\n", dim);
    for (int i = 0; i < dim; i++) printf("%s %s %d %s\n", generate_matricula(), generate_infracao(), generate_num(), generate_name());
    printf("TCHAU");
    return 0;
}