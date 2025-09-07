/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 20:35:00 by mohamed           #+#    #+#             */
/*   Updated: 2025/08/24 20:35:00 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include <sys/time.h>

void	init_app_vars(t_app_bonus *app)
{
	ft_memset(&app->mlx, 0, sizeof(t_mlx));
	app->show_help = 0;
	app->demo_mode = 0;
	app->fps = 0;
	app->needs_redraw = 1;
	app->color_mode = COLOR_DEFAULT;
	app->mouse_down = 0;
	app->mouse_button = 0;
	app->last_x = 0;
	app->last_y = 0;
}

void	setup_hooks(t_app_bonus *app)
{
	mlx_hook(app->mlx.win, 17, 0, hook_destroy_bonus, app);
	mlx_key_hook(app->mlx.win, hook_key_bonus_complete, app);
	mlx_hook(app->mlx.win, 2, 1L << 0, hook_key_bonus_complete, app);
	mlx_hook(app->mlx.win, 3, 1L << 1, hook_key_release_bonus, app);
	mlx_loop_hook(app->mlx.mlx, loop_hook_bonus, app);
	mlx_hook(app->mlx.win, 4, 1L << 2, hook_mouse_bonus, app);
	mlx_hook(app->mlx.win, 5, 1L << 3, hook_mouse_release_bonus, app);
	mlx_hook(app->mlx.win, 6, 1L << 6, hook_mouse_move_bonus, app);
}

static void	calculate_auto_scale(t_app_bonus *app, double *auto_scale)
{
	double	scale_x;
	double	scale_y;

	scale_x = (WIN_W * 0.6) / app->map.w;
	scale_y = (WIN_H * 0.6) / app->map.h;
	if (scale_x < scale_y)
		*auto_scale = scale_x;
	else
		*auto_scale = scale_y;
	if (*auto_scale < 0.5)
		*auto_scale = 0.5;
	else if (*auto_scale > 50.0)
		*auto_scale = 50.0;
}

void	init_view_bonus(t_app_bonus *app)
{
	double	auto_scale;

	app->view.angle = M_PI / 6.0;
	app->view.zscale = 1.0;
	app->view.proj = PROJ_ISO;
	app->view.rot_x = 0.0;
	app->view.rot_y = 0.0;
	app->view.rot_z = 0.0;
	gettimeofday(&app->view.last_render_time, NULL);
	calculate_auto_scale(app, &auto_scale);
	app->view.scale = auto_scale;
	app->view.offset_x = WIN_W / 2;
	app->view.offset_y = WIN_H / 2;
	app->show_help = 0;
	app->demo_mode = 0;
}
