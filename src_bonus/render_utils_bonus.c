/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 20:00:00 by mohamed           #+#    #+#             */
/*   Updated: 2025/09/07 20:00:00 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static t_point3d	rotate_point_x(t_point3d p, double cosx, double sinx)
{
	double	temp_y;
	double	temp_z;

	temp_y = p.y * cosx - p.z * sinx;
	temp_z = p.y * sinx + p.z * cosx;
	p.y = temp_y;
	p.z = temp_z;
	return (p);
}

static t_point3d	rotate_point_y(t_point3d p, double cosy, double siny)
{
	t_point3d	result;

	result.x = p.x * cosy + p.z * siny;
	result.z = -p.x * siny + p.z * cosy;
	result.y = p.y;
	return (result);
}

static t_point3d	rotate_point_z(t_point3d p, double cosz, double sinz)
{
	t_point3d	result;
	double		temp_y;

	temp_y = p.y;
	result.y = temp_y * cosz - p.x * sinz;
	result.x = temp_y * sinz + p.x * cosz;
	result.z = p.z;
	return (result);
}

t_point3d	apply_rotations(t_point3d p, double cx, double cy, t_view *view)
{
	t_point3d	result;

	p.x -= cx;
	p.y -= cy;
	result = rotate_point_x(p, cos(view->rot_x), sin(view->rot_x));
	result = rotate_point_y(result, cos(view->rot_y), sin(view->rot_y));
	result = rotate_point_z(result, cos(view->rot_z), sin(view->rot_z));
	result.x += cx;
	result.y += cy;
	return (result);
}

void	project_perspective(double *proj_x, double *proj_y, t_point3d rotated)
{
	double	d;
	double	denom;

	d = 800.0;
	denom = rotated.z + d;
	if (denom < 50.0)
		denom = 50.0;
	*proj_x = rotated.x * (d / denom);
	*proj_y = rotated.y * (d / denom);
}
