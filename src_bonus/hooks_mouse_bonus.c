/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_mouse_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:20:00 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/23 14:20:00 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

// Mouse scroll for zoom
int	hook_mouse_bonus(int button, int x, int y, void *param)
{
	t_app_bonus	*app;
	double		zoom_factor;

	app = (t_app_bonus *)param;
	
	// Handle scroll events for zoom
	if (button == 4) // Scroll up
		zoom_factor = 1.1;
	else if (button == 5) // Scroll down
		zoom_factor = 0.9;
	else if (button == 1 || button == 3) // Left or right click
	{
		// Start drag operation
		app->mouse_down = 1;
		app->mouse_button = button;
		app->last_x = x;
		app->last_y = y;
		return (0);
	}
	else
		return (0);
	
	// Apply zoom centered on mouse position
	double	ox = app->view.offset_x;
	double	oy = app->view.offset_y;
	app->view.scale *= zoom_factor;
	app->view.offset_x = x - (x - ox) * zoom_factor;
	app->view.offset_y = y - (y - oy) * zoom_factor;
	
	rerender_bonus_complete(app);
	return (0);
}

// Mouse release handler
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
	}
	return (0);
}

// Mouse move handler for drag operations
int	hook_mouse_move_bonus(int x, int y, void *param)
{
	t_app_bonus	*app;
	int			dx, dy;
	double		sensitivity;

	app = (t_app_bonus *)param;
	
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
	
	if (app->mouse_button == 1) // Left click = rotation
	{
		sensitivity = 0.01;
		app->view.rot_y += dx * sensitivity;
		app->view.rot_x += dy * sensitivity;
		
		// Limit pitch to prevent gimbal lock
		if (app->view.rot_x > M_PI / 2.0 * 0.9)
			app->view.rot_x = M_PI / 2.0 * 0.9;
		if (app->view.rot_x < -M_PI / 2.0 * 0.9)
			app->view.rot_x = -M_PI / 2.0 * 0.9;
	}
	else if (app->mouse_button == 3) // Right click = translation
	{
		app->view.offset_x += dx;
		app->view.offset_y += dy;
	}
	
	rerender_bonus_complete(app);
	return (0);
}
