#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void file_insert(char *file_name) {

    FILE *fp = fopen(file_name, "a+");
    char input[100];
    char input2[100];
    char c;

    // fscanf(stdin, "%[^\n]", input);   doesn't naturally read spaces
    c = fgetc(stdin);  // doesn't read escape characters, added a newline naturally
                               // will add a \0 to the end of the string before storing (scanf does too)
    fgets(input2, 100, fp);
    //input[strcspn(input, "\n")] = 0;

    /*
    for (int i = 0; i<100; i++) {
        if (input[i] == '\n') {
            printf("\nadded newline\n");
            if (input[i+1] == '\0') {
                printf("reached null terminator\n");
            }
            break;
        }
        printf("%c", input[i]);
    }
    printf("\n");
    */

    printf("%s", input);
    printf("%s", input2);
    int shit = fclose(fp);
    printf("%d", shit);

    FILE *p = fopen(file_name, "a");

    char *test = "fuck me in the ass c sucks so bad\n";

    int check;
    // check = fprintf(fp, "%s", input);
    check = fputc(c, fp);  // literally works the exact same as fprintf
    printf("%d", check);

    int fuck = fclose(p);
    printf("%d", fuck);

    return;

    /* Issues:
        - why add newline from keyboard and how stop
        - why fgets glitches with \n at end
    */
}


void file_retrieve(char *file_name) {
    return;
}


void clear_file() {
    return;
}


int main() {

    /* Goal:
        - Open file
        - Put things in
            - Use fprintf
            - Use fputc and fputs
        - Take things out
            - Use fscanf
            - Use fgetc and fgets
            - Use getline
        - Close file

        - Practice taking input from keyboard
    */

    char *file_name = "test.txt";

    file_insert(file_name);

    return 0;
}