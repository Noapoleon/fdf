/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@stud.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 23:58:48 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/07 14:50:16 by nlegrand         ###   ########.fr       */
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
