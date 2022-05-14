#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>


void swap(int *p, int *q) {
    /* pg. 255 Q4 */
    int temp = *p;
    *p = *q;
    *q = temp;
}


void palindrome() {
    /* pg. 275 Q2 */
    printf("Enter a message: ");
    const char message[30];
    scanf("%[^\n]", message);

    int i = 0;
    int k = 0;
    char copy[30];
    while (message[i] != '\0') {
        if (ispunct(message[i]) == 0 && isspace(message[i]) == 0) {
            copy[k] = toupper(message[i]);
            k++;
        }
        i++;
    }

    copy[i] = '\0';
    int half_message = (int) k/2;

    for (int j = 0; j < half_message; j++) {
        if (copy[j] != copy[k - 1 - j]) {
            printf("This message is not a palindrome");
            return;
        }
    }

    printf("This message is a palindrome");
    return;
}

bool palindrome_ptr(const char *message_ptr) {
    /* pg. 313 Q17 */
    int i = 0;
    int k = 0;
    char copy[30];
    char message[30];
    strcpy(message, message_ptr);
    while (message[i] != '\0') {
        if (ispunct(message[i]) == 0 && isspace(message[i]) == 0) {
            copy[k] = toupper(message[i]);
            k++;
        }
        i++;
    }

    copy[i] = '\0';
    int half_message = (int) k/2;

    for (int j = 0; j < half_message; j++) {
        if (copy[j] != copy[k - 1 - j]) {
            return false;
        }
    }

    return true;
}


void toUpper() {
    /* pg. 584 Q2 */
    printf("What file would you like to convert? ");
    const char file_name[30];
    scanf("%[^\n]", file_name);

    FILE *fptr;

    fptr = fopen(file_name, "r+");

    if (fptr == NULL) {
        printf("Not a valid file name \n");
        return;
    }

    char *file_txt = (char *)malloc(50*sizeof(char));
    fscanf(fptr, "%[^\n]", file_txt);

    int i = 0;
    char copy[30];

    while (*(file_txt+i) != '\0') {

        char temp = *(file_txt+i);

        if (ispunct(temp) == 0 && isspace(temp) == 0) {
            copy[i] = toupper(temp);
        }
        else {
            copy[i] = temp;
        }
        
        i++;
    }

    copy[i] = '\0';

    printf( "%s\n", copy);

    return;
}


int main() {

    /* Q4
    int test1 = 9;
    int test2 = 5;

    int *test1_ptr = &test1;
    int *test2_ptr = &test2;
    swap(test1_ptr, test2_ptr);

    printf("%d\n", *test1_ptr);
    printf("%d\n", *test2_ptr);
    */

    /*
    char message[30] = "He lived as a devil, eh?";
    bool temp = palindrome_ptr(message);

    if (temp) {
        printf("This message is a palindrome");
    }
    else {
        printf("This message is not a palindrome");
    }
    */

    toUpper();
    

    return 0;
}