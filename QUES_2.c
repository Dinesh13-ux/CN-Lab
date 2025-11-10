#include <stdio.h>
#include <string.h>

// XOR Division
void xor_div(char* msg, const char* poly, int msg_len, int poly_len) {
    for (int i = 0; i <= msg_len - poly_len; i++) {
        if (msg[i] == '1') {
            for (int j = 0; j < poly_len; j++) {
                msg[i + j] = (msg[i + j] == poly[j]) ? '0' : '1';
            }
        }
    }
}

// Utility to compute CRC remainder
void compute_remainder(const char* msg, const char* poly, char* remainder) {
    int msg_len = strlen(msg);
    int poly_len = strlen(poly);
    char temp[200];

    strcpy(temp, msg);
    xor_div(temp, poly, msg_len, poly_len);

    strcpy(remainder, &temp[msg_len - (poly_len - 1)]);
}

// Sender: prepares message and calls receiver
void compute_crc(const char* msg, const char* poly, int isSender) {
    int msg_len = strlen(msg);
    int poly_len = strlen(poly);
    int total_len = msg_len + poly_len - 1;

    char data[200], remainder[50];
    strcpy(data, msg);
    memset(data + msg_len, '0', poly_len-1);
    data[total_len] = '\0';

    compute_remainder(data, poly, remainder);

    if (isSender) {
        printf("\nOriginal message: %s\n", msg);
        printf("Generator polynomial: %s\n", poly);
        printf("CRC remainder: %s\n", remainder);

        strcpy(&data[msg_len], remainder);
        printf("Transmitted message: %s\n\n", data);

        // Receiver check
        compute_crc(data, poly, 0);
    } else {
        printf("Received message: %s\n", msg);
        printf("Generator polynomial: %s\n", poly);
        printf("CRC remainder: %s\n", remainder);


        int error = 0;
        for (int i = 0; remainder[i] != '\0'; i++)
            if (remainder[i] != '0') error++;

        if (error == 0) {
            char original[200];
            strncpy(original, msg, msg_len - (poly_len - 1));
            original[msg_len - (poly_len - 1)] = '\0';
            printf("No error detected. Original message: %s\n\n", original);
        } else {
            printf("Error detected! Number of error bits = %d\n\n", error);
        }
    }
}

int main() {
    char msg[256];
    printf("Enter a message bit stream: ");
    scanf("%s", msg);

    const char* crc12 = "1100000001111";
    const char* crc16 = "11000000000000101";
    const char* crcCCIP = "10001000000100001";

    int choice;
    while (1) {
        printf("\nChoose CRC type:\n1. CRC-12\n2. CRC-16\n3. CRC-CCIP\n4. Exit\n");
        scanf("%d", &choice);

        if (choice == 1) compute_crc(msg, crc12, 1);
        else if (choice == 2) compute_crc(msg, crc16, 1);
        else if (choice == 3) compute_crc(msg, crcCCIP, 1);
        else break;
    }
}
