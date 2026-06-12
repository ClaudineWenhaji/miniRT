/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 19:13:31 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/06/12 18:54:33 by clwenhaj         ###   ########.fr       */
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
	free(table);
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
	t_material	material;

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
