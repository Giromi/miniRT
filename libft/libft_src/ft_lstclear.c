/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:04:49 by sesim             #+#    #+#             */
/*   Updated: 2022/10/13 12:13:44 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*spot;

	if (!lst)
		return ;
	while (*lst)
	{
		spot = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = spot;
	}
	*lst = 0;
}
