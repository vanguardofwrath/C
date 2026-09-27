#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc > 2) {
        printf("This command takes in 1 parameter only!");
        return 1;
    }

    FILE *fptr = fopen(argv[1], "rb");
    if (!fptr) {
        return 1;
    }



    return 0;
}