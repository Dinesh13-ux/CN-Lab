#include <stdio.h>

#define BUCKET_SIZE 10
#define LEAK_RATE 2    

int main() {
    int bucket = 0;
    int packets_in = 0;
    int i;

    printf("Leaky Bucket Algorithm Simulation\n");
    printf("Bucket size: %d, Leak rate: %d packets/time unit\n\n", BUCKET_SIZE, LEAK_RATE);

    int packets_arrival[5] = {5, 7, 3, 4, 2};

    printf("Time\tIncoming\tBucket Before\tBucket After\tPackets Sent\tStatus\n");

   for(i = 0; i < 5; i++) {
    packets_in = packets_arrival[i];
    int bucket_before = bucket;
    int status = 0;  // 0 = OK, 1 = Overflow

    if(bucket + packets_in <= BUCKET_SIZE) {
        bucket += packets_in;
    } else {
        status = 1;
        bucket = BUCKET_SIZE; 
    }

    int bucket_after_arrival = bucket;

    int packets_sent = (bucket < LEAK_RATE) ? bucket : LEAK_RATE;
    bucket -= packets_sent;

    printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%s\n", 
        i+1, 
        packets_in, 
        bucket_before, 
        bucket_after_arrival, 
        packets_sent, 
        status ? "Overflow!" : "OK");
}
    return 0;
}
