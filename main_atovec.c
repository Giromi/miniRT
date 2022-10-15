#include "minirt.h"
#include <stdio.h>
#include <string.h>
#define	MAX		100
#define	WRITE	1
#define	READ	0
#define GREEN_OK	fprintf(stdout, "\x1b[32mOK\x1b[0m\n")
#define RED_KO		fprintf(stdout, "\x1b[31mKO\x1b[0m\n")
#define MAX_BUF		100

enum
{
	ANS,
	OUR,
};

void examine(int case_num, char *case_str, int idx, int result)
{
	const char	*type[3] = {"RGB", "XYZ", "UNIT"};
	t_vector	why;
	pid_t		pid;

	fprintf(stdout, "[CASE %2d] |%-40s| @ (%s):\t", case_num, case_str, type[idx]);
	result == 0 ? GREEN_OK : RED_KO;
	if (!result)
		return ;
	if ((pid = fork()) < 0)
		ft_strerror("error : fork");
	else if (!pid)
	{
		why = ft_atovec(case_str, idx); // if no exit -> under
		debugPrintVec("our", &why);
		exit(1);
	}
	waitpid(0, 0, 0);
	fprintf(stdout, "\n");
}

void print_compare(t_vector *val, t_vector *ans)
{
	printf("result x : val = %lf vs ans = %lf\n",  val->x, ans->x);
	printf("result y : val = %lf vs ans = %lf\n",  val->y, ans->y);
	printf("result z : val = %lf vs ans = %lf\n",  val->z, ans->z);
}

t_vector	my_atovec(char *buf, char *input, int idx)
{
	int			fd[2];
	pid_t		pid;
	t_vector	val;
	int			status;

	memset(buf, 0, MAX_BUF);
	if (pipe(fd) < 0)
		ft_strerror("error : pipe");
	if ((pid = fork()) < 0) 
		ft_strerror("error : fork");
	else if (!pid)
	{
		close(fd[READ]);
		dup2(fd[WRITE], STDERR_FILENO);
		close(fd[WRITE]);
		ft_atovec(input, idx);
		exit(0);		// 혹시나 exit 안될 경우를 대비해서...
						// 넘어오면 무조건 고쳐야 함...
	}
	else
	{
		close(fd[WRITE]);
		waitpid(0, &status, 0);
		read(fd[READ], buf, MAX_BUF);
		close(fd[READ]);
	}
	if (status == 0)
		val = ft_atovec(input, idx);
	return (val);
}


void	test_all(char *input[], char *buf, t_vector *val);
void	test_xyz(char *input[], char *buf, t_vector *val);
void	test_rgb(char *input[], char *buf, t_vector *val);
void	test_unit(char *input[], char *buf, t_vector *val);

int	main(void)
{
	int			idx;
	int			case_num;
	t_vector	val[2];
	char		buf[MAX_BUF];
	char		*input[MAX] = {												\
							"0,0,0",										\
							"-1,0,0",										\
							"-1,255,10",									\
							"000,0,0",										\
							"0,000,0",										\
							"a,0,0",										\
							"1-,0,0",										\
							"-1,255,10,",									\
							"--1,0,0,",										\
							"--1,0,0,0",									\
							"-,0,0",										\
							"256,0,1",										\
							"2147483647,0,0",								\
							"2147483648,0,0",								\
							"-2147483648,0,0",								\
							"-2147483649,0,0",								\
							"-2147483649,0,0",								\
							"-214a7483649,0,0",								\
							"+214a7483649,0,0",								\
							"+02147483649,0,0",								\
							"2147483649,,0",								\
							"2147483649,0",									\
							"9007199254740993,0,0",							\
							"9007199254740994,0,0",							\
							"9223372036854775808,0,0",						\
							"0.-1,0,0",										\
							"0.+1,0,0",										\
							"0.-,0,0",										\
							"0.+,0,0",										\
							"0.0,0,0",										\
							"0.3,,",										\
							".,.,.",										\
							".0,.0,.0",										\
							"0.0,0.0,0.0",									\
							"2147483647.999,0,0",							\
							"2147483648.999,0,0",							\
							"2147483647.331111111,0,0",						\
							"2147483646.99999999999,0,0",					\
							"+,0,0",										\
							",,,,0,0,",										\
							",,,0,0,0,",									\
							",,,0,0,0,",									\
							",,",											\
							" ,   , ",										\
							"0 , 1 , 2",									\
							"- 1 , 1 , 0",									\
							"-1, 1, 0",										\
							"-0.1,-0 1.0, 0.0",								\
							"-0.1,-01.0, 0.",								\
							"-0.1,-01., 0.",								\
							"-.1,-01.0, 0.0",								\
							"-0..,-01.., 0..",								\
							"+-,-0.0, 0",									\
							"-0, -0, -0",									\
							"+-1, +-1, +-1",								\
							"9999999999,9999999999,9999999999",				\
							"2147483647,2147483647,2147483647",				\
							"-0.999999,-0.999999,-0.999999",				\
							"-0.9999999,-0.9999999,-0.9999999",				\
							"0.9999999,0.9999999,0.9999999",				\
							"255.9999999,255.9999999,255.9999999",			\
							"254.9999999,254.9999999,254.9999999",			\
							"254.999999,254.999999,254.999999",			\
							};
	test_all(input, buf, val);
	test_xyz(input, buf, val);
	test_unit(input, buf, val);
	test_rgb(input, buf, val);
	// val[OUR] = ft_atovec(input[10], XYZ);
	// examine(10, input[10], XYZ, \
	//     strcmp(buf, "err: wrong number of values ','\n"));
	return (0);
}

