/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_keys_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:22:03 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/09/07 20:22:08 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf_bonus.h"

int	hook_key_bonus_complete(int keycode, void *param)
{
	t_app_bonus	*app;

	app = (t_app_bonus *)param;
	if (!app)
		return (0);
	if (keycode == KEY_ESC)
		return (hook_destroy_bonus(app));
	if (keycode != KEY_SPACE)
		app->demo_mode = 0;
	if (keycode == KEY_P)
		handle_projection_change(app);
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT || keycode == KEY_UP
		|| keycode == KEY_DOWN || keycode == KEY_A || keycode == KEY_D
		|| keycode == KEY_W || keycode == KEY_S)
		handle_movement_keys(keycode, app);
	else if (keycode == KEY_PLUS || keycode == KEY_KP_ADD
		|| keycode == KEY_MINUS || keycode == KEY_KP_SUB)
		handle_zoom_keys(keycode, app);
	else if (keycode == KEY_Q || keycode == KEY_E || keycode == KEY_I
		|| keycode == KEY_K || keycode == KEY_J || keycode == KEY_L)
		handle_rotation_keys(keycode, app);
	return (handle_other_keys(keycode, app));
}

int	hook_key_release_bonus(int keycode, void *param)
{
	(void)keycode;
	(void)param;
	return (0);
}

static int	*get_frame_count(void)
{
	static int	frame_count = 0;

	return (&frame_count);
}

static struct timeval	*get_fps_last(void)
{
	static struct timeval	fps_last = {0};

	return (&fps_last);
}

int	loop_hook_bonus(void *param)
{
	t_app_bonus	*app;

	app = (t_app_bonus *)param;
	if (!app)
		return (0);
	if (app->demo_mode)
		demo_mode_update(app);
	if (app->needs_redraw)
		handle_redraw(app, get_frame_count(), get_fps_last());
	return (0);
}
