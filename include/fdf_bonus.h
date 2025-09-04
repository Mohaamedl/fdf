/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 00:00:00 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/08/24 20:48:18 by mohamed          ###   ########.fr       */
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

#endif
