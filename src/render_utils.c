/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:50:11 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/24 15:46:08 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	img_clear(t_img *img, int color)
{
	int	*pixels;
	int	total_pixels;
	int	i;

	if (!img || !img->addr)
		return ;
	pixels = (int *)img->addr;
	total_pixels = img->w * img->h;
	i = 0;
	while (i < total_pixels)
	{
		pixels[i] = color;
		i++;
	}
}

static void	draw_line_low(t_img *img, t_point2d a, t_point2d b, int color)
{
	int	dx;
	int	dy;
	int	yi;
	int	d;

	dx = b.x - a.x;
	dy = b.y - a.y;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	d = 2 * dy - dx;
	while (a.x <= b.x)
	{
		put_px(img, a.x, a.y, color);
		if (d > 0)
		{
			a.y += yi;
			d -= 2 * dx;
		}
		d += 2 * dy;
		a.x++;
	}
}

static void	draw_line_high(t_img *img, t_point2d a, t_point2d b, int color)
{
	int	dx;
	int	dy;
	int	xi;
	int	d;

	dx = b.x - a.x;
	dy = b.y - a.y;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	d = 2 * dx - dy;
	while (a.y <= b.y)
	{
		put_px(img, a.x, a.y, color);
		if (d > 0)
		{
			a.x += xi;
			d -= 2 * dy;
		}
		d += 2 * dx;
		a.y++;
	}
}

void	draw_line_pts(t_img *img, t_point2d a, t_point2d b, int color)
{
	if (abs(b.y - a.y) < abs(b.x - a.x))
	{
		if (a.x > b.x)
			draw_line_low(img, b, a, color);
		else
			draw_line_low(img, a, b, color);
	}
	else
	{
		if (a.y > b.y)
			draw_line_high(img, b, a, color);
		else
			draw_line_high(img, a, b, color);
	}
}

void	draw_line_pts_color(t_img *img, t_point2d a, t_point2d b, int color)
{
	draw_line_pts(img, a, b, color);
}
