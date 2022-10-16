/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:11:47 by sesim             #+#    #+#             */
/*   Updated: 2022/10/16 20:21:33 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	_check_options(char *format)
{
	if (*format++ != '\0')
	{
		if (!ft_strncmp(format, "ch", 3))
			return (CH);
		else if (!ft_strncmp(format, "bm", 3))
			return (BM);
	}
	return (FALSE);
}

static int	_check_format(char *format, int *form_check)
{
	int	len;
	int	bit;

	if (!format)
		return (-1);
	len = ft_strchr_idx(format, '-');
	bit = 0;
	if (!ft_strncmp(format, "A", 2) && ++form_check[A])
		bit |= A;
	else if (!ft_strncmp(format, "L", 2) && ++form_check[L])
		bit |= L;
	else if (!ft_strncmp(format, "C", 2) && ++form_check[C])
		bit |= C;
	else if (!ft_strncmp(format, "pl", len))
		bit |= PL;
	else if (!ft_strncmp(format, "sp", len))
		bit |= SP;
	else if (!ft_strncmp(format, "cy", len))
		bit |= CY;
	else if (!ft_strncmp(format, "cn", len))
		bit |= CN;
	else
		ft_strerror("err: wrong format");
	bit |= _check_options(format + len);
	return (bit);
}

void	put_info(t_info *info, char **argv, int *form_check)
{
	static void	(*run[7])(t_info *, char **, int, int) = \
				{put_a, put_l, put_c, put_pl, put_sp, put_cny};
	int			type;
	int			cnt;
	int			idx;

	type = _check_format(argv[0], form_check);
	if (type > 3)
		idx = log(type & 0xFF) / log(2) + 1;
	else
		idx = type;
	cnt = -1;
	if (type & CN)
		idx = 5;
	while (argv[++cnt])
		;
	run[idx](info, argv, cnt, type);
}
