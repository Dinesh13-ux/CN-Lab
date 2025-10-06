#include <stdio.h>
int main() {
    int bucket_size;
    int leak_rate;
    int bucket = 0;
    int packets_in = 0;
    int i;
    printf("Enter Bucket Size and Leak rate\n");
    scanf("%d%d",&bucket_size,&leak_rate);
    printf("Leaky Bucket Algorithm Simulation\n");

    int packets_arrival[5] = {5, 7, 3, 4, 2};

    printf("Time\tIncoming\tBucket Before\tBucket After\tPackets Sent\tStatus\n");

   for(i = 0; i < 5; i++) {
    packets_in = packets_arrival[i];
    int bucket_before = bucket;
    int status = 0;  // 0 = OK, 1 = Overflow

    if(bucket + packets_in <= bucket_size) {
        bucket += packets_in;
    } else {
        status = 1;
        bucket = bucket_size; 
    }

    int bucket_after_arrival = bucket;

    int packets_sent = (bucket < leak_rate) ? bucket : leak_rate;
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
