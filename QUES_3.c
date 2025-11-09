#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>

#define W_SIZE 3
#define Frames 5
#define loss_prob 20

int base = 0;
int nextseqnum = 0;


bool is_lost(int frame){
    return (rand() % 100 <  loss_prob);
}

void send_frame(int frame){
    printf("Sender: Sending Frame %d\n",frame);
}

void resend_window(){
    printf("Resending Window...\n");
    for(int i=base;i<nextseqnum;i++){
        send_frame(i);
    }
}

int main(){

srand(time(NULL));

while(base<Frames){

    while(nextseqnum<base+W_SIZE && nextseqnum<Frames){
        send_frame(nextseqnum);
        nextseqnum++;
    }
    for(int i=base;i<nextseqnum;i++){
        if(is_lost(i)){
            printf("Error : Frame %d or ACK of %d lost!!\n",i,i);
            resend_window();
            break;
        }else{
            printf("ACK recieved for frame %d\n",i);
            base++;
        }
    }
}

printf("All frames sent successfully");
    return 0;
}