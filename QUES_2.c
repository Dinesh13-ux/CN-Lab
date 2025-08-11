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

    char temp[156];
    strcpy(temp,msg);
    xor_div(temp,poly,msg_len,poly_len);
    printf("\nTransmitted message: %s\n",msg);
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
        printf("No Error detected. Original message: %s\n\n",org_data);
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

    compute_crc_receiver(data,poly);
}

int main(){
    char msg[256];
    printf("Enter a message bit stream: ");scanf("%s",msg);
    // const char* msg = "1101011011";
    const char* crc12 = "1100000001111";
    const char* crc16 = "11000000000000101";
    const char* crcCCIP = "10001000000100001";
    int inp;
    printf("Enter your choice: \n");
    while(1){ 
        printf("1.CRC-12\n2.CRC-16\n3.CRC-CCIP\n");
        scanf("%d",&inp);
        if (inp == 1){
            printf("== CRC-12 Computation == \n");
            compute_crc_sender(msg,crc12);
        }
        else if (inp == 2){
            printf("== CRC-16 Computation == \n");
            compute_crc_sender(msg,crc16);
        }
        else if (inp == 3){
            printf("== CRC-CCIP Computation == \n");
            compute_crc_sender(msg,crcCCIP);
        }
        else{
            printf("Program exited\n");
            break;
        }
        
    }

}