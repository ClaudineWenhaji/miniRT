/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 19:13:31 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/05/29 01:40:20 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_free_table(void **table, int len)
{
	int	i;

	i = -1;
	if (len < 0)
		len = INT_MAX;
	while (table[++i] && i < len)
		free(table[i]);
}

double	ft_atod(char *number)
{
	char	**parts;
	double	integer_part;
	double	decimal_part;
	double	sign;
	int		i;

	sign = 1.0;
	if (*number == '-')
	{
		sign = -1.0;
		number++;
	}
	parts = ft_split(number, '.');
	if (!parts)
		return (0);
	integer_part = (double)ft_atoi(parts[0]);
	decimal_part = 0.0;
	if (parts[1])
	{
		decimal_part = (double)ft_atoi(parts[1]);
		i = -1;
		while (parts[1][++i])
			decimal_part /= 10.0;
	}
	ft_free_table((void **)parts, -1);
	return (sign * (integer_part + decimal_part));
}

static void	clean_window(t_win *window)
{
	if (!window)
		return ;
	if (window->img)
	{
		mlx_destroy_image(window->mlx, window->img->img_ptr);
		free(window->img);
	}
	if (window->win)
		mlx_destroy_window(window->mlx, window->win);
	if (window->mlx)
	{
		mlx_destroy_display(window->mlx);
		free(window->mlx);
	}
	free(window);
}

static void	clear_object_texture(t_scene *scene, void *object)
{
	t_material material;

	material = get_obj_material(object);
	if (material.texture)
	{
		mlx_destroy_image(scene->window->mlx,
				(material.texture)->img_ptr);
		free(material.texture);
	}
}

void	ft_clean(t_scene **scene)
{
	t_list	*object;

	object = (*scene)->objects;
	while (object)
	{
		clear_object_texture(*scene, object);
		object = object->next;
	}
	ft_lstclear(&(*scene)->objects, free);
	ft_lstclear(&(*scene)->lights, free);
	clean_window((*scene)->window);
	free(*scene);
	*scene = NULL;
}
