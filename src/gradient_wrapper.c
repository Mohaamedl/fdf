/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient_wrapper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:00:00 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/09/12 15:00:00 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	setup_line_data(t_line_gradient *line, t_img *img, t_point2d a,
	t_point2d b)
{
	line->img = img;
	line->start = a;
	line->end = b;
}

void	draw_line_with_colors(t_line_gradient *line, int c1, int c2)
{
	line->color1 = c1;
	line->color2 = c2;
	draw_gradient_line(line);
}
