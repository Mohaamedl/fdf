/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:49:39 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/23 13:49:51 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	recompute_view_fit(t_app *app)
{
	double	margin;
	double	span;
	double	map_w;
	double	map_h;
	double	sx;
	double	sy;

	margin = 40.0;
	span = (app->map.w + app->map.h);
	map_w = span * cos(app->view.angle);
	map_h = span * sin(app->view.angle) + 
		fabs((app->map.zmax - app->map.zmin) * app->view.zscale);
	
	if (map_w <= 1)
		map_w = 1;
	if (map_h <= 1)
		map_h = 1;
	
	sx = (WIN_W - 2 * margin) / map_w;
	sy = (WIN_H - 2 * margin) / map_h;
	
	if (sx < sy)
		app->view.scale = sx;
	else
		app->view.scale = sy;
	
	app->view.offset_x = WIN_W / 2.0;
	app->view.offset_y = WIN_H / 2.0;
}
