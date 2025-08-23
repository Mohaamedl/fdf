/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:47:22 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/23 13:48:19 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	pick_color(const t_point *p, const t_map *map)
{
	int	range;
	int	t;

	if (p->color != -1)
		return (p->color);
	range = map->zmax - map->zmin;
	if (range <= 0)
		return (0xFFFFFF);
	t = (p->z - map->zmin) * 255 / range;
	return ((t << 16) | (t << 8) | 0xFF);
}
