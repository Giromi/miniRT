/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:06:31 by sesim             #+#    #+#             */
/*   Updated: 2022/10/13 12:13:44 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*spot;
	t_list	*res;

	if (lst == 0 || f == 0)
		return (0);
	res = 0;
	while (lst)
	{
		spot = ft_lstnew(f(lst->content));
		if (!spot)
		{
			ft_lstclear(&res, del);
			return (0);
		}
		ft_lstadd_back(&res, spot);
		spot = spot->next;
		lst = lst->next;
	}
	return (res);
}
