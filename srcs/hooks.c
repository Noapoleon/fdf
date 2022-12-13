/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@stud.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 22:09:46 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/13 00:40:10 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Sets all x hooks through mlx functions
void	set_hooks(t_fdf *fdf)
{
	mlx_hook(fdf->win, KeyPress, KeyPressMask, key_press_h, fdf);
	mlx_hook(fdf->win, DestroyNotify, StructureNotifyMask, destroy_h, fdf);
	mlx_hook(fdf->win, ButtonPress, ButtonPressMask, mouse_press_h, fdf);
	mlx_hook(fdf->win, ButtonRelease, ButtonReleaseMask, mouse_release_h, fdf);
	mlx_hook(fdf->win, MotionNotify, PointerMotionMask, mouse_move_h, fdf);
	mlx_loop_hook(fdf->mlx, loop_h, fdf);
}

// Exits mlx_loop if cross icon is pressed
int	destroy_h(t_fdf *fdf)
{
	fdf_terminate(fdf);
	exit(EXIT_SUCCESS);
}

// Function bound to mlx_loop_hook that will execute unconditionally until the
// the loop is exited
int	loop_h(t_fdf *fdf)
{
	if (fdf->redraw == 1)
	{
		clear_img(fdf, 0);
		plot_map(fdf);
		mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);
		fdf->redraw = 0;
	}
	return (0);
}
