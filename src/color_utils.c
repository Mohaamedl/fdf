/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:00:00 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/09/12 15:00:00 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	extract_rgb(int color, int *rgb)
{
	rgb[0] = (color >> 16) & 0xFF;
	rgb[1] = (color >> 8) & 0xFF;
	rgb[2] = color & 0xFF;
}

int	lerp_color(int color1, int color2, double t)
{
	int	rgb1[3];
	int	rgb2[3];

	extract_rgb(color1, rgb1);
	extract_rgb(color2, rgb2);
	return (((int)(rgb1[0] + (rgb2[0] - rgb1[0]) * t) << 16)
		| ((int)(rgb1[1] + (rgb2[1] - rgb1[1]) * t) << 8)
		| (int)(rgb1[2] + (rgb2[2] - rgb1[2]) * t));
}
