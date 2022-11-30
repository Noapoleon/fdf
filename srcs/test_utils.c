/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:40:01 by nlegrand          #+#    #+#             */
/*   Updated: 2022/11/30 02:01:20 by nlegrand         ###   ########.fr       */
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
	// vector below (higher value but coords reversed)
	t_vertex	v;
	t_vertex	vr;
	t_vertex	vd;

	v.x = x * fdf->map->cs + fdf->map->xoff;
	v.y = y * fdf->map->cs + fdf->map->yoff;
	vr.x = v.x + fdf->map->cs;
	vr.y = v.y;
	vd.x = v.x;
	vd.y = v.y + fdf->map->cs;

	plot_line(fdf, &v, &vr);
	plot_line(fdf, &v, &vd);
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
	while (y < fdf->map->height) // remove -1 later
	{
		x = 0;
		while (x < fdf->map->width) // remove -1 later
		{
			plot_neighbours(fdf, x, y);
			++x;
		}
		++y;
	}
}

void	line_test(t_fdf *fdf)
{
	// PROBABLY BROKE THIS TEST BY CHANGING v1 to &v1
	// and the definition of plot_line arguments
	t_vertex v0;
	t_vertex v1;

	v0.x = 400;
	v0.y = 400;
	
	v1.x = 200;
	v1.y = 200;
	while (v1.x < 600)
	{
		plot_line(fdf, &v0, &v1);
		mlx_pixel_put(fdf->id, fdf->win, v1.x, v1.y, 0x0000ff00);
		++(v1.x);
//		usleep(1000);
	}
	while (v1.y < 600)
	{
		plot_line(fdf, &v0, &v1);
		mlx_pixel_put(fdf->id, fdf->win, v1.x, v1.y, 0x0000ff00);
		++(v1.y);
//		usleep(1000);
	}
	while (v1.x > 200)
	{
		plot_line(fdf, &v0, &v1);
		mlx_pixel_put(fdf->id, fdf->win, v1.x, v1.y, 0x0000ff00);
		--(v1.x);
//		usleep(1000);
	}
	while (v1.y > 200)
	{
		plot_line(fdf, &v0, &v1);
		mlx_pixel_put(fdf->id, fdf->win, v1.x, v1.y, 0x0000ff00);
		--(v1.y);
//		usleep(1000);
	}
	mlx_pixel_put(fdf->id, fdf->win, v0.x, v0.y, 0x00ff0000);
}
