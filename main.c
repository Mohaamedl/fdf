/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 18:46:07 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/07/28 18:46:53 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include <stdlib.h>

typedef struct s_mlx_data 
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img;
	char	*addr;
	int		line_len;
	int		bits_per_pixel;
	int		endian;
}	t_mlx_data;

void	ft_mlx_pixel_put(t_mlx_data *data, int x, int y, int color);
static void	destroy_and_exit(t_mlx_data *data, int code);
static int	handle_key(int keycode, void *param);
static int	handle_destroy(void *param);

int main(void)
{
	t_mlx_data	data;

	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, 1920, 1080, "yoooo");
	if (!data.win_ptr)
	{
		mlx_destroy_display(data.mlx_ptr);
		free(data.mlx_ptr);
		return (1);
	}
	data.img = mlx_new_image(data.mlx_ptr, 1920, 1080);
	if (!data.img)
		destroy_and_exit(&data, 1);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_len, &data.endian);

	ft_mlx_pixel_put(&data, 5, 5, 0x00FFFF00);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img, 0, 0);

	// Hooks for responsive, clean window management
	// ESC key
	mlx_key_hook(data.win_ptr, handle_key, &data);
	// Window close button (DestroyNotify)
	mlx_hook(data.win_ptr, 17, 0, handle_destroy, &data);

	mlx_loop(data.mlx_ptr);
	return (0);
}

static void	destroy_and_exit(t_mlx_data *data, int code)
{
	if (data->img)
		mlx_destroy_image(data->mlx_ptr, data->img);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	exit(code);
}

static int	handle_key(int keycode, void *param)
{
	// Linux ESC keycode
	if (keycode == 65307)
		destroy_and_exit((t_mlx_data *)param, 0);
	return (0);
}

static int	handle_destroy(void *param)
{
	destroy_and_exit((t_mlx_data *)param, 0);
	return (0);
}

void	ft_mlx_pixel_put(t_mlx_data *data, int x, int y, int color)
{
	char	*dest;
	dest = data -> addr + (y * data -> line_len + x * (data -> bits_per_pixel / 8));
	*(unsigned int *) dest = color;
}
