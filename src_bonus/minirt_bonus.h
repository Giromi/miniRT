/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 21:10:46 by minsuki2          #+#    #+#             */
/*   Updated: 2022/10/26 11:49:20 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include <pthread.h>

# ifndef PHILO_N
#  define PHILO_N 20
# endif

# ifndef SAMPLE_PER_PIXEL
#  define SAMPLE_PER_PIXEL 30
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

/*****  rendering funcs  *****/
void	*rendering(void *param);
void	*anti_aliaising(void *param);

#endif
