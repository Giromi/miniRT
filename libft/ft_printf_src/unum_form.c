/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unum_form.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:50:33 by sesim             #+#    #+#             */
/*   Updated: 2022/06/08 09:28:41 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

static int	unb_size(unsigned int n)
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

static char	*ft_uitoa(unsigned int n)
{
	char	*res;
	int		i;

	i = unb_size(n) + 1;
	res = (char *)malloc(sizeof(char) * i);
	if (res == 0)
		return (0);
	res[--i] = '\0';
	while (i)
	{
		res[--i] = 48 + (n % 10);
		n /= 10;
	}
	return (res);
}

int	form_u(unsigned int u)
{
	char	*val;
	int		res;

	val = ft_uitoa(u);
	res = form_s(val);
	if (val != 0)
		free(val);
	return (res);
}
