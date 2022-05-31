#include<stdio.h>

void PrintMainMenu(int cryptographyKey);
int SelectMenuOption();
int GetUserMenuItem(int invalidChoose);
int UserActionHandler(int userMenuChoose, int *cryptographyKey, int maxMessageSize);
int GetCryptographyKey();
int CheckValidKey(int cryptographyKey);
int GetMessage(char *message, int cryptographyKey, int maxMessageSize);
void CryptMessage(char *text, int key);

int main(){
    int maxStringSize = 100, cryptographyKey = 0, userMenuChoose;
    while(1==1){
        PrintMainMenu(cryptographyKey);
        userMenuChoose = SelectMenuOption();
        if(UserActionHandler(userMenuChoose, &cryptographyKey, maxStringSize) < 0) break;
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

int SelectMenuOption(){
    int userMenuChoose, invalidChoose = 0;
    do{
        userMenuChoose =  GetUserMenuItem(invalidChoose);
        invalidChoose ++;
    }while(userMenuChoose < 1 || userMenuChoose > 4); //repate until the choose is in the valid range
    return userMenuChoose;
}

int GetUserMenuItem(int invalidChoose){
    int choose;
    printf("%s", invalidChoose == 0 ? "" : "Not valid choose.\n");
    printf("Select an item from the menu: ");
    if(scanf("%d", &choose) != 1){
        printf("Not valid Input\n");
        return -1;
    }
    return choose;
}

int UserActionHandler(int userMenuChoose, int *cryptographyKey, int maxMessageSize){
    if (userMenuChoose == 1){
        *cryptographyKey = GetCryptographyKey();
            return 1;
    }else if (userMenuChoose == 2 || userMenuChoose == 3){
        char message[maxMessageSize];
        if(GetMessage(message, *cryptographyKey, maxMessageSize) < 0) return 1;
        CryptMessage(message, userMenuChoose == 2 ? *cryptographyKey : -(*cryptographyKey));
        printf("%srypt: %s\n\n", userMenuChoose == 2 ? "C" : "Dec", message);
        return 1;
    }else return -1;
}

int GetCryptographyKey(){
    int cryptographyKey;
    printf("Insert cryptography key: ");
    if(scanf("%d", &cryptographyKey) != 1){
        printf("Not a valid input\n");
        return -1;
    }
    if(CheckValidKey(cryptographyKey) == -1) return GetCryptographyKey();
    return cryptographyKey;
}

int CheckValidKey(int cryptographyKey){
    if(cryptographyKey == 0){
        printf("Invalid Key inserted \n");
        return -1;
    }else return cryptographyKey;
}

int GetMessage(char *message, int cryptographyKey, int maxMessageSize){
    if(cryptographyKey == 0){
        printf("Before continuing insert a valid key\n");
        return -1;
    }
    printf("\n(maximum message length is %d char)\nInsert message: ", maxMessageSize);
    scanf("%*c%[^\n]%*c", message);
    return 1;
}

int StringSize(char* a){
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

void CryptMessage(char *text, int key){
    int l = StringSize(text), n;
    //transform char by char of the string
    for(int i = 0; i < l; i++){
        if(*(text+i) <= '9' && *(text+i) >= '0') *(text+i) = (mod(*(text+i)-'0'+key,10)+'0');
        else if(*(text+i) <= 'z' && *(text+i) >= 'a') *(text+i) = (mod(*(text+i)-'a'+key,26)+'a');
        else if(*(text+i) <= 'Z' && *(text+i) >= 'A') *(text+i) = (mod(*(text+i)-'A'+key,26)+'A');
    }
}