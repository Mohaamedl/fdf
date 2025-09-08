/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:55:21 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/09/08 18:56:15 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	init_view_defaults(t_app *app)
{
	app->view.angle = M_PI / 6.0;
	app->view.zscale = 1.0;
	app->view.proj = PROJ_ISO;
	app->view.rot_x = -M_PI / 6.0;
	app->view.rot_y = M_PI / 4.0;
	app->view.rot_z = 0.0;
	recompute_view_fit(app);
}

static void	setup_hooks(t_app *app)
{
	mlx_key_hook(app->mlx.win, hook_key, app);
	mlx_hook(app->mlx.win, EVENT_DESTROY, 0, hook_destroy, app);
}

int	app_init(t_app *app, const char *path)
{
	if (!parse_map(path, &app->map))
		return (0);
	if (!mlx_init_safe(&app->mlx))
		return (free_map(&app->map), 0);
	init_view_defaults(app);
	setup_hooks(app);
	return (1);
}

void	app_destroy(t_app *app, int code)
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

int	main(int argc, char **argv)
{
	t_app	app;

	if (argc != 2)
	{
		ft_printf("Usage: ./fdf <map.fdf>\n");
		return (1);
	}
	if (!app_init(&app, argv[1]))
		return (1);
	render_wireframe(&app);
	mlx_put_image_to_window(app.mlx.mlx, app.mlx.win, app.mlx.img.ptr, 0, 0);
	mlx_loop(app.mlx.mlx);
	return (0);
}