void	test_all(char *input[], char *buf, t_vector *val)
{
	int			idx = 0;
	int			case_num = 0;

	printf("\n@@@@@@@@@@@@@@@@@@@@@[ INPUT CASE : ALL ]@@@@@@@@@@@@@@@@@@@@@@@@@\n");

	printf("\n>-----ERROR [%s]-----<\n", "err: wrong number of values ','");
	case_num = 7;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: wrong number of values ','\n"));
	}

	case_num = 8;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: wrong number of values ','\n"));
	}

	case_num = 9;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: wrong number of values ','\n"));
	}

	case_num = 21;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
			strcmp(buf, "err: wrong number of values ','\n"));
	}


	case_num = 39;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
			strcmp(buf, "err: wrong number of values ','\n"));
	}

	case_num = 40;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
			strcmp(buf, "err: wrong number of values ','\n"));
	}

	case_num = 41;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
			strcmp(buf, "err: wrong number of values ','\n"));
	}

	printf("\n>-----ERROR [%s]-----<\n", "err: ',' in a row");

	case_num = 20;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: ',' in a row\n"));
	}

	case_num = 30;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: ',' in a row\n"));
	}

	case_num = 42;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: ',' in a row\n"));
	}


	printf("\n>-----ERROR [%s]-----<\n", "err: bad arguemnts");

	case_num = 5;
	for (int idx = 0; idx < 3; idx++) 
	{
	val[OUR] = my_atovec(buf, input[case_num], idx);
	examine(case_num, input[case_num], idx, \
			strcmp(buf, "err: bad arguemnts\n"));
	}

	case_num = 6;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: bad arguemnts\n"));
	}

	case_num = 10;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: bad arguemnts\n"));
	}

	case_num = 38;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: bad arguemnts\n"));
	}

	case_num = 17;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: bad arguemnts\n"));
	}

	case_num = 18;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: bad arguemnts\n"));
	}

	case_num = 25;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: bad arguemnts\n"));
	}

	case_num = 26;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: bad arguemnts\n"));
	}

	case_num = 27;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: bad arguemnts\n"));
	}

	case_num = 28;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: bad arguemnts\n"));
	}

	case_num = 31;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: bad arguemnts\n"));
	}

	case_num = 32;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: bad arguemnts\n"));
	}

	case_num = 43;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: bad arguemnts\n"));
	}

	case_num = 44;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: bad arguemnts\n"));
	}

	case_num = 45;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: bad arguemnts\n"));
	}

	case_num = 46;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: bad arguemnts\n"));
	}

	case_num = 47;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: bad arguemnts\n"));
	}

	case_num = 48;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: bad arguemnts\n"));
	}

	case_num = 50;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: bad arguemnts\n"));
	}

	case_num = 51;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: bad arguemnts\n"));
	}

	case_num = 52;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: bad arguemnts\n"));
	}

	case_num = 53;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: bad arguemnts\n"));
	}

	case_num = 54;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: bad arguemnts\n"));
	}



	printf("\n>-----ERROR [%s]-----<\n", "err: multiple dots");
	case_num = 49;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: multiple dots\n"));
	}


	printf("\n>-----ERROR [%s]-----<\n", "err: exceed size");

	case_num = 13;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: exceed size at front point\n"));
	}

	case_num = 15;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: exceed size at front point\n"));
	}

	case_num = 16;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: exceed size at front point\n"));
	}

	case_num = 19;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: exceed size at front point\n"));
	}

	case_num = 22;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: exceed size at front point\n"));
	}

	case_num = 23;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: exceed size at front point\n"));
	}

	case_num = 24;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: exceed size at front point\n"));
	}

	case_num = 34;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: exceed size at behind point\n"));
	}

	case_num = 35;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: exceed size at front point\n"));
	}

	case_num = 36;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: exceed size at behind point\n"));
	}

	case_num = 55;
	for (int idx = 0; idx < 3; idx++) 
	{
		val[OUR] = my_atovec(buf, input[case_num], idx);
		examine(case_num, input[case_num], idx, \
				strcmp(buf, "err: exceed size at front point\n"));
	}
}

