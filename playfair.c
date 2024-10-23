#include<stdio.h>
#include<string.h>

char mat[6][6];
char en[100],de[100];
int ind1[2],ind2[2];

void find1(char a){
    for(int i=0;i<5;i++){
        int f=0;
        for(int j=0;j<5;j++){
            if(mat[i][j]==a){
                ind1[0]=i;
                ind1[1]=j;
                f=1;
                break;
            }
        }
        if(f){ 
            break; 
        }
    }
}

void find2(char a){
    for(int i=0;i<5;i++){
        int f=0;
        for(int j=0;j<5;j++){
            if(mat[i][j]==a){
                ind2[0]=i;
                ind2[1]=j;
                f=1;
                break;
            }
        }
        if(f){ 
            break; 
        }
    }
}

void encrypt(char plain[]){
    int len=0;
    int i=0;
    int n=strlen(plain);
    while(i<n){
        while(plain[i]==' ')i++;
        find1(plain[i]);i++;
        if(i>=n){
            find2('x');
        } else{
            while(plain[i]==' ')i++;
            find2(plain[i]);i++;
        }
        if(ind1[1]==ind2[1]){
            en[len++]=mat[(ind1[0]+1)%5][ind1[1]];
            en[len++]=mat[(ind2[0]+1)%5][ind2[1]];
        } else if(ind1[0]==ind2[0]){
            en[len++]=mat[ind1[0]][(ind1[1]+1)%5];
            en[len++]=mat[ind2[0]][(ind2[1]+1)%5];
        } else{
            en[len++]=mat[ind1[0]][ind2[1]];
            en[len++]=mat[ind2[0]][ind1[1]];
        }
    }
    en[len]='\0';
}

void decrypt(char cip[]){
    int dlen=0;
    int i=0;
    int n=strlen(cip);
    while(i<n){
        find1(cip[i]);i++;
        find2(cip[i]);i++;
        if(ind1[1]==ind2[1]){
            de[dlen++]=mat[(ind1[0]+4)%5][ind1[1]];
            de[dlen++]=mat[(ind2[0]+4)%5][ind2[1]];
        } else if(ind1[0]==ind2[0]){
            de[dlen++]=mat[ind1[0]][(ind1[1]+4)%5];
            de[dlen++]=mat[ind2[0]][(ind2[1]+4)%5];
        } else{
            de[dlen++]=mat[ind1[0]][ind2[1]];
            de[dlen++]=mat[ind2[0]][ind1[1]];
        }
    }
    de[dlen]='\0';
}

void formkeymat(char key[]){
    int check[26]={0};
    int u=0,v=0;
    for(int i=0;i<strlen(key);i++){
        if(key[i]!=' '){
            if(!check[key[i]-'a']){
                mat[u][v++]=key[i];
                check[key[i]-'a']=1;
                if(v>=5){
                    u++;
                    v=0;
                }
            }
        }
    }
    for(int i=0;i<26;i++){
        if(i==9)continue;
        if(!check[i]){
            mat[u][v++]=i+97;
            if(v>=5){
                u++;
                v=0;
            }
        }
    }
}

int main(){
    char plain[100];
    char key[100];

    printf("Enter plaintext: ");
    fgets(plain, sizeof(plain), stdin);
    plain[strcspn(plain, "\n")] = 0; 

    printf("Enter key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = 0; 

    formkeymat(key);
    encrypt(plain);
    printf("Encrypted: %s\n", en);
    decrypt(en);
    printf("Decrypted: %s\n", de);

    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            printf("%c",mat[i][j]);
        }
        printf("\n");
    }
}