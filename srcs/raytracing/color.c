/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 16:35:02 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/05/18 16:46:06 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int ft_clamp(int value, int min, int max)
{
    if (value < min)
        return (min);
    if (value > max)
        return (max);
    return (value);
}

int color_to_int(t_color color)
{
    int r; 
    int g;
    int b; 

    r = ft_clamp((int)color.red, 0, 255);
    g = ft_clamp((int)color.green, 0, 255);
    b = ft_clamp((int)color.blue, 0, 255);
    return ((r << 16) | (g << 8) | b);
}

void put_pixel(t_img *img, int x, int y, int color)
{
    char    *dst;
    
    if (x < 0 || y < 0 || x >= WINDOWS_WIDTH || y >= WINDOWS_HEIGHT)
        return ;
    dst = img->data
        + (y * img->size_line)
        + (x * (img->bit_per_pixel / 8));
    *(unsigned int *)dst = color;
}
