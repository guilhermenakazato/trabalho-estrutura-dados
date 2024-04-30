#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>

int readFile(char * filePath) {
    FILE* file;
    file = fopen(filePath, "r");
    wchar_t ch;

    if(file == NULL) {
        printf("Não foi possível abrir o arquivo");
    } else {
        int brokeLine = 0;
        int shouldSplit = 1;
        int printedCharBefore = 0;
        int counter = 1;

        while(ch != EOF) {
            ch = fgetwc(file);
            
            if(ch >= 45 && ch <= 57
            || ch >= 65 && ch <= 90
            || ch >= 95 && ch <= 122
            || ch >= 192 && ch <= 250) {
                brokeLine = 0;      
                printedCharBefore = 1;     

                if(counter % 2 == 0)
                    printf("%lc", ch);
            }

            if(ch == 32) {
                if(shouldSplit && !brokeLine) {
                    counter++;
                    shouldSplit = 0;
                } else if(!brokeLine && !shouldSplit) {
                    printf("%c", ch);
                }
            }

            if(ch == 10) {
                if(printedCharBefore) { 
                    printf("%c", ch);
                    counter++;
                }

                brokeLine = 1;
                shouldSplit = 1;
                printedCharBefore = 0;
            }
        }
    }

    fclose(file);
}

int main() {
    setlocale(LC_CTYPE, "");
    readFile("municipios.json");
    return EXIT_SUCCESS;
} 