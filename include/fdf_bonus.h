/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:53:28 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/09/08 18:53:32 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include "fdf.h"

typedef struct s_point3d
{
  double		x;
  double		y;
  double		z;
}	t_point3d;

/* Keycodes */
# define KEY_LEFT		65361
# define KEY_UP			65362
# define KEY_RIGHT		65363
# define KEY_DOWN		65364
# define KEY_Q			113
# define KEY_E			101
# define KEY_Z			122
# define KEY_X			120
# define KEY_R			114
# define KEY_P			112
# define KEY_F			102
# define KEY_PLUS		61
# define KEY_MINUS		45
# define KEY_KP_ADD		65451
# define KEY_KP_SUB		65453
# define KEY_W			119
# define KEY_A			97
# define KEY_S			115
# define KEY_D			100
# define KEY_C			99
# define KEY_V			118
# define KEY_B			98
# define KEY_N			110
# define KEY_M			109
# define KEY_1			49
# define KEY_2			50
# define KEY_3			51
# define KEY_4			52
# define KEY_5			53
# define KEY_0			48
# define KEY_SPACE		32
# define KEY_I			105
# define KEY_K			107
# define KEY_J			106
# define KEY_L			108
# define KEY_H			104

/* Mouse buttons (Linux) */
# define BTN_LEFT		1
# define BTN_MIDDLE		2
# define BTN_RIGHT		3
# define BTN_SCROLL_UP	4
# define BTN_SCROLL_DOWN	5

/* Color modes */
# define COLOR_DEFAULT	0
# define COLOR_RED		1
# define COLOR_BLUE		2
# define COLOR_GREEN		3
# define COLOR_RAINBOW	4
# define COLOR_FIRE		5
# define COLOR_ICE		6
# define COLOR_GRADIENT	7
# define COLOR_MONOCHROME	8

typedef struct s_app_bonus
{
  t_mlx		mlx;
  t_map		map;
  t_view		view;
  int			fps;
  int			demo_mode;
  double		demo_rotation;
  double		demo_scale_factor;
  int			demo_direction;
  double		demo_translation_x;
  double		demo_translation_y;
  int			show_overlay;
  int			wireframe_mode;
  int			color_mode;
  int			mouse_down;
  int			mouse_button;
  int			last_x;
  int			last_y;
  int			show_help;
  int			needs_redraw;
}	t_app_bonus;

typedef struct s_point_setup
{
	t_app_bonus	*app;
	int			x;
	int			y;
	int			is_horizontal;
}	t_point_setup;

int			hook_key_bonus_complete(int key, void *param);
int			hook_key_release_bonus(int key, void *param);
int			loop_hook_bonus(void *param);
int			hook_mouse_bonus(int button, int x, int y, void *param);
int			hook_mouse_release_bonus(int button, int x, int y, void *param);
int			hook_mouse_move_bonus(int x, int y, void *param);
int			hook_destroy_bonus(void *param);
void		rerender_bonus_immediate(t_app_bonus *app);
void		rerender_bonus_complete(t_app_bonus *app);
void		demo_mode_update(t_app_bonus *app);
void		draw_help_overlay_complete(t_app_bonus *app);
void		draw_status_display(t_app_bonus *app);
void		draw_text_line(t_app *app, char *text, int y, int color);
char		*get_projection_name(int proj);
void		draw_basic_controls(t_app *app, int *y, int color);
void		draw_movement_controls(t_app *app, int *y, int color);
t_point2d	project_bonus_complete(t_point3d p3d, t_view *view, t_map *map);
int			pick_color_mode(const t_point *p, const t_map *map, int mode);
void		render_wireframe_bonus_complete(t_app_bonus *app);
void		init_app_vars(t_app_bonus *app);
void		setup_hooks(t_app_bonus *app);
void		init_view_bonus(t_app_bonus *app);
t_point3d	apply_rotations(t_point3d p, double cx, double cy, t_view *view);
void		project_perspective(double *proj_x, double *proj_y, t_point3d rotated);
int			should_cull_line(t_point2d pt1, t_point2d pt2);
void		setup_horizontal_points(t_app_bonus *app, int x, int y,
			t_point2d *pts);
void		setup_vertical_points(t_app_bonus *app, int x, int y,
			t_point2d *pts);
void		handle_movement_keys(int keycode, t_app_bonus *app);
void		handle_zoom_keys(int keycode, t_app_bonus *app);
void		handle_rotation_keys(int keycode, t_app_bonus *app);
void		handle_xyz_rotation_keys(int keycode, t_app_bonus *app);
void		handle_zscale_keys(int keycode, t_app_bonus *app);
void		reset_view(t_app_bonus *app);
int			throttle_ok_and_stamp(t_app_bonus *app, long min_ms);
int			handle_other_keys(int keycode, t_app_bonus *app);
void		handle_redraw(t_app_bonus *app, int *frame_count,
			struct timeval *fps_last);
void		handle_scroll_zoom(t_app_bonus *app, int button, int x, int y);
void		handle_mouse_button_press(t_app_bonus *app, int button, int x,
			int y);
long		get_target_ms(t_app_bonus *app);
int			check_mouse_throttle(t_app_bonus *app);
void		handle_left_mouse_drag(t_app_bonus *app, int dx, int dy);
void		handle_right_mouse_drag(t_app_bonus *app, int dx, int dy);
void		handle_middle_mouse_drag(t_app_bonus *app, int dx);

#endif
