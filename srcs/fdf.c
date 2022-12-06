/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:41:28 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/06 15:59:23 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Unimportant function
int	main(int ac, char **av)
{
	t_fdf	fdf;

	errno = 0;
	fdf_setup(&fdf, ac, av);
	set_hooks(&fdf);

	//bres_grad_test(&fdf);
	dot_test(&fdf);

	mlx_loop(fdf.mlx);
	return (0);
}
