#include <stdio.h>
#include <math.h>

#define HEADER_SIZE 10   // IP header size
#define MTU 20           // Path MTU to force fragmentation

int main() {
    int pkt_size = 30; // total packet (header + data)
    int data_size = pkt_size - HEADER_SIZE;

    int max_data_per_frag = MTU - HEADER_SIZE;

    // Make fragment data size a multiple of 8 bytes (IP requirement)
    int frag_data_size = (max_data_per_frag / 8) * 8;

    // Calculate number of fragments needed
    int num_frags = (int)ceil((double)data_size / frag_data_size);

    printf("Packet Size: %d bytes (Data: %d bytes)\n", pkt_size, data_size);
    printf("MTU: %d bytes | Fragment Data Size: %d bytes\n\n", MTU, frag_data_size);

    // ---------- Fragmentation ----------
    printf("Fragmentation \n");
    printf("Frag#\tOffset\tFragment Size\tMF\n");

    int offset = 0;
    int remaining = data_size;

    for (int i = 0; i < num_frags; i++) {
        int len = (remaining > frag_data_size) ? frag_data_size : remaining;
        int MF = (i == num_frags - 1) ? 0 : 1;
        int total_frag_size = len + HEADER_SIZE;

        printf("%d\t%d\t%d\t\t%d\n", i + 1, offset / 8, total_frag_size, MF);

        offset += len;
        remaining -= len;
    }

    // ---------- Reassembly ----------
    printf("\nReassembly (Defragmentation):\n");
    offset = 0;
    remaining = data_size;

    printf("Frag#\tOffset\tFragment Size\n");
    for (int i = 0; i < num_frags; i++) {
        int len = (remaining > frag_data_size) ? frag_data_size : remaining;
        int total_frag_size = len + HEADER_SIZE;
        printf("%d\t%d\t%d\n", i + 1, offset / 8, total_frag_size);
        offset += len;
        remaining -= len;
    }

    printf("\nReassembled Data Size: %d bytes\n", data_size);
    printf("Reassembly successful!\n");

    return 0;
}
