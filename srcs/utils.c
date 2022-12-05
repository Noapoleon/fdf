/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:52:46 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/05 19:17:36 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_setup(t_fdf *fdf, int ac, char **av)
{
	if (ac != 2 && ac != 4)
		(ft_dprintf(2, USAGE, av[0]), exit(EXIT_FAILURE));
	fdf_zero_init(fdf);
	fdf->mlx = mlx_init();
	if (fdf->mlx == NULL)
		(ft_dprintf(2, MLX_ERROR), fdf_exit_failure());
	if (parse_map(fdf, av[1]) == -1)
		(fdf_terminate(fdf), ft_dprintf(2, MAP_ERROR), fdf_exit_failure());
	if (fdf_view_setup(fdf, ac, av) == -1) // might not need a return value here or even an if
		(fdf_terminate(fdf), ft_dprintf(2, VIEW_ERROR), fdf_exit_failure());
	if (fdf_win_setup(fdf) == -1) // change stuff here for correct window size
		(fdf_terminate(fdf), ft_dprintf(2, WIN_ERROR), fdf_exit_failure());
}

// DO LATER
int	fdf_view_setup(t_fdf *fdf, int ac, char **av)
{
	(void)fdf;
	(void)ac;
	(void)av;
	return (0);
}

// sets up the window size according the previously defined size to fit map
int	fdf_win_setup(t_fdf *fdf)
{
	fdf->win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE); // CHANGE THIS to fit screen to map size (up to a maximum WIN_MAX_WIDTH)
	if (fdf->win == NULL)
		return (-1);
	return (0);
}
