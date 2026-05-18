/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_vectors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 20:14:53 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/05/14 01:14:50 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	get_vector_from_str(char *vector_str, t_vec *vector)
{
	char	**tmp;

	tmp = ft_split(vector_str, ',');
	if (!tmp)
		return (0);
	vector->x = ft_atod(tmp[0]);
	vector->y = ft_atod(tmp[1]);
	vector->z = ft_atod(tmp[2]);
	return (ft_free_table((void **)tmp, -1), 1);
}
