#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readFile(char * filePath) {
    FILE* file;
    file = fopen(filePath, "r");
    char line[50];
    char attributes[][30] = {"codigo_ibge", "nome", "latitude",
                             "longitude", "capital", "codigo_uf",
                             "siafi_id", "ddd", "fuso_horario"};

    if(file == NULL) {
        printf("Não foi possível abrir o arquivo");
    } else {
        int codigo_ibge, capital, codigo_uf, siafi_id, ddd;
        float latitude, longitude; 
        char nome[50], fuso_horario[20], fuso_horario2[30];

        while(fgets(line, 50, file) != NULL) {
            if(strstr(line, attributes[0]) != NULL) {
                sscanf(line, "%*s %d", &codigo_ibge);
                printf("%d\n", codigo_ibge);
            } else if(strstr(line, attributes[1]) != NULL) {
                sscanf(line, "%*s \"%[^\"]", nome);
                printf("%s\n", nome);
            } else if(strstr(line, attributes[2]) != NULL) {
                sscanf(line, "%*s %f", &latitude);
                printf("%f\n", latitude);
            } else if(strstr(line, attributes[3]) != NULL) {
                sscanf(line, "%*s %f", &longitude);
                printf("%f\n", longitude);
            } else if(strstr(line, attributes[4]) != NULL) {
                sscanf(line, "%*s %d", &capital);
                printf("%d\n", capital);
            } else if(strstr(line, attributes[5]) != NULL) {
                sscanf(line, "%*s %d", &codigo_uf);
                printf("%d\n", codigo_uf);
            } else if(strstr(line, attributes[6]) != NULL) {
                sscanf(line, "%*s %d", &siafi_id);
                printf("%d\n", siafi_id);
            } else if(strstr(line, attributes[7]) != NULL) {
                sscanf(line, "%*s %d", &ddd);
                printf("%d\n", ddd);
            } else if(strstr(line, attributes[8]) != NULL) {
                sscanf(line, "%*s \"America\\%[^\"]", fuso_horario2);
                strcpy(fuso_horario, "America");
                strcat(fuso_horario, fuso_horario2);
                printf("%s\n", fuso_horario);
            }
        }
    }

    fclose(file);
}

int main() {
    readFile("municipios.json");
    return EXIT_SUCCESS;  
} 