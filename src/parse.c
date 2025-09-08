/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:55:33 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/09/08 18:56:15 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int	parse_and_store_token(const char *ptr, int len, t_point *point,
		t_map *map)
{
	int	z;
	int	color;

	if (!parse_token_direct(ptr, len, &z, &color))
		return (0);
	point->z = z;
	point->color = color;
	if (z < map->zmin)
		map->zmin = z;
	if (z > map->zmax)
		map->zmax = z;
	return (1);
}

static int	parse_line_direct(const char *line, int expected_w, t_point *row,
		t_map *map)
{
	const char	*ptr;
	int			x;
	int			len;

	ptr = line;
	x = 0;
	while (x < expected_w && *ptr)
	{
		while (*ptr == ' ' || *ptr == '\t')
			ptr++;
		if (!*ptr)
			break ;
		len = 0;
		while (ptr[len] && ptr[len] != ' ' && ptr[len] != '\t'
			&& ptr[len] != '\n')
			len++;
		if (!parse_and_store_token(ptr, len, &row[x], map))
			return (0);
		ptr += len;
		x++;
	}
	return (x == expected_w);
}

static int	parse_map_file(int fd, t_map *map)
{
	char	*line;
	int		y;

	init_map_parsing(map);
	y = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!parse_line_direct(line, map->w, map->pts[y], map))
		{
			free(line);
			return (0);
		}
		free(line);
		y++;
		line = get_next_line(fd);
	}
	return (1);
}

static int	process_map_file(const char *path, t_map *map)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		free_map(map);
		return (0);
	}
	if (!parse_map_file(fd, map))
	{
		close(fd);
		free_map(map);
		return (0);
	}
	close(fd);
	return (1);
}

int	parse_map(const char *path, t_map *map)
{
	if (!count_dimensions(path, &map->w, &map->h))
		return (0);
	if (!allocate_map(map))
		return (0);
	return (process_map_file(path, map));
}
