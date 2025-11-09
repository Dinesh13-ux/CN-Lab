#include <stdio.h>
#include <math.h>

#define HEADER_SIZE 20   

int main() {
    int pkt_size, MTU;


    printf("Enter total IP packet size (bytes): ");
    scanf("%d", &pkt_size);

    printf("Enter MTU size (bytes): ");
    scanf("%d", &MTU);

    if (pkt_size <= HEADER_SIZE) {
        printf("Invalid packet size! Must be greater than header size (%d bytes).\n", HEADER_SIZE);
        return 0;
    }

    if (MTU <= HEADER_SIZE) {
        printf("Invalid MTU! Must be greater than header size (%d bytes).\n", HEADER_SIZE);
        return 0;
    }

    int data_size = pkt_size - HEADER_SIZE;            // Actual data size
    int max_data_per_frag = MTU - HEADER_SIZE;         // Max data per fragment
    int frag_data_size = (max_data_per_frag / 8) * 8;  // Must be multiple of 8 bytes (IP rule)

    if (frag_data_size == 0) frag_data_size = 8;       // Minimum 8 bytes (IP rule)

    int num_frags = (int)ceil((double)data_size / frag_data_size);

    printf("Fragmentation Table:\n");
    printf("Frag#\tOffset(8B)\tFrag Size\tMF\n");

    int offset = 0;
    int remaining = data_size;

    int frag_offsets[num_frags];
    int frag_sizes[num_frags];
    int MF_flags[num_frags];

    for (int i = 0; i < num_frags; i++) {
        int len = (remaining > frag_data_size) ? frag_data_size : remaining;
        int MF = (i == num_frags - 1) ? 0 : 1;       // More Fragments flag
        int total_frag_size = len + HEADER_SIZE;      // Header + data

        frag_offsets[i] = offset / 8;  // Convert to 8-byte unit
        frag_sizes[i] = total_frag_size;
        MF_flags[i] = MF;

        printf("%d\t%d\t\t%d\t\t%d\n", i + 1, frag_offsets[i], total_frag_size, MF);

        offset += len;
        remaining -= len;
    }

    printf("\nReassembly (Defragmentation\n");

    int total_reassembled_data = 0;
    for (int i = 0; i < num_frags; i++) {
        total_reassembled_data += frag_sizes[i] - HEADER_SIZE; // Only data portion
    }

    printf("Total Fragments Received: %d\n", num_frags);
    printf("Total Reassembled Data: %d bytes\n", total_reassembled_data);

    if (total_reassembled_data == data_size) {
        printf("Reassembly successful! \n");
    } else {
        printf("Reassembly failed! (data mismatch)\n");
    }

    return 0;
}
