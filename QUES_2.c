#include<stdio.h>
#include<string.h>

void xor_div(char* msg,const char* poly, int msg_len,int poly_len){
    for (int i = 0; i <= msg_len - poly_len; i++){
        if (msg[i] == '1'){
            for (int j = 0; j < poly_len; j++){
                msg[i + j] = (msg[i + j] == poly[j]) ? '0' : '1';
            }         
        }
    } 
}

void compute_crc_receiver(const char* msg, const char* poly){
    int msg_len = strlen(msg);
    int poly_len = strlen(poly);
    int total_len = msg_len + poly_len - 1;

    char temp[156];
    strcpy(temp,msg);
    xor_div(temp,poly,msg_len,poly_len);
    printf("Received message: %s\n",msg);
    printf("Generator polynomial: %s\n",poly);
    printf("CRC remainder: %s\n",&temp[msg_len- (poly_len -1)]);

    int error = 0;
    for (int i = msg_len -(poly_len -1 ); i < msg_len; i++){
       if (temp[i] != '0'){
            error++;
       } 
    }
    
    if (error == 0){
        char org_data[256];
        for (int i = 0; i < msg_len- (poly_len -1); i++){
            org_data[i] = msg[i];
        }

        org_data[msg_len- (poly_len -1)] = '\0';
        printf("Decrypted message: %s\n\n",org_data);
    }
    else{
        printf("Error occured during transmission no of error bits = %d\n",error);
    }
    
    
}

void compute_crc_sender(const char* msg, const char* poly){
    int msg_len = strlen(msg);
    int poly_len = strlen(poly);
    int total_len = msg_len + poly_len - 1;

    char data[156];
    strcpy(data,msg);
    for (int i = 0; i < poly_len - 1; i++){
        data[msg_len + i]   = '0';
    }
    
    
    data[total_len] = '\0';
    char temp[156];
    strcpy(temp,data);
    xor_div(temp,poly,total_len,poly_len);

    printf("Original message: %s\n",msg);
    printf("Generator polynomial: %s\n",poly);
    printf("CRC remainder: %s\n",&temp[msg_len]);

    strcpy(data + msg_len,&temp[msg_len]);
    data[total_len] = '\0';
    printf("Transmitted message: %s\n\n",data);
}

int main(){

    //using static input
    const char* msg = "1101011011";
    const char* crc = "10011";
    compute_crc_sender(msg,crc);

    const char* msg2 = "11110000";
    const char* crc2 = "1001";
    compute_crc_sender(msg2,crc2);


    const char* enmsg = "11010110111110";
    const char* crc3 = "10011";
    compute_crc_receiver(enmsg,crc3);
    // //using dynamic input
    // char ch[15], ch_crc[15];
    // printf("Enter a message bit stream: ");
    // scanf("%s",ch);
    // printf("Enter a generator polynomial bit stream: ");
    // scanf("%s",ch_crc);
    // compute_crc_sender(ch,ch_crc);
}