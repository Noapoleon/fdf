/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:32:42 by nlegrand          #+#    #+#             */
/*   Updated: 2022/11/29 18:43:35 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// CURRENTLY FUNCTIONS HAVE TOO MANY ARGUMENTS
// IN THE FUTURE CHANGE DEFINITION OF T_VERTEX TO INCLUDE X AND Y
// THIS WILL PROBABLY ALSO ALLOW TO STORE THEIR SCREEN COORDINATES IN THE SAME
// STRUCT TOO

void	plot_line(t_fdf *fdf, t_vertex v0, t_vertex v1)
{
	if (abso(v1.x - v0.x) > abso(v1.y - v0.y))
	{
		if (v1.x > v0.x)
			plot_line_low(fdf, &v0, &v1);
		else
			plot_line_low(fdf, &v1, &v0);
	}
	else
	{
		if (v1.y > v0.y)
			plot_line_high(fdf, &v0, &v1);
		else
			plot_line_high(fdf, &v1, &v0);
	}
}

void	plot_line_low(t_fdf *fdf, t_vertex *v0, t_vertex *v1)
{
	const int	dx = v1->x - v0->x;
	const int	dy = (v1->y - v0->y) * (1 - ((v1->y - v0->y) < 0) * 2);
	const int	yi = 1 - ((v1->y - v0->y) < 0) * 2;
	int	d = 2 * dy - dx;

	while (v0->x <= v1->x)
	{
		// PROTECT
		mlx_pixel_put(fdf->id, fdf->win, v0->x, v0->y, 0x00ffffff);
		if (d > 0)
		{
			v0->y += yi;
			d += (2 * (dy - dx));
		}
		else	
			d += (2 * dy);
		++v0->x;
	}
}

void	plot_line_high(t_fdf *fdf, t_vertex *v0, t_vertex *v1)
{
	const int	dy = v1->y - v0->y;
	const int	dx = (v1->x - v0->x) * (1 - ((v1->x - v0->x) < 0) * 2);
	const int	xi = 1 - ((v1->x - v0->x) < 0) * 2;
	int	d = 2 * dx - dy;

	while (v0->y <= v1->y)
	{
		// PROTECT
		mlx_pixel_put(fdf->id, fdf->win, v0->x, v0->y, 0x00ffffff);
		if (d > 0)
		{
			v0->x += xi;
			d += (2 * (dx - dy));
		}
		else	
			d += (2 * dx);
		++v0->y;
	}
}

int	abso(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}
