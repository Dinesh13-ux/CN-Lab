#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define LOSS_PROB 20
#define FRAMES 5
#define WINDOW_SIZE 3

void xorDiv(char* msg,const char* poly, int msg_len, int poly_len){
    for (int i = 0; i <= msg_len - poly_len; i++){
       if(msg[i] == '1'){
            for (int j = 0; j < poly_len; j++){
                msg[i+j] = (msg[i+j] == poly[j])? '0' : '1';
            }
       }
    }
}

void compute_remainder(const char* msg, const char* poly, char* remainder){
    int msg_len = strlen(msg);
    int poly_len = strlen(poly);
    char temp[256];

    strcpy(temp,msg);
    xorDiv(temp,poly,msg_len,poly_len);

    strcpy(remainder, &temp[msg_len - (poly_len - 1)]);

}

void computeCRC(const char* msg, const char* poly, int isSender){
    int msg_len = strlen(msg);
    int poly_len = strlen(poly);
    int total_len = msg_len + poly_len -1;
    char data[256], remainder[128];
    strcpy(data,msg);
    memset(data + msg_len, '0', poly_len - 1);
    data[total_len] = '\0';

    compute_remainder(data,poly,remainder);

    if (isSender){
        printf("\nOriginal message: %s\n", msg);
        printf("Generator polynomial: %s\n", poly);
        printf("CRC remainder: %s\n", remainder);

        strcpy(&data[msg_len],remainder);

        
        printf("Transmitted message: %s\n\n", data);
        computeCRC(data,poly,0);
    }else{
        printf("Received message: %s\n", msg);
        printf("Generator polynomial: %s\n", poly);
        printf("CRC remainder: %s\n", remainder);

        int error = 0;
        for (int i = 0; remainder[i] != '\0' ; i++){
            if(remainder[i] != '0') error++;
        }

        if (error==0){
            char original[256];
            strncpy(original,msg,msg_len -(poly_len - 1));
            original[msg_len - (poly_len - 1)] = '\0';
            printf("\nOriginal Message: %s\n",original);
        }else{
            printf("\nError %d\n",error);
        }
        
        
    }
    

}





void charCount(char data[]){
    char frame[20];
    int j = 0;
    frame[j++] = (char)strlen(data);
    for (int i = 0; i <= strlen(data); i++){
        frame[j++] = data[i];
    }
    frame[j] = '\0';
    printf("Char Count: %d",frame[0]);
    for (int i = 1; i < strlen(data); i++){
        printf("%c",frame[i]);
    } 
    printf("\n");
}

void charStuff(char data[]){
    char str[50];
    char ESC = 'E';
    char FLAG = 'F';
    int j = 0;
    str[j++] = FLAG;
    for (int i = 0; i < strlen(data) - 1; i++){
        if (data[i] == FLAG || data[i] == ESC){
            str[j++] = ESC;
        }
        str[j++] = data[i];        
    }
    str[j++] = FLAG;
    str[j] = '\0';
    printf("Character Stuffing:\n");
    printf("Frame: ");
    for (int i = 0; i < j ; i++) {
        printf("%c", str[i]);
    }
    printf("\n");
    
}


void bitStuffing(char bitStream[]){
    char frame[256];
    char FLAG[] =  "  01111110  ";
    strcpy(frame,FLAG);
    int j = strlen(frame);
    int count = 0;
    for (int i = 0; i < strlen(bitStream); i++){
        frame[j++] = bitStream[i];
        if (bitStream[i] == '1'){
            count++;
            if (count == 5){
                frame[j++] = '0';
                count = 0;
            }
        }else{
            count = 0;
    
        }
    }
    strcpy(&frame[j],FLAG);
    printf("\n%s\n",frame);

}

int base = 0;
int nextseqnum = 0;

int isLost(){
    return (rand()%100 < LOSS_PROB);
}

void send_frame(int frame){
    printf("Sender: Sending Frame %d\n",frame);
}

void resend_frame(){
    for (int i = base; i < nextseqnum; i++){
        send_frame(i);
    }
    
}

void main(){

    srand(time(NULL));
    while (base < FRAMES){
        
        while (nextseqnum < base + WINDOW_SIZE && nextseqnum < FRAMES){
            send_frame(nextseqnum);
            nextseqnum++;
        }

        for (int i = base; i < nextseqnum; i++){
            if (isLost(i)){
                printf("Frame %d or ACK %d Lost\n",i,i);
                resend_frame();
                break;
            }else{
                printf("ACK %d received\n",i);
                base++;
            }
        }
    }

    printf("All Frames received correctly\n");
    





    // char data[5] = "ABCDE";
    // charCount(data);
    // charStuff(data);
    // char bits[] = "111111";
    // bitStuffing(bits);

    // const char* msg = "1101";
    // const char* poly = "110000001111";
    // computeCRC(msg,poly,1);
}