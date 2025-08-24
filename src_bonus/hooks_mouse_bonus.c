/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_mouse_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:20:00 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/24 20:35:40 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

// Mouse scroll zoom and button press
int				hook_mouse_bonus(int button, int x, int y, void *param)
{
	t_app_bonus	*app;

	app = (t_app_bonus *)param;
	if (!app)
		return (0);

	if (button == BTN_SCROLL_UP || button == BTN_SCROLL_DOWN)
	{
		// Blender-like zoom-to-cursor in screen space
		app->demo_mode = 0; // interaction cancels demo
		double old_scale = app->view.scale;
		double zoom_step = 1.12; // a touch faster than 1.1 for responsiveness
		double new_scale;

		if (button == BTN_SCROLL_UP)
			new_scale = old_scale * zoom_step;
		else
			new_scale = old_scale / zoom_step;

		// Clamp sensible bounds
		if (new_scale < 0.02)
			new_scale = 0.02;
		if (new_scale > 150.0)
			new_scale = 150.0;

		// Keep the cursor-anchored point fixed on screen
		app->view.offset_x = x - (x - app->view.offset_x) * (new_scale / old_scale);
		app->view.offset_y = y - (y - app->view.offset_y) * (new_scale / old_scale);
		app->view.scale = new_scale;

		app->needs_redraw = 1;
		return (0);
	}
	if (button == BTN_LEFT || button == BTN_RIGHT || button == BTN_MIDDLE)
	{
		app->mouse_down = 1;
		app->mouse_button = button;
		app->last_x = x;
		app->last_y = y;
		// Any user interaction should exit demo mode
		app->demo_mode = 0;
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
		app->demo_mode = 0;
		
		// Mark for final render when mouse is released
		app->needs_redraw = 1;
	}
	return (0);
}

// Mouse move handler inspired by inspiration code
// LEFT = rotate X/Y angles, RIGHT = pan/translate, MIDDLE = rotate Z
int				hook_mouse_move_bonus(int x, int y, void *param)
{
	t_app_bonus		*app;
	int				dx, dy;
	struct timeval	now;
	long			time_diff_ms;

	app = (t_app_bonus *)param;
	if (!app || !app->mouse_down)
		return (0);

	// Any drag disables demo mode
	app->demo_mode = 0;

	// Adaptive FPS throttle: compute target interval once
	gettimeofday(&now, NULL);
	time_diff_ms = (now.tv_sec - app->view.last_render_time.tv_sec) * 1000
		+ (now.tv_usec - app->view.last_render_time.tv_usec) / 1000;
	{
		long target_ms;
		long map_size = (long)app->map.w * (long)app->map.h;
		if (map_size < 50000)
			target_ms = 8;   // ~120 FPS for small maps
		else if (map_size < 150000)
			target_ms = 12;  // ~80 FPS
		else if (map_size < 350000)
			target_ms = 16;  // ~60 FPS
		else
			target_ms = 28;  // ~36 FPS for huge maps
		if (time_diff_ms < target_ms)
			return (0);
	}
	// Passed throttle check: update timestamp and proceed
	app->view.last_render_time = now;

	// Calculate mouse delta
	dx = x - app->last_x;
	dy = y - app->last_y;
	if (dx == 0 && dy == 0)
		return (0);
	app->last_x = x;
	app->last_y = y;

	// Update rotation/pan immediately for responsive feel
	if (app->mouse_button == BTN_LEFT)
	{
		// Blender-like orbit: horizontal = yaw (Y), vertical = pitch (X)
		const double sens = 0.004;
		app->view.rot_y += dx * sens;
		app->view.rot_x += dy * sens;

		// Limit pitch to avoid flipping
		const double max_pitch = 1.35; // ~77 degrees
		if (app->view.rot_x > max_pitch)
			app->view.rot_x = max_pitch;
		if (app->view.rot_x < -max_pitch)
			app->view.rot_x = -max_pitch;
	}
	else if (app->mouse_button == BTN_RIGHT)
	{
		// Pan speed inversely proportional to scale, clamped
		double pan_speed = 1.0 / (app->view.scale);
		if (pan_speed < 0.2)
			pan_speed = 0.2;
		if (pan_speed > 5.0)
			pan_speed = 5.0;
		app->view.offset_x += dx * pan_speed;
		app->view.offset_y += dy * pan_speed;
	}
	else if (app->mouse_button == BTN_MIDDLE)
	{
		// Z-axis roll rotation; use horizontal movement for roll
		app->view.rot_z += dx * 0.003;
	}

	app->needs_redraw = 1;
	return (0);
}
