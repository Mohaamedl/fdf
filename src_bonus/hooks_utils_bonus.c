/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:23:01 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/09/07 20:23:07 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf_bonus.h"

void	handle_movement_keys(int keycode, t_app_bonus *app)
{
	if (keycode == KEY_LEFT || keycode == KEY_A)
	{
		app->view.offset_x -= 10;
		app->needs_redraw = 1;
	}
	else if (keycode == KEY_RIGHT || keycode == KEY_D)
	{
		app->view.offset_x += 10;
		app->needs_redraw = 1;
	}
	else if (keycode == KEY_UP || keycode == KEY_W)
	{
		app->view.offset_y -= 10;
		app->needs_redraw = 1;
	}
	else if (keycode == KEY_DOWN || keycode == KEY_S)
	{
		app->view.offset_y += 10;
		app->needs_redraw = 1;
	}
}

void	handle_zoom_keys(int keycode, t_app_bonus *app)
{
	if (keycode == KEY_PLUS || keycode == KEY_KP_ADD)
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
}

void	handle_rotation_keys(int keycode, t_app_bonus *app)
{
	if (keycode == KEY_Q && throttle_ok_and_stamp(app, 12))
	{
		app->view.rot_z -= 0.1;
		app->needs_redraw = 1;
	}
	else if (keycode == KEY_E && throttle_ok_and_stamp(app, 12))
	{
		app->view.rot_z += 0.1;
		app->needs_redraw = 1;
	}
	else
		handle_xyz_rotation_keys(keycode, app);
}

void	handle_xyz_rotation_keys(int keycode, t_app_bonus *app)
{
	handle_x_rotation(keycode, app);
	handle_y_rotation(keycode, app);
}

void	handle_zscale_keys(int keycode, t_app_bonus *app)
{
	if ((keycode == KEY_Z || keycode == KEY_1) && throttle_ok_and_stamp(app, 8))
	{
		app->view.zscale *= 1.1;
		if (app->view.zscale > 100.0)
			app->view.zscale = 100.0;
		app->needs_redraw = 1;
	}
	else if ((keycode == KEY_X || keycode == KEY_2)
		&& throttle_ok_and_stamp(app, 8))
	{
		app->view.zscale /= 1.1;
		if (app->view.zscale < 0.1)
			app->view.zscale = 0.1;
		app->needs_redraw = 1;
	}
}
