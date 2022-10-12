/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 13:43:59 by sesim             #+#    #+#             */
/*   Updated: 2022/07/19 08:06:25 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_g(char *s)
{
	size_t	i;

	i = 0;
	if (s == 0)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr_g(char *s, int c)
{
	if (s == 0)
		return (0);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}

size_t	ft_strlcpy_g(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen_g(src);
	if (dstsize == 0)
		return (src_len);
	while (i < src_len && i + 1 < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

char	*ft_strjoin_g(char *s1, char *s2)
{
	char	*res;
	int		len;

	len = ft_strlen_g(s1);
	res = (char *)malloc(sizeof(char) * (len + ft_strlen_g(s2) + 1));
	if (res == 0)
		return (0);
	ft_strlcpy_g(res, s1, (len + 1));
	while (*s2)
	{
		res[len++] = *s2;
		s2++;
	}
	res[len] = '\0';
	free(s1);
	s1 = 0;
	return (res);
}

char	*new_line(char *bac)
{
	char	*new;
	int		m_len;
	int		c_len;

	if (!ft_strchr_g(bac, '\n'))
	{
		free (bac);
		bac = 0;
		return (0);
	}
	m_len = ft_strlen_g(bac) - (ft_strchr_g(bac, '\n') - bac) + 1;
	c_len = ft_strchr_g(bac, '\n') - bac + 1;
	new = malloc(sizeof(char) * m_len);
	if (new == 0)
		return (0);
	ft_strlcpy_g(new, (bac + c_len), m_len);
	free(bac);
	bac = 0;
	return (new);
}
