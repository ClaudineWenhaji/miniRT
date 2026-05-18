/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 00:16:12 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/05/13 14:57:03 by clwenhaj         ###   ########.fr       */
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

# define EPSILON 0.000001
# define WINDOWS_WIDTH 1920
# define WINDOWS_HEIGHT 1080
# define PI 3.14159265358979323846

typedef struct	s_vec
{
	double	x;
	double	y;
	double	z;	
} t_vec;

typedef struct	s_color
{
	double	red;
	double	green;
	double	blue;
} t_color;

typedef t_vec	t_point;
//typedef t_vec	t_color;

typedef enum e_type_light
{
        AMBIENT,
        LIGHT,
}       t_type_light;

typedef struct	s_ambient
{
	t_type_light	identifier;
	double			ratio;
	t_color			color;
} t_ambient;

typedef struct	s_light
{
	t_type_light	identifier;
	t_point	pos;
	double		brightness;
	t_color		color;
} t_light;

typedef struct	s_ray
{
	t_point	origin;
	t_vec		direction;
} t_ray;

typedef struct	s_camera
{
	t_point	viewpoint;
	t_vec	direction;
	double		fov;
	
// ces 3 vecteurs definissent les directions vers lesquelles
// regarde la camera et forment une base orthonormee

// ray.dir = forward + u*right + v*up pour chaque pixel du rayon 

	t_vec		forward; // direction dans la scene
	t_vec		right;   // direction vers la droite de la camera
	t_vec		up;		 // direction vers le haut
} t_camera;

typedef enum	e_type
{
	SPHERE,
	CYLINDER,
	PLANE,
	CONE
} t_type;

typedef struct	s_sphere
{
	t_type	identifier;
	t_point			center;
	double			radius;
	double			diameter;
	t_color			color;
} t_sphere;

typedef struct	s_plane
{
	t_type	identifier;
	t_point			point;
	t_vec			normal;
	t_color			color;
} t_plane;

typedef struct	s_cylinder
{
	t_type	identifier;
	t_point			center;
	t_vec			axis;
	double			radius;
	double			diameter;
	double			height;
	t_color			color;
} t_cylinder;

typedef struct s_cone
{
	t_type	identifier;
	t_point			apex;
	t_vec			axis;
	double			radius;
	double			height;
	t_color			color;
} t_cone;

typedef struct	s_material
{
	t_color	color;
	double	ambient;
	double	diffuse;
	double	specular;
	double	reflection;
	double	refraction;
} t_material;

typedef struct	s_hit
{
	double		t;
	t_point		point;
	t_vec		normal;
	t_material	*mat;
	int		front_face;
} t_hit;

struct s_object;

/*typedef int	(*t_intersect_fn)
(
	struct s_object *obj,
	t_ray	ray,
	double	tmin,
	double	tmax,
	t_hit	*hit
);*/

typedef bool    (*t_intersect_fn)(void *data, t_ray ray, double *t);

typedef struct	s_object
{
	t_type		type;
	void		*data;
	t_color		color;
	t_intersect_fn  intersect;
	struct s_object	*next;
} t_object;

typedef struct	s_scene
{
	t_camera	camera;
	t_list		*lights;
	t_list		*objects;
	t_win		*window; 
} t_scene;

typedef struct	s_data
{
	t_scene		*scene;
	t_object	*closest_object;
	t_camera	camera;
} t_data;

double	vec_length(t_vec v);
double	vec_dot(t_vec u, t_vec v);
double	distance(t_vec a, t_vec b);

t_vec	vector(double x, double y, double z);
t_vec	vec_add(t_vec a, t_vec b);
t_vec	vec_sub(t_vec a, t_vec b);
t_vec	vec_mult(t_vec v, double k);
t_vec	vec_div(t_vec v, double k);
t_vec	vec_cross_prod(t_vec u, t_vec v);
t_vec	vec_normalize(t_vec v);
t_vec	vec_inv(t_vec v);
t_vec	vec_reflection(t_vec v, t_vec n);

int                     parsing(char *file, t_scene *scene);
int                     get_camera(char **split_line, t_camera *camera);
void            ft_free_table(void **table, int len);
double          ft_atod(char *number);
void            ft_clean(t_scene **scene);
t_ambient       *get_ambient_light(char **line);
t_light         *get_normal_light(char **line);
t_sphere        *get_sphere(char **line);
t_plane         *get_plane(char **line);
t_cylinder      *get_cylinder(char **line);
int                     get_vector_from_str(char *vector_str, t_vec *vectors);
int                     get_color_from_str(char *color_str, t_color *color);

t_ray   camera_ray(t_camera *camera, int pixel_x, int pixel_y);
t_color  trace_ray(t_data *data, t_ray ray);
void    render(t_data *data);
int     intersect_sphere(t_sphere sphere, t_ray ray, double *t);

#endif
