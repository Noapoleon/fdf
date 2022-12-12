/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@stud.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 01:38:58 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/12 11:44:22 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	refresh_view_rotate(t_fdf *fdf)
{
	const double i = fdf->view.ri * (M_PI_4 / 4.0);
	const double j = (8 + fdf->view.ri) * (M_PI_4 / 4.0);

	fdf->view.i[0] = cos(i);
	fdf->view.i[1] = sin(i);
	fdf->view.j[0] = cos(j);
	fdf->view.j[1] = sin(j);
}
