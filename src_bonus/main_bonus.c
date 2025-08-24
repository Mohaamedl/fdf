/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:58:32 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/24 20:35:40 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include <sys/time.h>

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
	// Always render immediately - NO frame skipping for responsive controls
	// Modern computers can handle julia.fdf at full quality easily
	render_wireframe_bonus_complete(app);
	mlx_put_image_to_window(app->mlx.mlx, app->mlx.win, app->mlx.img.ptr, 0, 0);
	draw_help_overlay_complete(app);
	draw_status_display(app);
}

// Force immediate rerender (for single events like projection change)
void	rerender_bonus_immediate(t_app_bonus *app)
{
	render_wireframe_bonus_complete(app);
	mlx_put_image_to_window(app->mlx.mlx, app->mlx.win, app->mlx.img.ptr, 0, 0);
	draw_help_overlay_complete(app);
	draw_status_display(app);
}

// Initialize view with proper defaults and auto-scaling
static void	init_view_bonus(t_app_bonus *app)
{
	double	scale_x, scale_y, auto_scale;

	app->view.angle = M_PI / 6.0;
	app->view.zscale = 1.0;
	app->view.proj = PROJ_ISO;  // Start with isometric
	app->view.rot_x = 0.0;      // No initial tilt
	app->view.rot_y = 0.0;      // No initial rotation
	app->view.rot_z = 0.0;      // No initial roll
	
	// Initialize timing for smooth rendering
	gettimeofday(&app->view.last_render_time, NULL);
	
	// Auto-scale based on map size to fit the screen nicely
	scale_x = (WIN_W * 0.6) / app->map.w;
	scale_y = (WIN_H * 0.6) / app->map.h;
	auto_scale = (scale_x < scale_y) ? scale_x : scale_y;
	
	// Ensure minimum and maximum scale bounds
	if (auto_scale < 0.5)
		auto_scale = 0.5;
	else if (auto_scale > 50.0)
		auto_scale = 50.0;
	
	app->view.scale = auto_scale;
	app->view.offset_x = WIN_W / 2;
	app->view.offset_y = WIN_H / 2;
	app->show_help = 0;  // Start with help hidden so wireframe is visible
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
	
	// Initialize the MLX and other non-map parts
	ft_memset(&app.mlx, 0, sizeof(t_mlx));
	app.show_help = 0;
	app.demo_mode = 0;
	app.fps = 0;
	app.needs_redraw = 1;
	app.color_mode = COLOR_DEFAULT;  // Start with gradient colors
	app.mouse_down = 0;
	app.mouse_button = 0;
	app.last_x = 0;
	app.last_y = 0;
	
	if (!mlx_init_safe(&app.mlx))
	{
		free_map(&app.map);
		write(2, "Error: Failed to initialize MLX\n", 33);
		return (1);
	}
	
	init_view_bonus(&app);
	// Ensure demo is off at startup regardless of prior state
	app.demo_mode = 0;
	

	
	// Set up hooks
	mlx_hook(app.mlx.win, 17, 0, hook_destroy_bonus, &app);
	// Register both generic key hook and specific X11 KeyPress for reliability
	mlx_key_hook(app.mlx.win, hook_key_bonus_complete, &app);
	mlx_hook(app.mlx.win, 2, 1L<<0, hook_key_bonus_complete, &app);    // Key press
	mlx_hook(app.mlx.win, 3, 1L<<1, hook_key_release_bonus, &app);     // Key release
	mlx_loop_hook(app.mlx.mlx, loop_hook_bonus, &app);                 // Continuous loop
	
	// Add mouse drag support - button press and release
	mlx_hook(app.mlx.win, 4, 1L<<2, hook_mouse_bonus, &app);
	mlx_hook(app.mlx.win, 5, 1L<<3, hook_mouse_release_bonus, &app);
	mlx_hook(app.mlx.win, 6, 1L<<6, hook_mouse_move_bonus, &app);
	
	// Initial render
	app.needs_redraw = 1;
	
	// Start main loop
	mlx_loop(app.mlx.mlx);
	return (0);
}
