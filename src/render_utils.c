/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:55:58 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/09/08 18:56:15 by mhaddadi         ###   ########.fr       */
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

static void	draw_line_gradient_low(t_img *img, t_point2d a, t_point2d b, 
				int color1, int color2)
{
	int	dx;
	int	dy;
	int	yi;
	int	d;
	int	total_pixels;
	int	current_pixel;

	dx = b.x - a.x;
	dy = b.y - a.y;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	d = 2 * dy - dx;
	total_pixels = dx;
	current_pixel = 0;
	while (a.x <= b.x)
	{
		double t = (double)current_pixel / total_pixels;
		int color = interpolate_colors_direct(color1, color2, t);
		put_px(img, a.x, a.y, color);
		if (d > 0)
		{
			a.y += yi;
			d -= 2 * dx;
		}
		d += 2 * dy;
		a.x++;
		current_pixel++;
	}
}

static void	draw_line_gradient_high(t_img *img, t_point2d a, t_point2d b, 
				int color1, int color2)
{
	int	dx;
	int	dy;
	int	xi;
	int	d;
	int	total_pixels;
	int	current_pixel;

	dx = b.x - a.x;
	dy = b.y - a.y;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	d = 2 * dx - dy;
	total_pixels = dy;
	current_pixel = 0;
	while (a.y <= b.y)
	{
		double t = (double) (current_pixel / total_pixels * 2);
		int color = interpolate_colors_direct(color1, color2, t);
		put_px(img, a.x, a.y, color);
		if (d > 0)
		{
			a.x += xi;
			d -= 2 * dy;
		}
		d += 2 * dx;
		a.y++;
		current_pixel++;
	}
}

void	draw_line_gradient(t_img *img, t_point2d a, t_point2d b, 
			int color1, int color2)
{
	if (abs(b.y - a.y) < abs(b.x - a.x))
	{
		if (a.x > b.x)
			draw_line_gradient_low(img, b, a, color2, color1);
		else
			draw_line_gradient_low(img, a, b, color1, color2);
	}
	else
	{
		if (a.y > b.y)
			draw_line_gradient_high(img, b, a, color2, color1);
		else
			draw_line_gradient_high(img, a, b, color1, color2);
	}
}
