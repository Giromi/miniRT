/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsuki2 <minsuki2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:14:13 by minsuki2          #+#    #+#             */
/*   Updated: 2022/10/26 13:14:42 by minsuki2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

// debug
#include <stdio.h>

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
#endif
