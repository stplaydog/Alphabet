#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void createFolder(char *dir)
{
    char tmp[256];
    char buf[256];
    char *p = buf;


    char *tok;

    strcpy(tmp, dir);

    if(tmp[0] == '/')
    {
        *p = '/';
        p++;
    }

    tok = strtok(tmp, "/");

    while(tok != NULL)
    {
        strcpy(p, tok);
        printf("%s\n", buf);
        p += strlen(tok);
        *p = '/';
        p++;
        tok = strtok(NULL, "/");
    }
}

int main(int argc, char* argv[])
{
    char *a = "/eat/abc/seafood";
    char *b = "../eat/abc/seafood/";

    createFolder(a);
    createFolder(b);
}
