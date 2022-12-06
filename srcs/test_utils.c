/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@stud.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:50:38 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/06 15:57:17 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	bres_grad_test(t_fdf *fdf)
{
	t_vertex	v0;
	t_vertex	v1;

	v0.x = 138;
	v0.y = 138;
	v1.x = 10;
	v1.y = 10;
	v0.c = 0x00ffffff;
	v1.c = 0x00ff0000;
	while (v1.x < 265)
	{
		plot_line(fdf, &v0, &v1);
		++v1.x;
	}
	while (v1.y != 265)
	{
		plot_line(fdf, &v0, &v1);
		++v1.y;
	}
	while (v1.x != 10)
	{
		plot_line(fdf, &v0, &v1);
		--v1.x;
	}
	while (v1.y != 10)
	{
		plot_line(fdf, &v0, &v1);
		--v1.y;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);
}

void	dot_test(t_fdf *fdf)
{
	int	y;
	int	x;

	y = 0;
	while (y < fdf->mheight)
	{
		x = 0;
		while (x < fdf->mwidth)
		{
			my_pixel_put(fdf, x, y, 0x00ffffff);
			++x;
		}
		++y;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);
}
