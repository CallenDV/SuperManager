#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *text = "Doing your mama!";
    // Adjust the voice and speed if needed
    system("espeak -ven-us+f3 -s150 --stdout | aplay");

    return 0;
}
