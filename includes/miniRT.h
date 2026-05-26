/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 00:16:12 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/05/26 08:43:44 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "windows.h"
# include <math.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "mlx.h"

# define EPSILON 0.00001
# define WINDOWS_WIDTH 1920
# define WINDOWS_HEIGHT 1080
# define PI 3.14159265358979323846

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_color
{
	double	red;
	double	green;
	double	blue;
}	t_color;

typedef t_vec	t_point;

typedef enum e_type_light
{
	AMBIENT,
	LIGHT,
}	t_type_light;

typedef struct s_ambient
{
	t_type_light	identifier;
	double			ratio;
	t_color			color;
}	t_ambient;

typedef struct s_light
{
	t_type_light	identifier;
	t_point			pos;
	double			brightness;
	t_color			color;
}	t_light;

typedef struct s_ray
{
	t_point	origin;
	t_vec	direction;
}	t_ray;

typedef struct s_camera
{
	t_point		viewpoint;
	t_vec		direction;
	double		focal_length;
	double		fov;
	t_vec		forward;
	t_vec		right;
	t_vec		up;
}	t_camera;

typedef enum e_type
{
	SPHERE,
	CYLINDER,
	PLANE,
	CONE,
}	t_type;

typedef struct	s_material
{
	t_color	color;
	double	k_diff;
	double	k_spec;
	double	shinness;
	double	ior;
	double	transparency;
}	t_material;

typedef struct s_sphere
{
	t_type	identifier;
	t_point	center;
	double	radius;
	double	diameter;
	t_material	material;
}	t_sphere;

typedef struct s_plane
{
	t_type		identifier;
	t_point		point;
	t_vec		normal;
	t_material	material;
}	t_plane;

typedef struct s_cylinder
{
	t_type		identifier;
	t_point		center;
	t_vec		axis;
	double		radius;
	double		diameter;
	double		height;
	t_material	material;
}	t_cylinder;

typedef struct s_cone
{
	t_type		identifier;
	t_point		apex;
	t_vec		axis;
	double		angle;
	double		height;
	t_material	material;
}	t_cone;

typedef struct	s_viewport
{
	double	viewport_height;
	double	viewport_width;
	t_vec	viewport_u;
	t_vec	viewport_v;
	t_vec	pixel_delta_u;
	t_vec	pixel_delta_v;
	t_point	viewport_upper_left;
	t_point	pixel_center_loc;
}	t_viewport;

typedef struct s_scene
{
	t_camera	camera;
	t_viewport	viewport;
	t_list		*lights;
	t_list		*objects;
	t_win		*window;
}	t_scene;

double		vec_length(t_vec v);
double		vec_dot(t_vec u, t_vec v);
double		distance(t_vec a, t_vec b);
double		ft_discriminant(double a, double b, double c);
t_vec		vector(double x, double y, double z);
t_vec		vec_add(t_vec a, t_vec b);
t_vec		vec_sub(t_vec a, t_vec b);
t_vec		vec_mult(t_vec v, double k);
t_vec		vec_div(t_vec v, double k);
t_vec		vec_cross_prod(t_vec u, t_vec v);
t_vec		vec_normalize(t_vec v);
t_vec		vec_inv(t_vec v);
t_vec		vec_reflection(t_vec v, t_vec n);
int			parsing(char *file, t_scene *scene);
void		ft_free_table(void **table, int len);
double		ft_atod(char *number);
void		ft_clean(t_scene **scene);
void		print_scene_info(t_scene *scene);
t_ambient	*get_ambient_light(char **line);
t_light		*get_normal_light(char **line);
t_sphere	*get_sphere(char **line);
t_plane		*get_plane(char **line);
t_cylinder	*get_cylinder(char **line);
t_cone		*get_cone(char **split_line);
int			get_vector_from_str(char *vector_str, t_vec *vectors);
int			get_color_from_str(char *color_str, t_color *color);
int			setup_camera(char **split_line, t_camera *camera);
void		setup_viewport(t_camera *camera, t_viewport *viewport, t_img *img);
int			intersect_sphere(t_sphere *sphere, t_ray *ray, double *t);
int			intersect_plane(t_plane *plane, t_ray *ray, double *t);
t_vec		get_normal_cone(t_cone *cone, t_point hit_point);
int			intersect_cone(t_cone *cone, t_ray *ray, double *t);
int			intersect_object(void *object, t_ray *ray, double *t);
int			ray_color(t_scene *scene, t_ray ray);
void		put_pixel(t_img *img, int x, int y, int color);
t_ray		camera_ray(t_camera *camera, t_viewport *viewport,
				int pixel_x, int pixel_y);
void		render(t_scene *scene);
int			intersect_cylinder(t_cylinder *cylinder, t_ray *ray, double *t);
t_vec		get_normal_cylinder(t_cylinder *cylinder, t_point hit_point);
void		exit_program(void *param);

#endif
