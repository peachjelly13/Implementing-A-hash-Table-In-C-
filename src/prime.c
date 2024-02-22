#include<stdio.h>
#include<math.h>
#include "prime.h"

int is_prime(const int x){
    if(x<2){return -1;}// this means it is undefined like 1 and the numbers < 2
    if(x<4){return 1;} // the numbers are prime
    if(x%2==0){
        return 0; // it is not prime
    }
    for(int i =3;i<sqrt(x);i++){
        if(x%i==0){
            return 0;
        }
    }
    return 1;
}

int next_prime(int x){
    while(is_prime(x)!=1){
        x++;
    }
    return x;
}