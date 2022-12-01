/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:32:42 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/01 18:11:52 by nlegrand         ###   ########.fr       */
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

	set_grad(&grad, &v0, &v1, HIGH);
	while (v0.x <= v1.x)
	{
		// PROTECT
		my_pixel_put(fdf, &v0); // change this line for color
		// color can probably be done here
		if (d > 0)
		{
			v0.y += yi;
			d += (2 * (dy - dx));
		}
		else	
			d += (2 * dy);
		if (v0.c != v1.c)
			set_grad_col(&v0, &grad);
		++(v0.x);
	}
}

void	plot_line_high(t_fdf *fdf, t_vertex v0, t_vertex v1)
{
	const int	dy = v1.y - v0.y;
	const int	dx = (v1.x - v0.x) * (1 - ((v1.x - v0.x) < 0) * 2);
	const int	xi = 1 - ((v1.x - v0.x) < 0) * 2;
	int			d = 2 * dx - dy;
	//t_vertex	v;
	t_grad		grad;

	set_grad(&grad, &v0, &v1, HIGH);
	while (v0.y <= v1.y)
	{
		// PROTECT
		my_pixel_put(fdf, &v0); // color like this doesn't work needs to be a gradient
		if (d > 0)
		{
			v0.x += xi;
			d += (2 * (dx - dy));
		}
		else	
			d += (2 * dx);
		if (v0.c != v1.c)
			set_grad_col(&v0, &grad);
		++(v0.y);
	}
}

void	my_pixel_put(t_fdf *fdf, t_vertex *v)
{
	char	*dst;

	if (v->x >= 0 && v->x < fdf->wwidth && v->y >= 0 && v->y < fdf->wheight)
	{
		dst = fdf->buf.addr + (v->y * fdf->buf.ll + v->x * (fdf->buf.bpp / 8));
		*(unsigned int *)dst = v->c;
	}
}

void	set_grad(t_grad *grad, t_vertex *v0, t_vertex *v1, int mode)
{
	int	span;

	if (mode == LOW)
		span = abso(v1->x - v0->x);
	else
		span = abso(v1->y - v0->y);
	grad->rstep = (double)span /
		(double)((v1->c & M_COLR >> 16) - (v0->c & M_COLR >> 16)) * 255.0;
	grad->gstep = (double)span /
		(double)((v1->c & M_COLG >> 8) - (v0->c & M_COLR >> 8)) * 255.0;
	grad->bstep = (double)span /
		(double)((v1->c & M_COLB) - (v0->c & M_COLR)) * 255.0;
}

void set_grad_col(t_vertex *v, t_grad *grad)
{
	int	r;
	int	g;
	int	b;
	int	newcol;

	newcol = 0;
	r = (v->c | M_COLR) >> 16;
	g = (v->c | M_COLG) >> 8;
	b = v->c | M_COLB;
	if (grad->rstep != 0)
	{
		r += grad->rstep;
		newcol |= r << 16;
	}
	if (grad->gstep != 0)
	{
		g += grad->gstep;
		newcol |= g << 8;
	}
	if (grad->bstep != 0)
	{
		b += grad->bstep;
		newcol |= b;
	}
	v->c = newcol;
}
