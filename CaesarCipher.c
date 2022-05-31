#include<stdio.h>

void Crypt(char *text, int key);
void Clear(char *text);
void PrintMainMenu(int cryptographyKey);

int main(){
    //choose -> choose of the user in the menu
    //pick -> check variable to see if is the first loop of the while
    int maxStringSize = 100, cryptographyKey = 0, choose, pick;
    char text[maxStringSize];
    while(1==1){
        choose = 0, pick = 0;
        PrintMainMenu(cryptographyKey);
        
        do{
            //if is the first time (pick == 0) you enter there don't print "not valid choise"
            printf("%sScegliere voce del menù e premere invio: ", pick == 0 ? "" : "Scelta non presente nel menù.\n");
            //take in input the choose of the user and check if is valid or it generates a system error
            if(scanf("%d", &choose) != 1){
                printf("Input non valido\n");
                return -1;
            }
            pick ++;
        }while(choose < 1 || choose > 4); //repate until the choose is in the valid range
        pick = 0;
        if(choose == 1){
            do{
                printf("%sInserire la chiave di crittografia: ", pick == 0 ? "" : "Chiave inserita non valida.\n");
                //take in input the cryptography key of the user and check if is valid or it generates a system error
                if(scanf("%d", &cryptographyKey) != 1){
                    printf("Input non valido\n");
                    return -1;
                }
                pick++;
            }while (cryptographyKey == 0);
        }else if(choose == 2 || choose == 3){
            if(cryptographyKey == 0){
                printf("Prima di continuare impostare una chiave valida\n");
                continue;
            }
            printf("\n(lunghezza massima mex 100 caratteri)\nInserire il messaggio: ");
            Clear(text);
            scanf("%*c%[^\n]%*c", text);
            //Call the Crypt method whit key if is to crypt the message else -key if it is to decrypt it
            //Decrypting is the same process of Crypting but with -(key)
            Crypt(text, choose == 2 ? cryptographyKey : -cryptographyKey);
            printf("%srypt: %s\n\n", choose == 2 ? "C" : "Dec", text);
        }else if(choose == 4) break;
    }      
}

void PrintMainMenu(int cryptographyKey){
    printf("\n------------\n WELCOME TO CRYPTOGRAPHY \n------------\n");
    printf("\nMain Menu: \n\n");
    printf(cryptographyKey == 0 ? "Key not set\n\n" : "Key set with value: %d\n\n", cryptographyKey);
    printf("1) Set cryptography key \n");
    printf("2) Crypt a message \n");
    printf("3) Decrypt a message \n");
    printf("4) Quit\n\n");
}

//calculate the length of a string (how many chars)
int size(char* a){
    int l = 0;
    while(*(a+l) != '\0'){
        l++;
    }
    return l;
}

//Return the positive value of mod operation (ex: -2 mod 26=23)
int mod(int n, int mod){
    return (n >= 0 ? n : (mod+(n%mod)))%mod;
}

void Crypt(char *text, int key){
    int l = size(text), n;
    //transform char by char of the string
    for(int i = 0; i < l; i++){
        if(*(text+i) <= '9' && *(text+i) >= '0') *(text+i) = (mod(*(text+i)-'0'+key,10)+'0');
        else if(*(text+i) <= 'z' && *(text+i) >= 'a') *(text+i) = (mod(*(text+i)-'a'+key,26)+'a');
        else if(*(text+i) <= 'Z' && *(text+i) >= 'A') *(text+i) = (mod(*(text+i)-'A'+key,26)+'A');
    }
}

//put a '\0' (end of string) at the start of a char array, like so the string is interpreted as empty 
void Clear(char *text){
    *(text) = '\0';
}