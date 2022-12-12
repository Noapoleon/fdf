/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@stud.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:01:50 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/12 19:21:53 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Isometric projection logic
void	calc_iso_proj(t_fdf *fdf)
{
	int			x;
	int			y;
	double		tmp;
	t_vertex	*v;

	y = 0;
	while (y < fdf->mheight)
	{
		x = 0;
		while (x < fdf->mwidth)
		{
			v = &fdf->map[y][x];
			v->x = x * fdf->view.cs - fdf->view.map_xcenter;
			v->y = y * fdf->view.cs - fdf->view.map_ycenter;
			tmp = v->x;
			v->x = tmp * fdf->view.i[0] + v->y * fdf->view.j[0];
			v->y = (tmp * fdf->view.i[1] + v->y * fdf->view.j[1]) * 0.5;
			v->y -= v->z * fdf->view.zs * fdf->view.amp * fdf->view.relief;
			v->x += fdf->view.xoff;
			v->y += fdf->view.yoff;
			++x;
		}
		++y;
	}
}

// Milittary projection logic
void	calc_mili_proj(t_fdf *fdf)
{
	int			x;
	int			y;
	double		tmp;
	t_vertex	*v;

	y = 0;
	while (y < fdf->mheight)
	{
		x = 0;
		while (x < fdf->mwidth)
		{
			v = &fdf->map[y][x];
			v->x = x * fdf->view.cs - fdf->view.map_xcenter;
			v->y = y * fdf->view.cs - fdf->view.map_ycenter;
			tmp = v->x;
			v->x = tmp * fdf->view.i[0] + v->y * fdf->view.j[0];
			v->y = (tmp * fdf->view.i[1] + v->y * fdf->view.j[1]);
			v->y -= v->z * fdf->view.zs * fdf->view.amp * fdf->view.relief;
			v->x += fdf->view.xoff;
			v->y += fdf->view.yoff;
			++x;
		}
		++y;
	}
}

// Flat projection logic
void	calc_flat_proj(t_fdf *fdf)
{
	int			x;
	int			y;
	double		tmp;
	t_vertex	*v;

	y = 0;
	while (y < fdf->mheight)
	{
		x = 0;
		while (x < fdf->mwidth)
		{
			v = &fdf->map[y][x];
			v->x = x * fdf->view.cs - fdf->view.map_xcenter;
			v->y = y * fdf->view.cs - fdf->view.map_ycenter;
			tmp = v->x;
			v->x = tmp * fdf->view.i[0] + v->y * fdf->view.j[0];
			v->y = tmp * fdf->view.i[1] + v->y * fdf->view.j[1];
			v->x += fdf->view.xoff;
			v->y += fdf->view.yoff;
			++x;
		}
		++y;
	}
}
