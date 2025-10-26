#include <stdio.h>
#include <string.h>
#include <math.h>

#define HEADER_SIZE 10   // Simulated IP header
#define MTU 20           // Example MTU to force fragmentation

int main() {
    char data[] = "This is a test message.";
    int total_len = strlen(data);
    int data_size = total_len;

    int max_data_per_frag = MTU - HEADER_SIZE;

    // Make fragment data size a multiple of 8 bytes (IP rule)
    int frag_data_size = (max_data_per_frag / 8) * 8;

    // Compute number of fragments needed
    int num_frags = (int)ceil((double)data_size / frag_data_size);

    printf("Original Data (%d bytes):\n%s\n\n", total_len, data);

    // ---------- Fragmentation ----------
    printf("Fragmentation (8-byte aligned):\n");
    printf("Frag#\tOffset\tLength\tMF\tData\n");

    int offset = 0; // in bytes
    for (int i = 0; i < num_frags; i++) {
        int len = (data_size - offset > frag_data_size) ? frag_data_size : data_size - offset;
        int MF = (i == num_frags - 1) ? 0 : 1; // more fragments flag

        // Print details (offset shown in 8-byte units)
        printf("%d\t%d\t%d\t%d\t\"", i + 1, offset / 8, len, MF);

        for (int j = 0; j < len; j++)
            putchar(data[offset + j]);
        printf("\"\n");

        offset += len;
    }

    // ---------- Reassembly ----------
    printf("\nReassembly (Defragmentation):\n");
    char reassembled[512] = "";
    offset = 0;

    printf("Frag#\tOffset\tLength\n");
    for (int i = 0; i < num_frags; i++) {
        int len = (data_size - offset > frag_data_size) ? frag_data_size : data_size - offset;
        strncat(reassembled, data + offset, len);
        printf("%d\t%d\t%d\n",i + 1, offset / 8, len);
        offset += len;
    }

    printf("\nReassembled Data (%ld bytes):\n%s\n", strlen(reassembled), reassembled);

    return 0;
}
