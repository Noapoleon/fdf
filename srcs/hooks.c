/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@stud.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 22:09:46 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/06 00:08:35 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Sets all x hooks through mlx functions
void	set_hooks(t_fdf *fdf) // check if it  wouldn't be useful to return int
{
	mlx_key_hook(fdf->win, close_esc, fdf);
	mlx_hook(fdf->win, DestroyNotify, StructureNotifyMask, close_cross, fdf);
}

// Exits mlx_loop if escape key is pressed
int	close_esc(int keycode, t_fdf *fdf)
{
	if (keycode == XK_Escape)
	{
		fdf_terminate(fdf);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

// Exits mlx_loop if cross icon is pressed
int close_cross(t_fdf *fdf)
{
	fdf_terminate(fdf);
	exit(EXIT_SUCCESS);
}
