/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 21:10:46 by minsuki2          #+#    #+#             */
/*   Updated: 2022/10/19 18:33:11 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include <pthread.h>
# include "minirt.h"

# ifndef PHILO_N
#  define PHILO_N 6
# endif

typedef struct s_thread
{
	t_info		*info;
	t_moment	spot;
	t_ray		ray;
	pthread_t	hand;
	int			idx;
}	t_thread;

void	*ft_rendering(void *param);

#endif
