/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_keys_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:58:22 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/24 20:35:40 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static int	throttle_ok_and_stamp(t_app_bonus *app, long min_ms)
{
	struct timeval now;
	long diff;

	gettimeofday(&now, NULL);
	diff = (now.tv_sec - app->view.last_render_time.tv_sec) * 1000
		+ (now.tv_usec - app->view.last_render_time.tv_usec) / 1000;
	if (diff < min_ms)
		return (0);
	app->view.last_render_time = now;
	return (1);
}

int			hook_key_bonus_complete(int keycode, void *param)
{
	t_app_bonus *app = (t_app_bonus *)param;

	if (!app)
		return (0);
	if (keycode == KEY_ESC)
		return (hook_destroy_bonus(app));

	if (keycode != KEY_SPACE)
		app->demo_mode = 0;

	if (keycode == KEY_P)
	{
		app->view.proj = (app->view.proj + 1) % 3;
		app->needs_redraw = 1;
	}
	else if (keycode == KEY_LEFT)
	{
		app->view.offset_x -= 10;
		app->needs_redraw = 1;
	}
	else if (keycode == KEY_RIGHT)
	{
		app->view.offset_x += 10;
		app->needs_redraw = 1;
	}
	else if (keycode == KEY_UP)
	{
		app->view.offset_y -= 10;
		app->needs_redraw = 1;
	}
	else if (keycode == KEY_DOWN)
	{
		app->view.offset_y += 10;
		app->needs_redraw = 1;
	}
	else if (keycode == KEY_A)
	{
		app->view.offset_x -= 10;
		app->needs_redraw = 1;
	}
	else if (keycode == KEY_D)
	{
		app->view.offset_x += 10;
		app->needs_redraw = 1;
	}
	else if (keycode == KEY_W)
	{
		app->view.offset_y -= 10;
		app->needs_redraw = 1;
	}
	else if (keycode == KEY_S)
	{
		app->view.offset_y += 10;
		app->needs_redraw = 1;
	}
	else if (keycode == KEY_PLUS || keycode == KEY_KP_ADD)
	{
		app->view.scale *= 1.1;
		if (app->view.scale > 150.0)
			app->view.scale = 150.0;
		app->needs_redraw = 1;
	}
	else if (keycode == KEY_MINUS || keycode == KEY_KP_SUB)
	{
		app->view.scale /= 1.1;
		if (app->view.scale < 0.02)
			app->view.scale = 0.02;
		app->needs_redraw = 1;
	}
	else if (keycode == KEY_Q)
	{
		if (throttle_ok_and_stamp(app, 12))
		{
			app->view.rot_z -= 0.1;
			app->needs_redraw = 1;
		}
	}
	else if (keycode == KEY_E)
	{
		if (throttle_ok_and_stamp(app, 12))
		{
			app->view.rot_z += 0.1;
			app->needs_redraw = 1;
		}
	}
	else if (keycode == KEY_I)
	{
		if (throttle_ok_and_stamp(app, 12))
		{
			app->view.rot_x -= 0.1;
			app->needs_redraw = 1;
		}
	}
	else if (keycode == KEY_K)
	{
		if (throttle_ok_and_stamp(app, 12))
		{
			app->view.rot_x += 0.1;
			app->needs_redraw = 1;
		}
	}
	else if (keycode == KEY_J)
	{
		if (throttle_ok_and_stamp(app, 12))
		{
			app->view.rot_y -= 0.1;
			app->needs_redraw = 1;
		}
	}
	else if (keycode == KEY_L)
	{
		if (throttle_ok_and_stamp(app, 12))
		{
			app->view.rot_y += 0.1;
			app->needs_redraw = 1;
		}
	}
	else if (keycode == KEY_Z || keycode == KEY_1)
	{
		app->view.zscale *= 1.1;
		if (app->view.zscale > 100.0)
			app->view.zscale = 100.0;
		app->needs_redraw = 1;
	}
	else if (keycode == KEY_X || keycode == KEY_2)
	{
		app->view.zscale /= 1.1;
		if (app->view.zscale < 0.1)
			app->view.zscale = 0.1;
		app->needs_redraw = 1;
	}
	else if (keycode == KEY_R)
	{
		double scale_x = (WIN_W * 0.6) / app->map.w;
		double scale_y = (WIN_H * 0.6) / app->map.h;
		double auto_scale = (scale_x < scale_y) ? scale_x : scale_y;
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

int			hook_key_release_bonus(int keycode, void *param)
{
	(void)keycode;
	(void)param;
	return (0);
}

int			loop_hook_bonus(void *param)
{
	t_app_bonus *app = (t_app_bonus *)param;
	static int frame_count = 0;
	static struct timeval fps_last = {0};

	if (!app)
		return (0);

	if (app->demo_mode)
		demo_mode_update(app);

	if (app->needs_redraw)
	{
		struct timeval now;
		long elapsed_ms;
		const long target_ms = 16; // ~60 FPS cap

		gettimeofday(&now, NULL);
		elapsed_ms = (now.tv_sec - app->view.last_render_time.tv_sec) * 1000
			+ (now.tv_usec - app->view.last_render_time.tv_usec) / 1000;
		if (elapsed_ms >= target_ms)
		{
			app->view.last_render_time = now;
			app->needs_redraw = 0;
			rerender_bonus_complete(app);
			frame_count++;
			if (fps_last.tv_sec == 0 && fps_last.tv_usec == 0)
				fps_last = now;
			long fps_window_ms = (now.tv_sec - fps_last.tv_sec) * 1000
				+ (now.tv_usec - fps_last.tv_usec) / 1000;
			if (fps_window_ms >= 1000)
			{
				app->fps = (int)((frame_count * 1000L) / (fps_window_ms ? fps_window_ms : 1));
				frame_count = 0;
				fps_last = now;
			}
		}
	}
	return (0);
}
