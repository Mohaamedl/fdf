/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:53:18 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/24 10:32:31 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	hook_key(int keycode, void *param)
{
	t_app	*app;

	app = (t_app *)param;
	if (keycode == KEY_ESC)
		app_destroy(app, 0);
	return (0);
}

int	hook_destroy(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	app_destroy(app, 0);
	return (0);
}
