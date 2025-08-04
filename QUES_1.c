#include<stdio.h>
#include<string.h>
#include<ctype.h>
void byte_counting(char data[]){
    char frame[32];
    int len = strlen(data)+1;
    int j = 0;
    frame[j++] = (char)len;
    for (int i = 0; i < len-1; i++){
        frame[j++] = data[i];
    }
    frame[j] = '\0';
    printf("Byte Counting: %d",frame[0]);
    for (int i = 1; i < len; i++){
        printf("%c",frame[i]);
    }
    printf("\n");
}

void bit_stuffing(char data[]){
    char FLAG[] = "  01111110  ";
    char frame[32];
    strcpy(frame,FLAG);
    int j= strlen(frame);
    int count = 0;
    for (int i = 0; i < strlen(data); i++){
        frame[j++] = data[i];
        if (data[i] == '1'){
            count++;
            if (count == 5){
                frame[j++] = '0';
                count = 0;
            }
        }
        else{
            count = 0;
        }
    }
    strcpy(&frame[j],FLAG);
    printf("Bit stuffing: %s\n",frame);
}

void char_stuffing(char data[]){
    char FLAG = 'F';
    char ESC = 'E';
    char frame[32];
    int j= 0;
    frame[j++] = FLAG;
    for (int i = 0; i < strlen(data); i++){
        if (toupper(data[i]) ==  FLAG || toupper(data[i]) == ESC){
            frame[j++] = ESC;
        }
        frame[j++] = data[i];
    }
    frame[j++] = FLAG;
    frame[j] = '\0';
    printf("Character stuffing: %s\n",frame);
}
int main(){
    char string[20];
    char bit_stream[20];
    printf("Enter a Frame string: ");
    scanf("%s",&string);
    printf("Enter a Bit Stream: ");
    scanf("%s",&bit_stream);
    byte_counting(string);
    char_stuffing(string);
    bit_stuffing(bit_stream);
}