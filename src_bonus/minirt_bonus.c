/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 21:38:54 by minsuki2          #+#    #+#             */
/*   Updated: 2022/10/19 18:20:11 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "my_func.h"
#include "get_next_line.h"
#include "minirt_bonus.h"

static void	_info_error(int *form_check)
{
	if (form_check[A] != 1)
		ft_strerror("err: wrong ambeint format");
	if (form_check[L] < 0)
		ft_strerror("err: wrong light format");
	if (form_check[C] < 1)
		ft_strerror("err: wrong camera format");
}

void	info_init(t_info *info, char *file)
{
	char		**split;
	char		*line;
	int			form_check[3];
	int			fd;

	fd = my_open_rt(file, O_RDONLY);
	ft_bzero(form_check, sizeof(form_check));
	line = get_one_line(fd);
	if (line == NULL)
		ft_strerror("err: empty file");
	while (line)
	{
		if (line[0] && line[0] != COMMENT)
		{
			split = my_split(line, ' ');
			put_info(info, split, form_check);
			split_free(split);
		}
		free(line);
		line = get_one_line(fd);
	}
	close(fd);
	_info_error(form_check);
}

void	main_loop(t_info *info, t_mlx *mlx, int key)
{
	mlx_destroy_image(mlx->ptr, mlx->img.img_ptr);
	mlx_clear_window(mlx->ptr, mlx->win);
	mlx->img.img_ptr = mlx_new_image(mlx->ptr, WIN_W, WIN_H);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img_ptr, \
									&(mlx->img.bits_per_pixel), \
									&(mlx->img.line_length), \
									&(mlx->img.endian));
	if (key == 8)
		info->camera = info->camera->next;
	ft_draw(info, mlx);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.img_ptr, 0, 0);
}

int	key_press(int keycode, void *param)
{
	t_info *const	info = param;

	if (keycode == KEY_ESC)
		exit(0);
	else if (keycode == 8)
	{
		printf("C clicked\n");
		main_loop(info, &info->mlx, keycode);
	}
	return (0);
}


void	slave_whip(t_info *info, t_thread *slave)
{
	int			i;
	int			check;

	i = -1;
	while (++i < PHILO_N)
	{
		slave[i].idx = i;
		slave[i].info = info;
		check = pthread_create(&slave[i].hand, NULL, ft_rendering, &slave[i]);
		if (check)
			break ;
	}
	while (--i)
		pthread_join(slave[i].hand, NULL);
	if (check)
		ft_strerror("err: pthread_create error");
}

int	main(int argc, char **argv)
{
	t_info		info;
	t_thread	*slave;

	if (argc != 2)
		ft_strerror("err: wrong arguments");
	ft_memset(&info, 0, sizeof(t_info));
	info.mlx.ptr = mlx_init();
	info.mlx.win = mlx_new_window(info.mlx.ptr, WIN_W, WIN_H, "miniRT");
	info.mlx.img.img_ptr = mlx_new_image(info.mlx.ptr, IMG_W, IMG_H);
	info.mlx.img.addr = mlx_get_data_addr(info.mlx.img.img_ptr, \
											&(info.mlx.img.bits_per_pixel), \
											&(info.mlx.img.line_length), \
											&(info.mlx.img.endian));
	info_init(&info, argv[1]);
	slave = my_calloc(PHILO_N, sizeof(t_thread));
	slave_whip(&info, slave);
	mlx_put_image_to_window(info.mlx.ptr, info.mlx.win, \
							info.mlx.img.img_ptr, 0, 0);
	mlx_hook(info.mlx.win, EVENT_KEY_PRESS, 0, key_press, slave);
	mlx_loop(info.mlx.ptr);
	return (0);
}