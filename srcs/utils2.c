/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@stud.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 23:58:48 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/12 11:40:28 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// gives x, y and z coordinates to 2d vector
void	set_vector_2d(double v[3], double x, double y)
{
	v[0] = x;
	v[1] = y;
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

// does nothing :)
// used with ft_lstclear so that it won't free the content
void	do_nothing(void *ptr)
{
	(void)ptr;
}
