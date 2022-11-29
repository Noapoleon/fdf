/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:45:57 by nlegrand          #+#    #+#             */
/*   Updated: 2022/11/29 20:58:28 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	t_fdf		fdf;
	t_map		map;

	errno = 0;
	fdf_setup(&fdf, ac, av, &map);
	set_hooks(&fdf);

	// TESTS //
	//show_map(&map);
	//line_test(&fdf);
	//map_lines_test(&fdf);
	// ----- //

	mlx_loop(fdf.id);
	return (0);
}

