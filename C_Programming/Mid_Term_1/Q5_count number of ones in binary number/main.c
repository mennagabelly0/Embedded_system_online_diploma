#include <stdio.h>
#include <stdlib.h>
//count number of ones in binary number
void Count(int number)
{
	int i,c;
	int sum=0;
	for(i=31;i>=0;i--)
	{
		c = number>>i;
		if(c&1)
		{
			printf("1");
			sum++;
		}
		else
			printf("0");
	}
	printf("\nNumber of ones is %d",sum);
}

int main(void)
{
	int num;
	printf("Input: ");
	scanf("%d",&num);

	printf("Binary of %d is : ",num);
	Count(num);
	return 0;
}
