/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 19:13:31 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/05/14 12:07:38 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	get_camera(char **split_line, t_camera *camera)
{
	camera->fov = ft_atod(split_line[3]);
	return (get_vector_from_str(split_line[1], &camera->viewpoint)
		&& get_vector_from_str(split_line[2], &camera->direction));
}

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
	double	floatant;
	double	dec_part;
	int		i;

	parts = ft_split(number, '.');
	if (!parts)
		return (0);
	floatant = 0.0;
	dec_part = 0.0;
	floatant = (double)ft_atoi(parts[0]);
	if (parts[1])
		dec_part = (double)ft_atoi(parts[1]);
	i = -1;
	if (parts[1])
		while (parts[1][++i])
			dec_part /= 10;
	floatant += dec_part;
	return (ft_free_table((void **)parts, -1), floatant);
}

void	clean_window(t_win *window)
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


void	ft_clean(t_scene **scene)
{
	ft_lstclear(&(*scene)->objects, free);
	ft_lstclear(&(*scene)->lights, free);
	clean_window((*scene)->window);
	free(*scene);
	*scene = NULL;
}
