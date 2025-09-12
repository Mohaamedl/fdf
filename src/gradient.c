/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 12:00:00 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/09/12 12:00:00 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	draw_gradient_pixel(t_line_gradient *line, int i, int steps)
{
	double	t;
	int		x;
	int		y;
	int		color;

	if (steps > 0)
		t = (double)i / steps;
	else
		t = 0.0;
	x = line->start.x + (line->end.x - line->start.x) * i / steps;
	y = line->start.y + (line->end.y - line->start.y) * i / steps;
	color = lerp_color(line->color1, line->color2, t);
	put_px(line->img, x, y, color);
}

void	draw_line_gradient_simple(t_line_gradient *line)
{
	int		dx;
	int		dy;
	int		steps;
	int		i;

	dx = abs(line->end.x - line->start.x);
	dy = abs(line->end.y - line->start.y);
	if (dx > dy)
		steps = dx;
	else
		steps = dy;
	if (steps == 0)
	{
		put_px(line->img, line->start.x, line->start.y, line->color1);
		return ;
	}
	i = 0;
	while (i <= steps)
	{
		draw_gradient_pixel(line, i, steps);
		i++;
	}
}

void	draw_gradient_line(t_line_gradient *line)
{
	draw_line_gradient_simple(line);
}
