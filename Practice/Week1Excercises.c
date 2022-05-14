/* 
Page 123 Q# 6.6, 6.11, 6.12
Page 177 Q# 6
Page 180-181 Q# 15, 16
*/

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

void sixpointsix() {

    int n;
    scanf("%d", &n);

    for (int i = 2; i < n+1; i++) {
        if (floorf(pow(i, 0.5)) == pow(i, 0.5) && i % 2 == 0) {
            printf("%d\n", i);
        }
    }

    return;
}


double factorial(int i) {
    if (i == 0) {
        return 1.0;
    }

    int product = 1;
    for (int j=1; j<=i; j++) {
        product *= j;
    }

    return product;
}


double sixpointeleven() {

    int n;
    scanf("%d", &n);

    double sum = 0.0;
    
    for (int i = 0; i <= n; i++) {
        double fact = factorial(i);
        sum += 1 / fact;
    }

    return sum;
}


double sixpointtwelve() {

    double e;
    scanf("%lf", &e);

    double sum = 1.0;
    int counter = 1;

    while (1) {
        double fact = factorial(counter);

        if (1/fact < e) {
            printf("%lf\n", 1/fact);
            return sum;
        }

        sum += 1/fact;
        counter++; 
    }
    
}


void eightpointsix() {
    const char message[30];
    scanf("%[^\n]", message);

    for (int i = 0; i < strlen(message); i++) {

        char temp = message[i];

        if (isalpha(temp) != 0) {
            temp = toupper(temp);

            if (temp == 'A') {
                temp = '4';
            }
            else if (temp == 'B') {
                temp = '8';
            }
            else if (temp == 'E') {
                temp = '3';
            }
            else if (temp == 'I') {
                temp = '1';
            }
            else if (temp == 'O') {
                temp = '0';
            }
            else if (temp == 'S') {
                temp = '5';
            }
        }

        printf("%c", temp);
    }

    printf("!!!!!!!\n");
}


void eightpointfifteen() {
    const char message[80];
    printf("Enter message to be encrypted: ");
    scanf("%[^\n]", message);

    int n;
    printf("Enter shift amount (1-25): ");
    scanf("%d", &n);

    printf("Encrypted message: ");

    for (int i=0; i<strlen(message); i++) {

        char temp = message[i];

        if (isalpha(temp)) {
            
            if (isupper(temp)) {
                temp = ((temp - 'A') + n) % 26 + 'A';
            }
            else {
                temp = toupper(temp);
                temp = ((temp - 'A') + n) % 26 + 'A';
                temp = tolower(temp);
            }

        } 

        printf("%c", temp);

    }

    return;

}


void eightpointsixteen() {
    const char word_one[30];
    printf("Enter the first word: ");
    scanf("%s", word_one);

    const char word_two[30];
    printf("Enter the second word: ");
    scanf("%s", word_two);

    int letters[26] = {0};

    for (int i=0; i < strlen(word_one); i++) {

        char temp = word_one[i];

        if (isalpha(temp)) {
            temp = tolower(temp);

            letters[((int) temp) - 97] += 1;
        }
    }

    for (int i=0; i < strlen(word_two); i++) {

        char temp = word_two[i];

        if (isalpha(temp)) {
            temp = tolower(temp);

            letters[((int) temp) - 97] -= 1;
        }
    }

    for (int i=0; i < sizeof(letters)/sizeof(int); i++) {
        printf("%d %d\n", letters[i], i);

        if (letters[i] != 0) {
            printf("Not an anagram");
            return;
        }
    }

    printf("Anagram");
    return;
}


int main() {

    eightpointsixteen();

    return 0;
}