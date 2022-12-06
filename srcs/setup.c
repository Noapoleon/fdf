/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:52:46 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/06 15:30:13 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Gives default values to all fdf struct attributes
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
	if (fdf_view_setup(fdf, ac, av) == -1)
		(fdf_terminate(fdf), ft_dprintf(2, VIEW_ERROR), fdf_exit_failure());
	if (fdf_win_setup(fdf) == -1)
		(fdf_terminate(fdf), ft_dprintf(2, WIN_ERROR), fdf_exit_failure());
	if (fdf_img_setup(fdf) == -1)
		(fdf_terminate(fdf), ft_dprintf(2, IMG_ERROR), fdf_exit_failure());
}

// Sets the view struct for matrix multiplication later
int	fdf_view_setup(t_fdf *fdf, int ac, char **av)
{
	(void)ac;
	(void)av;
	// STATIC VALUES HERE, CHANGE LATER
	// CHECK IF THERE'S A NEED TO RETURN -1

	set_vector_3d(fdf->view.i, 1.0, 0.0, 0.0);
	set_vector_3d(fdf->view.j, 0.0, 1.0, 0.0);
	set_vector_3d(fdf->view.k, 0.0, 0.0, 1.0);
	fdf->view.xoff = WIN_WIDTH / 2;
	fdf->view.yoff = WIN_HEIGHT / 2;
	fdf->view.c_size = 20;
	fdf->view.z_size = 1;
	fdf->view.zoom = 0.0;
	return (0);
}

// Sets up the window size according the previously defined size to fit map
int	fdf_win_setup(t_fdf *fdf)
{
	// CHANGE THIS WHEN VIEW_SETUP IS DONE
	fdf->wwidth = WIN_WIDTH;
	fdf->wheight = WIN_HEIGHT;
	fdf->win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE); // CHANGE THIS to fit screen to map size (up to a maximum WIN_MAX_WIDTH)
	if (fdf->win == NULL)
		return (-1);
	return (0);
}

int	fdf_img_setup(t_fdf *fdf)
{
	// CHANGE IMAGE RESOLUTION TO DYNAMIC STUFF
	fdf->img.img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (fdf->img.img == NULL)
		return (-1);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bpp, &fdf->img.ll,
			&fdf->img.endian);
	if (fdf->img.addr == NULL)
		return (-1);
	return (0);
}
