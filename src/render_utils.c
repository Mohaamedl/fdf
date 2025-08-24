/* ***********void	img_clear(t_img *img, int color)
{
	int		*pixels;
	int		total_pixels;
	int		i;

	if (!img || !img->addr)
		return;
	
	pixels = (int *)img->addr;
	total_pixels = img->w * img->h;
	
	// Ultra-fast clear using 32-bit writes
	if (color == 0)
	{
		// Use fastest possible clear for black
		ft_bzero(img->addr, total_pixels * 4);
	}
	else
	{
		// Unrolled loop for maximum speed
		i = 0;
		while (i < total_pixels - 7)
		{
			pixels[i] = color;
			pixels[i + 1] = color;
			pixels[i + 2] = color;
			pixels[i + 3] = color;
			pixels[i + 4] = color;
			pixels[i + 5] = color;
			pixels[i + 6] = color;
			pixels[i + 7] = color;
			i += 8;
		}
		// Handle remaining pixels
		while (i < total_pixels)
		{
			pixels[i] = color;
			i++;
		}
	}
}******************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:50:11 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/23 22:15:47 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	img_clear(t_img *img, int color)
{
	if (!img || !img->addr)
		return;
	
	// Use fast bzero for black, or memset for other colors
	if (color == 0)
		ft_bzero(img->addr, img->w * img->h * (img->bpp / 8));
	else
	{
		int *pixels = (int *)img->addr;
		int total_pixels = img->w * img->h;
		int i = 0;
		while (i < total_pixels)
		{
			pixels[i] = color;
			i++;
		}
	}
}

void	put_px(t_img *img, int x, int y, int color)
{
	char *dst;

	if (!img || !img->addr)
		return;
	if (x < 0 || y < 0 || x >= img->w || y >= img->h)
		return;
	dst = img->addr + y * img->line_len + x * (img->bpp / 8);
	*(unsigned int *)dst = (unsigned int)color;
}

// Fast inline pixel writing without bounds checking (for internal use)
static inline void	put_px_fast(t_img *img, int x, int y, int color)
{
	*(int *)(img->addr + y * img->line_len + x * 4) = color;
}

// Color interpolation for smooth gradients
static int	interpolate_color(int color1, int color2, float progress)
{
	int r1, g1, b1, r2, g2, b2;
	int r, g, b;
	
	if (progress <= 0) return color1;
	if (progress >= 1) return color2;
	
	// Extract RGB components
	r1 = (color1 >> 16) & 0xFF;
	g1 = (color1 >> 8) & 0xFF;
	b1 = color1 & 0xFF;
	
	r2 = (color2 >> 16) & 0xFF;
	g2 = (color2 >> 8) & 0xFF;
	b2 = color2 & 0xFF;
	
	// Interpolate
	r = r1 + (int)((r2 - r1) * progress);
	g = g1 + (int)((g2 - g1) * progress);
	b = b1 + (int)((b2 - b1) * progress);
	
	return ((r << 16) | (g << 8) | b);
}

// Ultra-fast line drawing with optimized memory access
static void	draw_line_low(t_img *img, t_point2d a, t_point2d b, int color)
{
	int dx = b.x - a.x;
	int dy = b.y - a.y;
	int yi = 1;
	int d, y;
	int *pixel_row;

	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	d = (2 * dy) - dx;
	y = a.y;
	
	while (a.x <= b.x)
	{
		if (a.x >= 0 && y >= 0 && a.x < img->w && y < img->h)
		{
			pixel_row = (int *)(img->addr + y * img->line_len);
			pixel_row[a.x] = color;
		}
		if (d > 0)
		{
			y += yi;
			d -= 2 * dx;
		}
		d += 2 * dy;
		a.x++;
	}
}

static void	draw_line_high(t_img *img, t_point2d a, t_point2d b, int color)
{
	int dx = b.x - a.x;
	int dy = b.y - a.y;
	int xi = 1;
	int d, x;
	int *pixel_row;

	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	d = (2 * dx) - dy;
	x = a.x;
	
	while (a.y <= b.y)
	{
		if (x >= 0 && a.y >= 0 && x < img->w && a.y < img->h)
		{
			pixel_row = (int *)(img->addr + a.y * img->line_len);
			pixel_row[x] = color;
		}
		if (d > 0)
		{
			x += xi;
			d -= 2 * dy;
		}
		d += 2 * dx;
		a.y++;
	}
}

void	draw_line_pts(t_img *img, t_point2d a, t_point2d b, int color)
{
	int abs_dx;
	int abs_dy;

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

// Color interpolated line drawing for better gradients
static void	draw_line_low_color(t_img *img, t_point2d a, t_point2d b, int color1, int color2)
{
	int dx = b.x - a.x;
	int dy = b.y - a.y;
	int yi = 1;
	int d, y;
	int *pixel_row;
	int total_steps = dx;
	int step = 0;

	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	d = (2 * dy) - dx;
	y = a.y;
	
	while (a.x <= b.x)
	{
		if (a.x >= 0 && y >= 0 && a.x < img->w && y < img->h)
		{
			pixel_row = (int *)(img->addr + y * img->line_len);
			float progress = (total_steps > 0) ? (float)step / total_steps : 0;
			pixel_row[a.x] = interpolate_color(color1, color2, progress);
		}
		if (d > 0)
		{
			y += yi;
			d -= 2 * dx;
		}
		d += 2 * dy;
		a.x++;
		step++;
	}
}

static void	draw_line_high_color(t_img *img, t_point2d a, t_point2d b, int color1, int color2)
{
	int dx = b.x - a.x;
	int dy = b.y - a.y;
	int xi = 1;
	int d, x;
	int *pixel_row;
	int total_steps = dy;
	int step = 0;

	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	d = (2 * dx) - dy;
	x = a.x;
	
	while (a.y <= b.y)
	{
		if (x >= 0 && a.y >= 0 && x < img->w && a.y < img->h)
		{
			pixel_row = (int *)(img->addr + a.y * img->line_len);
			float progress = (total_steps > 0) ? (float)step / total_steps : 0;
			pixel_row[x] = interpolate_color(color1, color2, progress);
		}
		if (d > 0)
		{
			x += xi;
			d -= 2 * dy;
		}
		d += 2 * dx;
		a.y++;
		step++;
	}
}

void	draw_line_pts_color(t_img *img, t_point2d a, t_point2d b, int color1, int color2)
{
	int abs_dx;
	int abs_dy;

	abs_dx = b.x - a.x;
	if (abs_dx < 0)
		abs_dx = -abs_dx;
	abs_dy = b.y - a.y;
	if (abs_dy < 0)
		abs_dy = -abs_dy;
	if (abs_dy < abs_dx)
	{
		if (a.x > b.x)
			draw_line_low_color(img, b, a, color2, color1);
		else
			draw_line_low_color(img, a, b, color1, color2);
	}
	else
	{
		if (a.y > b.y)
			draw_line_high_color(img, b, a, color2, color1);
		else
			draw_line_high_color(img, a, b, color1, color2);
	}
}
