/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 21:10:46 by minsuki2          #+#    #+#             */
/*   Updated: 2022/10/12 16:39:29 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <limits.h>
# include <math.h>
# include <fcntl.h>
# include "libft/libft_src/libft.h"
# include "libft/gnl_src/get_next_line.h"
# include "mlx/mlx.h"

# define IMG_W WIN_W
# define IMG_H WIN_H

# define WIN_W 1280
# define WIN_H 720

# define EPSILON 1e-6
# define LUMEN 3
# define COMMENT '#'

enum e_options
{
	A	=	0,
	C	=	1,
	L	=	2,
	PL	=	0b100,
	SP	=	0b1000,
	CY	=	0b10000,
	CN	=	0b100000,
	CP	=	0b1000000,
	BM	=	0b010000000000000000000000,
	CH	=	0b100000000000000000000000
};

enum e_return_val
{
	ERROR = -1,
	FALSE,
	TRUE,
};

enum e_event
{
	EVENT_KEY_PRESS		=	2,
	EVENT_MOUSE_CLICK	=	4,
	EVENT_CLICK_EXIT	=	17
};

enum e_keycode
{
	KEY_ESC			=		53,
	KEY_UP			=		126,
	KEY_DOWN		=		125,
	KEY_LEFT		=		123,
	KEY_RIGHT		=		124,
	KEY_A			=		0,
	KEY_S			=		1,
	KEY_D			=		2,
	KEY_Q			=		12,
	KEY_W			=		13,
	KEY_E			=		14,
	KEY_R			=		15,
	KEY_I			=		34,
	KEY_TAB			=		48
};

enum e_tool
{
	RGB,
	XYZ,
	UNIT
};

enum e_two_idx
{
	X		=		0,
	Y		=		1,
	U		=		0,
	V		=		1,
	W		=		0,
	H		=		1,
	HORI	=		0,
	VERT	=		1,
	RADIUS	=		0,
	HEIGHT	=		1
};

enum e_three_idx
{
	CENTER	=	0,
	COLOR	=	1,
	ALBEDO	=	2,
	NORMAL	=	3
};

// enum e_material_type
// {
// 	A,
// 	C,
// 	L,
// 	SP,
// 	PL,
// 	CY,
// 	CN,
// 	CP
// };

typedef int			t_object_type;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef t_vector	t_color;
typedef t_vector	t_point;

typedef struct s_img
{
	void			*img_ptr;
	char			*file_name;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
}	t_image;

typedef struct s_mlx
{
	void		*ptr;
	void		*win;
	t_image		img;
}	t_mlx;

typedef struct s_ray
{
	t_point		orig;
	t_vector	dir;
}	t_ray;

typedef struct s_cam
{
	struct s_cam	*next;
	t_vector		mlx_vec[2];
	t_vector		normal;
	t_point			orig;
	t_point			start_point;
	double			viewport[2];
	double			focal_len;
	int				fov;
}	t_camera;

// typedef struct s_sphere
// {
// 	t_point	center;
// 	double	radius;
// 	double	radius2;
// }	t_sphere;

// typedef struct s_plane
// {
// 	t_point		center;
// 	t_vector	normal;
// 	double		radius;
// }	t_plane;

// typedef struct s_cylinder
// {
// 	t_point		center;
// 	double		radius;
// 	double		radius2;
// 	double		height;
// 	t_vector	normal;
// }	t_cylinder;

// typedef t_cylinder	t_cone;
// typedef struct s_object
// {
// 	t_object_type	type;
// 	void			*element;
// 	void			*next;
// 	t_color			albedo;
// 	t_image			*bump;
// 	t_image			*tex;
// 	int				checker;
// }	t_object;

typedef struct s_model   // radius 2 지움
{
	t_point		center;
	t_vector	normal;
	double		radius;
	double		height;
}	t_model;

typedef t_model		t_plane;
typedef t_model		t_sphere;
typedef t_model		t_cylinder;
typedef t_model		t_cone;

typedef struct	s_object
{
	struct s_object	*next;
	t_image			*bump;
	t_image			*tex;
	t_model			*elem;
	t_color			albedo;
	t_object_type   type;
}	t_object;


typedef struct s_hit_record
{
	t_point		p;
	t_vector	normal;
	t_vector	normal2;
	t_vector	albedo;
	t_vector	e1;
	t_vector	e2;
	double		tmin;
	double		tmax;
	double		t;
	double		u;
	double		v;
	int			front_face;
	int			checker;
	int			type;
}	t_hit_record;

typedef struct s_light
{
	struct s_light	*next;
	t_vector		origin;
	t_vector		light_color;
	double			brightness;
}	t_light;

typedef struct s_info
{
	t_hit_record	rec;
	t_mlx			mlx;
	t_image			bump;
	t_camera		*camera;
	t_object		*obj;
	t_light			*light;
	t_color			ambient;
	t_ray			ray;
}	t_info;

/***** vector funcs *****/
t_vector	vec_min(t_vector vec1, t_vector vec2);
t_vector	vec_once_add_point(t_point o, t_vector a, t_vector b, t_vector c);
t_vector	vec_add(t_vector u, t_vector v);
t_vector	vec_sub(t_vector u, t_vector v);
t_vector	vec_multi(t_vector u, t_vector v);
t_vector	vec_div(t_vector u, t_vector v);
t_vector	vec_multi_double(t_vector u, double n);
t_vector	vec_div_double(t_vector u, double n);
t_vector	vec_cross(t_vector u, t_vector v);
t_vector	vec_unit(t_vector u);
t_vector	vec_init(double x, double y, double z);
double		vec_dot(t_vector u, t_vector v);
double		vec_len(t_vector u);
double		vec_len_sqr(t_vector u);

/***** init funcs *****/
t_sphere	*sp_init(t_point center, double radius);
t_plane		*pl_init(t_point center, t_vector normal, double radius);
t_cylinder	*cy_init(t_point center, t_vector normal, \
							double radius, double height);
t_cone		*cn_init(t_point center, t_vector normal, \
						double radius, double height);
t_object	*obj_init(t_object_type type, t_vector albedo, t_model *element);

/***** put light funcs *****/
void		put_a(t_info *info, char **argv, int cnt, int type);
void		put_l(t_info *info, char **argv, int cnt, int type);

/***** put obj funcs *****/
void		put_pl(t_info *info, char **argv, int cnt, int type);
void		put_sp(t_info *info, char **argv, int cnt, int type);
void		put_cny(t_info *info, char **argv, int cnt, int type);
// void		put_cn(t_info *info, char **argv, int cnt, int type);

/***** obj utils funcs 1 *****/
t_point		get_cap_point(t_point center, t_vector normal, \
							double height, double sign);
void		get_texture_addr(t_object *obj, t_mlx *mlx);
void		get_bump_addr(t_object *obj, t_mlx *mlx);
void		obj_add(t_object **list, t_object *new);

/***** obj utils funcs 2 *****/
void		init_conlinder(t_vector *vec, double *format, char **argv);
void		bump_init(t_mlx *mlx, t_object *new, char *argv);
t_cone		*cone_init(t_point center, t_vector normal, \
						double radius, double height);


/*****  utils funcs  *****/
void		split_free(char **split);
void		ft_strerror(char *err);
void		is_sign(char *str, int *idx, double *sign);
double		ft_atod(char *str);
t_vector	ft_atovec(char *str, int flag);

/*****  my funcs  *****/
char		**my_split(char *line, char c);
void		*my_calloc(size_t count, size_t size);
int			my_open(const char *path, int oflag);

#endif
