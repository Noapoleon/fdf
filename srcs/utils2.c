/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@stud.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 23:58:48 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/11 06:59:46 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// gives x, y and z coordinates to 3d vector
void	set_vector_3d(double v[3], double x, double y, double z)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

int	abso(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

void	clear_img(t_fdf *fdf, int col)
{
	int		x;
	int		y;
	char	*dst;

	y = 0;
	while (y < fdf->wheight)
	{
		x = 0;
		while (x < fdf->wwidth)
		{
			dst = fdf->img.addr + y * fdf->img.ll + x * (fdf->img.bpp / 8);
			*(unsigned int *)dst = col;
			++x;
		}
		++y;
	}
}

// Recalculates some view variables after performing a zoom
void	refresh_view_zoom(t_fdf *fdf)
{
	fdf->view.cs = fdf->view.cs_og * fdf->view.zoom;
	//fdf->view.cs += (fdf->view.cs == 0); // might need to remove 0 check because of new type now
	fdf->view.zs = fdf->view.zs_og * fdf->view.zoom;
	//fdf->view.zs += (fdf->view.zs == 0);
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
//	fdf->view.xoff = fdf->wwidth / 2 + fdf->view.xmov * fdf->view.cs; // MAKES THE ZOOM PERFECT BUT NOT THE MOVEMENT AFTERWARDS
//	fdf->view.yoff = fdf->wheight / 2 + fdf->view.ymov * fdf->view.cs;
	fdf->view.xoff = fdf->wwidth / 2 + fdf->view.xmov;
	fdf->view.yoff = fdf->wheight / 2 + fdf->view.ymov;
}
