#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000

char* base64Encoder(char input_str[], int len_str);
char* base64Decoder(char input_str[], int len_str);

int main() {
    char input_str[SIZE];
    int len_str;

    printf("Enter the input string: ");
    fgets(input_str, SIZE, stdin);

    // Removing trailing newline character
    input_str[strcspn(input_str, "\n")] = '\0';

    len_str = strlen(input_str);

    printf("Input string is : %s\n", input_str);
    
    char* encoded_str = base64Encoder(input_str, len_str);
    printf("Encoded string is : %s\n", encoded_str);

    char* decoded_str = base64Decoder(encoded_str, strlen(encoded_str));
    printf("Decoded string is : %s\n", decoded_str);

    free(encoded_str);
    free(decoded_str);

    return 0;
}

char* base64Encoder(char input_str[], int len_str) {
    char char_set[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    char *res_str = (char *) malloc(SIZE * sizeof(char));
    int index, no_of_bits = 0, padding = 0, val = 0, count = 0, temp;
    int i, j, k = 0;

    for (i = 0; i < len_str; i += 3) {
        val = 0, count = 0, no_of_bits = 0;

        for (j = i; j < len_str && j <= i + 2; j++) {
            val = val << 8;
            val = val | input_str[j];
            count++;
        }

        no_of_bits = count * 8;
        padding = no_of_bits % 3;

        while (no_of_bits != 0) {
            if (no_of_bits >= 6) {
                temp = no_of_bits - 6;
                index = (val >> temp) & 63;
                no_of_bits -= 6;
            } else {
                temp = 6 - no_of_bits;
                index = (val << temp) & 63;
                no_of_bits = 0;
            }
            res_str[k++] = char_set[index];
        }
    }

    for (i = 1; i <= padding; i++) {
        res_str[k++] = '=';
    }

    res_str[k] = '\0';

    return res_str;
}

char* base64Decoder(char input_str[], int len_str) {
    char char_set[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int char_index[256];

    // Initialize the char_index array
    for (int i = 0; i < 256; ++i) {
        char_index[i] = -1;
    }

    // Populate the char_index array with the Base64 character set
    for (int i = 0; i < 64; ++i) {
        char_index[char_set[i]] = i;
    }

    char *res_str = (char *) malloc(SIZE * sizeof(char));
    int val = 0, count = 0, temp;
    int i, j, k = 0;

    for (i = 0; i < len_str; ++i) {
        if (input_str[i] == '=') {
            break;  // Padding character, stop decoding
        }

        if (char_index[input_str[i]] == -1) {
            continue;  // Skip characters not in the Base64 set
        }

        val = (val << 6) | char_index[input_str[i]];
        count++;

        if (count == 4) {
            for (j = 2; j >= 0; --j) {
                if (input_str[i - j] != '=') {
                    temp = (val >> (8 * j)) & 255;
                    res_str[k++] = temp;
                }
            }
            val = 0;
            count = 0;
        }
    }

    // Handle remaining bits
    for (j = 2; j >= 0 && count > 1; --j) {
        if (input_str[i - j] != '=') {
            temp = (val >> (8 * j)) & 255;
            res_str[k++] = temp;
        }
    }

    res_str[k] = '\0';

    return res_str;
}
