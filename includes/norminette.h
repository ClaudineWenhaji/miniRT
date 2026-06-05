/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norminette.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 17:17:51 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/06/05 12:49:04 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NORMINETTE_H
# define NORMINETTE_H

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_quad
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
}	t_quad;

typedef struct s_cyl_quad
{
	t_vec	d;
	t_vec	dir_tho;
	t_vec	d_tho;
	double	discriminant;
}	t_cyl_quad;

typedef struct s_cone_quad
{
	t_vec	oc;
	double	cosine;
	double	dv;
	double	xv;
	double	a;
	double	b;
	double	c;
	double	discriminant;
}	t_cone_quad;

typedef struct s_plane_uv
{
	double	u_coord;
	double	v_coord;
	int		x_check;
	int		y_check;
}	t_plane_uv;

typedef struct s_sph_uv
{
	double	u_coord;
	double	v_coord;
	int		x_check;
	int		y_check;
}	t_sph_uv;

typedef struct s_cyl_uv
{
	double	u_coord;
	double	v_coord;
	int		x_check;
	int		y_check;
}	t_cyl_uv;

typedef struct s_cone_uv
{
	double	u_coord;
	double	v_coord;
	int		x_check;
	int		y_check;
	double	angle;
	t_vec	tangent;
	t_vec	bitangent;
}	t_cone_uv;

typedef struct s_uv
{
	double	u_coord;
	double	v_coord;
}	t_uv;

#endif
