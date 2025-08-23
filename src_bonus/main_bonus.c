/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:58:32 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/23 14:35:00 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	app_destroy_bonus(t_app_bonus *app, int code)
{
	if (app->mlx.img.ptr)
		mlx_destroy_image(app->mlx.mlx, app->mlx.img.ptr);
	if (app->mlx.win)
		mlx_destroy_window(app->mlx.mlx, app->mlx.win);
	if (app->mlx.mlx)
	{
		mlx_destroy_display(app->mlx.mlx);
		free(app->mlx.mlx);
	}
	free_map(&app->map);
	exit(code);
}

int	hook_destroy_bonus(void *param)
{
	t_app_bonus	*app;

	app = (t_app_bonus *)param;
	app_destroy_bonus(app, 0);
	return (0);
}

void	rerender_bonus_complete(t_app_bonus *app)
{
	render_wireframe_bonus_complete(app);
	draw_help_overlay_complete(app);
	draw_status_display(app);
	mlx_put_image_to_window(app->mlx.mlx, app->mlx.win, app->mlx.img.ptr, 0, 0);
}

// Initialize view with proper defaults
static void	init_view_bonus(t_app_bonus *app)
{
	app->view.angle = M_PI / 6.0;
	app->view.zscale = 1.0;
	app->view.proj = PROJ_ISO;  // Start with isometric
	app->view.rot_x = -M_PI / 6.0;  // Initial rotation
	app->view.rot_y = M_PI / 4.0;
	app->view.rot_z = 0.0;
	recompute_view_fit((t_app *)app);  // Calculate fit
	app->show_help = 1;  // Show help by default
	app->demo_mode = 0;
}

int	main(int argc, char **argv)
{
	t_app_bonus	app;

	if (argc != 2)
	{
		write(2, "Usage: ./fdf_bonus map_file\n", 29);
		return (1);
	}
	
	if (!parse_map(argv[1], &app.map))
	{
		write(2, "Error: Failed to parse map\n", 28);
		return (1);
	}
	
	if (!mlx_init_safe(&app.mlx))
	{
		free_map(&app.map);
		write(2, "Error: Failed to initialize MLX\n", 33);
		return (1);
	}
	
	init_view_bonus(&app);
	
	// Initialize mouse state
	app.mouse_down = 0;
	app.mouse_button = 0;
	app.last_x = 0;
	app.last_y = 0;
	
	// Initialize key repeat system
	int i = 0;
	while (i < 512)
	{
		app.keys_pressed[i] = 0;
		i++;
	}
	app.key_repeat_enabled = 1;
	
	// Set up hooks
	mlx_hook(app.mlx.win, 17, 0, hook_destroy_bonus, &app);
	mlx_hook(app.mlx.win, 2, 1L<<0, hook_key_bonus_complete, &app);    // Key press
	mlx_hook(app.mlx.win, 3, 1L<<1, hook_key_release_bonus, &app);     // Key release
	mlx_loop_hook(app.mlx.mlx, loop_hook_bonus, &app);                 // Continuous loop
	
	// Add mouse drag support - button press and release
	mlx_hook(app.mlx.win, 4, 1L<<2, hook_mouse_bonus, &app);
	mlx_hook(app.mlx.win, 5, 1L<<3, hook_mouse_release_bonus, &app);
	mlx_hook(app.mlx.win, 6, 1L<<6, hook_mouse_move_bonus, &app);
	
	// Initial render
	rerender_bonus_complete(&app);
	
	// Start main loop
	mlx_loop(app.mlx.mlx);
	return (0);
}
