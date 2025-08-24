/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_keys_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:58:22 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/24 11:16:40 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

// Main key handler for bonus features
int	hook_key_bonus_complete(int keycode, void *param)
{
	t_app_bonus	*app;

	app = (t_app_bonus *)param;
	if (!app)
		return (0);
	
	// Exit
	if (keycode == KEY_ESC)
		hook_destroy_bonus(app);
	
	// PROJECTION TOGGLE (P key) - Required bonus
	else if (keycode == KEY_P)
	{
		app->view.proj = (app->view.proj + 1) % 3;
		if (app->view.proj == 0)
			write(1, "Isometric projection\n", 21);
		else if (app->view.proj == 1)
			write(1, "Parallel projection\n", 20);
		else
			write(1, "Perspective projection\n", 23);
		rerender_bonus_immediate(app);  // Immediate for single events
	}
	
	// TRANSLATION (Arrow keys) - Required bonus
	else if (keycode == KEY_LEFT)
	{
		app->view.offset_x -= 10;
		rerender_bonus_complete(app);
	}
	else if (keycode == KEY_RIGHT)
	{
		app->view.offset_x += 10;
		rerender_bonus_complete(app);
	}
	else if (keycode == KEY_UP)
	{
		app->view.offset_y -= 10;
		rerender_bonus_complete(app);
	}
	else if (keycode == KEY_DOWN)
	{
		app->view.offset_y += 10;
		rerender_bonus_complete(app);
	}
	
	// ZOOM (+ and -) - Required bonus
	else if (keycode == KEY_PLUS || keycode == KEY_KP_ADD)
	{
		app->view.scale *= 1.1;
		rerender_bonus_complete(app);
	}
	else if (keycode == KEY_MINUS || keycode == KEY_KP_SUB)
	{
		app->view.scale /= 1.1;
		if (app->view.scale < 0.1)
			app->view.scale = 0.1;
		rerender_bonus_complete(app);
	}
	
	// TRANSLATION (WASD same as arrows) - Required bonus
	else if (keycode == KEY_W)
	{
		app->view.offset_y -= 10;
		rerender_bonus_complete(app);
	}
	else if (keycode == KEY_S)
	{
		app->view.offset_y += 10;
		rerender_bonus_complete(app);
	}
	else if (keycode == KEY_A)
	{
		app->view.offset_x -= 10;
		rerender_bonus_complete(app);
	}
	else if (keycode == KEY_D)
	{
		app->view.offset_x += 10;
		rerender_bonus_complete(app);
	}
	
	// Z-axis rotation (Q/E) and more rotation options
	else if (keycode == KEY_Q)
	{
		app->view.rot_z -= 0.1;
		rerender_bonus_complete(app);  // Throttled for rotation
	}
	else if (keycode == KEY_E)
	{
		app->view.rot_z += 0.1;
		rerender_bonus_complete(app);  // Throttled for rotation
	}
	
	// Additional rotation controls (I/K for X, J/L for Y)
	else if (keycode == KEY_I)
	{
		app->view.rot_x -= 0.1;
		rerender_bonus_complete(app);  // Throttled for rotation
	}
	else if (keycode == KEY_K)
	{
		app->view.rot_x += 0.1;
		rerender_bonus_complete(app);  // Throttled for rotation
	}
	else if (keycode == KEY_J)
	{
		app->view.rot_y -= 0.1;
		rerender_bonus_complete(app);  // Throttled for rotation
	}
	else if (keycode == KEY_L)
	{
		app->view.rot_y += 0.1;
		rerender_bonus_complete(app);  // Throttled for rotation
	}
	
	// Height scaling (Z/X and 1/2)
	else if (keycode == KEY_Z || keycode == KEY_1)
	{
		app->view.zscale *= 1.1;
		rerender_bonus_complete(app);
	}
	else if (keycode == KEY_X || keycode == KEY_2)
	{
		app->view.zscale /= 1.1;
		if (app->view.zscale < 0.1)
			app->view.zscale = 0.1;
		rerender_bonus_complete(app);
	}
	
	// Reset view (R key)
	else if (keycode == KEY_R)
	{
		// Use adaptive scaling like initialization
		double	scale_x, scale_y, auto_scale;
		
		scale_x = (WIN_W * 0.6) / app->map.w;
		scale_y = (WIN_H * 0.6) / app->map.h;
		auto_scale = (scale_x < scale_y) ? scale_x : scale_y;
		
		// Ensure minimum and maximum scale bounds
		if (auto_scale < 0.5)
			auto_scale = 0.5;
		else if (auto_scale > 50.0)
			auto_scale = 50.0;
		
		app->view.scale = auto_scale;  // Adaptive scale instead of fixed 20.0
		app->view.offset_x = WIN_W / 2;
		app->view.offset_y = WIN_H / 2;
		app->view.rot_x = 0.0;     // Start with no tilt
		app->view.rot_y = 0.0;     // Start with no rotation
		app->view.rot_z = 0.0;     // Start with no roll
		app->view.zscale = 1.0;
		app->view.proj = PROJ_ISO;
		rerender_bonus_immediate(app);  // Immediate for reset
	}
	
	// Help toggle (H key)
	else if (keycode == KEY_H)
	{
		app->show_help = !app->show_help;
		rerender_bonus_immediate(app);  // Immediate for toggle
	}
	
	// Demo mode toggle (SPACE) - Extra bonus
	else if (keycode == KEY_SPACE)
	{
		app->demo_mode = !app->demo_mode;
		if (app->demo_mode)
			write(1, "Demo mode ON\n", 13);
		else
			write(1, "Demo mode OFF\n", 14);
		rerender_bonus_immediate(app);  // Immediate for toggle
	}
	
	// Color mode cycling (C key)
	else if (keycode == KEY_C)
	{
		app->color_mode = (app->color_mode + 1) % 5;
		rerender_bonus_immediate(app);
	}
	
	return (0);
}

// Key release handler
int	hook_key_release_bonus(int keycode, void *param)
{
	(void)keycode;
	(void)param;
	return (0);
}

// Loop hook for demo mode 
int	loop_hook_bonus(void *param)
{
	t_app_bonus	*app;

	app = (t_app_bonus *)param;
	if (!app)
		return (0);
	
	// Handle demo mode
	if (app->demo_mode)
		demo_mode_update(app);
	
	return (0);
}
