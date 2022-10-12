/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_form.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 18:11:40 by sesim             #+#    #+#             */
/*   Updated: 2022/06/08 09:28:21 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_hex(unsigned int x, const char format, int *res)
{
	if (x >= 16)
	{
		print_hex(x / 16, format, res);
		print_hex(x % 16, format, res);
	}
	else
	{
		if (x <= 9)
			form_c(x + '0');
		else
		{
			if (format == 'x')
				form_c(x - 10 + 'a');
			else if (format == 'X')
				form_c(x - 10 + 'A');
		}
		(*res)++;
	}
}

int	form_x(unsigned int x, const char format)
{
	int	res;

	res = 0;
	if (x == 0)
		res += write(1, "0", 1);
	else
		print_hex(x, format, &res);
	return (res);
}

static void	print_ptr(uintptr_t p, int *res)
{
	if (p >= 16)
	{
		print_ptr(p / 16, res);
		print_ptr(p % 16, res);
	}
	else
	{
		if (p <= 9)
			form_c(p + '0');
		else
			form_c(p - 10 + 'a');
		(*res)++;
	}
}

int	form_p(uintptr_t p)
{
	int	res;

	res = write(1, "0x", 2);
	if (p == 0)
		res += write(1, "0", 1);
	else
		print_ptr(p, &res);
	return (res);
}
