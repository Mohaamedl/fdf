/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_mouse_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:22:38 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/09/07 20:22:54 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf_bonus.h"

int	hook_mouse_bonus(int button, int x, int y, void *param)
{
	t_app_bonus	*app;

	app = (t_app_bonus *)param;
	if (!app)
		return (0);
	if (button == BTN_SCROLL_UP || button == BTN_SCROLL_DOWN)
		handle_scroll_zoom(app, button, x, y);
	else
		handle_mouse_button_press(app, button, x, y);
	return (0);
}

int	hook_mouse_release_bonus(int button, int x, int y, void *param)
{
	t_app_bonus	*app;

	app = (t_app_bonus *)param;
	(void)x;
	(void)y;
	if (app->mouse_down && app->mouse_button == button)
	{
		app->mouse_down = 0;
		app->mouse_button = 0;
		app->demo_mode = 0;
		app->needs_redraw = 1;
	}
	return (0);
}

int	hook_mouse_move_bonus(int x, int y, void *param)
{
	t_app_bonus	*app;
	int			dx;
	int			dy;

	app = (t_app_bonus *)param;
	if (!app || !app->mouse_down)
		return (0);
	app->demo_mode = 0;
	if (!check_mouse_throttle(app))
		return (0);
	dx = x - app->last_x;
	dy = y - app->last_y;
	if (dx == 0 && dy == 0)
		return (0);
	app->last_x = x;
	app->last_y = y;
	if (app->mouse_button == BTN_LEFT)
		handle_left_mouse_drag(app, dx, dy);
	else if (app->mouse_button == BTN_RIGHT)
		handle_right_mouse_drag(app, dx, dy);
	else if (app->mouse_button == BTN_MIDDLE)
		handle_middle_mouse_drag(app, dx);
	app->needs_redraw = 1;
	return (0);
}

void	handle_right_mouse_drag(t_app_bonus *app, int dx, int dy)
{
	double	pan_speed;

	pan_speed = 1.0 / (app->view.scale);
	if (pan_speed < 0.2)
		pan_speed = 0.2;
	if (pan_speed > 5.0)
		pan_speed = 5.0;
	app->view.offset_x += dx * pan_speed;
	app->view.offset_y += dy * pan_speed;
}

void	handle_middle_mouse_drag(t_app_bonus *app, int dx)
{
	app->view.rot_z += dx * 0.003;
}
