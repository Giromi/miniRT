/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 21:10:46 by minsuki2          #+#    #+#             */
/*   Updated: 2022/10/11 22:52:44 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <limits.h>
# include <math.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "mlx/mlx.h"

# define IMG_W WIN_W
# define IMG_H WIN_H

# define WIN_W 1280
# define WIN_H 720

# define EPSILON 1e-6
# define LUMEN 3
# define COMMENT '#'

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

enum e_idx
{
	X		=		0,
	Y		=		1,
	U		=		0,
	V		=		1,
	W		=		0,
	H		=		1,
	HORI	=		0,
	VERT	=		1
};

enum e_material_type
{
	A,
	C,
	L,
	SP,
	PL,
	CY,
	CN,
	CAP
};


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
}	t_img;

typedef struct s_mlx
{
	void		*ptr;
	void		*win;
	t_img		img;
}			t_mlx;

typedef struct s_ray
{
	t_point		orig;
	t_vector	dir;
}	t_ray;

typedef struct s_camera
{
	t_point			orig;
	t_point			start_point;
	t_vector		mlx_vec[2];
	double			viewport[2];
	double			focal_len;
	t_vector		normal;
	int				fov;
	void			*next;
}	t_camera;

typedef struct s_sphere
{
	t_point	center;
	double	radius;
	double	radius2;
}			t_sphere;

typedef struct s_plane
{
	t_point		center;
	t_vector	normal;
	double		radius;
}			t_plane;

typedef struct s_cylinder
{
	t_point		center;
	double		radius;
	double		radius2;
	double		height;
	t_vector	normal;
}	t_cylinder;

typedef t_cylinder	t_cone;

typedef struct s_object
{
	t_object_type	type;
	void			*element;
	void			*next;
	t_color			albedo;
	t_img			*bump;
	t_img			*tex;
	int				checker;
}	t_object;

typedef struct s_hit_record
{
	t_point		p;
	t_vector	normal;
	t_vector	normal2;
	double		tmin;
	double		tmax;
	double		t;
	int			front_face;
	int			type;
	t_vector	albedo;
	double		u;
	double		v;
	t_vector	e1;
	t_vector	e2;
	int			checker;
}				t_hit_record;

typedef struct s_light
{
	t_vector	origin;
	t_vector	light_color;
	double		brightness;
	void		*next;
}			t_light;

typedef struct s_info
{
	t_mlx			mlx;
	t_img			bump;
	t_camera		*camera;
	t_object		*obj;
	t_light			*light;
	t_color			ambient;
	t_ray			ray;
	t_hit_record	rec;
}					t_info;

t_vector	vec_min(t_vector vec1, t_vector vec2);
t_vector	vec_once_add_at_point(t_point o, t_vector a, t_vector b, t_vector c);
t_vector	vec_add(t_vector u, t_vector v);
t_vector	vec_sub(t_vector u, t_vector v);
t_vector	vec_multi(t_vector u, t_vector v);
t_vector	vec_div(t_vector u, t_vector v);
t_vector	vec_multi_double(t_vector u, double n);
t_vector	vec_div_double(t_vector u, double n);
double		vec_dot(t_vector u, t_vector v);
t_vector	vec_cross(t_vector u, t_vector v);
double		vec_len(t_vector u);
double		vec_len_sqr(t_vector u);
t_vector	vec_unit(t_vector u);
t_vector	vec_init(double x, double y, double z);

t_object	*object_init(t_object_type type, void *element, t_vector albedo, \
																int checker);
t_sphere	*sphere_init(t_point center, double radius);
t_plane		*plane_init(t_point center, t_vector normal, double radius);
t_cylinder	*cylinder_init(t_point center, double radius, double height, \
															t_vector normal);
t_light		*light_init(t_vector light_origin, t_vector light_color, \
															double brightness);
t_cone		*cone_init(t_point center, double radius, double height, \
															t_vector normal);

// ---------utils.c---------//
void		is_sign(char *str, int *idx, double *sign);
double		ft_atod(char *str);
void		check_unit(double *x, double *y, double *z, int flag);
t_vector	ft_atovec(char *str, int flag);
void		ft_strerror(char *err);
void		split_free(char **split);

// ---------object.c--------//
void		record_init(t_hit_record *rec);
int			hit_sphere(t_object *obj, t_ray ray, t_hit_record *rec);
int			hit_obj(t_object *obj, t_ray ray, t_hit_record *rec);
int			hit(t_object *obj, t_ray ray, t_hit_record *rec);
t_vector	point_light_get(t_info *info, t_light *light);
t_vector	phong_lighting(t_info *info);
t_point		ray_at(t_ray ray, double t);
int			hit_plane(t_object *obj, t_ray ray, t_hit_record *rec);
int			in_shadow(t_object *objs, t_ray light_ray, double light_len);
t_ray		ray_init(t_point orig, t_vector dir);

void		set_face_normal(t_ray ray, t_hit_record *rec);
t_vector	convert_color_to_normal(int color);

// ---------put.c--------//
void		obj_add(t_object **list, t_object *new);
void		light_add(t_light **list, t_light *new);
void		put_a(t_info *info, char **argv, int cnt);
t_camera	*camera_init(t_point coor, t_vector normal, int fov);
void		camera_add(t_camera **list, t_camera *new);
void		put_c(t_info *info, char **argv, int cnt);
void		put_l(t_info *info, char **argv, int cnt);
void		put_sp(t_info *info, char **argv, int cnt);
void		put_pl(t_info *info, char **argv, int cnt);
t_point		get_cap_point(t_point center, double height, t_vector normal, \
																double sign);
void		put_cy(t_info *info, char **argv, int cnt);
void		put_cn(t_info *info, char **argv, int cnt);
int			check_format(char *format);
void		get_bump_addr(t_object *bump, t_mlx *mlx);
void		put_info(t_info *info, char **argv);

// ---------minirt.c--------//
void		info_init(t_info *info, char *file);
t_vector	convert_color_to_normal(int color);
int			convert_color(t_vector clr);
void		my_mlx_pixel_put(t_img *img, int x, int y, t_color color);
void		ray_primary(t_ray *ray, t_camera *cam, double u, double v);
t_color		ray_color(t_info *info);
t_ray		ray_init(t_point orig, t_vector dir);
void		set_face_normal(t_ray ray, t_hit_record *rec);
void		ft_draw(t_info *info, t_mlx *mlx);
void		main_loop(t_info *info, t_mlx *mlx, int key);
int			key_press(int keycode, void *param);

// ---------tmp--------//
void		print_obj(t_object *obj);
void		print_cam(t_camera *cam);
void		debugPrintVec(char *str, t_vector *vector);
void		debugPrintDouble(char *str1, char *str2, double a, double b);
int			my_open(const char *path, int oflag);
void		*my_calloc(size_t count, size_t size);

#endif
