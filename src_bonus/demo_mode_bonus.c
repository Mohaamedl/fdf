/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   demo_mode_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:58:21 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/23 13:58:56 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "fdf_bonus.h"

// Demo mode update for bonus app
void	demo_mode_update(t_app_bonus *app)
{
	if (!app->demo_mode)
		return;
	
	// Simple demo rotation
	app->view.rot_y += 0.01;
	app->view.rot_x += 0.005;
	
	// Ensure we don't get extreme angles
	if (app->view.rot_x > M_PI / 3.0)
		app->view.rot_x = -M_PI / 6.0;
	if (app->view.rot_y > M_PI * 2.0)
		app->view.rot_y = 0.0;
}

void	app_message(t_app *app, char *msg)
{
	(void)app;
	(void)msg;
	// Simple message display - could be enhanced with overlay text
}
