/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   demo_mode_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:58:21 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/24 20:35:40 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static int	demo_frame_count = 0;

// Enhanced demo mode update for bonus app
void	demo_mode_update(t_app_bonus *app)
{
	static double	time = 0.0;
	static double	base_scale = 0.0;
	
	if (!app->demo_mode)
		return;
	
	// Initialize base scale on first run using adaptive scaling
	if (base_scale == 0.0)
	{
		double	scale_x, scale_y;
		
		scale_x = (WIN_W * 0.6) / app->map.w;
		scale_y = (WIN_H * 0.6) / app->map.h;
		base_scale = (scale_x < scale_y) ? scale_x : scale_y;
		
		// Ensure minimum and maximum scale bounds
		if (base_scale < 0.5)
			base_scale = 0.5;
		else if (base_scale > 50.0)
			base_scale = 50.0;
	}
	
	time += 0.02;
	demo_frame_count++;
	
	// Smooth orbital rotation
	app->view.rot_y = sin(time * 0.5) * 0.8;
	app->view.rot_x = 0.3 + cos(time * 0.3) * 0.4;
	app->view.rot_z = sin(time * 0.2) * 0.2;
	
	// Gentle scale pulsing based on adaptive base scale
	app->view.scale = base_scale + sin(time) * (base_scale * 0.15);
	
	// Height scale variation
	app->view.zscale = 1.0 + sin(time * 0.7) * 0.3;
	
	// Cycle through projections every 300 frames
	if (demo_frame_count % 300 == 0)
	{
		app->view.proj = (app->view.proj + 1) % 3;
	}
	
	// Request redraw; loop hook will render at most ~60 FPS
	if (demo_frame_count % 2 == 0)
		app->needs_redraw = 1;
}

void	app_message(t_app *app, char *msg)
{
	(void)app;
	(void)msg;
}
