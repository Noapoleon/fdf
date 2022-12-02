/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:32:42 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/01 23:44:02 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// IN THE FUTURE CHANGE DEFINITION OF T_VERTEX TO INCLUDE X AND Y
// THIS WILL PROBABLY ALSO ALLOW TO STORE THEIR SCREEN COORDINATES IN THE SAME
// STRUCT TOO

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

void	plot_line_low(t_fdf *fdf, t_vertex v0, t_vertex v1)
{
	const int	dx = v1.x - v0.x;
	const int	dy = (v1.y - v0.y) * (1 - ((v1.y - v0.y) < 0) * 2);
	const int	yi = 1 - ((v1.y - v0.y) < 0) * 2;
	int			d = 2 * dy - dx;
	t_grad		grad;

	grad.dc = v1.c - v0.c;
	grad.dp = dx;
	grad.og_p = v0.x;
	while (v0.x <= v1.x)
	{
		// PROTECT (from what lol ? i dont remember)
		my_pixel_put(fdf, &v0, grad_col(&grad, &v0, v0.x));
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

void	plot_line_high(t_fdf *fdf, t_vertex v0, t_vertex v1)
{
	const int	dy = v1.y - v0.y;
	const int	dx = (v1.x - v0.x) * (1 - ((v1.x - v0.x) < 0) * 2);
	const int	xi = 1 - ((v1.x - v0.x) < 0) * 2;
	int			d = 2 * dx - dy;
	t_grad		grad;

	grad.dc = v1.c - v0.c;
	grad.dp = dy;
	grad.og_p = v0.y;
	while (v0.y <= v1.y)
	{
		my_pixel_put(fdf, &v0, grad_col(&grad, &v0, v0.y));
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

void	my_pixel_put(t_fdf *fdf, t_vertex *v, int col)
{
	char	*dst;

	if (v->x >= 0 && v->x < fdf->wwidth && v->y >= 0 && v->y < fdf->wheight)
	{
		dst = fdf->buf.addr + (v->y * fdf->buf.ll + v->x * (fdf->buf.bpp / 8));
		*(unsigned int *)dst = col;
	}
}

int	grad_col(t_grad *grad, t_vertex *v, int pos)
{
	int	r;
	int	g;
	int	b;
	int				col;
	const double	factor = ((pos - grad->og_p) / (double)(grad->dp + 1));


	r = (v->c & M_COLR) >> 16;
	g = (v->c & M_COLG) >> 8;
	b = (v->c & M_COLB);
	r += ((grad->dc & M_COLR) >> 16) * factor;
	g += ((grad->dc & M_COLG) >> 8) * factor;
	b += (grad->dc & M_COLB) * factor;
	col = 0;
	col |= r << 16;
	col |= g << 8;
	col |= b;
	col &= M_COL;
	return (col);
}
