/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:49:22 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/24 11:16:40 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include "../libft/inc/libft.h"
#include "../libft/inc/ft_printf.h"
#include "../libft/inc/get_next_line.h"
#include "../mlx/mlx.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define WIN_W 1280
#define WIN_H 720

/* Essential keycodes */
#define KEY_ESC 65307

/* MLX event numbers */
#define EVENT_DESTROY 17

/* Projection types */
#define PROJ_ISO 0
#define PROJ_PAR 1
#define PROJ_PER 2

/* Mouse buttons */
#define BTN_LEFT 1
#define BTN_MIDDLE 2
#define BTN_RIGHT 3
#define BTN_SCROLL_UP 4
#define BTN_SCROLL_DOWN 5

/* Basic structures */
typedef struct s_point
{
	double	z;
	int		color;
}	t_point;

typedef struct s_point2d
{
	int	x;
	int	y;
}	t_point2d;

typedef struct s_map
{
	t_point	**pts;
	int		w;
	int		h;
	int		zmin;
	int		zmax;
}	t_map;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		w;
	int		h;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
}	t_mlx;

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
}	t_view;

typedef struct s_smooth
{
	int		active;
	double	duration;
	double	progress;
	double	start_rot_x;
	double	start_rot_y;
	double	start_scale;
	double	target_rot_x;
	double	target_rot_y;
	double	target_scale;
}	t_smooth;

typedef struct s_app
{
	t_mlx	mlx;
	t_map	map;
	t_view	view;
#ifdef BONUS
	t_smooth smooth;
	int		mouse_down;
	int		mouse_button;
	int		last_x;
	int		last_y;
	int		press_x;
	int		press_y;
	int		move_accum;
	int		sel_valid;
	int		sel_x;
	int		sel_y;
#endif
}	t_app;

typedef struct s_proj_params
{
	int		x;
	int		y;
	double	z;
	double	*sx;
	double	*sy;
}	t_proj_params;

/* Core functions */
int		parse_map(const char *path, t_map *map);
void	free_map(t_map *map);

/* MLX functions */
int		mlx_init_safe(t_mlx *mlx);

/* Rendering functions */
void	render_wireframe(t_app *app);
void	img_clear(t_img *img, int color);
void	put_px(t_img *img, int x, int y, int color);
void	draw_line_pts(t_img *img, t_point2d pt1, t_point2d pt2, int color);

/* View functions */
void	recompute_view_fit(t_app *app);
void	project_point_safe(const t_view *view, t_proj_params *params);

/* Color functions */
int		pick_color(const t_point *p, const t_map *map);
int		pick_color_mode(const t_point *p, const t_map *map, int color_mode);
int		pick_color_bonus(const t_point *p, const t_map *map, const void *app);

/* Hook functions */
int		hook_key(int keycode, void *param);
int		hook_destroy(void *param);
int		hook_close(void *param);

/* Bonus hook functions */
int		hook_mouse_button(int button, int x, int y, void *param);
int		hook_mouse_release(int button, int x, int y, void *param);
int		hook_mouse_move(int x, int y, void *param);

/* Animation functions */
void	init_smooth_camera(t_app *app);
void	start_smooth_transition(t_app *app, double target_rx, double target_ry, double target_scale);
void	update_smooth_camera(t_app *app);
void	stop_smooth_camera(t_app *app);
void	start_demo_mode(t_app *app);

/* Rendering functions */
void	render(t_app *app);
void	rerender(t_app *app);

/* App functions */
int		app_init(t_app *app, const char *path);
void	app_destroy(t_app *app, int code);

#endif
