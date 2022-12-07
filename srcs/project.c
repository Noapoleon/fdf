/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@stud.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 16:29:33 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/07 16:07:51 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	plot_map(t_fdf *fdf)
{
	int	x;
	int	y;

	calc_coords(fdf);
	y = 0;
	while (y < fdf->mheight)
	{
		x = 0;
		while (x < fdf->mwidth)
		{
			if (x != fdf->mwidth - 1)
				plot_line(fdf, &fdf->map[y][x], &fdf->map[y][x + 1]);
			if (y != fdf->mheight - 1)
				plot_line(fdf, &fdf->map[y][x], &fdf->map[y + 1][x]);
			++x;
		}
		++y;
	}
}


void	calc_coords(t_fdf *fdf) // for changing projection type maybe use this as function pointer like calc_coords_iso or something
{
	int			x;
	int			y;
	t_coord		coord;

	coord.cs_zoom = fdf->view.cs * fdf->view.zoom;
	coord.cs_zoom += (coord.cs_zoom == 0);
	coord.zs_zoom = fdf->view.cs * fdf->view.zoom;
	coord.zs_zoom += (coord.cs_zoom == 0);
	coord.xcenter = fdf->mwidth * coord.cs_zoom / 2.0;
	coord.ycenter = fdf->mheight * coord.cs_zoom / 2.0;
	y = 0;
	while (y < fdf->mheight)
	{
		x = 0;
		while (x < fdf->mwidth)
		{
			coord.xmap = x;
			coord.ymap = y;
			calc_iso(fdf, &fdf->map[y][x], &coord);
			++x;
		}
		++y;
	}
}

void	calc_iso(t_fdf *fdf, t_vertex *v, t_coord *coord)
{
	int	tmp;


	v->x = coord->xmap * coord->cs_zoom - coord->xcenter;
	v->y = coord->ymap * coord->cs_zoom - coord->ycenter;
	tmp = v->x;
	v->x = tmp * fdf->view.i[0] + v->y * fdf->view.j[0];
	v->y = (tmp * fdf->view.i[1] + v->y * fdf->view.j[1]) * 0.5; // change that later for top view and stuff
	v->x += fdf->view.xoff + coord->xcenter;
	v->y += fdf->view.yoff + coord->ycenter;
	v->y -= v->z * coord->zs_zoom;
}
