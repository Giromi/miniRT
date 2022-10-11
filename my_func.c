#include "minirt.h"

int	my_open(const char *path, int oflag)
{
	int	fd;

	fd = open(path, oflag);
	if (fd < 0)
		ft_strerror("err: cannot open file");
	return (fd);
}

void	*my_calloc(size_t count, size_t size)
{
	void	*res;

	res = ft_calloc(count, size);
	if (!res)
		ft_strerror("err: cannot allocate");
	return (res);
}
