/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:55:27 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/09/08 18:56:15 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

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

static int	count_width_from_tokens(char **tokens)
{
	int	w;

	w = 0;
	if (tokens)
	{
		while (tokens[w])
			w++;
		free_string_array(tokens);
	}
	return (w);
}

static int	count_file_lines(int fd, int *width)
{
	char	*line;
	char	**tokens;
	int		w;
	int		h;

	h = 0;
	w = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (h == 0)
		{
			tokens = ft_split(line, ' ');
			w = count_width_from_tokens(tokens);
		}
		free(line);
		h++;
		line = get_next_line(fd);
	}
	*width = w;
	return (h);
}

int	count_dimensions(const char *path, int *width, int *height)
{
	int		fd;
	int		h;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	h = count_file_lines(fd, width);
	close(fd);
	*height = h;
	return (*width > 0 && h > 0);
}
