/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_keys_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:58:22 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/23 13:58:56 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_keys_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:15:00 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/23 14:15:00 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

// Complete key handler with ALL required bonuses
int	hook_key_bonus_complete(int keycode, void *param)
{
	t_app_bonus	*app;

	app = (t_app_bonus *)param;
	
	// Handle immediate actions (non-repeatable)
	if (keycode == KEY_ESC)
		hook_destroy_bonus(app);
	else if (keycode == 112) // P - Projection toggle
	{
		app->view.proj = (app->view.proj + 1) % 3;
		if (app->view.proj == 0)
			write(1, "Isometric projection\n", 21);
		else if (app->view.proj == 1)
			write(1, "Parallel projection\n", 20);
		else
			write(1, "Perspective projection\n", 23);
		rerender_bonus_complete(app);
	}
	else if (keycode == 104) // H - Toggle help
	{
		app->show_help = !app->show_help;
		rerender_bonus_complete(app);
	}
	else if (keycode == 65289) // TAB - Demo mode
	{
		app->demo_mode = !app->demo_mode;
		rerender_bonus_complete(app);
	}
	else
	{
		// Mark key as pressed for continuous actions
		if (keycode >= 0 && keycode < 512)
			app->keys_pressed[keycode] = 1;
	}
	
	return (0);
}

// Key release handler to stop continuous actions
int	hook_key_release_bonus(int keycode, void *param)
{
	t_app_bonus	*app;

	app = (t_app_bonus *)param;
	if (keycode >= 0 && keycode < 512)
		app->keys_pressed[keycode] = 0;
	return (0);
}

// Process all currently pressed keys for smooth continuous movement
void	process_continuous_keys(t_app_bonus *app)
{
	int	needs_rerender = 0;
	
	if (!app)
		return;
	
	// Use only safe, known keycodes
	// Basic movement (WASD)
	if (app->keys_pressed[119]) // W
	{
		app->view.offset_y -= 5;
		needs_rerender = 1;
	}
	if (app->keys_pressed[115]) // S
	{
		app->view.offset_y += 5;
		needs_rerender = 1;
	}
	if (app->keys_pressed[97]) // A
	{
		app->view.offset_x -= 5;
		needs_rerender = 1;
	}
	if (app->keys_pressed[100]) // D
	{
		app->view.offset_x += 5;
		needs_rerender = 1;
	}
	
	// Basic rotation (QE, ZX, RT)
	if (app->keys_pressed[113]) // Q
	{
		app->view.rot_z -= 0.05;
		needs_rerender = 1;
	}
	if (app->keys_pressed[101]) // E
	{
		app->view.rot_z += 0.05;
		needs_rerender = 1;
	}
	if (app->keys_pressed[122]) // Z
	{
		app->view.rot_x -= 0.05;
		needs_rerender = 1;
	}
	if (app->keys_pressed[120]) // X
	{
		app->view.rot_x += 0.05;
		needs_rerender = 1;
	}
	if (app->keys_pressed[114]) // R
	{
		app->view.rot_y -= 0.05;
		needs_rerender = 1;
	}
	if (app->keys_pressed[116]) // T
	{
		app->view.rot_y += 0.05;
		needs_rerender = 1;
	}
	
	// Zoom (+/-)
	if (app->keys_pressed[61]) // = (plus)
	{
		app->view.scale *= 1.05;
		needs_rerender = 1;
	}
	if (app->keys_pressed[45]) // -
	{
		app->view.scale /= 1.05;
		needs_rerender = 1;
	}
	
	// Height scaling (1/2)
	if (app->keys_pressed[49]) // 1
	{
		app->view.zscale *= 1.02;
		needs_rerender = 1;
	}
	if (app->keys_pressed[50]) // 2
	{
		app->view.zscale *= 0.98;
		needs_rerender = 1;
	}
	
	if (needs_rerender)
		rerender_bonus_complete(app);
}

// Loop hook for continuous key processing
int	loop_hook_bonus(void *param)
{
	t_app_bonus	*app;

	app = (t_app_bonus *)param;
	if (!app)
		return (0);
	
	// Handle demo mode
	if (app->demo_mode)
		demo_mode_update(app);
	
	// Handle key repeat
	if (app->key_repeat_enabled)
		process_continuous_keys(app);
	return (0);
}
