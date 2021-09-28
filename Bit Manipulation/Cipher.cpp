#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void decrypt(unsigned char *enc, int plain_text_length, int shift_count) {
    int dec[plain_text_length];

    dec[0] = enc[0] - '0';

    /*
     * hackerrank.com/whorahul
     */
    for (int i = 1; i < shift_count; i++) {
        dec[i] = (enc[i] - '0') ^ (enc[i - 1] - '0');
    }

    for (int i = shift_count; i < plain_text_length; i++) {
        dec[i] = (enc[i] - '0') ^ (enc[i - 1] - '0') ^ dec[i - shift_count];
    }

    for (int i = 0; i < plain_text_length; i++) {
        printf("%d", dec[i]);
    }
}


int main() {
    int N;
    int K;

    scanf("%d", &N);
    scanf("%d", &K);
    unsigned char encrypted_data[N + K];

    scanf("%s", encrypted_data);
    decrypt(encrypted_data, N, K);

    return 0;
}
