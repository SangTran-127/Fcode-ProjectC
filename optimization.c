#include <string.h>
#include <math.h>
#include <stdio.h>
void replace(char str[], char c, int start, int end)
{
    str[start] = c;
    strcpy(&str[start + 1], &str[end + 1]);
}

void insert(char str[], char c, int pos)
{
    int temp = strlen(str);
    for (int j = strlen(str); j > pos; j--)
        str[j] = str[j - 1];
    str[pos] = c;
    str[temp + 1] = '\0';
}

int main(){
    char* tmpStr = malloc(200);
    strcpy(tmpStr, "XXX");
    printf("\n'%s'", tmpStr);
    replace(tmpStr, '.', 0, 0);
    printf("\n'%s'", tmpStr);

}
