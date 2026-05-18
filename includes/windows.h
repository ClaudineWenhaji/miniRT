/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 02:23:45 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/05/14 12:00:14 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOWS_H
#define WINDOWS_H

#include "../minilibx-linux/mlx.h"

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define FDF_TITLE "minirt : "
# define COLOR_DISCO 0x9A1F6A
# define COLOR_BRICK 0xC2294E
# define COLOR_FLAMINGO 0xEC4B27
# define COLOR_JAFFA 0xEF8633
# define COLOR_SAFFRON 0xF3AF3D
# define COLOR_BLACK 0x000000
# define KEY_ESC 65307
# define KEY_R 114
# define KEY_DIR_UP 65362
# define KEY_DIR_DOWN 65364
# define KEY_DIR_LEFT 65361
# define KEY_DIR_RIGHT 65363
# define KEY_ZOOM_P 65451
# define KEY_ZOOM_M 65453
# define KEY_W 119
# define KEY_A 97
# define KEY_Q 113
# define KEY_S 115
# define KEY_D 100
# define KEY_E 101
# define KEY_I 105
# define KEY_P 112
# define KEY_PAGE_UP 65365
# define KEY_PAGE_DOWN 65366
# define KEY_K 107
# define KEY_L 108

typedef struct s_img
{
	void	*img_ptr;
	char	*data;
	int		bit_per_pixel;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_win
{
	t_img	*img;
	void	*mlx;
	void	*win;
}	t_win;

#endif
