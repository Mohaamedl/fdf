/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_mouse_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:20:00 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/24 12:58:18 by mohamed          ###   ########.fr       */
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

	app = (t_app_bonus *)param;
	if (!app)
		return (0);

	if (button == BTN_SCROLL_UP || button == BTN_SCROLL_DOWN)
	{
		// Fixed zoom increment like inspiration (more predictable)
		if (button == BTN_SCROLL_UP)
			app->view.scale += 2.0;
		else
			app->view.scale -= 2.0;
		if (app->view.scale < 1.0)
			app->view.scale = 1.0;
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
		
		// Final render when mouse is released to ensure clean image
		rerender_bonus_complete(app);
	}
	return (0);
}

// Mouse move handler inspired by inspiration code
// LEFT = rotate X/Y angles, RIGHT = pan/translate, MIDDLE = rotate Z
int				hook_mouse_move_bonus(int x, int y, void *param)
{
	t_app_bonus	*app;
	int			dx;
	int			dy;
	double		sens;
	static int	move_count = 0;

	app = (t_app_bonus *)param;
	if (!app || !app->mouse_down)
		return (0);

	dx = x - app->last_x;
	dy = y - app->last_y;
	app->last_x = x;
	app->last_y = y;
	sens = 0.005;  // Good sensitivity for smooth control

	// LEFT MOUSE = ORBIT/ROTATE (Blender-style turntable mode)
	if (app->mouse_button == BTN_LEFT)
	{
		// Horizontal mouse movement = yaw around Y axis (left/right orbit)
		app->view.rot_y += dx * sens;
		
		// Vertical mouse movement = pitch around X axis (up/down orbit)
		app->view.rot_x += dy * sens;
		
		// Normalize angles to prevent overflow
		app->view.rot_x = normalize_angle(app->view.rot_x);
		app->view.rot_y = normalize_angle(app->view.rot_y);
		
		// Clamp X rotation to prevent flipping upside down (like Blender)
		if (app->view.rot_x > M_PI / 2.0)
			app->view.rot_x = M_PI / 2.0;
		if (app->view.rot_x < -M_PI / 2.0)
			app->view.rot_x = -M_PI / 2.0;
	}
	// RIGHT MOUSE = PAN/TRANSLATE (move the view around) 
	else if (app->mouse_button == BTN_RIGHT)
	{
		app->view.offset_x += dx;
		app->view.offset_y += dy;
	}
	// MIDDLE MOUSE = Z-ROTATION (roll around Z-axis)
	else if (app->mouse_button == BTN_MIDDLE)
	{
		if (x < (WIN_W / 2) + app->view.offset_x)
			app->view.rot_z -= dy * sens;
		else
			app->view.rot_z += dy * sens;
		app->view.rot_z = normalize_angle(app->view.rot_z);
	}

	// Throttle rendering: only render every 3rd movement for smooth performance
	move_count++;
	if (move_count >= 3)
	{
		move_count = 0;
		rerender_bonus_complete(app);
	}

	return (0);
}
