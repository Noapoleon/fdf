/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:26:54 by nlegrand          #+#    #+#             */
/*   Updated: 2022/11/29 20:59:05 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <time.h>

int	set_hooks(t_fdf *fdf)
{
	mlx_key_hook(fdf->win, &key_hook, fdf);
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
