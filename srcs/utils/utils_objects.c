/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 19:34:08 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/05/21 14:40:52 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_sphere *get_sphere(char **split_line)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	sphere->identifier = SPHERE;
	get_vector_from_str(split_line[1], &(sphere->center));
	sphere->diameter = ft_atod(split_line[2]);
	sphere->radius = sphere->diameter / 2.0;
	get_color_from_str(split_line[3], &(sphere->color));
	return (sphere);
}

t_plane	*get_plane(char **split_line)
{
	t_plane	*plane;

	plane = (t_plane *)malloc(sizeof(t_plane));
	if (!plane)
		return (NULL);
	plane->identifier = PLANE;
	get_vector_from_str(split_line[1], &(plane->point));
	get_vector_from_str(split_line[2], &(plane->normal));
	get_color_from_str(split_line[3], &(plane->color));
	return (plane);
}

t_cylinder	*get_cylinder(char **split_line)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (NULL);
	cylinder->identifier = CYLINDER;
	get_vector_from_str(split_line[1], &(cylinder->center));
	get_vector_from_str(split_line[2], &(cylinder->axis));
	cylinder->diameter = ft_atod(split_line[3]);
	cylinder->radius = cylinder->diameter / 2.0;
	cylinder->height = ft_atod(split_line[4]);
	get_color_from_str(split_line[5], &(cylinder->color));
	return (cylinder);
}

t_cone	*get_cone(char **split_line)
{
	t_cone	*cone;

	cone = (t_cone *)malloc(sizeof(t_cone));
	if (!cone)
		return (NULL);
	cone->identifier = CONE;
	get_vector_from_str(split_line[1], &(cone->apex));
	get_vector_from_str(split_line[2], &(cone->axis));
	cone->angle = ft_atod(split_line[3]) * PI / 180.0;
	cone->height = ft_atod(split_line[4]);
	get_color_from_str(split_line[5], &(cone->color));
	return (cone);
		
}