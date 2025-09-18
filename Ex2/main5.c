#include <stdio.h>
int main() {
    char grade='B';
    printf("your grade is %c\n",grade);
    switch (grade) {
    case 'A':
        printf("lExcellent!\n");
        break;
    case 'B':
    case 'C':
        printf("well done!\n");
        break;
    case 'D':
    case 'F':
        printf("better try again!\n");
        break;
    default:
        printf("invail grade\n");
    }
    return 0;
}
   
