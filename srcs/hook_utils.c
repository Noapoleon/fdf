/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:26:54 by nlegrand          #+#    #+#             */
/*   Updated: 2022/11/28 21:25:55 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <time.h>

int	set_hooks(t_fdf *fdf)
{
	mlx_key_hook(fdf->win->id, &key_hook, fdf);
	return (0);
}

int	key_hook(int keycode, void *param)
{
	t_fdf *fdf = param;

	if (keycode == K_ESCAPE)
	{
		fdf_terminate(fdf);
		exit(EXIT_SUCCESS);
	}
	return (0);
}
