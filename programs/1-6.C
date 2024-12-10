#include <stdio.h>

main(argc, argv) 
int argc;
char* argv[];
{
    FILE *infile;
    int c, nl, tb, bl;

    if (argc <= 1) {
        printf("USE MORE INPUTS!\n");
        return;
    }

    nl = 0, tb = 0, bl = 0;

    infile = fopen(argv[1], "r"); // r is for read
    while ((c = fgetc(infile)) != EOF) { // fgetc increments
        if (c == '\n') {
            nl++;
        } else if (c == '\t') {
            tb++;
        } else if (c == ' ') {
            bl++;
        }
    }

    fclose(infile);

    printf("Number of newlines: %d\n", nl);
    printf("Number of tabs: %d\n", tb);
    printf("Number of blanks: %d\n", bl);
}