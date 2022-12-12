/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@stud.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 22:09:46 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/12 15:30:57 by nlegrand         ###   ########.fr       */
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

void	center_overlay(t_fdf *fdf)
{
	// REMOVE LATER
	t_vertex vu;
	t_vertex vd;
	t_vertex vl;
	t_vertex vr;

	vu.c = 0x00ff0000;
	vd.c = 0x00ff0000;
	vl.c = 0x00ff0000;
	vr.c = 0x00ff0000;

	vu.x = fdf->wwidth / 2.0;
	vu.y = 0;
	vd.x = fdf->wwidth / 2.0;
	vd.y = fdf->wheight;

	vl.x = 0;
	vl.y = fdf->wheight / 2.0;
	vr.x = fdf->wwidth;
	vr.y = fdf->wheight / 2.0;

	plot_line(fdf, &vu, &vd);
	plot_line(fdf, &vl, &vr);
}

int	loop_h(t_fdf *fdf)
{
	if (fdf->redraw == 1)
	{
		clear_img(fdf, 0);
		plot_map(fdf);
//		center_overlay(fdf); // REMOVE LATER
		mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);
		fdf->redraw = 0;
	}
	return (0);
}
