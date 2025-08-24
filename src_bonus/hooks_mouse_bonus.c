/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_mouse_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:20:00 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/23 19:47:30 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

// normalize angle to [-PI, PI]
static double	normalize_angle(double a)
{
	while (a > M_PI)
		a -= 2.0 * M_PI;
	while (a < -M_PI)
		a += 2.0 * M_PI;
	return (a);
}

// Mouse scroll zoom and button press
int				hook_mouse_bonus(int button, int x, int y, void *param)
{
	t_app_bonus	*app;
	double			zoom_factor;

	app = (t_app_bonus *)param;
	if (!app)
		return (0);

	if (button == BTN_SCROLL_UP || button == BTN_SCROLL_DOWN)
	{
		zoom_factor = (button == BTN_SCROLL_UP) ? 1.1 : 0.9;
		// Zoom around cursor
		double ox = app->view.offset_x;
		double oy = app->view.offset_y;
		app->view.scale *= zoom_factor;
		if (app->view.scale < 0.05)
			app->view.scale = 0.05;
		app->view.offset_x = x - (x - ox) * zoom_factor;
		app->view.offset_y = y - (y - oy) * zoom_factor;
		rerender_bonus_complete(app);
		return (0);
	}
	if (button == BTN_LEFT || button == BTN_RIGHT || button == BTN_MIDDLE)
	{
		app->mouse_down = 1;
		app->mouse_button = button;
		app->last_x = x;
		app->last_y = y;
	}
	return (0);
}

// Mouse release handler
int				hook_mouse_release_bonus(int button, int x, int y, void *param)
{
	t_app_bonus	*app;

	app = (t_app_bonus *)param;
	(void)x;
	(void)y;
	
	if (app->mouse_down && app->mouse_button == button)
	{
		app->mouse_down = 0;
		app->mouse_button = 0;
	}
	return (0);
}

// Mouse move handler inspired by insp.c
// Left drag = pan, Right drag = rotate X/Y, Middle drag = rotate Z
int				hook_mouse_move_bonus(int x, int y, void *param)
{
	t_app_bonus	*app;
	int			dx;
	int			dy;
	double		sens;

	app = (t_app_bonus *)param;
	if (!app)
		return (0);
	if (!app->mouse_down)
	{
		app->last_x = x;
		app->last_y = y;
		return (0);
	}

	dx = x - app->last_x;
	dy = y - app->last_y;
	app->last_x = x;
	app->last_y = y;
	sens = 0.002;

	if (app->mouse_button == BTN_LEFT)
	{
		// Rotate X/Y
		app->view.rot_x = normalize_angle(app->view.rot_x + dy * sens);
		app->view.rot_y = normalize_angle(app->view.rot_y + dx * sens);
	}
	else if (app->mouse_button == BTN_RIGHT)
	{
		// Pan
		app->view.offset_x += dx;
		app->view.offset_y += dy;
	}
	else if (app->mouse_button == BTN_MIDDLE)
	{
		// Rotate Z depending on side of screen (like insp.c)
		if (x < (WIN_W / 2) + app->view.offset_x)
			app->view.rot_z = normalize_angle(app->view.rot_z - dy * sens);
		else
			app->view.rot_z = normalize_angle(app->view.rot_z + dy * sens);
	}

	rerender_bonus_complete(app);
	return (0);
}
