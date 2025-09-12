/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:53:39 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/09/08 18:54:47 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>
# include "../libft/inc/libft.h"
# include "../libft/inc/ft_printf.h"
# include "../libft/inc/get_next_line.h"
# include "../mlx/mlx.h"

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define WIN_W 1280
# define WIN_H 720

/* Essential keycodes */
# define KEY_ESC 65307

/* MLX event numbers */
# define EVENT_DESTROY 17

/* Projection types */
# define PROJ_ISO 0
# define PROJ_PAR 1

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

typedef struct s_gradient_params
{
	int	color1;
	int	color2;
}	t_gradient_params;

typedef struct s_line_gradient
{
	t_img		*img;
	t_point2d	start;
	t_point2d	end;
	int			color1;
	int			color2;
}	t_line_gradient;


typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
}	t_mlx;

typedef struct s_view
{
	double			scale;
	double			offset_x;
	double			offset_y;
	double			angle;
	double			zscale;
	int				proj;
	double			rot_x;
	double			rot_y;
	double			rot_z;
	struct timeval	last_render_time;
}	t_view;

typedef struct s_app
{
	t_mlx	mlx;
	t_map	map;
	t_view	view;
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
int		count_dimensions(const char *path, int *width, int *height);
int		allocate_map(t_map *map);
void	init_map_parsing(t_map *map);

/* MLX functions */
int		mlx_init_safe(t_mlx *mlx);
int		hex_color_to_int(const char *hex_str);
int		string_to_int_len(const char *str, int len);
int		parse_token_direct(const char *tok, int len, int *z, int *color);
void	free_string_array(char **array);
int		count_words(const char *str, char delimiter);
char	*skip_whitespace(char *str);

/* Rendering functions */
void	render_wireframe(t_app *app);
void	draw_horizontal_line(t_app *app, int x, int y);
void	draw_vertical_line(t_app *app, int x, int y);
void	img_clear(t_img *img, int color);
void	put_px(t_img *img, int x, int y, int color);
void	draw_line_pts(t_img *img, t_point2d pt1, t_point2d pt2, int color);
void	setup_line_data(t_line_gradient *line, t_img *img, t_point2d a,
		t_point2d b);
void	draw_line_with_colors(t_line_gradient *line, int c1, int c2);
void	draw_gradient_line(t_line_gradient *line);
int		lerp_color(int color1, int color2, double t);

/* View functions */
void	recompute_view_fit(t_app *app);
void	project_point_safe(const t_view *view, t_proj_params *params);

/* Color functions */
int		pick_color(const t_point *p, const t_map *map);

/* Hook functions */
int		hook_key(int keycode, void *param);
int		hook_destroy(void *param);
void	free_string_array(char **array);

/* App functions */
int		app_init(t_app *app, const char *path);
void	app_destroy(t_app *app, int code);

#endif
