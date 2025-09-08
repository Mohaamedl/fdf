/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_keys_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:23:01 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/09/07 20:23:07 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf_bonus.h"

void	reset_view(t_app_bonus *app)
{
	double	scale_x;
	double	scale_y;
	double	auto_scale;

	scale_x = (WIN_W * 0.6) / app->map.w;
	scale_y = (WIN_H * 0.6) / app->map.h;
	if (scale_x < scale_y)
		auto_scale = scale_x;
	else
		auto_scale = scale_y;
	if (auto_scale < 0.5)
		auto_scale = 0.5;
	else if (auto_scale > 50.0)
		auto_scale = 50.0;
	app->view.scale = auto_scale;
	app->view.offset_x = WIN_W / 2;
	app->view.offset_y = WIN_H / 2;
	app->view.rot_x = 0.0;
	app->view.rot_y = 0.0;
	app->view.rot_z = 0.0;
	app->view.zscale = 1.0;
	app->view.proj = PROJ_ISO;
	app->needs_redraw = 1;
}

int	throttle_ok_and_stamp(t_app_bonus *app, long min_ms)
{
	struct timeval	now;
	long			diff;

	gettimeofday(&now, NULL);
	diff = (now.tv_sec - app->view.last_render_time.tv_sec) * 1000
		+ (now.tv_usec - app->view.last_render_time.tv_usec) / 1000;
	if (diff < min_ms)
		return (0);
	app->view.last_render_time = now;
	return (1);
}

int	handle_other_keys(int keycode, t_app_bonus *app)
{
	if (keycode == KEY_Z || keycode == KEY_1 || keycode == KEY_X
		|| keycode == KEY_2)
		handle_zscale_keys(keycode, app);
	else if (keycode == KEY_R)
		reset_view(app);
	else if (keycode == KEY_H)
	{
		app->show_help = !app->show_help;
		app->needs_redraw = 1;
	}
	else if (keycode == KEY_SPACE)
	{
		app->demo_mode = !app->demo_mode;
		app->needs_redraw = 1;
	}
	else if (keycode == KEY_C)
	{
		app->color_mode = (app->color_mode + 1) % 5;
		app->needs_redraw = 1;
	}
	return (0);
}

void	handle_redraw(t_app_bonus *app, int *frame_count,
	struct timeval *fps_last)
{
	struct timeval	now;
	long			elapsed_ms;
	long			fps_window_ms;
	const long		target_ms = 16;

	gettimeofday(&now, NULL);
	elapsed_ms = (now.tv_sec - app->view.last_render_time.tv_sec) * 1000
		+ (now.tv_usec - app->view.last_render_time.tv_usec) / 1000;
	if (elapsed_ms >= target_ms)
	{
		app->view.last_render_time = now;
		app->needs_redraw = 0;
		rerender_bonus_complete(app);
		(*frame_count)++;
		if (fps_last->tv_sec == 0 && fps_last->tv_usec == 0)
			*fps_last = now;
		fps_window_ms = (now.tv_sec - fps_last->tv_sec) * 1000
			+ (now.tv_usec - fps_last->tv_usec) / 1000;
		if (fps_window_ms >= 1000)
		{
			app->fps = (int)((*frame_count * 1000L) / fps_window_ms);
			*frame_count = 0;
			*fps_last = now;
		}
	}
}
