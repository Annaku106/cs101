#include <stdio.h>
int main(){
    int i=8;
    if(i&(i-1)){
        printf("faise");
    }
    else{
        printf("true");
    }
    return 0;
}
