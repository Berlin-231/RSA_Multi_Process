#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
 
long int op,n,p,q,t,chck,encryptors[100],decryptors[100],temp[100],k,j,m[100],encMsg[100],i;
char msg[100];
int prime(long int);
void calc_enc();
long int calc_dec(long int);
void main() {

    printf("\n\nPlease select the execution type -\n\t1. Manual Mode \n\t2. Auto Mode\n\n");
    scanf("%d",&op);

    if(op==1){
    printf("\nEnter a Prime Number (P)\n");
    scanf("%d",&p);
 
    chck=isPrime(p);
 
    if(chck==0) {
        printf("\nNot a prime number\n");
        exit(1);
    }
    printf("\nEnter a Prime Number (Q)\n");
    scanf("%d",&q);
    
    chck=isPrime(q);
    
    if(chck==0||p==q) {
        printf("\nNot a prime number\n");
        exit(1);
    }

    printf("\nEnter message to encrypt-\n");
    fflush(stdin);
    scanf("%s",msg);
    
    }
    else{
        printf("Running with default values for P= 957 , Q = 943 , Msg = Hello\n");
        p=953;
        q=947;
        //msg={'H','e','l','l','o'};
        strcpy(msg, "Hello");
        printf("\n*******************************************************************\n");

    }
    for (i=0;msg[i]!=NULL;i++)
            m[i]=msg[i];
    
    n=p*q;
    t=(p-1)*(q-1);
    calc_enc();
 
    printf("\nEncryptor/Decryptor possible pairs\n");
    for (i=0;i<k-1;i++)
        printf("\n%ld\t%ld",encryptors[i],decryptors[i]);
    
    printf("\n*******************************************************************\n");
    encryption(encryptors[0]);
    encMsg[i]=-1;
     
    printf("\nEncrypted message =>::");
    for (i=0;encMsg[i]!=-1;i++)
    printf("%c",encMsg[i]);
  
    printf("\n");

    printf("*******************************************************************\n");
    int status;
    int pid = fork();

    if(pid == 0 ){ // case where random decryption key wont work

        printf("Hacker Process Started.......\n");
        printf("Trying to decrypt the message using random Decryptor and public key.....\n");
        printf("Hacker Process result =  ");
        decryption(decryptors[1]);
        printf("\n\n");
        printf("*******************************************************************\n");
    }
    else{

        wait(&status);
        int pid2 = fork();
        if (pid2==0){

          printf("\nReciepient Process Started.....");
          printf("\nTrying to decrypt using Correct decryptor (n = %d, d = %d)\n", n, decryptors[0]);
          printf("\nReciepient result =  ");
          decryption(decryptors[0]);
          printf("\n\n");
          printf("*******************************************************************\n");
        }
        else{

            wait(&status);
            // printf("Message is decrypted to %d\n", m);

            printf("\n****************************  END  ***************************************\n");
            return 0;
        }
    }
}
 
int isPrime(long int n) {
    int i;
    k=sqrt(n);
    for (i=2;i<=k;i++) {
        if(n%i==0)
            return 0;
    }
    return 1;
}
 
void calc_enc() {
    
    int k;
    k=0;
    for (i=2;i<t;i++) {
        if(t%i==0)
           continue;
        chck=isPrime(i);
 
        if(chck==1&&i!=p&&i!=q) {
 
            encryptors[k]=i;
           chck=calc_dec(encryptors[k]);
            if(chck>0) {
 
                decryptors[k]=chck;
                k++;
            }
            if(k==99)
                 break;
        }
    }
}
 
long int calc_dec(long int a) {
    
    long int j=1;
    
    while(1) {
        j=j+t;
        if(j%a==0)
            return(j/a);
    }
}
 
void encryption(long int keyEn) {
 
    long int pt,ct,key=keyEn,k,len;
    i=0;
    len=strlen(msg);
    while(i!=len){
 
        pt=m[i];
        pt=pt-96;
        k=1;
        for (j=0;j<key;j++){
 
            k=k*pt;
            k=k%n;
        }
        temp[i]=k;
        ct=k+96;
        encMsg[i]=ct;
        i++;
    }
}
 
void decryption(long int keyDec) {
   long int charval,ct,key=keyDec,k;
    i=0;
    while(encMsg[i]!=-1) {
 
        ct=temp[i];
        k=1;
 
        for (j=0;j<key;j++) {
            k=k*ct;
            k=k%n;
        }
 
        charval=k+96;
        m[i]=charval;
        i++;
    }
    m[i]=-1;
    for (i=0;m[i]!=-1;i++)
    printf("%c",m[i]);
 
}