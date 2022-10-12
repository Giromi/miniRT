/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_form.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:50:33 by sesim             #+#    #+#             */
/*   Updated: 2022/06/08 09:28:28 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

static size_t	nb_size(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*ft_itoa(int n)
{
	char	*res;
	size_t	i;

	i = nb_size(n) + 1;
	res = (char *)malloc(sizeof(char) * i);
	if (res == 0)
		return (0);
	res[--i] = '\0';
	while (i)
	{
		if (n < 0)
		{
			res[--i] = 48 - (n % 10);
		}
		else
			res[--i] = 48 + (n % 10);
		if (n <= 0 && res[1] != '\0')
			res[0] = '-';
		n /= 10;
	}
	return (res);
}

int	form_d(int d)
{
	char	*val;
	int		res;

	val = ft_itoa(d);
	res = form_s(val);
	if (val != 0)
		free(val);
	return (res);
}
