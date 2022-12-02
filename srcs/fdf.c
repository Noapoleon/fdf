/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:45:57 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/02 22:24:57 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	t_fdf		fdf;

	errno = 0;
	fdf_setup(&fdf, ac, av);
	set_hooks(&fdf);

	// TESTS //
	//show_map(&fdf);
	//line_test(&fdf);
	map_lines_test(&fdf);
	// ----- //

	//mlx_put_image_to_window(fdf.id, fdf.win, fdf.buf.img, 0, 0);
	mlx_loop(fdf.id);
	return (0);
}

