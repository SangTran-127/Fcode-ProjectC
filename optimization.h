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

void optimizeCal(char str[])
{
	
	for (int i = 0; i < strlen(str); i++)
    {
    	if(str[0] == '-' || str[0] == '+' )
    		insert(str, '0', 0);
        if(str[i] == '(' && str[i+1] == '-' && 
		  (str[i+2] == 's' || str[i+2] == 't' || str[i+2] == 'c' || str[i + 2] == 'a' || str[i + 2] == 'l' || str[i + 2] == 'g'))
            insert(str, '0', i+1);
        int start = i;
        int countPlus = 0, countMinus = 0;
        
        
        while (str[i] == '+' || str[i] == '-')
        {
            if (str[i] == '+')
                countPlus++;
            if (str[i] == '-')
                countMinus++;
            i++;
        }

        if (countPlus > 0 || countMinus > 0)
        {
            int end = i - 1;
            if (countMinus % 2 == 0)
                replace(str, '+', start, end);
            else
                replace(str, '-', start, end);
        }
        
        if (str[i] == ')' && ((str[i + 1] >= '0' && str[i + 1] <= '9') || str[i+1] == '.')) 
            insert(str, '*', i + 1);
        if (str[i] == '(' && ((str[i - 1] >= '0' && str[i - 1] <= '9') || str[i-1] == ')' || str[i-1] == '.'))
            insert(str, '*', i);
        if(str[i] == 'x' && ((str[i - 1] >= '0' && str[i - 1] <= '9') || str[i - 1] == ')'))
        	insert(str, '*', i);
        if(str[i] == 'x' &&  (str[i + 1] == '(' || str[i + 1] == 'x'))
        	insert(str, '*', i + 1);
        if((str[i] == '!' || str[i] == '%' || (str[i] >= '0' && str[i] <= '9') || str[i] == 'x' || str[i] == ')') &&
		(str[i + 1] == 's' || str[i + 1] == 't' || str[i + 1] == 'c' || str[i + 1] == 'l' || str[i + 1] == 'a' || str[i + 1] == 'g' || str[i + 1] == 'l'))
        	insert(str, '*', i + 1);
        i = start;
    }
}

int isOperand(char c){
	return (('0' <= c && c <= '9') || c == 'x');
}

int checkError(char str[]){
	
	int balance = 0;
	
	//The end char. For ex: 5+5*
	if(!isOperand(str[strlen(str) - 1]) && str[strlen(str) - 1] != ')' && str[strlen(str) - 1] != '.' 
				&& str[strlen(str) - 1] != '!' && str[strlen(str) - 1] != '%')
		return 1;
	//The beginning char. For ex: *5+5
	if(!isOperand(str[0]) && str[0] != '+' && str[0] != '-' && str[0] != '.' 
		&& str[0] != 's' && str[0] != 'c' && str[0] != 't' && str[0] != 'l' 
		&& str[0] != '(' && str[0] != 'a' && str[0] != 'g' && str[0] != 'x') 
		return 1;
	for(int i = 0; i < strlen(str); i++){
		//5+.
		if(str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
		{
			//5+*5
			if(!isOperand(str[i+1]) && str[i+1] != '(' && str[i+1] != '+' && str[i + 1] != '-' &&
				str[i+1] != 's' && str[i+1] != 'c' && str[i+1] != 't' && str[i+1] != 'l' && str[i+1] != '.' &&
				str[i + 1] != 'a' && str[i + 1] != 'g' && str[i + 1] != 'x') 
				return 1;
		}
		if(str[i] == '(' && str[i + 1] == ')')
			return 1;
		
		if(str[i] == '.' && str[i + 1] == '.'){
			return 1;
		}
		if((str[i] == '!' || str[i] == '%') && isOperand(str[i + 1]))
			return 1;
		if(str[i] == '(' && (str[i + 1] == '*' || str[i + 1 ] == '/' || str[i + 1] == '%' || str[i + 1] == '!'))
			return 1;
		if(str[i] == '(') balance++;
		if(str[i] == ')') balance--;
	}
				
	if(balance != 0){
		return 1;
	}
	
	
	return 0;
}
