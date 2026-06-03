/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_objects_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 15:35:59 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/06/03 15:36:04 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	color_checker(char *split_line, t_material *material)
{
	char	**lines;

	lines = ft_split(split_line, ':');
	if (!lines)
		return (0);
	material->is_checkerboard = 1;
	if (lines[1])
		get_color_from_str(lines[1], &material->checker_color1);
	else
		return (1);
	if (lines[2])
		get_color_from_str(lines[2], &material->checker_color2);
	else
		return (1);
	if (lines[3])
	{
		material->checker_scale = ft_atod(lines[3]);
		if (material->checker_scale <= 0)
			material->checker_scale = 1.0;
	}
	ft_free_table((void **)lines, -1);
	return (1);
}

static double	*get_material_fields(char *element, t_material *material)
{
	if (ft_strncmp(element, "dif", 3) == 0)
		return (&(material->k_diff));
	else if (ft_strncmp(element, "spe", 3) == 0)
		return (&(material->k_spec));
	else if (ft_strncmp(element, "shi", 3) == 0)
		return (&(material->shinness));
	else if (ft_strncmp(element, "ior", 3) == 0)
		return (&(material->ior));
	else if (ft_strncmp(element, "tra", 3) == 0)
		return (&(material->transparency));
	else if (ft_strncmp(element, "emi", 3) == 0)
		return (&(material->emissive));
	else
		return (NULL);
}

int	get_specific_el(char *element, t_material *material, t_scene *scene)
{
	double	*caractere;

	if (!element || element == NULL)
		return (0);
	if (ft_strncmp(element, "tex", 3) == 0)
	{
		material->texture = get_texture(scene, element + 4);
		return (1);
	}
	if (ft_strncmp(element, "chk", 3) == 0)
		return (color_checker(element, material));
	caractere = get_material_fields(element, material);
	if (!caractere)
		return (0);
	*caractere = ft_atod(element + 4);
	return (1);
}
