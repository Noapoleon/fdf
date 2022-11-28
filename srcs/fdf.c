/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:45:57 by nlegrand          #+#    #+#             */
/*   Updated: 2022/11/28 21:26:11 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	t_fdf		fdf;
	t_window	win;
	t_map		map;

	errno = 0;
	if (ac < 2)
		return (ft_printf("Usage: %s <filename>\n", av[0]), 0);
	if (parse_map(&map, av[1]) == -1)
		return (ft_dprintf(2, "[ERROR] Failed to parse map.\n", 0));
	win_init(&win, WIN_WIDTH, WIN_HEIGHT, av[1]);
	fdf_setup(&fdf, &win, &map);
//	if (parse_map(&map), av[1]) == -1)
//		return (ft_dprintf(2, "[ERROR] Failed to parse map.\n"), 0);
//	nlgw_setup(&nlgw, &window, &map);
	ft_printf("WIN_WIDTH -> %d\n", WIN_WIDTH);
	ft_printf("WIN_HEIGHT -> %d\n", WIN_HEIGHT);
	set_hooks(&fdf);
	show_map(&map);
	line_test(&fdf);


	// line testing //
	// straight
	//plot_line(&nlgw, 400, 300, 500, 300);
	//plot_line(&nlgw, 400, 300, 300, 300);
	//plot_line(&nlgw, 400, 300, 400, 200);
	//plot_line(&nlgw, 400, 300, 400, 400);
	//// 45 degree
	//plot_line(&nlgw, 400, 300, 500, 200);
	//plot_line(&nlgw, 400, 300, 500, 400);
	//plot_line(&nlgw, 400, 300, 300, 400);
	//plot_line(&nlgw, 400, 300, 300, 200);
	// ------------ //

	mlx_loop(fdf.id);
	return (0);
}
