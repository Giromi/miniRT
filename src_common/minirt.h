/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 21:10:46 by minsuki2          #+#    #+#             */
/*   Updated: 2022/10/20 14:31:40 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <limits.h>
# include <math.h>
# include <fcntl.h>
# include "mlx.h"

# define IMG_W WIN_W
# define IMG_H WIN_H

# define WIN_W 1280
# define WIN_H 720

# define EPSILON 1e-6
# define MAX_VIEW 1e6
# define LUMEN 3
# define COMMENT '#'

# define KS 0.5
# define KSN 64

enum e_options
{
	A	=	0,
	L	=	1,
	C	=	2,
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
	U		=		0,
	V		=		1,
	W		=		0,
	H		=		1,
	UP		=		0,
	DOWN	=		1,
	HORI	=		0,
	VERT	=		1,
	RADIUS	=		0,
	HEIGHT	=		1,
	C_P		=		0,
	C_Q		=		1,
	C_H		=		1,
	O_C		=		1,
	ONE		=		0,
	TWO		=		1,
	E_ONE	=		0,
	E_TWO	=		1,
	LIGHT	=		0,
	OBJECT	=		1,
	RAY		=		0,
	DIR		=		1,
	LEN		=		0,
	KD		=		1,
	GAP		=		0,
	OFFSET	=		1
};

enum e_three_idx
{
	B			=		1,
	V_N			=		0,
	V_W			=		1,
	W_N			=		2,
	MIN			=		0,
	VAL			=		1,
	MAX			=		2,
	CENTER		=		0,
	COLOR		=		1,
	ALBEDO		=		2,
	NORMAL		=		3,
	NUMERATOR	=		0,
	DENOMINATOR	=		1,
	TARGET		=		2,
	COMPUTE		=		0,
	DIFFUSE		=		2,
	SPECULAR	=		3
};

typedef int			t_object_type;

typedef struct s_img
{
	void	*img_ptr;
	char	*file_name;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_image;

typedef struct s_mlx
{
	t_image	img;
	void	*ptr;
	void	*win;
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

typedef struct s_func
{
	double	term[3];
	double	root[2];
	double	h_prime;
	int		idx;
	t_point	hit_p;
}	t_function;

typedef struct s_model
{
	t_point		center;
	t_vector	normal;
	double		radius;
	double		height;
}	t_model;

typedef t_model		t_plane;
typedef t_model		t_sphere;
typedef t_model		t_conlinder;

typedef struct s_object
{
	struct s_object	*next;
	t_image			*bump;
	t_image			*tex;
	t_model			*elem;
	t_color			albedo;
	t_object_type	type;
}	t_object;

typedef struct s_moment
{
	t_vector	e_[2];
	t_vector	normal;	// 빛의 방향으로 변경
	t_vector	albedo;
	t_point		p;
	double		t_[3];
	double		uv_dir[2];
	int			checker;
	int			type;
}	t_moment;

typedef struct s_light
{
	struct s_light	*next;
	t_vector		origin;
	t_vector		light_color;
	double			brightness;
}	t_light;

typedef struct s_record
{
	t_moment		spot;
	t_ray			ray;
}	t_record;

typedef struct s_info
{
	t_mlx			mlx;
	t_camera		*camera;
	t_object		*obj;
	t_light			*light;
	t_color			ambient;
}	t_info;

/***** init funcs *****/
t_sphere	*sp_init(t_point center, double radius);
t_plane		*pl_init(t_point center, t_vector normal, double radius);
t_conlinder	*cny_init(t_point center, t_vector normal, \
							double radius, double height);
t_object	*obj_init(t_object_type type, t_vector albedo, t_model *element);

/***** put funcs *****/
void		info_init(t_info *info, char *file);
void		info_error(int *form_check);
void		put_a(t_info *info, char **argv, int cnt, int type);
void		put_l(t_info *info, char **argv, int cnt, int type);
void		put_c(t_info *info, char **argv, int cnt, int type);
void		put_pl(t_info *info, char **argv, int cnt, int type);
void		put_sp(t_info *info, char **argv, int cnt, int type);
void		put_cny(t_info *info, char **argv, int cnt, int type);

/***** obj utils funcs 1 *****/
void		get_texture_addr(t_object *obj, t_mlx *mlx);
void		get_bump_addr(t_object *obj, t_mlx *mlx);
void		obj_add(t_object **list, t_object *new);

/***** obj utils funcs 2 *****/
void		init_conlinder(t_vector *vec, double *format, char **argv);
void		bump_init(t_mlx *mlx, t_object *new, char **argv, int cnt);
t_conlinder	*cone_init(t_point center, t_vector normal, \
						double radius, double height);

/***** draw funcs *****/
void		my_mlx_pixel_put(t_image *img, int x, int y, t_color color);
t_color		cur_point_color(t_info *info, t_record *rec);
void		set_ray_vec(t_ray *ray, t_camera *cam, int x, int y);
void		flip_normal_face(t_ray *ray, t_moment *spot);

/***** draw utils funcs *****/
t_vector	convert_color_to_normal(int color);
int			convert_color(t_vector *clr);

/***** ray funcs *****/
int			is_ray_hit(t_object *obj, t_ray *ray, t_moment *spot);
int			ray_at_plane(t_object *obj, t_ray *ray, t_moment *spot);
int			ray_at_cap(t_object *obj, t_ray *ray, t_moment *spot);
int			ray_at_sphere(t_object *obj, t_ray *ray, t_moment *spot);
int			ray_at_conlinder(t_object *obj, t_ray *ray, t_moment *spot, \
					void (*get_abc)(double *term, t_ray *ray, t_model *cy));
int			ray_at_cap(t_object *obj, t_ray *ray, t_moment *spot);
t_point		get_hit_point(t_ray *ray, double t);

/***** ray utils funcs 1 *****/
void		get_spot_e_vector(t_moment *spot, t_vector *obj_n, t_vector std_n);
void		get_bump_rgb(t_moment *spot, t_object *obj);
int			is_t_in_range(t_moment *spot, double root);
int			is_h_in_range(t_model *cny, t_ray *ray, t_vector *coor, \
															t_function *func);

/***** light funcs *****/
t_vector	phong_lighting(t_info *info, t_record *rec);
int			get_diffuse(t_object *obj, t_record *rec, t_light *cur_light, t_vector *light);
void		get_specular(t_record *rec, t_light *cur_light, t_vector *light);

/*****  math funcs  *****/
void		get_sp_abc(double *term, t_ray *ray, t_model *sp);
void		get_cy_abc(double *term, t_ray *ray, t_model *cy);
void		get_cn_abc(double *term, t_ray *ray, t_model *cy);
int			get_2d_root(t_function	*func, t_ray *ray, t_model *elem, \
						void (*get_abc)(double *, t_ray *, t_model *));

/*****  mlx funcs  *****/
int			key_press(int keycode, void *param);

/*****  utils funcs  *****/
void		is_sign(char *str, int *idx, double *sign);
double		ft_atod(char *str);
int			ft_atoi_exit(const char *str);
t_vector	ft_atovec(char *str, int flag);



/*****  mandatory funcs  *****/
void		ft_draw(t_info *info, t_mlx *mlx);




void		print_light(t_light *light); // 지워야함
void		debugPrintVec(char *str, t_vector *vector);

#endif
