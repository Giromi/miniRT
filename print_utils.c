#include "libft.h"

void	ft_strerror(char *err)
{
	ft_putendl_fd(err, 2);
	exit(1);
}
