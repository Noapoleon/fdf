/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:45:57 by nlegrand          #+#    #+#             */
/*   Updated: 2022/11/26 17:09:44 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	show_map(t_map *map); // remove later

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_nlgw	nlgw;
	t_map	map;

	errno = 0;
	nlgw_setup(&nlgw, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (parse_map(&map, av[1]) == -1)
	{
		nlgw_terminate(&nlgw);
		ft_dprintf(2, "[ERROR] Failed parsing map.\n");
		perror("parse_map");
		exit(EXIT_FAILURE);
	}
	show_map(&map);
	set_hooks(&nlgw);
	mlx_loop(nlgw.id);
	return (0);
}

void	show_map(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			ft_printf("%u ", (unsigned int)(map->m[y][x] & M_ZPOS));
			++x;
		}
		ft_putchar_fd('\n', 1);
		++y;
	}
}
