/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 21:10:46 by minsuki2          #+#    #+#             */
/*   Updated: 2022/10/20 14:46:37 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include <pthread.h>
# include "minirt.h"

# ifndef PHILO_N
#  define PHILO_N 20
# endif

typedef struct s_thread
{
	t_record	rec;
	t_info		*info;
	pthread_t	hand;
	int			idx;
	int			section;
}	t_thread;

/*****  thread funcs  *****/
void	slave_whip(t_thread *slave);

#endif
