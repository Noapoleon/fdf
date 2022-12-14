/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:52:46 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/14 03:54:31 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Gives default values to all fdf struct attributes
void	fdf_setup(t_fdf *fdf, int ac, char **av)
{
	if (ac != 2 && ac != 4)
		(ft_printf(USAGE, av[0]), exit(EXIT_FAILURE));
	fdf_vars_init(fdf);
	fdf->mlx = mlx_init();
	if (fdf->mlx == NULL)
		(ft_dprintf(2, MLX_ERROR), fdf_exit_failure());
	if (parse_map(fdf, av[1]) == -1)
		(fdf_terminate(fdf), ft_dprintf(2, MAP_ERROR), fdf_exit_failure());
	map_relative_height(fdf);
	if (fdf_win_setup(fdf) == -1)
		(fdf_terminate(fdf), ft_dprintf(2, WIN_ERROR), fdf_exit_failure());
	if (fdf_view_setup(fdf, ac, av) == -1)
		(fdf_terminate(fdf), ft_dprintf(2, VIEW_ERROR), fdf_exit_failure());
	if (fdf_img_setup(fdf) == -1)
		(fdf_terminate(fdf), ft_dprintf(2, IMG_ERROR), fdf_exit_failure());
}

// Sets up the window size according the previously defined size to fit map
int	fdf_win_setup(t_fdf *fdf)
{
	mlx_get_screen_size(fdf->mlx, &fdf->wwidth, &fdf->wheight);
	fdf->wwidth -= 50;
	fdf->wheight -= 50;
	if (fdf->wwidth > WIN_MAX_WIDTH)
		fdf->wwidth = WIN_MAX_WIDTH;
	if (fdf->wheight > WIN_MAX_HEIGHT)
		fdf->wheight = WIN_MAX_HEIGHT;
	fdf->win = mlx_new_window(fdf->mlx, fdf->wwidth, fdf->wheight, WIN_TITLE);
	if (fdf->win == NULL)
		return (-1);
	return (0);
}

// Sets the view struct for matrix multiplication later
int	fdf_view_setup(t_fdf *fdf, int ac, char **av)
{
	fdf->view.ri = -4.0;
	fdf->view.relief = 1;
	fdf->view.zoom = 1.0;
	fdf->view.cs_og = 20;
	if (fdf->view.cs_og * fdf->mwidth > fdf->wwidth)
		fdf->view.cs_og = (fdf->wwidth * 0.8) / fdf->mwidth;
	fdf->view.cs_og += (fdf->view.cs_og == 0);
	fdf->view.zs_og = fdf->view.cs_og;
	if (ac == 4)
	{
		fdf->view.cs_og = ft_atoi(av[2]);
		fdf->view.cs_og += (fdf->view.cs_og <= 0);
		fdf->view.zs_og = ft_atoi(av[3]);
		fdf->view.zs_og += (fdf->view.zs_og == 0);
	}
	refresh_view_zoom(fdf);
	refresh_view_move(fdf);
	refresh_view_rotate(fdf);
	return (0);
}

// Safely creates an mlx image
int	fdf_img_setup(t_fdf *fdf)
{
	fdf->img.img = mlx_new_image(fdf->mlx, fdf->wwidth, fdf->wheight);
	if (fdf->img.img == NULL)
		return (-1);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bpp, &fdf->img.ll,
			&fdf->img.endian);
	if (fdf->img.addr == NULL)
		return (-1);
	return (0);
}
