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

void compute_crc(const char* msg, const char* poly){
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
    printf("Transmitted message: %s\n",data);
}

int main(){

    //using static input
    const char* msg = "1101011011";
    const char* crc = "10011";
    compute_crc(msg,crc);

    const char* msg2 = "11110000";
    const char* crc2 = "1001";
    compute_crc(msg2,crc2);


    //using dynamic input
    char ch[15], ch_crc[15];
    printf("Enter a message bit stream: ");
    scanf("%s",ch);
    printf("Enter a generator polynomial bit stream: ");
    scanf("%s",ch_crc);
    compute_crc(ch,ch_crc);
}