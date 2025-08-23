/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:51:05 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/23 13:51:34 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	free_tokens(char **tokens)
{
	int i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

static int	parse_hex_color(const char *hex_str)
{
	int		result;
	int		i;
	char	c;

	result = 0;
	i = 0;
	while (hex_str[i])
	{
		c = hex_str[i];
		result *= 16;
		if (c >= '0' && c <= '9')
			result += c - '0';
		else if (c >= 'A' && c <= 'F')
			result += c - 'A' + 10;
		else if (c >= 'a' && c <= 'f')
			result += c - 'a' + 10;
		i++;
	}
	return (result);
}

static int	parse_token(const char *tok, int *z, int *color)
{
	char	*comma_pos;
	long	val;

	*color = 0xFFFFFF;
	comma_pos = ft_strchr(tok, ',');
	if (comma_pos)
		*comma_pos = '\0';
	val = ft_atol(tok);
	if (val < -2147483648LL || val > 2147483647LL)
		return (0);
	*z = (int)val;
	if (comma_pos)
	{
		*comma_pos = ',';
		if (ft_strncmp(comma_pos + 1, "0x", 2) == 0)
			*color = parse_hex_color(comma_pos + 3);
		else if (ft_strncmp(comma_pos + 1, "0X", 2) == 0)
			*color = parse_hex_color(comma_pos + 3);
	}
	return (1);
}

static int	parse_line_tokens(char **tokens, int expected_w, t_point *row,
		t_map *map)
{
	int	x;
	int	z;
	int	c;

	x = 0;
	while (tokens[x])
	{
		if (!parse_token(tokens[x], &z, &c))
			return (0);
		row[x].z = z;
		row[x].color = c;
		if (z < map->zmin)
			map->zmin = z;
		if (z > map->zmax)
			map->zmax = z;
		x++;
	}
	if (x != expected_w)
		return (0);
	return (1);
}

static int	parse_map_file(int fd, t_map *map)
{
	char	*line;
	char	**tokens;
	int		y;

	map->zmin = 2147483647;
	map->zmax = -2147483648;
	y = 0;
	while ((line = get_next_line(fd)))
	{
		tokens = ft_split(line, ' ');
		free(line);
		if (!tokens)
			return (0);
		if (!parse_line_tokens(tokens, map->w, map->pts[y], map))
		{
			free_tokens(tokens);
			return (0);
		}
		free_tokens(tokens);
		y++;
	}
	return (1);
}

static int	count_dimensions(const char *path, int *width, int *height)
{
	int		fd;
	char	*line;
	char	**tokens;
	int		w;
	int		h;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	h = 0;
	w = 0;
	while ((line = get_next_line(fd)))
	{
		if (h == 0)
		{
			tokens = ft_split(line, ' ');
			if (tokens)
			{
				while (tokens[w])
					w++;
				free_tokens(tokens);
			}
		}
		free(line);
		h++;
	}
	close(fd);
	*width = w;
	*height = h;
	return (w > 0 && h > 0);
}

static int	allocate_map(t_map *map)
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
			while (--i >= 0)
				free(map->pts[i]);
			free(map->pts);
			return (0);
		}
		i++;
	}
	return (1);
}

int	parse_map(const char *path, t_map *map)
{
	int	fd;

	if (!count_dimensions(path, &map->w, &map->h))
		return (0);
	if (!allocate_map(map))
		return (0);
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

void	free_map(t_map *map)
{
	int	i;

	if (!map || !map->pts)
		return ;
	i = 0;
	while (i < map->h)
	{
		if (map->pts[i])
			free(map->pts[i]);
		i++;
	}
	free(map->pts);
	map->pts = NULL;
}
