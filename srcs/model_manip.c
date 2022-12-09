/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_manip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:52:05 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/09 14:55:38 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	model_zoom(t_fdf *fdf, int button)
{
	if (button == MOUSE_SCROLL_UP)
		fdf->view.zoom *= 1.1;
	else
		fdf->view.zoom *= 0.9;
	if (fdf->view.zoom < 0.0)
		fdf->view.zoom = 0.0;
	refresh_view_zoom(fdf);
	fdf->redraw = 1;
}

void	model_move(t_fdf *fdf, int x, int y)
{
	fdf->view.xmov += x - fdf->view.mov_start[0];
	fdf->view.ymov += y - fdf->view.mov_start[1];
	fdf->view.mov_start[0] = x;
	fdf->view.mov_start[1] = y;
	refresh_view_move(fdf);
	fdf->redraw = 1;
}

void	model_rotate(t_fdf *fdf, int x, int y)
{
	const double	*i = fdf->view.i;
	const double	*j = fdf->view.j;
	(void)fdf;
	(void)x;
	(void)y;
	fdf->view.i[2] += M_PI_4/4;
	fdf->view.j[2] += M_PI_4/4;
	// refresh_rotate()
	set_vector_3d(fdf->view.i, cos(i[2]), sin(i[2]), i[2]);
	set_vector_3d(fdf->view.j, cos(j[2]), sin(j[2]), j[2]);
	fdf->redraw = 1;
	//fdf->view.
}
