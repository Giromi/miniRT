/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:56:58 by sesim             #+#    #+#             */
/*   Updated: 2022/06/08 09:27:47 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

int	format_checker(va_list *ap, const char format)
{
	int	res;

	res = 0;
	if (format == 'c')
		res += form_c(va_arg(*ap, int));
	else if (format == 's')
		res += form_s(va_arg(*ap, char *));
	else if (format == 'd' || format == 'i')
		res += form_d(va_arg(*ap, int));
	else if (format == 'u')
		res += form_u(va_arg(*ap, unsigned int));
	else if (format == 'p')
		res += form_p((uintptr_t)va_arg(*ap, void *));
	else if (format == 'x' || format == 'X')
		res += form_x(va_arg(*ap, unsigned int), format);
	else if (format == '%')
		res += write(1, "%", 1);
	return (res);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		res;

	va_start(ap, format);
	res = 0;
	while (*format != 0)
	{
		if (*format == '%')
		{
			res += format_checker(&ap, *(format + 1));
			format += 2;
		}
		else
		{
			res += write(1, format, 1);
			format++;
		}
	}
	va_end(ap);
	return (res);
}
