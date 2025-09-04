/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlay_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 22:11:37 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/09/04 22:11:53 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf_bonus.h"

void	draw_controls_overlay(t_app *app)
{
	int	y;
	int	color;

	y = 20;
	color = 0xFFFFFF;
	draw_text_line(app, "=== FdF BONUS CONTROLS ===", y, 0x00FF00);
	y += 25;
	draw_basic_controls(app, &y, color);
	draw_movement_controls(app, &y, color);
	draw_text_line(app, "OTHER:", y, 0xFFFF00);
	y += 20;
	draw_text_line(app, "  ESC - Exit", y, color);
	y += 15;
	draw_text_line(app, "  H - Toggle help", y, color);
}

void	draw_help_overlay_complete(t_app_bonus *app)
{
	int	y;
	int	color;

	if (!app->show_help)
		return ;
	y = 20;
	color = 0xFFFFFF;
	draw_text_line((t_app *)app, "=== FdF BONUS CONTROLS ===", y, 0x00FF00);
	y += 25;
	draw_basic_controls((t_app *)app, &y, color);
	draw_movement_controls((t_app *)app, &y, color);
	draw_text_line((t_app *)app, "EXTRA:", y, 0xFFFF00);
	y += 20;
	draw_text_line((t_app *)app, "  Z/X - Height scale", y, color);
	y += 15;
	draw_text_line((t_app *)app, "  SPACE - Demo mode", y, color);
	y += 15;
	draw_text_line((t_app *)app, "  ESC - Exit", y, 0xFF0000);
}

static void	draw_status_info(t_app_bonus *app, int x, int *y)
{
	char	*proj_name;
	char	*fps_str;

	proj_name = get_projection_name(app->view.proj);
	if (app->fps > 0)
	{
		fps_str = ft_itoa(app->fps);
		if (fps_str)
		{
			mlx_string_put(app->mlx.mlx, app->mlx.win, x, *y, 0xCCCCCC,
				"FPS:");
			mlx_string_put(app->mlx.mlx, app->mlx.win, x + 40, *y, 0xFFFFFF,
				fps_str);
			free(fps_str);
		}
		*y += 25;
	}
	mlx_string_put(app->mlx.mlx, app->mlx.win, x, *y, 0xCCCCCC,
		"Projection:");
	*y += 15;
	mlx_string_put(app->mlx.mlx, app->mlx.win, x + 10, *y, 0xFFFFFF,
		proj_name);
	*y += 25;
}

void	draw_status_display(t_app_bonus *app)
{
	int	x;
	int	y;

	x = WIN_W - 220;
	y = 20;
	mlx_string_put(app->mlx.mlx, app->mlx.win, x, y, 0x00FFFF,
		"=== STATUS ===");
	y += 25;
	draw_status_info(app, x, &y);
	if (app->demo_mode)
	{
		mlx_string_put(app->mlx.mlx, app->mlx.win, x, y, 0x00FF00,
			"DEMO MODE");
		mlx_string_put(app->mlx.mlx, app->mlx.win, x, y + 15, 0x00FF00,
			"Auto rotating...");
		y += 40;
	}
	mlx_string_put(app->mlx.mlx, app->mlx.win, x, y, 0xCCCCCC,
		"Controls: Press H");
}