void	test_xyz(char *input[], char *buf, t_vector *val)
{
	int			idx = UNIT;
	int			case_num = 0;

	printf("\n@@@@@@@@@@@@@@@@@@@@@[ INPUT CASE : XYZ ]@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	idx = XYZ;

	printf("\n>---------RIGHT---------<\n");
	case_num = 0;
	val[ANS] = vec_init(0, 0, 0);
	val[OUR] = my_atovec(buf, input[case_num], idx);
	examine(case_num, input[case_num], idx, \
			memcmp(&val[OUR], &val[ANS], sizeof(t_vector)));

	case_num = 1;
	val[ANS] = vec_init(-1, 0, 0);
	val[OUR] = my_atovec(buf, input[case_num], idx);
	examine(case_num, input[case_num], idx, \
			memcmp(&val[OUR], &val[ANS], sizeof(t_vector)));

	case_num = 2;
	val[OUR] = my_atovec(buf, input[case_num], idx);
	val[ANS] = vec_init(-1, 255, 10);
	examine(case_num, input[case_num], idx, \
			memcmp(&val[OUR], &val[ANS], sizeof(t_vector)));

	case_num = 3;
	val[ANS] = vec_init(0, 0, 0);
	val[OUR] = my_atovec(buf, input[case_num], idx);
	examine(case_num, input[case_num], idx, \
			memcmp(&val[OUR], &val[ANS], sizeof(t_vector)));

	case_num = 4;
	val[ANS] = vec_init(0, 0, 0);
	val[OUR] = my_atovec(buf, input[case_num], idx);
	examine(case_num, input[case_num], idx, \
			memcmp(&val[OUR], &val[ANS], sizeof(t_vector)));

	case_num = 11;
	val[ANS] = vec_init(256, 0, 1);
	val[OUR] = my_atovec(buf, input[case_num], idx);
	examine(case_num, input[case_num], idx, \
			memcmp(&val[OUR], &val[ANS], sizeof(t_vector)));

	case_num = 12;
	val[ANS] = vec_init(2147483647, 0, 0);
	val[OUR] = my_atovec(buf, input[case_num], idx);
	examine(case_num, input[case_num], idx, \
			memcmp(&val[OUR], &val[ANS], sizeof(t_vector)));

	case_num = 14;
	val[ANS] = vec_init(-2147483648, 0, 0);
	val[OUR] = my_atovec(buf, input[case_num], idx);
	examine(case_num, input[case_num], idx, \
			memcmp(&val[OUR], &val[ANS], sizeof(t_vector)));

	case_num = 29;
	val[ANS] = vec_init(0, 0, 0);
	val[OUR] = my_atovec(buf, input[case_num], idx);
	examine(case_num, input[case_num], idx, \
			memcmp(&val[OUR], &val[ANS], sizeof(t_vector)));

	case_num = 33;
	val[ANS] = vec_init(0, 0, 0);
	val[OUR] = my_atovec(buf, input[case_num], idx);
	examine(case_num, input[case_num], idx, \
			memcmp(&val[OUR], &val[ANS], sizeof(t_vector)));

	case_num = 37;
	val[ANS] = vec_init(2147483647, 0, 0);
	val[OUR] = my_atovec(buf, input[case_num], idx);
	examine(case_num, input[case_num], idx, \
			memcmp(&val[OUR], &val[ANS], sizeof(t_vector)));
}

void	test_unit(char *input[], char *buf, t_vector *val)
{
	int			idx = UNIT;
	int			case_num = 0;

	printf("\n@@@@@@@@@@@@@@@@@@@@@[ INPUT CASE : UNIT ]@@@@@@@@@@@@@@@@@@@@@@@@@\n");

	case_num = 1;
	val[ANS] = vec_unit(vec_init(-1, 0, 0));
	val[OUR] = my_atovec(buf, input[case_num], idx);
	examine(case_num, input[case_num], idx, \
			memcmp(&val[OUR], &val[ANS], sizeof(t_vector)));
	

	case_num = 2;
	val[ANS] = vec_unit(vec_init(-1, 255, 10));
	val[OUR] = my_atovec(buf, input[case_num], idx);
	examine(case_num, input[case_num], idx, \
			memcmp(&val[OUR], &val[ANS], sizeof(t_vector)));
	

	case_num = 3;
	val[OUR] = my_atovec(buf, input[case_num], idx);
	examine(case_num, input[case_num], idx, \
			strcmp(buf, "err: normal vector value is zero\n"));

	case_num = 4;
	val[OUR] = my_atovec(buf, input[case_num], idx);
	examine(case_num, input[case_num], idx, \
			strcmp(buf, "err: normal vector value is zero\n"));
	

	case_num = 56;
	val[ANS] = vec_unit(vec_init(2147483647, 2147483647, 2147483647));
	val[OUR] = my_atovec(buf, input[case_num], idx);
	examine(case_num, input[case_num], idx, \
			memcmp(&val[OUR], &val[ANS], sizeof(t_vector)));
}

void	test_rgb(char *input[], char *buf, t_vector *val)
{
	int			idx = UNIT;
	int			case_num = 0;

	printf("\n@@@@@@@@@@@@@@@@@@@@@[ INPUT CASE : RGB ]@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	idx = RGB;

	case_num = 1;
	val[OUR] = my_atovec(buf, input[case_num], idx);
	examine(case_num, input[case_num], idx, \
			strcmp(buf, "err: exceed RGB value range\n"));
	

	case_num = 2;
	val[OUR] = my_atovec(buf, input[case_num], idx);
	examine(case_num, input[case_num], idx, \
			strcmp(buf, "err: exceed RGB value range\n"));
	

	case_num = 3;
	val[ANS] = vec_init(0, 0, 0);
	val[OUR] = my_atovec(buf, input[case_num], idx);
	examine(case_num, input[case_num], idx, \
			memcmp(&val[OUR], &val[ANS], sizeof(t_vector)));
	
	case_num = 59;
	val[ANS] = vec_init(0.9999999, 0.9999999, 0.9999999);
	// val[ANS] = vec_init(1, 1, 1);
	val[OUR] = my_atovec(buf, input[case_num], idx);
	examine(case_num, input[case_num], idx, \
			memcmp(&val[OUR], &val[ANS], sizeof(t_vector)));

	case_num = 61;
	val[ANS] = vec_init(254.9999999, 254.9999999, 254.9999999);
	val[OUR] = my_atovec(buf, input[case_num], idx);
	examine(case_num, input[case_num], idx, \
			memcmp(&val[OUR], &val[ANS], sizeof(t_vector)));

	case_num = 62;
	val[ANS] = vec_init(254.999999, 254.999999, 254.999999);
	val[OUR] = my_atovec(buf, input[case_num], idx);
	examine(case_num, input[case_num], idx, \
			memcmp(&val[OUR], &val[ANS], sizeof(t_vector)));
	 
	case_num = 4;
	val[ANS] = vec_init(0, 0, 0);
	val[OUR] = my_atovec(buf, input[case_num], idx);
	examine(case_num, input[case_num], idx, \
			memcmp(&val[OUR], &val[ANS], sizeof(t_vector)));
	

	case_num = 11;
	val[OUR] = my_atovec(buf, input[case_num], idx);
	examine(case_num, input[case_num], idx, \
			strcmp(buf, "err: exceed RGB value range\n"));
	

	case_num = 12;
	val[OUR] = my_atovec(buf, input[case_num], idx);
	examine(case_num, input[case_num], idx, \
			strcmp(buf, "err: exceed RGB value range\n"));

	case_num = 57;
	val[OUR] = my_atovec(buf, input[case_num], idx);
	examine(case_num, input[case_num], idx, \
			strcmp(buf, "err: exceed RGB value range\n"));

	case_num = 58;
	val[OUR] = my_atovec(buf, input[case_num], idx);
	examine(case_num, input[case_num], idx, \
			strcmp(buf, "err: exceed RGB value range\n"));

	case_num = 60;
	val[OUR] = my_atovec(buf, input[case_num], idx);
	examine(case_num, input[case_num], idx, \
			strcmp(buf, "err: exceed RGB value range\n"));
}
// cc vector.c remove.c main_atovec.c print_utils.c ft_atovec.c ft_atod.c free_utils.c -Llibft/ -lft -Ilibft/libft_src -g && ./a.out
