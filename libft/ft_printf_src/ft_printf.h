/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:41:11 by sesim             #+#    #+#             */
/*   Updated: 2022/06/08 09:27:37 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdint.h>

int	ft_printf(const char *format, ...);
int	form_c(int c);
int	form_s(char *s);
int	form_d(int d);
int	form_u(unsigned int u);
int	form_p(uintptr_t p);
int	form_x(unsigned int x, char format);

#endif
