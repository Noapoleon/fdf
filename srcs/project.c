/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@stud.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 16:29:33 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/10 02:38:55 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	plot_map(t_fdf *fdf)
{
	int	x;
	int	y;

	calc_coords(fdf);
	if (fdf->view.ri > -8 && fdf->view.ri <= 8)
	{
		y = 0;
		while (y < fdf->mheight)
		{
			x = 0;
			while (x < fdf->mwidth)
			{
				if ((x != fdf->mwidth - 1) && check_out(fdf, &fdf->map[y][x],
					&fdf->map[y][x + 1]) == 0)
					plot_line(fdf, &fdf->map[y][x], &fdf->map[y][x + 1]);
				if ((y != fdf->mheight - 1) && check_out(fdf, &fdf->map[y][x],
					&fdf->map[y + 1][x]) == 0)
					plot_line(fdf, &fdf->map[y][x], &fdf->map[y + 1][x]);
				++x;
			}
			++y;
		}
	}
	else
	{
		y = fdf->mheight;
		while (y--)
		{
			x = fdf->mwidth;
			while (x--)
			{
				if ((x != 0) && check_out(fdf, &fdf->map[y][x],
					&fdf->map[y][x - 1]) == 0)
					plot_line(fdf, &fdf->map[y][x], &fdf->map[y][x - 1]);
				if ((y != 0) && check_out(fdf, &fdf->map[y][x],
					&fdf->map[y - 1][x]) == 0)
					plot_line(fdf, &fdf->map[y][x], &fdf->map[y - 1][x]);
			}
		}
	}
}

void	calc_coords(t_fdf *fdf) // for changing projection type maybe use this as function pointer like calc_coords_iso or something
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->mheight)
	{
		x = 0;
		while (x < fdf->mwidth)
		 {
			calc_iso(fdf, &fdf->map[y][x], x, y);
			++x;
		}
		++y;
	}
}

void	calc_iso(t_fdf *fdf, t_vertex *v, int x, int y)
{
	int	tmp;

	v->x = x * fdf->view.cs - fdf->view.map_xcenter;
	v->y = y * fdf->view.cs - fdf->view.map_ycenter;
	tmp = v->x;
	v->x = tmp * fdf->view.i[0] + v->y * fdf->view.j[0];
	v->y = (tmp * fdf->view.i[1] + v->y * fdf->view.j[1]) * 0.5; // change that later for top view and stuff
	//v->y = (tmp * fdf->view.i[1] + v->y * fdf->view.j[1]); // change that later for top view and stuff
	v->y -= v->z * fdf->view.zs * fdf->view.flat;
//	printf("v->z -> %d and fdf->view.zs -> %d\n", v->z, fdf->view.zs);
	v->x += fdf->view.xoff + fdf->view.xmov;
	v->y += fdf->view.yoff + fdf->view.ymov;
}

// Prevents drawing lines outside of the window completely
// (not all cases covered)
int	check_out(t_fdf *fdf, t_vertex *v0, t_vertex *v1)
{
	if ((v0->x < 0 && v1->x < 0) ||
			(v0->x >= fdf->wwidth && v1->x >= fdf->wwidth))
		return (1);
	if ((v0->y < 0 && v1->y < 0) ||
			(v0->y >= fdf->wheight && v1->y >= fdf->wheight))
		return (1);
	return (0);
}
