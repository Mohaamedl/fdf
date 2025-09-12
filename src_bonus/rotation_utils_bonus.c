/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 22:30:00 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/09/12 22:30:01 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf_bonus.h"

void	handle_x_rotation(int keycode, t_app_bonus *app)
{
	if (keycode == KEY_I && throttle_ok_and_stamp(app, 12))
	{
		if (app->view.rot_x > -0.35)
		{
			app->view.rot_x -= 0.1;
			app->needs_redraw = 1;
		}
	}
	else if (keycode == KEY_K && throttle_ok_and_stamp(app, 12))
	{
		if (app->view.rot_x < 0.35)
		{
			app->view.rot_x += 0.1;
			app->needs_redraw = 1;
		}
	}
}

void	handle_y_rotation(int keycode, t_app_bonus *app)
{
	if (keycode == KEY_J && throttle_ok_and_stamp(app, 12))
	{
		if (app->view.rot_y > -0.35)
		{
			app->view.rot_y -= 0.1;
			app->needs_redraw = 1;
		}
	}
	else if (keycode == KEY_L && throttle_ok_and_stamp(app, 12))
	{
		if (app->view.rot_y < 0.35)
		{
			app->view.rot_y += 0.1;
			app->needs_redraw = 1;
		}
	}
}
