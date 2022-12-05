/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:26:54 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/04 16:37:12 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <time.h>

#define CLOCKS_PER_MILLI (CLOCKS_PER_SEC / 1000)

void	clear_image(t_fdf *fdf, unsigned int col)
{
	const int	tot = fdf->wwidth * fdf->wheight;
	int			i;
	char		*dst;

	dst = fdf->buf.addr;
	i = 0;
	while (i < tot)
	{
//		printf("x: %d, y: %d\n", 
		dst += fdf->buf.bpp / 8;
		*(unsigned int *)dst = col;
		++i;
	}
}

int	loop_hook(void *param)
{
	t_fdf			*fdf = param;
	static clock_t	last;


	if (last == 0)
	{
		last = clock();
		return (0);
	}
	//big if
	if ((clock() - last) / CLOCKS_PER_MILLI > 1)
	{
		last = clock();
		fdf->mtr[0] = cos(last);
		fdf->mtr[1] = sin(last);
		fdf->mtr[2] = -sin(last);
		fdf->mtr[3] = cos(last);
		// redraw image
		clear_image(fdf, 0);
		map_lines_test(fdf);
		mlx_put_image_to_window(fdf->id, fdf->win, fdf->buf.img, 0, 0);
	}
	return (0);
}
int	set_hooks(t_fdf *fdf)
{
	mlx_key_hook(fdf->win, &key_hook, fdf);
	mlx_loop_hook(fdf->id, loop_hook, fdf);
	return (0);
}

int	key_hook(int keycode, void *param)
{
	t_fdf *fdf = param;

	if (keycode == K_ESCAPE)
	{
		terminate_fdf(fdf);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

