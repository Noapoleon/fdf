/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_manip2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:32:28 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/13 00:47:38 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Resets some view variables to recenter map on screen
// Not all view variables are reset
void	model_view_focus(t_fdf *fdf)
{
	fdf->view.zoom = 1.0;
	fdf->view.xmov = 0;
	fdf->view.ymov = 0;
	refresh_view_zoom(fdf);
	refresh_view_move(fdf);
	fdf->redraw = 1;
}

// Changes to amplitude view variable that will be multiplied to each vertex's
// z coordinate
void	model_scale_amp(t_fdf *fdf, int keycode)
{
	if (keycode == 'w')
		fdf->view.amp += 0.05;
	else if (keycode == 's')
		fdf->view.amp -= 0.05;
	else if (keycode == 'i')
		fdf->view.amp *= 1.1;
	else
		fdf->view.amp *= 0.9;
	if (isgreater(fdf->view.amp, -0.00001) && isless(fdf->view.amp, 0.0))
		fdf->view.amp = -0.00001;
	else if (isgreater(fdf->view.amp, 0.00001) && isless(fdf->view.amp, 0.0))
		fdf->view.amp = 0.00001;
	else if (fdf->view.amp > 1000.0)
		fdf->view.amp = 1000.0;
	else if (fdf->view.amp < -1000.0)
		fdf->view.amp = -1000.0;
	fdf->redraw = 1;
}

// Toggles on and off height map view mode
void	model_toggle_height(t_fdf *fdf)
{
	int	x;
	int	y;

	fdf->view.height = (fdf->view.height == 0);
	y = 0;
	while (y < fdf->mheight)
	{
		x = 0;
		while (x < fdf->mwidth)
		{
			fdf->map[y][x].c = fdf->map[y][x].cols[fdf->view.height];
			++x;
		}
		++y;
	}
	fdf->redraw = 1;
}
