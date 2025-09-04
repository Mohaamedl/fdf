/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 22:12:02 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/09/04 22:12:21 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf_bonus.h"

void	draw_text_line(t_app *app, char *text, int y, int color)
{
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, color, text);
}

char	*get_projection_name(int proj)
{
	if (proj == 0)
		return ("Isometric");
	else if (proj == 1)
		return ("Perspective");
	else if (proj == 2)
		return ("Orthographic");
	return ("Unknown");
}

void	draw_basic_controls(t_app *app, int *y, int color)
{
	draw_text_line(app, "PROJECTION:", *y, 0xFFFF00);
	*y += 20;
	draw_text_line(app, "  P - Cycle projection", *y, color);
	*y += 25;
	draw_text_line(app, "ZOOM:", *y, 0xFFFF00);
	*y += 20;
	draw_text_line(app, "  +/- - Zoom in/out", *y, color);
	*y += 15;
	draw_text_line(app, "  Mouse scroll - Zoom", *y, color);
	*y += 25;
}

void	draw_movement_controls(t_app *app, int *y, int color)
{
	draw_text_line(app, "TRANSLATION:", *y, 0xFFFF00);
	*y += 20;
	draw_text_line(app, "  WASD/Arrows - Move model", *y, color);
	*y += 15;
	draw_text_line(app, "  Right mouse - Pan view", *y, color);
	*y += 25;
	draw_text_line(app, "ROTATION:", *y, 0xFFFF00);
	*y += 20;
	draw_text_line(app, "  Q/E - Z-axis rotation", *y, color);
	*y += 15;
	draw_text_line(app, "  I/K - X-axis rotation", *y, color);
	*y += 15;
	draw_text_line(app, "  J/L - Y-axis rotation", *y, color);
	*y += 25;
}
