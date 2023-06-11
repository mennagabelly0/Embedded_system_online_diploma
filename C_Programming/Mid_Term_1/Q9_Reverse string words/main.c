#include <stdio.h>
#include <stdlib.h>
#include<string.h>

void reverse_words(char str[],int size)
{
	int i;
	for(i=size-1 ; i>=0 ; i--){

		if(str[i]==' ' || i==0)
		{

			if(i==0)
			{
				printf(" %s",&str[i]);
				break;

			}
			printf("%s",&str[i]);
			str[i]='\0';
			}
	}

}

int main(void) {

	char str[100];
	printf("Please enter a sentence to reverse: ");
	gets(str);

	printf("the reversed words is : ");
	reverse_words(str,strlen(str));
	return 0;
}
