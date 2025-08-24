/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 14:25:12 by mohamed          #+#    #+#             */
/*   Updated: 2025/08/24 14:25:12 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	parse_token_direct(const char *tok, int len, int *z, int *color)
{
	int		comma_pos;
	int		i;

	*color = -1;
	comma_pos = -1;
	i = 0;
	while (i < len)
	{
		if (tok[i] == ',')
		{
			comma_pos = i;
			break ;
		}
		i++;
	}
	if (comma_pos >= 0)
	{
		*z = string_to_int_len(tok, comma_pos);
		if (comma_pos + 3 < len && tok[comma_pos + 1] == '0'
			&& (tok[comma_pos + 2] == 'x' || tok[comma_pos + 2] == 'X'))
			*color = hex_color_to_int(tok + comma_pos + 3);
	}
	else
		*z = string_to_int_len(tok, len);
	return (1);
}

static void	cleanup_map_allocation(t_map *map, int i)
{
	while (--i >= 0)
		free(map->pts[i]);
	free(map->pts);
}

int	allocate_map(t_map *map)
{
	int	i;

	map->pts = malloc(sizeof(t_point *) * map->h);
	if (!map->pts)
		return (0);
	i = 0;
	while (i < map->h)
	{
		map->pts[i] = malloc(sizeof(t_point) * map->w);
		if (!map->pts[i])
		{
			cleanup_map_allocation(map, i);
			return (0);
		}
		i++;
	}
	return (1);
}
