/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 12:54:56 by charles           #+#    #+#             */
/*   Updated: 2020/11/14 12:54:58 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "../src/GNL/get_next_line.h"
# include "mlx.h"

typedef struct	s_vect
{
	float		x;
	float		y;
	float		z;
}				t_vect;

typedef struct	s_ray
{
	t_vect		orig;
	t_vect		dir;
	t_vect		s_rgb;
}				t_ray;

typedef struct	s_camera
{
	t_vect		orig;
	t_vect		orit;
	float		fov;
}				t_camera;

typedef struct	s_res
{
	int			width;
	int			height;
}				t_res;

typedef struct	s_sphere
{
	t_vect		center;
	float		radius;
	int			mirror;
	int			transparent;
	float		mir_ratio;
}				t_sphere;

typedef struct	s_plane
{
	t_vect		p0;
	t_vect		n;
}				t_plane;

typedef struct	s_cylinder
{
	t_vect		p0;
	t_vect		n;
	float		radius;
	float		height;
	int			transparent;
}				t_cylinder;

typedef struct	s_square
{
	t_vect		p0;
	t_vect		n;
	float		height;
	int			mirror;
}				t_square;

typedef struct	s_triangle
{
	t_vect		p0;
	t_vect		p1;
	t_vect		p2;
}				t_triangle;

typedef struct	s_light
{
	int			type;
	t_vect		pos_light;
	float		ratio;
	t_vect		color;
}				t_light;

typedef struct	s_object
{
	int			type;
	t_plane		plane;
	t_sphere	sphere;
	t_cylinder	cylinder;
	t_square	square;
	t_triangle	triangle;
	int			spe_mat;
	int			flat_mat;
	float		spec_rate;
	t_vect		rgb;
	t_vect		p;
	t_vect		n;
	float		t;
}				t_object;

typedef struct	s_data
{
	void		*mlx_ptr;
	void		*mlx_win;
	void		*img_ptr;
	char		*img_data;
	char		*bmp_img;
	int			bpp;
	int			size_line;
	int			endian;
}				t_data;

typedef struct	s_error
{
	char		*error_type;
}				t_error;

typedef struct	s_scene
{
	t_res		res;
	t_camera	*cam;
	t_ray		ray;
	t_ray		ray_light;
	t_object	*objects;
	t_light		*lights;
	t_data		data;
	t_error		error;
	int			nb_light;
	int			nb_object;
	int			nb_cam;
	int			nb_r;
	int			nb_a;
	int			curr_cam;
	int			antialiasing;
	int			diffuse_light;
	int			sepia;
	int			nb_rebound;
	int			nrays;
	int			a_def;
	int			save_bmp;
	int			pos_img;
}				t_scene;

/*
** t_vectors
*/
t_vect			vectsub(t_vect v1, t_vect v2);
t_vect			vectadd(t_vect v1, t_vect v2);
t_vect			vectmult(t_vect v1, float num);
t_vect			vectsmult(t_vect v1, t_vect v2);
t_vect			vectdiv(t_vect v1, float num);
float			dot(t_vect v1, t_vect v2);
float			getnorm2 (t_vect ray);
t_vect			normalize(t_vect ray);
t_vect			crossp(t_vect v1, t_vect v2);

/*
** matrix calculations
*/
t_vect			x_axis_rot(t_vect dir, float theta);
t_vect			y_axis_rot(t_vect dir, float theta);
t_vect			z_axis_rot(t_vect dir, float theta);

/*
** utils
*/
t_vect			set_surface_color(t_scene scene, t_ray ray, int a);
t_vect			filter_sepia(t_vect color_def);
void			*ft_memset(void *b, int c, size_t len);
int				ft_atoi(const char *str, int *i);
double			ft_atof(const char *str, int *i);
t_vect			ft_atov(t_scene *sc, const char *str, int *i);
t_vect			ft_vect_range(t_vect v, float low, float high);
int				ft_strcmp(const char *s1, const char *s2);
int				close_button(t_scene *sc);
size_t			ft_strlen(const char *s);
void			*ft_calloc(size_t count, size_t size);

/*
** triangles & squares
*/
int				inter_triangle2(t_triangle *tr, t_vect pt, t_vect n);
int				inter_triangle(t_ray d, t_object *obj);
int				square_dot(t_vect *corner, t_vect p, t_vect n);
int				inter_square(t_object *obj, float t, t_vect p);
int				inter_plane_square(t_ray d, t_object *obj);

/*
** cylinders
*/
float			find_t0(float a, float b, float c);
t_vect			find_normal(t_vect p, t_cylinder *c);
float			cylinder_delta(t_ray d, t_object *object, float *a1);
int				inter_disk(t_ray d, t_object *obj, t_vect p);
int				inter_cap(t_ray d, t_object *object);
int				inter_cylinder(t_ray d, t_object *object);

/*
** spheres & planes
*/
int				i_s_p(t_ray d_ray, t_plane *plane);
float			sphere_delta(t_ray d, t_sphere s, float *b);
int				inter_sphere(t_ray d, t_object *object);
int				inter_plane(t_ray r, t_object *object);

/*
** intersections
*/
float			inter_shadow_type(t_scene scene, t_ray ray_light,
								float t_light_min);
int				inter_shadow(t_scene scene, t_vect pos_light, float *shadows,
								t_ray ray_light);
float			inter_object_type(t_scene *scene, t_ray r, float min_t);
t_vect			get_color(t_ray r, t_scene scene, int nb_rebound);

/*
** lights
*/
t_vect			get_shadow(t_scene scene, t_ray ray, int a, float *shadows);
t_vect			get_light(t_scene scene, int a_def, t_vect int_pix, t_ray ray);

/*
** antialiasing
*/
t_vect			antialiasing_off(t_ray r, t_scene scene, int i, int j);

/*
** save bmp
*/
void			get_bmpfileheader(int width, int height, int *fd);
void			get_bmpinfoheader(int width, int height, int *fd);
int				save_bmp_image(char *bmp_img, int width, int height);
void			fill_bmp_data(t_scene *scene, t_vect color_def, int i, int j);

/*
** parsing
*/
int				parsing(t_scene *scene, int argc, char **argv);
int				rt_parsing(t_scene *scene, char **argv);
void			scene_creation(t_scene *scene, char *line);
void			create_light(t_scene *sc, char *data, char *data_type, int *i);
void			create_res_cam(t_scene *sc, char *data,
				char *data_type, int *i);
void			create_sphere(t_scene *sc, char *data, int *i);
void			create_plane(t_scene *sc, char *data, int *i);
void			create_cylinder(t_scene *sc, char *data, int *i);
void			create_square_triangle(t_scene *sc, char *data,
				char *data_type, int *i);
void			check_file(int fd, t_scene *sc, int ret);
void			check_file2(t_scene *sc, char *data_type);
void			check_file3(t_scene *sc, char *str, int i);
void			check_file4(t_scene *sc);
void			has_n_param(t_scene *sc, char *str, int nb);

/*
** minirt
*/
int				key_hook(int keycode, t_scene *sc);
int				refresh_hook(t_scene *scene);
void			rendering(t_scene *scene);
int				data_init(t_scene *scene);

#endif
