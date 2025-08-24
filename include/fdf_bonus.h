/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 00:00:00 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/24 15:46:08 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
#define FDF_BONUS_H

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include "mlx.h"
#include "libft.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define WIN_W 1280
#define WIN_H 720

/* Linux keycodes */
#define KEY_ESC 65307
#define KEY_LEFT 65361
#define KEY_UP 65362
#define KEY_RIGHT 65363
#define KEY_DOWN 65364
#define KEY_Q 113
#define KEY_E 101
#define KEY_Z 122
#define KEY_X 120
#define KEY_R 114
#define KEY_P 112
#define KEY_F 102
#define KEY_PLUS 61
#define KEY_MINUS 45
#define KEY_KP_ADD 65451
#define KEY_KP_SUB 65453
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_H 104
#define KEY_I 105
#define KEY_J 106
#define KEY_K 107
#define KEY_L 108
#define KEY_SPACE 32
#define KEY_1 49
#define KEY_2 50
#define KEY_3 51
#define KEY_L 108
#define KEY_F1 65470
#define KEY_F2 65471
#define KEY_F3 65472
#define KEY_F4 65473
#define KEY_N 110
#define KEY_M 109
#define KEY_B 98
#define KEY_T 116
#define KEY_Y 121
#define KEY_U 117
#define KEY_I 105
#define KEY_O 111
#define KEY_C 99

/* Animation keys */
#define KEY_SPACE 32
#define KEY_TAB 65289

/* Mouse buttons (Linux) */
#define BTN_LEFT 1
#define BTN_MIDDLE 2
#define BTN_RIGHT 3
#define BTN_SCROLL_UP 4
#define BTN_SCROLL_DOWN 5

/* Color modes */
#define COLOR_GRADIENT 0
#define COLOR_RAINBOW 1
#define COLOR_MONOCHROME 2
#define COLOR_FIRE 3
#define COLOR_ICE 4
#define COLOR_MODES_COUNT 5

/* MLX event numbers */
#define EVENT_DESTROY 17

/* X11 event masks (for mlx_hook) */
#define MASK_KEY_PRESS        1L
#define MASK_KEY_RELEASE      2L
#define MASK_BUTTON_PRESS     4L
#define MASK_BUTTON_RELEASE   8L
#define MASK_POINTER_MOTION   64L

/* Basic data structures */

typedef struct s_point3d
{
	double	x;
	double	y;
	double	z;
}			t_point3d;

typedef struct s_point2d
{
	int		x;
	int		y;
}			t_point2d;

typedef struct s_proj_params
{
	int		x;
	int		y;
	double	z;
	double	*sx;
	double	*sy;
}			t_proj_params;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		w;
	int		h;
}			t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
}			t_mlx;

typedef struct s_point
{
	double	z;
	int		color;
}			t_point;

typedef struct s_map
{
	t_point	**pts;
	int		w;
	int		h;
	int		zmin;
	int		zmax;
}			t_map;

typedef enum e_proj
{
	PROJ_ISO = 0,
	PROJ_PAR = 1,
	PROJ_PER = 2
}			t_proj;

typedef struct s_view
{
	double	scale;
	double	offset_x;
	double	offset_y;
	double	angle;
	double	zscale;
	int		proj;
	double	rot_x;
	double	rot_y;
	double	rot_z;
	double	cx;
	double	cy;
	double	persp_d;
}			t_view;

typedef struct s_app
{
	t_mlx	mlx;
	t_map	map;
	t_view	view;
	int		show_help;
	int		demo_mode;
	int		mouse_down;
	int		mouse_button;
	int		last_x;
	int		last_y;
}			t_app;

/* Bonus app structure for simplified bonus features */
typedef struct s_app_bonus
{
	t_mlx	mlx;
	t_map	map;
	t_view	view;
	int		show_help;
	int		demo_mode;
	int		color_mode;
	int		mouse_down;
	int		mouse_button;
	int		last_x;
	int		last_y;
	int		keys_pressed[512];
	int		key_repeat_enabled;
	int		frame_skip_counter;
	int		needs_rerender;
}			t_app_bonus;

