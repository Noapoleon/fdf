/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@stud.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 16:29:33 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/13 00:50:01 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Writes map pixels to the image buffer
void	plot_map(t_fdf *fdf)
{
	(fdf->view.calc_coords)(fdf);
	if (isgreater(fdf->view.ri, -8.0) && islessequal(fdf->view.ri, 8.0))
		plot_up_left(fdf);
	else
		plot_down_right(fdf);
}

// Draws the map start from the top left vertex
// Prevents clipping of lines when map rotation is higher than 180 degrees
void	plot_up_left(t_fdf *fdf)
{
	int	x;
	int	y;

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

// Draws the map start from the bottom right vertex
// Prevents clipping of lines when map rotation is lower than 180 degrees
void	plot_down_right(t_fdf *fdf)
{
	int	x;
	int	y;

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

// Prevents drawing lines completely outside of the window
int	check_out(t_fdf *fdf, t_vertex *v0, t_vertex *v1)
{
	if ((v0->x < 0 && v1->x < 0)
		|| (v0->x >= fdf->wwidth && v1->x >= fdf->wwidth))
		return (1);
	if ((v0->y < 0 && v1->y < 0)
		|| (v0->y >= fdf->wheight && v1->y >= fdf->wheight))
		return (1);
	return (0);
}
