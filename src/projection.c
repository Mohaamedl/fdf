/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:50:48 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/24 14:25:12 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	project_point_safe(const t_view *view, t_proj_params *params)
{
	double	x;
	double	y;
	double	z;

	if (!view || !params || !params->sx || !params->sy)
		return ;
	x = (double)params->x;
	y = (double)params->y;
	z = params->z * view->zscale;
	*params->sx = (x - y) * cos(view->angle) * view->scale + view->offset_x;
	*params->sy = (x + y) * sin(view->angle) * view->scale - z * view->scale
		+ view->offset_y;
}
