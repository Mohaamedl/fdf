/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:51:05 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/24 09:45:14 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int	parse_int_fast(const char *str, int len);
static int	parse_token_direct(const char *tok, int len, int *z, int *color);
static int	parse_line_direct(const char *line, int expected_w, t_point *row, t_map *map);

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

static int	parse_hex_color_fast(const char *hex_str)
{
	int		result;
	char	c;

	result = 0;
	// Unrolled loop for exactly 6 hex digits (RRGGBB)
	// Most colors in julia.fdf are exactly 6 digits
	c = *hex_str++;
	if (c >= '0' && c <= '9') result = (result << 4) + (c - '0');
	else if (c >= 'A' && c <= 'F') result = (result << 4) + (c - 'A' + 10);
	else if (c >= 'a' && c <= 'f') result = (result << 4) + (c - 'a' + 10);
	
	c = *hex_str++;
	if (c >= '0' && c <= '9') result = (result << 4) + (c - '0');
	else if (c >= 'A' && c <= 'F') result = (result << 4) + (c - 'A' + 10);
	else if (c >= 'a' && c <= 'f') result = (result << 4) + (c - 'a' + 10);
	
	c = *hex_str++;
	if (c >= '0' && c <= '9') result = (result << 4) + (c - '0');
	else if (c >= 'A' && c <= 'F') result = (result << 4) + (c - 'A' + 10);
	else if (c >= 'a' && c <= 'f') result = (result << 4) + (c - 'a' + 10);
	
	c = *hex_str++;
	if (c >= '0' && c <= '9') result = (result << 4) + (c - '0');
	else if (c >= 'A' && c <= 'F') result = (result << 4) + (c - 'A' + 10);
	else if (c >= 'a' && c <= 'f') result = (result << 4) + (c - 'a' + 10);
	
	c = *hex_str++;
	if (c >= '0' && c <= '9') result = (result << 4) + (c - '0');
	else if (c >= 'A' && c <= 'F') result = (result << 4) + (c - 'A' + 10);
	else if (c >= 'a' && c <= 'f') result = (result << 4) + (c - 'a' + 10);
	
	c = *hex_str++;
	if (c >= '0' && c <= '9') result = (result << 4) + (c - '0');
	else if (c >= 'A' && c <= 'F') result = (result << 4) + (c - 'A' + 10);
	else if (c >= 'a' && c <= 'f') result = (result << 4) + (c - 'a' + 10);
	
	return (result);
}

static int	parse_int_fast(const char *str, int len)
{
	int		result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	
	// Handle sign
	if (str[0] == '-')
	{
		sign = -1;
		i = 1;
	}
	else if (str[0] == '+')
		i = 1;
	
	// Parse digits
	while (i < len && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	
	return (result * sign);
}

static int	parse_line_direct(const char *line, int expected_w, t_point *row, t_map *map)
{
	const char	*ptr;
	int			x;
	int			z;
	int			color;
	int			len;

	ptr = line;
	x = 0;
	
	while (x < expected_w && *ptr)
	{
		// Skip whitespace
		while (*ptr == ' ' || *ptr == '\t')
			ptr++;
		
		if (!*ptr)
			break;
		
		// Find end of current token
		len = 0;
		while (ptr[len] && ptr[len] != ' ' && ptr[len] != '\t' && ptr[len] != '\n')
			len++;
		
		if (!parse_token_direct(ptr, len, &z, &color))
			return (0);
		
		row[x].z = z;
		row[x].color = color;
		if (z < map->zmin)
			map->zmin = z;
		if (z > map->zmax)
			map->zmax = z;
		
		ptr += len;
		x++;
	}
	
	return (x == expected_w);
}

static int	parse_token_direct(const char *tok, int len, int *z, int *color)
{
	int		comma_pos;
	int		i;

	*color = -1;
	comma_pos = -1;
	
	// Find comma position
	for (i = 0; i < len; i++)
	{
		if (tok[i] == ',')
		{
			comma_pos = i;
			break;
		}
	}
	
	if (comma_pos >= 0)
	{
		// Parse Z value before comma
		*z = parse_int_fast(tok, comma_pos);
		
		// Parse color after comma
		if (comma_pos + 3 < len && tok[comma_pos + 1] == '0' && 
			(tok[comma_pos + 2] == 'x' || tok[comma_pos + 2] == 'X'))
		{
			*color = parse_hex_color_fast(tok + comma_pos + 3);
		}
	}
	else
	{
		// No comma, just parse Z value
		*z = parse_int_fast(tok, len);
	}
	
	return (1);
}

static int	parse_map_file(int fd, t_map *map)
{
	char	*line;
	int		y;
	int		progress_counter;

	map->zmin = 2147483647;
	map->zmax = -2147483648;
	y = 0;
	progress_counter = 0;
	
	while ((line = get_next_line(fd)))
	{
		// Show progress for very large maps every 100 lines
		if (map->w * map->h > 50000 && ++progress_counter % 100 == 0)
		{
			write(1, ".", 1);  // Simple progress indicator
		}
		
		// Parse directly without splitting - much faster!
		if (!parse_line_direct(line, map->w, map->pts[y], map))
		{
			free(line);
			return (0);
		}
		free(line);
		y++;
	}
	
	// Newline after progress dots
	if (map->w * map->h > 50000)
		write(1, "\n", 1);
	
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
	
	// Show loading message for large maps
	if (map->w * map->h > 50000)
	{
		write(1, "Loading large map, please wait...\n", 34);
	}
	
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
