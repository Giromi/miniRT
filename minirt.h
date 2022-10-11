#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <limits.h>
# include <math.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "mlx2/mlx.h"

# define EVENT_KEY_PRESS 2
# define EVENT_MOUSE_CLICK 4
# define EVENT_CLICK_EXIT 17
# define KEY_ESC 53
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_Q 12
# define KEY_W 13
# define KEY_E 14
# define KEY_R 15
# define KEY_I 34
# define KEY_TAB 48

# define COMMENT '#'

# define X 0
# define Y 1
# define U 0
# define V 1

# define WIN_H 720
# define WIN_W 1280

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

enum e_return_val
{
	ERROR = -1,
	TRUE,
	FALSE
};

# define RGB 0
# define XYZ 1
# define UNIT 2

# define EPSILON 1e-6
# define LUMEN 3

typedef enum e_material_type	t_object_type;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef t_vec	t_point;
typedef t_vec	t_color;

typedef struct s_img
{
	void	*img_ptr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	char	*file_name;
	char	*addr;
}	t_img;

typedef struct s_mlx
{
	t_img		img;
	void		*ptr;
	void		*win;
}	t_mlx;

typedef struct s_ray
{
	t_point	orig;
	t_vec	dir;
}	t_ray;

typedef struct s_camera
{
	t_point	orig;
	t_point	start_point;
	t_vec	mlx_vector[2];   // 0번은 mlx horizon 벡터, 1번은 mlx vertical 벡터
	t_vec	normal;
	double	viewport[2];    // 0번 : mlx w, 1번 : mlx h
	double	focal_len;
	void	*next;
	int		fov;
}	t_camera;

typedef struct s_model   // radius 2 지움
{
	t_point	center;
	t_vec	normal;
	double	radius;
	double	height;
}	t_model;

typedef t_model	t_plane;
typedef t_model	t_sphere;
typedef t_model	t_cylinder;
typedef t_model	t_cone;

typedef struct	s_object
{
    struct s_object	*next;
	t_img			*bump;
	t_img			*tex;
	t_model			*elem;
	t_color			albedo;
	t_object_type   type;
	int				checker;
}	t_object;

typedef struct s_record
{
    t_point		p;
    t_vec		normal;  // normal2 지움
	t_color		albedo;
	t_vec		dir_vec[2];  // e1, e2
    double		root[3];     // 0이 min, 1이 t val, 2가 max
	double		uv[2];       // u, v
    int			front_face;
	int			checker;
}	t_record;

typedef struct  s_light
{
	struct s_light	*next;
    t_color			light_color;
    t_vec			origin;
    double			brightness;
}	t_light;

typedef struct s_info
{
	t_mlx		mlx;
    t_object	*obj;
    t_record	hit_p;
    t_camera	*camera;
    t_light		*light;
    t_ray		ray;
    t_color		ambient;
}	t_info;

t_vec 	vec_min(t_vec vec1, t_vec vec2);
t_vec	vec_add(t_vec u, t_vec v);
t_vec	vec_sub(t_vec u, t_vec v);
t_vec	vec_multi(t_vec u, t_vec v);
t_vec	vec_div(t_vec u, t_vec v);
t_vec	vec_multi_double(t_vec u, double n);
t_vec	vec_div_double(t_vec u, double n);
double	vec_dot(t_vec u, t_vec v);
t_vec	vec_cross(t_vec u, t_vec v);
double	vec_len(t_vec u);
double	vec_len_sqr(t_vec u);
t_vec	vec_unit(t_vec u);
t_vec	vec_init(double x, double y, double z);


t_object    *object_init(t_object_type type, void *element, t_vec albedo, int checker);
t_sphere	*sphere_init(t_point center, double radius);
t_plane		*plane_init(t_point center, t_vec normal, double radius);
t_cylinder	*cylinder_init(t_point center, double radius, double height, t_vec normal);
t_light     *light_init(t_vec light_origin, t_vec light_color, double brightness);
t_cone		*cone_init(t_point center, double radius, double height, t_vec normal);



// ---------utils.c---------//
void	is_sign(char *str, int *idx, double *sign);
double	ft_atod(char *str);
void	check_unit(double *x, double *y, double *z, int flag);
t_vec	ft_atovec(char *str, int flag);
void	ft_strerror(char *err);
void	split_free(char **split);


// ---------object.c--------//
void			record_init(t_record *rec);
int				hit_sphere(t_object *obj, t_ray ray, t_record *rec);
int				hit_obj(t_object *obj, t_ray ray, t_record *rec);
int				hit(t_object *obj, t_ray ray, t_record *rec);
t_vec			point_light_get(t_info *info, t_light *light);
t_vec	phong_lighting(t_info *info);
t_point			ray_at(t_ray ray, double t);
int				hit_plane(t_object *obj, t_ray ray, t_record *rec);
int				in_shadow(t_object *objs, t_ray light_ray, double light_len);
t_ray			ray_init(t_point orig, t_vec dir);

void    set_face_normal(t_ray ray, t_record *rec);
t_vec	convert_color_to_normal(int	color);


// ---------put.c--------//
void    obj_add(t_object **list, t_object *new);
void    light_add(t_light **list, t_light *new);
void	put_a(t_info *info, char **argv, int cnt);
t_camera    *camera_init(t_point coor, t_vec normal, int fov);
void    camera_add(t_camera **list, t_camera *new);
void	put_c(t_info *info, char **argv, int cnt);
void	put_l(t_info *info, char **argv, int cnt);
void	put_sp(t_info *info, char **argv, int cnt);
void	put_pl(t_info *info, char **argv, int cnt);
t_point	get_cap_point(t_point center, double height, t_vec normal, double sign);
void	put_cy(t_info *info, char **argv, int cnt);
void	put_cn(t_info *info, char **argv, int cnt);
int 	check_format(char *format);
void	put_info(t_info *info, char **argv);
void	get_bump_addr(t_object *bump, t_mlx *mlx);

// ---------minirt.c--------//
void info_init(t_info *info, char *file);
t_vec	convert_color_to_normal(int	color);
int	convert_color(t_vec clr);
void  my_mlx_pixel_put(t_img *img, int x, int y, t_color color);
void	ray_primary(t_ray *ray, t_camera *cam, double u, double v);
t_color    ray_color(t_info *info);
t_ray	ray_init(t_point orig, t_vec dir);
void    set_face_normal(t_ray ray, t_record *rec);
void ft_draw(t_info *info, t_mlx *mlx);
void	main_loop(t_info *info, t_mlx *mlx, int key);
int	key_press(int keycode, void *param);


// ---------tmp--------//
void	print_obj(t_object *obj);
void	print_cam(t_camera *cam);
void debugPrintVec(char *str, t_vec *vector);
void	ae();
void debugPrintDouble(char *str1, char *str2, double a, double b);


/*********  my func  ********/
int		my_open(const char *path, int oflag);
void	*my_calloc(size_t count, size_t size);

#endif
