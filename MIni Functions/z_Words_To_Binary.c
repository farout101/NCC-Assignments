#include <stdio.h>
#include <string.h>

void wordToBinary(char *word) {
    printf("\n--Binary representation of '%s'--\n________________________________", word); for(int i = 0; word[i] != '\0'; i++) {printf("_");} printf("\n\n");
    for (int i = 0; word[i] != '\0'; i++) {
        char character = word[i];
        int ascii_code = (int)character;
        printf("Character '%c': ASCII code %d, Binary: ", character, ascii_code);
        for (int j = 7; j >= 0; j--) {
            printf("%d", (ascii_code >> j) & 1);
        }
        printf("\n");
    }
}

int main() {
    char word[50];

    printf("Enter a word: ");
    fgets(word, sizeof(word), stdin);

    word[strcspn(word, "\n")] = '\0'; // Remove the new line

    wordToBinary(word);
    
    return 0;
}
