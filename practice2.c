#include<stdio.h>
#include<math.h>
int main(){
    // int bucket_size,leak_rate;
    // printf("Enter Bucket Size and Leak Rate: ");
    // scanf("%d%d",&bucket_size,&leak_rate);

    // int packets_arrival[] = {5,7,3,4,2};
    // int packets_in = 0;
    // int bucket = 0;

    // printf("Time\t   Incoming\tbucket before\tbucket after\tpackets sent\t\tstatus\n");
    // for (int i = 0; i < 5; i++){
    //     packets_in = packets_arrival[i];
    //     int bkt_before = bucket;
    //     int status = 0;

    //     if (bucket + packets_in <= bucket_size)
    //     {
    //         bucket += packets_in;
    //     }else{
    //         status = 1;
    //         bucket =bucket_size;
    //     }
        
    //     int bkt_after = bucket;

    //     int packets_sent = (bucket < leak_rate)? bucket: leak_rate;
    //     bucket -= packets_sent;

    //     printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%s\n",
    //         i+1,packets_in,bkt_before,bkt_after,packets_sent,status? "Overflow":"OK"
    //     );
    // }

    int pkt_size,MTU;
    printf("Enter packet size and path MTU: ");
    scanf("%d%d",&pkt_size,&MTU);
    int header = 20;
    int data_size = pkt_size - 20;
    int max_data_frag = MTU - header;
    int frag_data_size = (max_data_frag/8)*8;
    int num_frags = (int)ceil((double)data_size/frag_data_size);

    int offset = 0,remaining = data_size;
    printf("Frag#\tFrag Size\toffset\tMF\n");

    int frag_size[num_frags];

    for (int i = 0; i < num_frags; i++)
    {
        int len = (remaining >frag_data_size)? frag_data_size : remaining;
        int MF = (i == num_frags - 1)? 0 : 1;
        int total_frag_data_size = len + header;

        frag_size[i] = total_frag_data_size;

        printf("%d\t%d\t\t%d\t%d\n",i+1,total_frag_data_size,offset/8,MF);

        offset += len;
        remaining -= len;
    }
    
    printf("Reaasembly: \n");
    int reassembled_data = 0;
    for (int i = 0; i < num_frags; i++){
        reassembled_data += frag_size[i] - header;
    }
    printf("Total Reassembled data = %d\n",reassembled_data);   
}