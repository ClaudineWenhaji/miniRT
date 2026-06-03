/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:49:54 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/06/03 14:50:03 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	get_decimal_part(char *decimal_str)
{
	double	decimal_part;
	int		i;

	decimal_part = (double)ft_atoi(decimal_str);
	i = -1;
	while (decimal_str[++i])
		decimal_part /= 10.0;
	return (decimal_part);
}

double	ft_atod(char *number)
{
	char	**parts;
	double	integer_part;
	double	decimal_part;
	double	sign;

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
		decimal_part = get_decimal_part(parts[1]);
	ft_free_table((void **)parts, -1);
	return (sign * (integer_part + decimal_part));
}
