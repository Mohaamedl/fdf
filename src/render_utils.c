/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:50:11 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/23 13:50:28 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	img_clear(t_img *img, int color)
{
	int	y;
	int	x;
	int	*row;

	if (!img || !img->addr)
		return ;
	y = 0;
	while (y < img->h)
	{
		row = (int *)(img->addr + y * img->line_len);
		x = 0;
		while (x < img->w)
		{
			row[x] = color;
			x++;
		}
		y++;
	}
}

void	put_px(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!img || !img->addr || x < 0 || y < 0 || x >= img->w || y >= img->h)
		return ;
	dst = img->addr + y * img->line_len + x * (img->bpp / 8);
	*(unsigned int *)dst = (unsigned int)color;
}

static void	draw_line_low(t_img *img, t_point2d a, t_point2d b, int color)
{
	int	dx;
	int	dy;
	int	yi;
	int	d;
	int	y;

	dx = b.x - a.x;
	dy = b.y - a.y;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	d = (2 * dy) - dx;
	y = a.y;
	while (a.x <= b.x)
	{
		put_px(img, a.x, y, color);
		if (d > 0)
		{
			y = y + yi;
			d = d + (2 * (dy - dx));
		}
		else
			d = d + 2 * dy;
		a.x++;
	}
}

static void	draw_line_high(t_img *img, t_point2d a, t_point2d b, int color)
{
	int	dx;
	int	dy;
	int	xi;
	int	d;
	int	x;

	dx = b.x - a.x;
	dy = b.y - a.y;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	d = (2 * dx) - dy;
	x = a.x;
	while (a.y <= b.y)
	{
		put_px(img, x, a.y, color);
		if (d > 0)
		{
			x = x + xi;
			d = d + (2 * (dx - dy));
		}
		else
			d = d + 2 * dx;
		a.y++;
	}
}

void	draw_line_pts(t_img *img, t_point2d a, t_point2d b, int color)
{
	int	abs_dx;
	int	abs_dy;

	abs_dx = b.x - a.x;
	if (abs_dx < 0)
		abs_dx = -abs_dx;
	abs_dy = b.y - a.y;
	if (abs_dy < 0)
		abs_dy = -abs_dy;
	if (abs_dy < abs_dx)
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
