/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@stud.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 00:37:53 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/13 01:00:10 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Draws a line on the image with two given coordinates using bresenham's
// algorithm
// Switches arguments order in order to handle all possible angles (8 octants)
void	plot_line(t_fdf *fdf, t_vertex *v0, t_vertex *v1)
{
	if (abso(v1->x - v0->x) > abso(v1->y - v0->y))
	{
		if (v1->x > v0->x)
			plot_line_low(fdf, *v0, *v1);
		else
			plot_line_low(fdf, *v1, *v0);
	}
	else
	{
		if (v1->y > v0->y)
			plot_line_high(fdf, *v0, *v1);
		else
			plot_line_high(fdf, *v1, *v0);
	}
}

// Sub-function of plot_line handles octants whose angles is less than 45
// degrees
void	plot_line_low(t_fdf *fdf, t_vertex v0, t_vertex v1)
{
	const int	dx = v1.x - v0.x;
	const int	dy = (v1.y - v0.y) * (1 - ((v1.y - v0.y) < 0) * 2);
	const int	yi = 1 - ((v1.y - v0.y) < 0) * 2;
	int			d;
	t_grad		grad;

	grad.dc = v1.c - v0.c;
	grad.dp = dx;
	grad.og_p = v0.x;
	d = 2 * dy - dx;
	while (v0.x <= v1.x)
	{
		my_pixel_put(fdf, v0.x, v0.y, grad_col(&grad, &v0, &v1, v0.x));
		if (d > 0)
		{
			v0.y += yi;
			d += (2 * (dy - dx));
		}
		else
			d += (2 * dy);
		++(v0.x);
	}
}

// Sub-function of plot_line handles octants whose angles is more than 45
// degrees
void	plot_line_high(t_fdf *fdf, t_vertex v0, t_vertex v1)
{
	const int	dy = v1.y - v0.y;
	const int	dx = (v1.x - v0.x) * (1 - ((v1.x - v0.x) < 0) * 2);
	const int	xi = 1 - ((v1.x - v0.x) < 0) * 2;
	int			d;
	t_grad		grad;

	grad.dc = v1.c - v0.c;
	grad.dp = dy;
	grad.og_p = v0.y;
	d = 2 * dx - dy;
	while (v0.y <= v1.y)
	{
		my_pixel_put(fdf, v0.x, v0.y, grad_col(&grad, &v0, &v1, v0.y));
		if (d > 0)
		{
			v0.x += xi;
			d += (2 * (dx - dy));
		}
		else
			d += (2 * dx);
		++(v0.y);
	}
}

// Substitue function for mlx_pixel_put
// Writes pixels into the image buffer instead of directly to the screen for
// much better performance
void	my_pixel_put(t_fdf *fdf, int x, int y, int col)
{
	char	*dst;

	if (x >= 0 && x < fdf->wwidth && y >= 0 && y < fdf->wheight)
	{
		dst = fdf->img.addr + (y * fdf->img.ll + x * (fdf->img.bpp / 8));
		*(unsigned int *)dst = col;
	}
}

// Computes the color of each pixel in a line between 2 vertices to make a
// gradient line
int	grad_col(t_grad *grad, t_vertex *v0, t_vertex *v1, int pos)
{
	int				r;
	int				g;
	int				b;
	int				col;
	const double	factor = (pos - grad->og_p) / (double)(grad->dp + 1);

	r = (((v1->c & M_COLR) >> 16) - ((v0->c & M_COLR) >> 16)) * factor;
	g = (((v1->c & M_COLG) >> 8) - ((v0->c & M_COLG) >> 8)) * factor;
	b = ((v1->c & M_COLB) - (v0->c & M_COLB)) * factor;
	col = 0;
	col |= ((r << 16) + (v0->c & M_COLR)) & M_COL;
	col |= ((g << 8) + (v0->c & M_COLG)) & M_COL;
	col |= (b + (v0->c & M_COLB)) & M_COL;
	return (col);
}
