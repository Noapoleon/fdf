/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@stud.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 23:58:48 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/13 00:54:46 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Gives x and y coordinates to 2d vector
void	set_vector_2d(double v[2], double x, double y)
{
	v[0] = x;
	v[1] = y;
}

// Absolute value, had to implement it because it's not math.h but stdlib.h
// which is not allowed by the subject
int	abso(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

// Clears all the pixels of the image buffer to the specified color
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
