#include "minirt.h"

void	split_free(char **split)
{
	int		i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
	split = 0;
}
