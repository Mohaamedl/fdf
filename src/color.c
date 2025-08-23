/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 00:00:00 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/01/12 00:00:00 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
