/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_adtoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 13:18:55 by sesim             #+#    #+#             */
/*   Updated: 2022/06/17 08:05:02 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_isdigit(int c);

int	check_val(size_t nb, int pn)
{
	if (nb > 2147483647 && pn == 1)
		return (-1);
	else if (nb > 2147483648 && pn == -1)
		return (0);
	return ((int)nb * pn);
}

int	ft_adtoi(const char *str)
{
	unsigned int	i;
	size_t			res;
	int				pn;

	i = 0;
	res = 0;
	pn = 1;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			pn *= -1;
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		res *= 10;
		res += str[i] - 48;
		i++;
	}
	return (check_val(res, pn));
}
