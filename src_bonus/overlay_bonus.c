/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlay_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:58:38 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/23 13:58:56 by mhaddadi         ###   ########.fr       */
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
	draw_text_line(app, "  Right mouse - Drag to move", y, color);
	y += 25;
	draw_text_line(app, "ROTATION:", y, 0xFFFF00);
	y += 20;
	draw_text_line(app, "  Q/E - Z-axis rotation", y, color);
	y += 15;
	draw_text_line(app, "  Z/X - X-axis rotation", y, color);
	y += 15;
	draw_text_line(app, "  R/F - Y-axis rotation", y, color);
	y += 15;
	draw_text_line(app, "  Left mouse - Orbit camera", y, color);
	y += 25;
	draw_text_line(app, "EXTRA:", y, 0xFFFF00);
	y += 20;
	draw_text_line(app, "  1/2 - Height scale", y, color);
	y += 15;
	draw_text_line(app, "  TAB - Demo mode", y, color);
	y += 15;
	draw_text_line(app, "  H - Toggle this help", y, color);
	y += 25;
	draw_text_line(app, "ESC - Exit", y, 0xFF0000);
}

// Help overlay display for bonus app
void	draw_help_overlay_complete(t_app_bonus *app)
{
	int	y = 20;
	
	if (!app->show_help)
		return;
	
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0x00FF00, "=== FdF BONUS CONTROLS ===");
	y += 25;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0x00FFFF, "Hold keys for smooth movement!");
	y += 25;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFF00, "PROJECTIONS:");
	y += 20;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFFFF, "  P - Cycle projection (ISO/PAR/PER)");
	y += 25;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFF00, "ZOOM:");
	y += 20;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFFFF, "  +/- - Zoom (hold for smooth)");
	y += 15;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFFFF, "  Mouse scroll - Zoom");
	y += 25;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFF00, "TRANSLATION:");
	y += 20;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFFFF, "  WASD/Arrows - Move model");
	y += 15;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFFFF, "  Right mouse drag - Pan view");
	y += 25;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFF00, "ROTATION:");
	y += 20;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFFFF, "  Q/E - Z-axis rotation");
	y += 15;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFFFF, "  Z/X - X-axis rotation");
	y += 15;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFFFF, "  R/T - Y-axis rotation");
	y += 15;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFFFF, "  Left mouse drag - Orbit camera");
	y += 25;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFF00, "EXTRA:");
	y += 20;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFFFF, "  1/2 - Height scale");
	y += 15;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFFFF, "  TAB - Demo mode");
	y += 15;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFFFFFF, "  H - Toggle this help");
	y += 25;
	mlx_string_put(app->mlx.mlx, app->mlx.win, 10, y, 0xFF0000, "ESC - Exit");
}

void	draw_status_overlay(t_app *app)
{
	char	*proj_name;
	int		x, y;

	x = WIN_W - 200;
	y = 20;
	
	if (app->view.proj == PROJ_ISO)
		proj_name = "ISOMETRIC";
	else if (app->view.proj == PROJ_PAR)
		proj_name = "PARALLEL";
	else
		proj_name = "PERSPECTIVE";
		
	draw_text_line(app, "=== STATUS ===", y, 0x00FFFF);
	y += 25;
	
	mlx_string_put(app->mlx.mlx, app->mlx.win, x, y, 0xFFFFFF, "Projection:");
	y += 15;
	mlx_string_put(app->mlx.mlx, app->mlx.win, x + 10, y, 0xFFFFFF, proj_name);
	y += 25;
	
	mlx_string_put(app->mlx.mlx, app->mlx.win, x, y, 0xFFFFFF, "Scale:");
	y += 20;
	
	mlx_string_put(app->mlx.mlx, app->mlx.win, x, y, 0xFFFFFF, "Z-Scale:");
	y += 20;
	
	if (app->demo_mode)
		mlx_string_put(app->mlx.mlx, app->mlx.win, x, y, 0x00FF00, "DEMO MODE ON");
}

// Status display for bonus app
void	draw_status_display(t_app_bonus *app)
{
	int		x = WIN_W - 200;
	int		y = 20;
	char	*proj_name;
	
	// Display current projection
	if (app->view.proj == PROJ_ISO)
		proj_name = "ISOMETRIC";
	else if (app->view.proj == PROJ_PAR)
		proj_name = "PARALLEL";
	else
		proj_name = "PERSPECTIVE";
		
	mlx_string_put(app->mlx.mlx, app->mlx.win, x, y, 0x00FFFF, "=== STATUS ===");
	y += 25;
	mlx_string_put(app->mlx.mlx, app->mlx.win, x, y, 0xFFFFFF, "Projection:");
	y += 15;
	mlx_string_put(app->mlx.mlx, app->mlx.win, x + 10, y, 0xFFFFFF, proj_name);
	y += 25;
	mlx_string_put(app->mlx.mlx, app->mlx.win, x, y, 0xFFFFFF, "Scale: Interactive");
	y += 20;
	mlx_string_put(app->mlx.mlx, app->mlx.win, x, y, 0xFFFFFF, "Z-Scale: Interactive");
	y += 25;
	
	if (app->demo_mode)
		mlx_string_put(app->mlx.mlx, app->mlx.win, x, y, 0x00FF00, "DEMO MODE ON");
}
