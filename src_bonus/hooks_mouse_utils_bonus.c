/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_mouse_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:23:01 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/09/07 20:23:07 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf_bonus.h"

void	handle_scroll_zoom(t_app_bonus *app, int button, int x, int y)
{
	double	old_scale;
	double	zoom_step;
	double	new_scale;

	app->demo_mode = 0;
	old_scale = app->view.scale;
	zoom_step = 1.12;
	if (button == BTN_SCROLL_UP)
		new_scale = old_scale * zoom_step;
	else
		new_scale = old_scale / zoom_step;
	if (new_scale < 0.02)
		new_scale = 0.02;
	if (new_scale > 150.0)
		new_scale = 150.0;
	app->view.offset_x = x - (x - app->view.offset_x) * (new_scale / old_scale);
	app->view.offset_y = y - (y - app->view.offset_y) * (new_scale / old_scale);
	app->view.scale = new_scale;
	app->needs_redraw = 1;
}

void	handle_mouse_button_press(t_app_bonus *app, int button, int x, int y)
{
	if (button == BTN_LEFT || button == BTN_RIGHT || button == BTN_MIDDLE)
	{
		app->mouse_down = 1;
		app->mouse_button = button;
		app->last_x = x;
		app->last_y = y;
		app->demo_mode = 0;
	}
}

long	get_target_ms(t_app_bonus *app)
{
	long	map_size;

	map_size = (long)app->map.w * (long)app->map.h;
	if (map_size < 50000)
		return (8);
	else if (map_size < 150000)
		return (12);
	else if (map_size < 350000)
		return (16);
	else
		return (28);
}

int	check_mouse_throttle(t_app_bonus *app)
{
	struct timeval	now;
	long			time_diff_ms;
	long			target_ms;

	gettimeofday(&now, NULL);
	time_diff_ms = (now.tv_sec - app->view.last_render_time.tv_sec) * 1000
		+ (now.tv_usec - app->view.last_render_time.tv_usec) / 1000;
	target_ms = get_target_ms(app);
	if (time_diff_ms < target_ms)
		return (0);
	app->view.last_render_time = now;
	return (1);
}

void	handle_left_mouse_drag(t_app_bonus *app, int dx, int dy)
{
	const double	sens = 0.004;
	const double	max_pitch = 1.35;

	app->view.rot_y += dx * sens;
	app->view.rot_x -= dy * sens;
	if (app->view.rot_x > max_pitch)
		app->view.rot_x = max_pitch;
	if (app->view.rot_x < -max_pitch)
		app->view.rot_x = -max_pitch;
}
