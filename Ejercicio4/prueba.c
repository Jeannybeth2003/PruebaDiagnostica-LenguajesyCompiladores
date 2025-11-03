#include <stdio.h>
#include <stdlib.h>

int main() {
int i = 0;
            for (i = 0; i < 10; i++) {
               if (i % 2 == 0) {
                   continue;
               }
               printf("El numero es: %d", i);
           }
            double PI = 3.14159;
            return 0;
}