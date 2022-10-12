#include <stdio.h>
#include <math.h>

int	main()
{
	char	*test = "hello";

	printf("*test++ : e vs %c\n", *test++);
	printf("*test++ : e vs %c\n", *test);
	printf("*(test)++ : f vs %c\n", *(test)++);
	printf("*test++ : e vs %c\n", *test);
	printf("*(test++) : l vs %c\n", *(test++));
}

void putstr(char *str)
{
	while (*str)
		putchar(*str++);
}