/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@stud.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 01:38:58 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/12 20:58:21 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Recalculates some view variables after performing a zoom
void	refresh_view_zoom(t_fdf *fdf)
{
	fdf->view.cs = fdf->view.cs_og * fdf->view.zoom;
	fdf->view.zs = fdf->view.zs_og * fdf->view.zoom;
	fdf->view.map_xcenter = (fdf->mwidth - 1) * fdf->view.cs / 2.0;
	fdf->view.map_ycenter = (fdf->mheight - 1) * fdf->view.cs / 2.0;
	if (fdf->view.map_xcenter == 0)
		fdf->view.map_xcenter = fdf->mwidth / 2.0;
	if (fdf->view.map_ycenter == 0)
		fdf->view.map_ycenter = fdf->mheight / 2.0;
	refresh_view_move(fdf);
}

// Recalculates some view variables after performing a move
void	refresh_view_move(t_fdf *fdf)
{
	fdf->view.xoff = fdf->wwidth / 2 + fdf->view.xmov;
	fdf->view.yoff = fdf->wheight / 2 + fdf->view.ymov;
}

// recalculates unit vectors locations
void	refresh_view_rotate(t_fdf *fdf)
{
	const double i = fdf->view.ri * (M_PI_4 / 4.0);
	const double j = (8 + fdf->view.ri) * (M_PI_4 / 4.0);

	fdf->view.i[0] = cos(i);
	fdf->view.i[1] = sin(i);
	fdf->view.j[0] = cos(j);
	fdf->view.j[1] = sin(j);
}

void	get_map_limits(t_fdf *fdf)
{
	int	x;
	int	y;

	fdf->mmin = fdf->map[0][0].z;
	fdf->mmax = fdf->map[0][0].z;
	y = 0;
	while (y < fdf->mheight)
	{
		x = 0;
		while (x < fdf->mwidth)
		{
			if (fdf->map[y][x].z < fdf->mmin)
				fdf->mmin = fdf->map[y][x].z;
			if (fdf->map[y][x].z > fdf->mmax)
				fdf->mmax = fdf->map[y][x].z;
			++x;
		}
		++y;
	}
}

void	map_relative_height(t_fdf *fdf)
{
	int		x;
	int		y;
	double	span;
	int		r;
	int		g;

	get_map_limits(fdf);
	span = fdf->mmax - fdf->mmin;
	y = 0;
	while (y < fdf->mheight)
	{
		x = 0;
		while (x < fdf->mwidth)
		{
			r = (int)(255.0 * ((fdf->map[y][x].z - fdf->mmin)
				/ (span + 1))) & 0xff;
			g = (int)(255 - r) & 0xff;
			fdf->map[y][x].cols[1] = (r << 16) | (g << 8);
			++x;
		}
		++y;
	}
}
