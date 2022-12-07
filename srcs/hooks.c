/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@stud.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 22:09:46 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/07 14:58:15 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Sets all x hooks through mlx functions
void	set_hooks(t_fdf *fdf) // check if it  wouldn't be useful to return int
{
	mlx_key_hook(fdf->win, close_esc, fdf);
	mlx_hook(fdf->win, DestroyNotify, StructureNotifyMask, close_cross, fdf);
	mlx_mouse_hook(fdf->win, zoom_map, fdf);
	mlx_loop_hook(fdf->mlx, loop_hook, fdf);
}

// Exits mlx_loop if escape key is pressed
int	close_esc(int keycode, t_fdf *fdf)
{
	if (keycode == XK_Escape)
	{
		fdf_terminate(fdf);
		exit(EXIT_SUCCESS);
	}
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
		fdf->view.zoom += 0.1;
	if (button == 5)
		fdf->view.zoom -= 0.1;
	ft_printf("button -> %d\n", button);
	printf("zoom ---> %f\n\n", fdf->view.zoom); // my ft_printf doesn't support floats
	fdf->redraw = 1;
	return (0);
}

int	loop_hook(t_fdf *fdf)
{
	if (fdf->redraw == 1 || fdf->redraw == -1)
	{
		clear_img(fdf, 0); // use unsigned int maybe??
		plot_map(fdf);
		mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);
		ft_printf("redrew!\n");
	}
	fdf->redraw = 0;
	return (0);
}
