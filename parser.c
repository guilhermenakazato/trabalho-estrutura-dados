#include <stdio.h>
#include <stdlib.h>

void readFile(char * filePath) {
    FILE* file;
    file = fopen(filePath, "r");
    char ch;
    char *aux;
    char attributes[][20] = {"codigoibge", ""};

    if(file == NULL) {
        printf("Não foi possível abrir o arquivo");
    } else {
        do {
            ch = fgetc(file);
            
            if(ch >= 45 && ch <= 57
            || ch >= 65 && ch <= 90
            || ch >= 97 && ch <= 122
            || ch < 0 || ch == 10 || ch == 32 || ch == 95
            )   
                printf("%c", ch);
        } while(ch != EOF);
    }

    fclose(file);
}

int main() {
    readFile("municipios.json");
    return EXIT_SUCCESS;
}