/* main / lifecycle */
int		app_init(t_app *app, const char *path);
void	app_destroy(t_app *app, int code);
int		mlx_init_safe(t_mlx *m);

/* view operations */
void	rerender(t_app *app);
void	recompute_view_fit(t_app *app);
void	view_apply_limits(t_app *app);

/* hooks */
int		hook_key(int keycode, void *param);
int		hook_destroy(void *param);
int		hook_mouse_button(int button, int x, int y, void *param);
int		hook_mouse_release(int button, int x, int y, void *param);
int		hook_mouse_move(int x, int y, void *param);
int		in_button_bar(int x, int y, int *index);

/* parsing */
int		parse_map(const char *path, t_map *map);
void	free_map(t_map *map);

/* render */
void	render_all(t_app *app);
void	render_fast(t_app *app);
void	render_wireframe(t_app *app);
void	render_wireframe_bonus(t_app *app);
void	draw_overlay(t_app *app);

/* game features */
void	init_game_state(t_app *app);
void	update_animation(t_app *app);
int		get_animated_color(const t_point *p, const t_map *map, t_app *app);
void	cycle_color_mode(t_app *app);
void	cycle_render_quality(t_app *app);

/* animation features */
void	init_smooth_camera(t_app *app);
void	stop_smooth_camera(t_app *app);
void	start_smooth_transition(t_app *app, double target_rx, 
			double target_ry, double target_scale);
void	update_smooth_camera(t_app *app);
void	start_demo_mode(t_app *app);

/* color utilities */
int		pick_color(const t_point *p, const t_map *map);
int		pick_color_mode(const t_point *p, const t_map *map, int color_mode);
int		pick_color_bonus(const t_point *p, const t_map *map, const t_app_bonus *app);
int		mix(int a, int b);

/* drawing helpers */
void	img_clear(t_img *img, int color);
void	put_px(t_img *img, int x, int y, int color);
void	draw_line_pts(t_img *img, t_point2d a, t_point2d b, int color);
void	draw_line_pts_color(t_img *img, t_point2d a, t_point2d b, int color);

/* projection */
void	project_point_safe(const t_view *v, t_proj_params *params);
void	project_point_iso_safe(const t_view *v, t_proj_params *params);
void	project_point_par_safe(const t_view *v, t_proj_params *params);

/* animation */
void	start_demo_mode(t_app *app);
int	demo_hook(void *param);
void	app_message(t_app *app, char *msg);

/* bonus mouse hooks */
int	hook_mouse_bonus(int button, int x, int y, void *param);
int	hook_mouse_move_bonus(int x, int y, void *param);
int	hook_mouse_up_bonus(int button, int x, int y, void *param);

/* bonus keyboard hooks */
int	hook_key(int keycode, void *param);
int	hook_key_bonus_complete(int keycode, void *param);
int	hook_key_release_bonus(int keycode, void *param);
int	loop_hook_bonus(void *param);
void	process_continuous_keys(t_app_bonus *app);

/* bonus mouse hooks */
int	hook_mouse_bonus(int button, int x, int y, void *param);
int	hook_mouse_release_bonus(int button, int x, int y, void *param);
int	hook_mouse_move_bonus(int x, int y, void *param);

/* bonus rendering */
void	render_wireframe_bonus_complete(t_app_bonus *app);
void	rerender_bonus_complete(t_app_bonus *app);
void	rerender_bonus_immediate(t_app_bonus *app);
int		loop_hook_bonus(void *param);

/* bonus overlay and display */
void	draw_help_overlay_complete(t_app_bonus *app);
void	draw_status_display(t_app_bonus *app);

/* bonus demo mode */
void	demo_mode_update(t_app_bonus *app);

/* bonus lifecycle */
void	app_destroy_bonus(t_app_bonus *app, int code);
int	hook_destroy_bonus(void *param);

/* bonus projection */
t_point3d	rotate_point(t_point3d p, t_view *view);
t_point2d	project_bonus(t_point3d p3d, t_view *view);

/* overlay */
void	draw_controls_overlay(t_app *app);
void	draw_status_overlay(t_app *app);

#endif
