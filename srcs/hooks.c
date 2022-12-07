/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@stud.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 22:09:46 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/07 23:05:45 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Sets all x hooks through mlx functions
void	set_hooks(t_fdf *fdf) // check if it  wouldn't be useful to return int
{
	mlx_key_hook(fdf->win, key_hook, fdf);
	mlx_hook(fdf->win, DestroyNotify, StructureNotifyMask, close_cross, fdf);
	mlx_mouse_hook(fdf->win, zoom_map, fdf);
	mlx_hook(fdf->win, MotionNotify, PointerMotionMask, move_model, fdf);
	mlx_loop_hook(fdf->mlx, loop_hook, fdf);
}

// Exits mlx_loop if escape key is pressed
int	key_hook(int keycode, t_fdf *fdf)
{
	ft_printf("k = %d\n", keycode);
	if (keycode == KEY_ESC)
	{
		fdf_terminate(fdf);
		exit(EXIT_SUCCESS);
	}
	if (keycode == KEY_G)
	{
		fdf->view.moving = (fdf->view.moving == 0);
		return (0);
	}
	//if (keycode == KEY_R)
	//{
	//	rot_model(fdf);
	//}
	return (0);
}

// Exits mlx_loop if cross icon is pressed
int close_cross(t_fdf *fdf)
{
	fdf_terminate(fdf);
	exit(EXIT_SUCCESS);
}

int	zoom_map(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (button == 4)
		fdf->view.zoom *= 1.1;
	if (button == 5)
		fdf->view.zoom *= 0.9;
	if (fdf->view.zoom < 0.0)
		fdf->view.zoom = 0.0;
	refresh_view_zoom(fdf);
	fdf->redraw = 1;
	return (0);
}

int	loop_hook(t_fdf *fdf)
{
	if (fdf->redraw == 1)
	{
		clear_img(fdf, 0); // use unsigned int maybe??
		plot_map(fdf);
		mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);
	}
	fdf->redraw = 0;
	return (0);
}

int	move_model(int x, int y, t_fdf *fdf)
{
	static int	start;
	static int	lastx;
	static int	lasty;

	if (fdf->view.moving == 0)
	{
		start = 0;
		return (0);
	}
	if (start == 0)
	{
		lastx = x;
		lasty = y;
		start = 1;
	}
	else
	{
		fdf->view.xmov += x - lastx;
		fdf->view.ymov += y - lasty;
		lastx = x;
		lasty = y;
		fdf->redraw = 1;
	}
	return (0);
}
