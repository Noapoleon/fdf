/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_manip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:52:05 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/13 00:47:23 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Updates view for variables for zooming
// Triggers a redraw
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
	if (fdf->view.zoom != 10000.0 && fdf->view.zoom != 0.001)
	{
		if (button == MOUSE_SCROLL_UP)
		{
		fdf->view.xmov *= 1.1;
		fdf->view.ymov *= 1.1;
		}
		else
		{
		fdf->view.xmov *= 0.9;
		fdf->view.ymov *= 0.9;
		}
	}
	refresh_view_zoom(fdf);
	fdf->redraw = 1;
}

// Updates view variables for movement
// Triggers a redraw
void	model_move(t_fdf *fdf, int x, int y)
{
	fdf->view.xmov += x - fdf->view.mov_start[0];
	fdf->view.ymov += y - fdf->view.mov_start[1];
	fdf->view.mov_start[0] = x;
	fdf->view.mov_start[1] = y;
	refresh_view_move(fdf);
	fdf->redraw = 1;
}

// Updates view variables for rotation
// Triggers a redraw
void	model_rotate(t_fdf *fdf, int x)
{
	double	diff;

	diff = -((x - fdf->view.rot_start) / 150.0) * M_PI;
	fdf->view.ri += diff;
	if (fdf->view.ri > 16)
		fdf->view.ri -= 32;
	else if (fdf->view.ri <= -16)
		fdf->view.ri += 32;
	fdf->view.rot_start = x;
	refresh_view_rotate(fdf);
	fdf->redraw = 1;
}

// Toggles on and off the z coordinates displacement
void	model_relief(t_fdf *fdf)
{
	fdf->view.relief = (fdf->view.relief == 0);
	fdf->redraw = 1;
}

// Changes the fdf->view.calc_coords function pointer to appropriate projection
// mode
void	model_set_proj(t_fdf *fdf, int keycode)
{
	if (keycode == '1')
		fdf->view.calc_coords = &calc_iso_proj;
	else if (keycode == '2')
		fdf->view.calc_coords = &calc_mili_proj;
	else if (keycode == '3')
		fdf->view.calc_coords = &calc_flat_proj;
	fdf->redraw = 1;
}
