/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 18:44:16 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/05/28 23:01:51 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	int_to_color(int color)
{
	t_color	res;

	res.red = ((color >> 16) & 0xFF) / 255.0;
	res.green = ((color >> 8) & 0xFF) / 255.0;
	res.blue = (color & 0xFF) / 255.0;
	return (res);
}

int	get_color_from_str(char *color_str, t_color *color)
{
	char	**tmp;

	if (!color_str)
		return (0);
	tmp = ft_split(color_str, ',');
	if (!tmp)
		return (0);
	if (!tmp[0] || !tmp[1] || !tmp[2])
		return (ft_free_table((void **)tmp, -1), 0);
	color->red = ft_atod(tmp[0]) / 255.0;
	color->green = ft_atod(tmp[1]) / 255.0;
	color->blue = ft_atod(tmp[2]) / 255.0;
	return (ft_free_table((void **)tmp, -1), 1);
}
