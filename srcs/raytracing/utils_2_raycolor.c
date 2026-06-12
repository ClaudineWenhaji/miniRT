/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2_raycolor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 17:49:33 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/06/05 17:50:56 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	c_mult(t_color c, double f)
{
	return ((t_color){c.red * f, c.green * f, c.blue * f});
}

t_color	c_add(t_color c1, t_color c2)
{
	return ((t_color){c1.red + c2.red, c1.green + c2.green, c1.blue + c2.blue});
}

t_color	c_prod(t_color color_a, t_color color_b)
{
	return ((t_color){color_a.red * color_b.red, color_a.green * color_b.green,
		color_a.blue * color_b.blue});
}

int	color_to_int_local(t_color color)
{
	int	r;
	int	g;
	int	b;

	r = (int)fmin(255.0, fmax(0.0, color.red * 255.0));
	g = (int)fmin(255.0, fmax(0.0, color.green * 255.0));
	b = (int)fmin(255.0, fmax(0.0, color.blue * 255.0));
	return ((r << 16) | (g << 8) | b);
}
