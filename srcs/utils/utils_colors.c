/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 18:44:16 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/05/14 02:06:30 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int get_color_from_str(char *color_str, t_color *color)
{
	char	**tmp;

	tmp = ft_split(color_str, ',');
	if (!tmp)
		return (0);
	color->red = ft_atod(tmp[0]);
	color->green = ft_atod(tmp[1]);
	color->blue = ft_atod(tmp[2]);
	return (ft_free_table((void **)tmp, -1), 1);
}
