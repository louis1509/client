#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<conio.h>
#include<dir.h>

int main(int argc, char* argv[])
{
    system("C:\\windows\\notepad.exe");
    chdir("D:");
    char st[80];

    getcwd(st,80);
    printf("Current Working Directory : %s",st);
    getch();
    system("mkdir test");
    return 0;
}
