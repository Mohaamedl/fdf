/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   demo_mode_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 21:57:17 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/09/04 21:57:42 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf_bonus.h"

static double	init_base_scale(t_app_bonus *app)
{
	double	scale_x;
	double	scale_y;
	double	base_scale;

	scale_x = (WIN_W * 0.6) / app->map.w;
	scale_y = (WIN_H * 0.6) / app->map.h;
	if (scale_x < scale_y)
		base_scale = scale_x;
	else
		base_scale = scale_y;
	if (base_scale < 0.5)
		base_scale = 0.5;
	else if (base_scale > 50.0)
		base_scale = 50.0;
	return (base_scale);
}

static void	update_view_params(t_app_bonus *app, double time,
	double base_scale, int frame_count)
{
	app->view.rot_y = sin(time * 0.5) * 0.8;
	app->view.rot_x = 0.3 + cos(time * 0.3) * 0.4;
	app->view.rot_z = sin(time * 0.2) * 0.2;
	app->view.scale = base_scale + sin(time) * (base_scale * 0.15);
	app->view.zscale = 1.0 + sin(time * 0.7) * 0.3;
	if (frame_count % 300 == 0)
	{
		app->view.proj = (app->view.proj + 1) % 4;
		app->view.offset_x = WIN_W / 2;
		app->view.offset_y = WIN_H / 2;
	}
	if (frame_count % 2 == 0)
		app->needs_redraw = 1;
}

void	demo_mode_update(t_app_bonus *app)
{
	static double	time = 0.0;
	static double	base_scale = 0.0;
	static int		frame_count = 0;

	if (!app->demo_mode)
		return ;
	if (base_scale == 0.0)
		base_scale = init_base_scale(app);
	time += 0.09;
	frame_count++;
	update_view_params(app, time, base_scale, frame_count);
}

void	app_message(t_app *app, char *msg)
{
	(void)app;
	(void)msg;
}
