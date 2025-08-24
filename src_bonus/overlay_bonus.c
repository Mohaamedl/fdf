/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlay_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:58:38 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/24 20:35:40 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	draw_text_line(t_app *app, char *text, int y, int color)
{
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, color, text);
}

void	draw_controls_overlay(t_app *app)
{
	int	y;
	int	color;

	y = 20;
	color = 0xFFFFFF;
	
	draw_text_line(app, "=== FdF BONUS CONTROLS ===", y, 0x00FF00);
	y += 25;
	draw_text_line(app, "PROJECTION:", y, 0xFFFF00);
	y += 20;
	draw_text_line(app, "  P - Cycle projection (ISO/PAR/PER)", y, color);
	y += 25;
	draw_text_line(app, "ZOOM:", y, 0xFFFF00);
	y += 20;
	draw_text_line(app, "  +/- - Zoom in/out", y, color);
	y += 15;
	draw_text_line(app, "  Mouse scroll - Zoom", y, color);
	y += 25;
	draw_text_line(app, "TRANSLATION:", y, 0xFFFF00);
	y += 20;
	draw_text_line(app, "  WASD/Arrows - Move model", y, color);
	y += 15;
	draw_text_line(app, "  Right mouse - Pan/Move view", y, color);
	y += 25;
	draw_text_line(app, "ROTATION:", y, 0xFFFF00);
	y += 20;
	draw_text_line(app, "  Q/E - Z-axis rotation", y, color);
	y += 15;
	draw_text_line(app, "  I/K - X-axis rotation (pitch)", y, color);
	y += 15;
	draw_text_line(app, "  J/L - Y-axis rotation (yaw)", y, color);
	y += 15;
	draw_text_line(app, "  Left mouse - Orbit/Rotate", y, color);
	y += 15;
	draw_text_line(app, "  Right mouse - Pan/Move view", y, color);
	y += 15;
	draw_text_line(app, "  Middle mouse - Z-axis rotation", y, color);
	y += 25;
	draw_text_line(app, "EXTRA:", y, 0xFFFF00);
	y += 20;
	draw_text_line(app, "  Z/X or 1/2 - Height scale", y, color);
	y += 15;
	draw_text_line(app, "  SPACE - Demo mode", y, color);
	y += 15;
	draw_text_line(app, "  H - Toggle this help", y, color);
	y += 25;
	draw_text_line(app, "ESC - Exit", y, 0xFF0000);
}

// Clean help overlay for bonus app
void	draw_help_overlay_complete(t_app_bonus *app)
{
	int	y = 20;
	
	if (!app->show_help)
		return;
	
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0x00FF00, "=== FdF BONUS CONTROLS ===");
	y += 25;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFF00, "PROJECTION:");
	y += 20;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFFFF, "  P - Cycle projection (ISO/PAR/PER)");
	y += 25;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFF00, "ZOOM:");
	y += 20;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFFFF, "  +/- - Zoom in/out");
	y += 15;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFFFF, "  Mouse scroll - Zoom");
	y += 25;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFF00, "TRANSLATION:");
	y += 20;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFFFF, "  WASD/Arrows - Move model");
	y += 15;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFFFF, "  Right mouse - Pan/Move view");
	y += 25;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFF00, "ROTATION:");
	y += 20;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFFFF, "  Q/E - Z-axis rotation");
	y += 15;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFFFF, "  I/K - X-axis rotation (pitch)");
	y += 15;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFFFF, "  J/L - Y-axis rotation (yaw)");
	y += 15;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFFFF, "  Left mouse - Orbit/Rotate");
	y += 15;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFFFF, "  Right mouse - Pan/Move view");
	y += 15;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFFFF, "  Middle mouse - Z-axis rotation");
	y += 25;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFF00, "EXTRA:");
	y += 20;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFFFF, "  Z/X or 1/2 - Height scale");
	y += 15;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFFFF, "  C - Cycle color modes");
	y += 15;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFFFF, "  SPACE - Demo mode");
	y += 15;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFFFF, "  H - Toggle this help");
	y += 25;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFF0000, "ESC - Exit");
}

// Status display for bonus app
void	draw_status_display(t_app_bonus *app)
{
	int		x = WIN_W - 220;
	int		y = 20;
	char	*proj_name;
	char	*color_name;
	
	// Display current projection
	if (app->view.proj == PROJ_ISO)
		proj_name = "ISOMETRIC";
	else if (app->view.proj == PROJ_PAR)
		proj_name = "PARALLEL";
	else
		proj_name = "PERSPECTIVE";
	
	// Display current color mode (0..4 supported)
	if (app->color_mode == 0)
		color_name = "PALETTE";
	else if (app->color_mode == 1)
		color_name = "RAINBOW";
	else if (app->color_mode == 2)
		color_name = "GRAYSCALE";
	else if (app->color_mode == 3)
		color_name = "FIRE";
	else if (app->color_mode == 4)
		color_name = "ICE";
	else
		color_name = "PALETTE";
		
	mlx_string_put(app->mlx.mlx, app->mlx.win, x, y, 0x00FFFF, "=== STATUS ===");
	y += 25;
	// Show FPS if measured (>0)
	if (app->fps > 0)
	{
		char *fps_str = ft_itoa(app->fps);
		if (fps_str)
		{
			mlx_string_put(app->mlx.mlx, app->mlx.win, x, y, 0xCCCCCC, "FPS:");
			mlx_string_put(app->mlx.mlx, app->mlx.win, x + 40, y, 0xFFFFFF, fps_str);
			free(fps_str);
		}
		y += 25;
	}
	mlx_string_put(app->mlx.mlx, app->mlx.win, x, y, 0xCCCCCC, "Projection:");
	y += 15;
	mlx_string_put(app->mlx.mlx, app->mlx.win, x + 10, y, 0xFFFFFF, proj_name);
	y += 25;
	mlx_string_put(app->mlx.mlx, app->mlx.win, x, y, 0xCCCCCC, "Colors:");
	y += 15;
	mlx_string_put(app->mlx.mlx, app->mlx.win, x + 10, y, 0xFFFFFF, color_name);
	y += 25;
	
	if (app->demo_mode)
	{
		mlx_string_put(app->mlx.mlx, app->mlx.win, x, y, 0x00FF00, "DEMO MODE");
		mlx_string_put(app->mlx.mlx, app->mlx.win, x, y + 15, 0x00FF00, "Auto rotating...");
		y += 40;
	}
	
	mlx_string_put(app->mlx.mlx, app->mlx.win, x, y, 0xCCCCCC, "Controls: Press H");
}
