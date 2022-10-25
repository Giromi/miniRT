/* ************************************************************************** */
/*                                                                            */ /*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 21:10:46 by minsuki2          #+#    #+#             */
/*   Updated: 2022/10/24 19:01:31 by minsuki2         ###   ########.fr       */
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
# define WEIGHT_VAL_TRANSLATED_CAM	0.3
# define WEIGHT_VAL_ROTATED_CAM	0.2

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
	TRUE
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
	KEY_C			=		8,
	KEY_Q			=		12,
	KEY_W			=		13,
	KEY_E			=		14,
	KEY_R			=		15,
	KEY_O			=		31,
	KEY_P			=		35,
	KEY_I			=		34,
	KEY_V			=		9,
	KEY_SHIFT		=		57,
	KEY_SPC			=		49,
	KEY_CTRL		=		256,
	KEY_COMMA		=		43,
	KEY_DOT			=		47,
	KEY_TAB			=		48,
	MOU_HEEL_UP		=		4,
	MOU_HEEL_DOWN	=		5
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
	OFFSET	=		1,
	R_HALF	=		0
};

enum e_three_idx
{
	T			=		0,
	B			=		1,
	N			=		2,
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
	struct s_cam	*prev;
	struct s_cam	*next;
	t_vector		mlx_vec[3][2];
	t_vector		vec[3];
	t_point			orig;
	t_point			start_point;
	double			viewport[2];
	double			focal_len;
	int				fov;
}	t_camera;

typedef struct s_func
{
	t_point	hit_p;
	double	term[3];
	double	root[2];
	double	h_prime;
	int		idx;
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
	struct s_object	*prev;
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
	t_vector	normal;
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
	t_camera		*cam;
	t_object		*obj;
	t_light			*light;
	t_color			ambient;
	int				status;
}	t_info;

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
void		set_ray_vec(t_ray *ray, t_camera *cam, double *vdx);
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
void		set_viewport(double *viewport, int fov);
int			key_compatible_param(int keycode, void *param);
int			mouse_compatible_param(int x, int y, int button, void *param);
void		key_event(t_info *info, int key);
void		mouse_event(t_info *info, int button);
void		change_obj(t_info *info, int key);
int			is_translate_key(int key);
int			is_rotate_key(int key);
void		translate_center(t_camera *cam, t_point *center, int key);

/*****  mandatory funcs  *****/
void		ft_draw(t_info *info, t_mlx *mlx);




void		print_light(t_light *light); // 지워야함
void		debugPrintVec(char *str, t_vector *vector);
void	print_prev_cam(t_camera *cam); // 지워야함

#endif
