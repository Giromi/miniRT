/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 13:18:55 by sesim             #+#    #+#             */
/*   Updated: 2022/10/18 12:16:30 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "my_func.h"

static int	_check_val(size_t nb, int pn)
{
	if (nb > 2147483647 && pn == 1)
		return (-1);
	else if (nb > 2147483648 && pn == -1)
		return (0);
	return ((int)nb * pn);
}

int	ft_atoi_exit(const char *str)
{
	unsigned int	i;
	size_t			res;
	int				pn;

	i = -1;
	res = 0;
	pn = 1;
	if (str[++i] == 43 || str[i] == 45)
		if (str[i++] == 45)
			pn *= -1;
	if (!str[i])
		ft_strerror("err: invalid digit arguemnts");
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			ft_strerror("err: invalid digit arguemnts");
		res *= 10;
		res += str[i++] - 48;
	}
	return (_check_val(res, pn));
}
