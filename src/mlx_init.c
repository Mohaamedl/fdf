/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 00:00:00 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/01/12 00:00:00 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	mlx_init_safe(t_mlx *m)
{
	m->mlx = mlx_init();
	if (!m->mlx)
		return (0);
	m->win = mlx_new_window(m->mlx, WIN_W, WIN_H, "FdF");
	if (!m->win)
		return (0);
	m->img.w = WIN_W;
	m->img.h = WIN_H;
	m->img.ptr = mlx_new_image(m->mlx, m->img.w, m->img.h);
	if (!m->img.ptr)
		return (0);
	m->img.addr = mlx_get_data_addr(m->img.ptr, &m->img.bpp,
			&m->img.line_len, &m->img.endian);
	return (1);
}
