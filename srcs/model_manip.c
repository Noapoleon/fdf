/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_manip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:52:05 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/10 18:21:50 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	model_zoom(t_fdf *fdf, int button)
{
	if (button == MOUSE_SCROLL_UP)
		fdf->view.zoom *= 1.1;
	else
		fdf->view.zoom *= 0.9;
	if (fdf->view.zoom < 0.001)
		fdf->view.zoom = 0.001;
	if (fdf->view.zoom > 10000.0)
		fdf->view.zoom = 10000.0;
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

void	model_rotate(t_fdf *fdf, int dir)
{
	const double	*i = fdf->view.i;
	const double	*j = fdf->view.j;
	//const double	*k = fdf->view.k;
	fdf->view.i[2] += (M_PI_4/4.0) * dir;
	fdf->view.j[2] += (M_PI_4/4.0) * dir;
	fdf->view.ri += dir;
	if (fdf->view.ri > 16)
	{
		fdf->view.ri -= 32;
		fdf->view.i[2] -= 2 * M_PI;
	}
	if (fdf->view.ri <= -16)
	{
		fdf->view.ri += 32;
		fdf->view.i[2] += 2 * M_PI;
	}
	set_vector_3d(fdf->view.i, cos(i[2]), sin(i[2]), i[2]);
	set_vector_3d(fdf->view.j, cos(j[2]), sin(j[2]), j[2]);
	fdf->redraw = 1;
}

void	model_flatten(t_fdf *fdf)
{
	fdf->view.relief = (fdf->view.relief == 0);
	fdf->redraw = 1;
}

void	model_set_proj(t_fdf *fdf, int keycode)
{
	if (keycode == '1')
		fdf->view.calc_coords = &calc_iso_proj;
	else if (keycode == '2')
		fdf->view.calc_coords = &calc_mili_proj;
	fdf->redraw = 1;
}
