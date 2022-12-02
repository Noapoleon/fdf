/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:26:54 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/02 22:27:43 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <time.h>

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

int	loop_hook(void *param)
{
	t_fdf *fdf = param;
	static last = clock();

	//big if
	if ((clock() - last) / (CLOCKS_PER_SEC * 1000) > 100)
	{
		last = clock();
		// redraw image
		mlx_put_image_to_window(fdf->id, fdf->win, fdf->buf.img, 0, 0);
	}
}
