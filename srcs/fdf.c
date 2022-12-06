/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:41:28 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/06 23:11:36 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// CRASHES WHEN PARSING MAP WITH A SPACE AT THE END OF LINE OTHER THAN FIRST LINE

// Unimportant function
int	main(int ac, char **av)
{
	t_fdf	fdf;

	errno = 0;
	fdf_setup(&fdf, ac, av);
	set_hooks(&fdf);

	//bres_grad_test(&fdf);
	//dot_test(&fdf);
	plot_map(&fdf);
	mlx_put_image_to_window(fdf.mlx, fdf.win, fdf.img.img, 0, 0); // this will ahve to be somewhere else

	mlx_loop(fdf.mlx);
	return (0);
}
