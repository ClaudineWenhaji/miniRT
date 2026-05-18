/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 18:47:14 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/05/14 02:12:37 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ambient	*get_ambient_light(char **split_line)
{
	t_ambient	*light;

	light = (t_ambient *)malloc(sizeof(t_ambient));
	if (!light)
		return (NULL);
	light->identifier = AMBIENT;
	light->ratio = ft_atod(split_line[1]);
	get_color_from_str(split_line[2], &light->color);
	return (light);
}

t_light	*get_normal_light(char **split_line)
{
	t_light		*light;

	light = (t_light *)malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	light->identifier = LIGHT;
	get_vector_from_str(split_line[1], &light->pos);
	light->brightness = ft_atod(split_line[2]);
	get_color_from_str(split_line[3], &light->color);
	return (light);
}
