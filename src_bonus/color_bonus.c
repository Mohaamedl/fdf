/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:47:22 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/23 21:15:29 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static int	get_gradient_color(int z, const t_map *map)
{
	double			percent;
	unsigned int	range;

	range = map->zmax - map->zmin;
	if (range == 0)
		return (0x432371);
	percent = ((double)(z - map->zmin) / range);
	if (percent < 0.2)
		return (0x432371);  // Deep purple
	else if (percent < 0.4)
		return (0x714674);  // Purple
	else if (percent < 0.6)
		return (0x9F6976);  // Pink-purple
	else if (percent < 0.8)
		return (0xCC8B79);  // Orange-pink
	else
		return (0xFAAE7B);  // Light orange
}

int	pick_color(const t_point *p, const t_map *map)
{
	if (p->color != -1)
		return (p->color);
	return (get_gradient_color(p->z, map));
}
