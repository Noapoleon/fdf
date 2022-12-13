/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@stud.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 21:54:41 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/13 00:50:58 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Initializes every variable of the fdf struct to avoid freeing the an
// uninitialized pointer with fdf_terminate
void	fdf_vars_init(t_fdf *fdf)
{
	fdf->mlx = NULL;
	fdf->win = NULL;
	fdf->map = NULL;
	fdf->img.img = NULL;
	fdf->img.addr = NULL;
	fdf->img.bpp = 0;
	fdf->img.ll = 0;
	fdf->img.endian = 0;
	view_vars_init(&fdf->view);
	fdf->wtitle = NULL;
	fdf->wwidth = 0;
	fdf->wheight = 0;
	fdf->mwidth = 0;
	fdf->mheight = 0;
	fdf->mmin = 0;
	fdf->mmax = 0;
	fdf->redraw = 1;
}

// Puts every variable in view struct to default value
void	view_vars_init(t_view *view)
{
	view->calc_coords = &calc_iso_proj;
	set_vector_2d(view->i, 0.0, 0.0);
	set_vector_2d(view->j, 0.0, 0.0);
	view->xoff = 0;
	view->yoff = 0;
	view->move = 0;
	view->xmov = 0;
	view->ymov = 0;
	view->mov_start[0] = 0;
	view->mov_start[1] = 0;
	view->rotate = 0;
	view->rot_start = 0;
	view->ri = 0;
	view->amp = 1.0;
	view->cs_og = 0;
	view->zs_og = 0;
	view->cs = 0;
	view->zs = 0;
	view->map_xcenter = 0;
	view->map_ycenter = 0;
	view->zoom = 0.0;
	view->relief = 0;
	view->height = 0;
}

// Frees the 2D array map
void	fdf_destroy_map(t_fdf *fdf)
{
	int	y;

	y = 0;
	while (y < fdf->mheight)
		free(fdf->map[y++]);
	free(fdf->map);
}

// Frees everything and destroys mlx stuff
void	fdf_terminate(t_fdf *fdf)
{
	if (fdf->map)
		fdf_destroy_map(fdf);
	if (fdf->img.img)
		mlx_destroy_image(fdf->mlx, fdf->img.img);
	if (fdf->win)
		mlx_destroy_window(fdf->mlx, fdf->win);
	if (fdf->mlx)
	{
		mlx_destroy_display(fdf->mlx);
		free(fdf->mlx);
	}
}

// exits the program and printf an error context message
void	fdf_exit_failure(void)
{
	perror("[EXIT] fdf_setup()");
	exit(EXIT_FAILURE);
}
