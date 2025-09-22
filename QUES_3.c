#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define TOTAL_FRAMES 3
#define WINDOW_SIZE 2    
#define LOSS_PROB 20 

int sender = 0;
int receiver = 0;

int isLost() {
    return (rand() % 100) < LOSS_PROB;
}

void Transmit() {
    int ack;
    while (receiver < TOTAL_FRAMES) {
        int window_end = sender + WINDOW_SIZE;

        for (int i = sender; i < window_end && i < TOTAL_FRAMES; i++) {
            printf("Sender: Sending Frame %d\n", i);

            if (!isLost()) {
                printf("Receiver: Frame %d received correctly\n", i);
                receiver = i + 1;
                ack = receiver;

                if (!isLost()) {
                    printf("Sender: ACK %d received\n", ack);
                    sender = ack; 
                } else {
                    printf("Sender: ACK %d lost\n", ack);
                    printf("Sender: Timeout! Resending from Frame %d\n", sender);
                    break; 
                }

            } else {
                printf("Frame %d lost during transmission!\n", i);
                printf("Sender: Timeout! Resending from Frame %d\n", sender);
                break;
            }
        }
        sleep(0.5); 
    }
    printf("\nAll frames transmitted successfully\n");
}

int main() {
    srand(time(NULL));
    printf("Go-Back-N Sliding Window Protocol\n");
    printf("Total Frames: %d | Window Size: %d | Loss Probability: %d%%\n\n",
           TOTAL_FRAMES, WINDOW_SIZE, LOSS_PROB);

    Transmit();
    return 0;
}