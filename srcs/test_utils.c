/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:40:01 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/03 22:17:05 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

# include <time.h>

void	show_map(t_fdf *fdf)
{
	int x;
	int y;

	y = 0;
	ft_printf("map->width -----> %d\n", fdf->mwidth);
	ft_printf("map->height ----> %d\n", fdf->mheight);
	ft_printf("map->cs --------> %d\n", fdf->csize);
	ft_printf("map->zs --------> %d\n", fdf->zsize);
	while (y < fdf->mheight)
	{
		x = 0;
		while (x < fdf->mwidth)
		{
			ft_printf("%d[%d;%d] ", fdf->vs[y][x].z, fdf->vs[y][x].x, fdf->vs[y][x].y);
			++x;
		}
		ft_printf("\n");
		++y;
	}
}

void	map_dots_test(t_fdf *fdf)
{
	int x;
	int y;

	y = 0;
	while (y < fdf->mheight)
	{
		x = 0;
		while (x < fdf->mwidth)
		{
			mlx_pixel_put(fdf->id, fdf->win, fdf->vs[y][x].x, fdf->vs[y][x].y, 0x00ff0000);
			++x;
		}
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
	if (x != fdf->mwidth - 1)
		plot_line(fdf, &fdf->vs[y][x], &fdf->vs[y][x + 1]);
	if (y != fdf->mheight - 1)
		plot_line(fdf, &fdf->vs[y][x], &fdf->vs[y + 1][x]);
}

void	calc_coords(t_fdf *fdf)
{
	int	x;
	int	y;
	int	tmp;

	y = 0;
	while (y < fdf->mheight)
	{
		x = 0;
		while (x < fdf->mwidth)
		{
			fdf->vs[y][x].x = x * fdf->csize + fdf->xoff;
			fdf->vs[y][x].y = y * fdf->csize + fdf->yoff;
			fdf->vs[y][x].x -= WIN_WIDTH / 2;
			fdf->vs[y][x].y -= WIN_HEIGHT / 2;
			tmp = fdf->vs[y][x].x;
			//fdf->vs[y][x].x = fdf->mtr[0] * tmp + fdf->mtr[1] * fdf->vs[y][x].y;
			//fdf->vs[y][x].y = fdf->mtr[2] * tmp + fdf->mtr[3] * fdf->vs[y][x].y;
			//fdf->vs[y][x].y *= 0.5;
			//fdf->vs[y][x].x += WIN_WIDTH / 2;
			//fdf->vs[y][x].y += WIN_HEIGHT / 2 - fdf->vs[y][x].z * fdf->zsize;
			++x;
		}
		++y;
	}
}

void	map_lines_test(t_fdf *fdf)
{
	int	x;
	int	y;

	calc_coords(fdf);
//	map_dots_test(fdf);

	//show basic map
	y = 0;
	while (y < fdf->mheight)
	{
		x = 0;
		while (x < fdf->mwidth)
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
//	const int	def[4]= {1, 0, 1, 0};
//	const int	rot[4]= {1, -1, 1, 1};
	t_vertex v0;
	t_vertex v1;

	v0.x = 600;
	v0.y = 600;
	v0.c = 0x0000ff00;
	
	v1.x = 0;
	v1.y = 0;
	v1.c = 0x000000ff;
	while (v1.x < 1200)
	{
		plot_line(fdf, &v0, &v1);
//		mlx_pixel_put(fdf->id, fdf->win, v1.x, v1.y, 0x0000ff00);
		++(v1.x);
//		usleep(1000);
	}
	while (v1.y < 1200)
	{
		plot_line(fdf, &v0, &v1);
//		mlx_pixel_put(fdf->id, fdf->win, v1.x, v1.y, 0x0000ff00);
		++(v1.y);
//		usleep(1000);
	}
	while (v1.x > 0)
	{
		plot_line(fdf, &v0, &v1);
//		mlx_pixel_put(fdf->id, fdf->win, v1.x, v1.y, 0x0000ff00);
		--(v1.x);
//		usleep(1000);
	}
	while (v1.y > 0)
	{
		plot_line(fdf, &v0, &v1);
//		mlx_pixel_put(fdf->id, fdf->win, v1.x, v1.y, 0x0000ff00);
		--(v1.y);
//		usleep(1000);
	}
//	mlx_pixel_put(fdf->id, fdf->win, v0.x, v0.y, 0x00ff0000);

}
