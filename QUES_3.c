#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>

#define W_SIZE 3
#define Frames 5
#define loss_prob 20

int sender = 0;
int receiver = 0;


bool is_lost(int frame){
    return (rand() % 100 <  loss_prob);
}

void send_frame(int frame){
    printf("Sender: Sending Frame %d\n",frame);
}

void resend_window(){
    printf("Resending Window...\n");
    for(int i=sender;i<receiver;i++){
        send_frame(i);
    }
}

int main(){

srand(time(NULL));

while(sender<Frames){

    while(receiver<sender+W_SIZE && receiver<Frames){
        send_frame(receiver);
        receiver++;
    }
    for(int i=sender;i<receiver;i++){
        if(is_lost(i)){
            printf("Error : Frame %d or ACK of %d lost!!\n",i,i);
            resend_window();
            break;
        }else{
            printf("ACK recieved for frame %d\n",i);
            sender++;
        }
    }
}

printf("All frames sent successfully");
    return 0;
}