#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define TOTAL_FRAMES 7
#define WINDOW_SIZE 3
#define LOSS_PROB 20 // % chance of loss

int sender = 0; // first frame in the window
int next_frame_to_send = 0;
int receiver = 0;

int isLost() {
    return (rand() % 100) < LOSS_PROB;
}

void printWindow() {
    printf("Sender Window: [");
    for (int i = sender; i < sender + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
        printf(" %d ", i);
    }
    printf("]\n");
}

void Transmit() {
    while (sender < TOTAL_FRAMES) {
        printf("\n--- Transmission Round ---\n");
        printWindow();


        int frame_lost = -1;
        for (int i = sender; i < sender + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
            if (isLost()) {
                printf("Receiver: Frame %d lost!\n", i);
                frame_lost = i;
                break;
            } else {
                printf("Receiver: Frame %d received correctly\n", i);
                receiver = i + 1;
            }
        }

        // ACK handling
        if (frame_lost != -1) {
            printf("Receiver: Cannot send ACK (Frame %d lost)\n", frame_lost);
            printf("Timeout! Sender resending from Frame %d\n", sender);
            sleep(1);
            continue; 
        } else {
            // Simulate ACK loss
            if (isLost()) {
                printf("ACK for Frame %d lost!\n", receiver - 1);
                printf("Timeout! Sender resending from Frame %d\n", sender);
                sleep(1);
                continue;
            } else {
                printf("Sender: ACK %d received\n", receiver);
                sender = receiver; // Slide the window
            }
        }

        sleep(1); // Simulate delay
    }

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
