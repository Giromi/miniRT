/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 11:29:10 by sesim             #+#    #+#             */
/*   Updated: 2022/07/10 00:02:42 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

size_t	ft_strlen(const char *s);
int		ft_isspace(int c);
int		ft_tolower(int c);

int	ft_base_cmp(char c)
{
	static char	*u_base = "0123456789ABCDEF";
	static char	*l_base = "0123456789abcdef";
	int	i;
	int	base;

	i = 0;
	base = ft_tolower(c);
	while (u_base[i] != '\0')
	{
		if (u_base[i] == base || l_base[i] == base)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_hex(char *str)
{
	int	k;
	int	dec_num;
	int	hex_num;

	k = 0;
	dec_num = 0;
	if (str[k] == '0' && str[k + 1] == 'x')
		k += 2;
	else
		return (-1);
	hex_num = ft_base_cmp(str[k]);
	while (hex_num != -1)
	{
		dec_num *= 16;
		dec_num += hex_num;
		k++;
		hex_num = ft_base_cmp(str[k]);
	}
	return (dec_num);
}
