/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 19:34:08 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/06/03 15:35:36 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static	void	get_caracteristic(char **split_line, t_material *material,
		int start_index, t_scene *scene)
{
	int	i;

	if (!split_line[start_index])
		return ;
	get_color_from_str(split_line[start_index], &material->color);
	material->k_diff = 1.0;
	material->k_spec = 0.0;
	material->shinness = 1.0;
	material->ior = 1.0;
	material->transparency = 0.0;
	material->emissive = 0.0;
	material->texture = NULL;
	material->is_checkerboard = 0;
	material->checker_color1 = (t_color){0, 0, 0};
	material->checker_color2 = (t_color){0, 0, 0};
	material->checker_scale = 0;
	i = start_index;
	while (split_line[++i])
		if (!get_specific_el(split_line[i], material, scene))
			break ;
}

t_sphere	*get_sphere(t_scene *scene, char **split_line)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	sphere->identifier = SPHERE;
	get_vector_from_str(split_line[1], &(sphere->center));
	sphere->diameter = ft_atod(split_line[2]);
	sphere->radius = sphere->diameter / 2.0;
	get_caracteristic(split_line, &(sphere->material), 3, scene);
	return (sphere);
}

t_plane	*get_plane(t_scene *scene, char **split_line)
{
	t_plane	*plane;

	plane = (t_plane *)malloc(sizeof(t_plane));
	if (!plane)
		return (NULL);
	plane->identifier = PLANE;
	get_vector_from_str(split_line[1], &(plane->point));
	get_vector_from_str(split_line[2], &(plane->normal));
	plane->normal = vec_normalize(plane->normal);
	get_caracteristic(split_line, &(plane->material), 3, scene);
	return (plane);
}

t_cylinder	*get_cylinder(t_scene *scene, char **split_line)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (NULL);
	cylinder->identifier = CYLINDER;
	get_vector_from_str(split_line[1], &(cylinder->center));
	get_vector_from_str(split_line[2], &(cylinder->axis));
	cylinder->axis = vec_normalize(cylinder->axis);
	cylinder->diameter = ft_atod(split_line[3]);
	cylinder->radius = cylinder->diameter / 2.0;
	cylinder->height = ft_atod(split_line[4]);
	get_caracteristic(split_line, &(cylinder->material), 5, scene);
	return (cylinder);
}

t_cone	*get_cone(t_scene *scene, char **split_line)
{
	t_cone	*cone;

	cone = (t_cone *)malloc(sizeof(t_cone));
	if (!cone)
		return (NULL);
	cone->identifier = CONE;
	get_vector_from_str(split_line[1], &(cone->apex));
	get_vector_from_str(split_line[2], &(cone->axis));
	cone->angle = ft_atod(split_line[3]);
	cone->height = ft_atod(split_line[4]);
	get_caracteristic(split_line, (&cone->material), 5, scene);
	return (cone);
}
