/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 00:16:12 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/05/12 17:30:49 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include <math.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include "mlx.h"

typedef struct	s_vec
{
	double	x;
	double	y;
	double	z;	
} t_vec;

/*tydef struct	s_color
{
	double	red;
	double	green;
	double	blue;
} t_color;*/

typedef t_vec	t_point;
typedef t_vec	t_color;

typedef struct	s_ambient
{
	double	ratio;
	t_color	color;
} t_ambient;

typedef struct	s_light
{
	t_point	pos;
	double		brightness;
	t_color		color;
	struct s_light	*next;
} t_light;

typedef struct	s_ray
{
	t_point	origin;
	t_vec		dir;
} t_ray;

typedef struct	s_camera
{
	t_point	viewpoint;
	
// ces 3 vecteurs definissent les directions vers lesquelles
// regarde la camera et forment une base orthonormee

// ray.dir = forward + u*right + v*up our chaque pixel du rayon 

	t_vec		forward; // direction dans la scene
	t_vec		right;   // direction vers la droite de la camera
	t_vec		up;		 // direction vers le haut

	double		fov;
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
	t_point	center;
	double		radius;
} t_sphere;

typedef struct	s_plane
{
	t_point	point;
	t_vec		normal;
} t_plane;

typedef struct	s_cylinder
{
	t_point	center;
	t_vec		axis;
	double		radius;
	double		height;
} t_cylinder;

typedef struct s_cone
{
	t_point		apex;
	t_vec		axis;
	double		radius;
	double		height;
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

typedef int	(*t_intersect_fn)
(
	struct s_object *obj,
	t_ray	ray,
	double	tmin,
	double	tmax,
	t_hit	*hit;
);

typedef struct	s_object
{
	t_type		type;
	void		*data;
	t_material	material;
	t_intersect_fn  intersect;
	struct s_object	*next;
} t_object;

typedef struct	s_scene
{
	t_camera	camera;
	t_light		*lights;
	t_object	*objects;
} t_scene;

double	vec_length(t_vec v);
double	vec_dot(t_vec u, t_vec v);
double	distance(t_vec a, t_vec b);

t_vec	vector(double x, double y, double z);
t_vec	vec_add(t_vec a, t_vec b);
t_vec	vec_sub(t_vec a, t_vec b);
t_vec	vec_scale(t_vec v, double k);
t_vec	vec_div(t_vec v, double k);
t_vec	vec_cross_prod(t_vec u, t_vec v);
t_vec	vec_normalize(t_vec v);
t_vec	vec_inv(t_vec v);
t_vec	vec_reflection(t_vec v, t_vec n);

#endif
