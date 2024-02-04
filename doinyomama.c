#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *text = "Doing your mama!";
    system("espeak -ven-us+f3 -s150 --stdout | aplay");

    return 0;
}
