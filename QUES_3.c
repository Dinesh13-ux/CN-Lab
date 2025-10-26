#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define TOTAL_FRAMES 7
#define WINDOW_SIZE 3
#define LOSS_PROB 20

int sender = 0;
int receiver = 0;

int isLost() {
    return (rand() % 100) < LOSS_PROB;
}

void Transmit() {
    while (sender < TOTAL_FRAMES) {
        printf("\n--- Sending Window ---\n");

        int window_end = sender + WINDOW_SIZE;
        for (int i = sender; i < window_end && i < TOTAL_FRAMES; i++) {
            printf("Sender: Sending Frame %d\n", i);

            if (isLost()) {
                printf("Frame %d lost during transmission!\n", i);
                printf("Timeout! Resending from Frame %d\n", sender);
                break;
            } else {
                printf("Receiver: Frame %d received correctly\n", i);
                receiver = i + 1;

                if (isLost()) {
                    printf("ACK %d lost!\n", receiver);
                    printf("Resending from Frame %d\n", sender);
                    break;
                } else {
                    printf("Sender: ACK %d received\n", receiver);
                    sender = receiver; // slide the window
                }
            }
        }

        sleep(1); // 1 sec delay
    }
    printf("Receiver : %d",receiver);
    printf("\nAll frames transmitted successfully!\n");
}

int main() {
    srand(time(NULL));
    printf("Go-Back-N Sliding Window Protocol Simulation\n");
    printf("Total Frames: %d | Window Size: %d | Loss Probability: %d%%\n\n",
           TOTAL_FRAMES, WINDOW_SIZE, LOSS_PROB);

    Transmit();
    return 0;
}
