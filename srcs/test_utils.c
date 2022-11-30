/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:40:01 by nlegrand          #+#    #+#             */
/*   Updated: 2022/11/30 00:47:56 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	show_map(t_map *map)
{
	int x;
	int y;

	y = 0;
	ft_printf("map->width -----> %d\n", map->width);
	ft_printf("map->height ----> %d\n", map->height);
	ft_printf("map->cs --------> %d\n", map->cs);
	ft_printf("map->zs --------> %d\n", map->zs);
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			ft_printf("%d[%d;%d] ", map->vs[y][x].z, map->vs[y][x].x, map->vs[y][x].y);
			++x;
		}
		ft_printf("\n");
		++y;
	}
}

//typedef struct s_matrix t_matrix;
//struct s_matrix
//{
//	int	i;
//	int j;
//};

void	plot_neighbours(t_fdf *fdf, int x, int y)
{
	t_vertex	v1;
	t_vertex	v2;

	(void)v2;
	v1.x = x * fdf->map->cs + fdf->map->xoff;
	v1.y = y * fdf->map->cs + fdf->map->yoff;
//	v1.x = x * fdf->map->cs + fdf->width / 2;
//	v1.y = y * fdf->map->cs + fdf->height / 2;

	mlx_pixel_put(fdf->id, fdf->win, v1.x, v1.y, 0x00ffffff);
}

void	map_lines_test(t_fdf *fdf)
{
//	const t_matrix iso = {
//	const int	def[4]= {1, 0, 1, 0};
//	const int	rot[4]= {1, -1, 1, 1};
	int				x;
	int				y;

	//show basic map
	y = 0;
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			plot_neighbours(fdf, x, y);
			++x;
		}
		++y;
	}
}

void	line_test(t_fdf *fdf)
{
	t_vertex v0;
	t_vertex v1;

	v0.x = 400;
	v0.y = 400;
	
	v1.x = 200;
	v1.y = 200;
	while (v1.x < 600)
	{
		plot_line(fdf, v0, v1);
		mlx_pixel_put(fdf->id, fdf->win, v1.x, v1.y, 0x0000ff00);
		++(v1.x);
//		usleep(1000);
	}
	while (v1.y < 600)
	{
		plot_line(fdf, v0, v1);
		mlx_pixel_put(fdf->id, fdf->win, v1.x, v1.y, 0x0000ff00);
		++(v1.y);
//		usleep(1000);
	}
	while (v1.x > 200)
	{
		plot_line(fdf, v0, v1);
		mlx_pixel_put(fdf->id, fdf->win, v1.x, v1.y, 0x0000ff00);
		--(v1.x);
//		usleep(1000);
	}
	while (v1.y > 200)
	{
		plot_line(fdf, v0, v1);
		mlx_pixel_put(fdf->id, fdf->win, v1.x, v1.y, 0x0000ff00);
		--(v1.y);
//		usleep(1000);
	}
	mlx_pixel_put(fdf->id, fdf->win, v0.x, v0.y, 0x00ff0000);
}
