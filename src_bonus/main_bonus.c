/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:58:32 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/24 20:35:40 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include <sys/time.h>

void	app_destroy_bonus(t_app_bonus *app, int code)
{
	if (app->mlx.img.ptr)
		mlx_destroy_image(app->mlx.mlx, app->mlx.img.ptr);
	if (app->mlx.win)
		mlx_destroy_window(app->mlx.mlx, app->mlx.win);
	if (app->mlx.mlx)
	{
		mlx_destroy_display(app->mlx.mlx);
		free(app->mlx.mlx);
	}
	free_map(&app->map);
	exit(code);
}

int	hook_destroy_bonus(void *param)
{
	t_app_bonus	*app;

	app = (t_app_bonus *)param;
	app_destroy_bonus(app, 0);
	return (0);
}

void	rerender_bonus_complete(t_app_bonus *app)
{
	render_wireframe_bonus_complete(app);
	mlx_put_image_to_window(app->mlx.mlx, app->mlx.win, app->mlx.img.ptr, 0, 0);
	draw_help_overlay_complete(app);
	draw_status_display(app);
}

void	rerender_bonus_immediate(t_app_bonus *app)
{
	render_wireframe_bonus_complete(app);
	mlx_put_image_to_window(app->mlx.mlx, app->mlx.win, app->mlx.img.ptr, 0, 0);
	draw_help_overlay_complete(app);
	draw_status_display(app);
}

int	main(int argc, char **argv)
{
	t_app_bonus	app;

	if (argc != 2)
	{
		write(2, "Usage: ./fdf_bonus map_file\n", 29);
		return (1);
	}
	if (!parse_map(argv[1], &app.map))
	{
		write(2, "Error: Failed to parse map\n", 28);
		return (1);
	}
	init_app_vars(&app);
	if (!mlx_init_safe(&app.mlx))
	{
		free_map(&app.map);
		write(2, "Error: Failed to initialize MLX\n", 33);
		return (1);
	}
	init_view_bonus(&app);
	app.demo_mode = 0;
	setup_hooks(&app);
	app.needs_redraw = 1;
	mlx_loop(app.mlx.mlx);
	return (0);
}
