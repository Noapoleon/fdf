/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:52:46 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/06 22:11:48 by nlegrand         ###   ########.fr       */
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
	// PROTECT FOR BAD RESOLUTIONS FOR DEFENSE (might already be protected by mlx_new_window but need to check)
	mlx_get_screen_size(fdf->mlx, &fdf->wwidth, &fdf->wheight);
	fdf->wwidth -= 50;
	fdf->wheight -= 50;
	if (fdf->wwidth > WIN_MAX_WIDTH)
		fdf->wwidth = WIN_MAX_WIDTH;
	if (fdf->wheight > WIN_MAX_HEIGHT)
		fdf->wheight = WIN_MAX_HEIGHT;
	// CHANGE THIS WHEN VIEW_SETUP IS DONE
	fdf->win = mlx_new_window(fdf->mlx, fdf->wwidth, fdf->wheight, WIN_TITLE);
	if (fdf->win == NULL)
		return (-1);
	return (0);
}

// Sets the view struct for matrix multiplication later
int	fdf_view_setup(t_fdf *fdf, int ac, char **av)
{
	// STATIC VALUES HERE, CHANGE LATER
	// CHECK IF THERE'S A NEED TO RETURN -1

	set_vector_3d(fdf->view.i, M_SQRT1_2, -M_SQRT1_2, 0.0); // Can probably do this in a subfunction that will also handle switching projection mode
	set_vector_3d(fdf->view.j, M_SQRT1_2, M_SQRT1_2, 0.0); // set_projection() or something
	set_vector_3d(fdf->view.k, 0.0, 0.0, 1.0);
	fdf->view.zoom = 1.0; // will be divided a lot when dezoomed so make sure to protect this
	fdf->view.cs = 20;
	fdf->view.zs = 1;
	if (ac == 4)
	{
		fdf->view.cs = atoi(av[2]);
		fdf->view.cs += (fdf->view.cs <= 0);
		fdf->view.zs = atoi(av[3]);
		fdf->view.zs += (fdf->view.zs  == 0);
	}
	if (fdf->view.cs * fdf->mwidth > fdf->wwidth) // only resizes based on map width, need to do height too (or not)
		fdf->view.cs = (fdf->wwidth * 0.8) / fdf->mwidth;
	fdf->view.cs += (fdf->view.cs == 0);
	//// CORRECT THIS
	fdf->view.xoff = fdf->wwidth / 2 - ((fdf->mwidth - 1) * fdf->view.cs) / 2; // does zoom have an impact here?
	fdf->view.yoff = fdf->wheight / 2 - ((fdf->mheight - 1) * fdf->view.cs) / 2;
	return (0);
}

int	fdf_img_setup(t_fdf *fdf)
{
	// CHANGE IMAGE RESOLUTION TO DYNAMIC STUFF
	fdf->img.img = mlx_new_image(fdf->mlx, fdf->wwidth, fdf->wheight);
	if (fdf->img.img == NULL)
		return (-1);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bpp, &fdf->img.ll,
			&fdf->img.endian);
	if (fdf->img.addr == NULL)
		return (-1);
	return (0);
}
