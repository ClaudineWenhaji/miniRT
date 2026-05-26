/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_events.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 16:43:55 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/05/22 17:08:57 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "miniRT.h"

int	handle_keypress(int keysym, void *param)
{
	if (keysym == KEY_ESC)
		exit_program(param);
	return (0);
}
