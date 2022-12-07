/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <nlegrand@stud.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 21:54:41 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/07 21:26:51 by nlegrand         ###   ########.fr       */
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
	set_vector_3d(fdf->view.i, 1.0, 0.0, 0.0);
	set_vector_3d(fdf->view.j, 0.0, 1.0, 0.0);
	set_vector_3d(fdf->view.k, 0.0, 0.0, 1.0);
	fdf->view.xoff = 0;
	fdf->view.yoff = 0;
	fdf->view.xmov = 0;
	fdf->view.ymov = 0;
	fdf->view.moving = 0;
	fdf->view.cs_og = 0;
	fdf->view.zs_og = 0;
	fdf->view.cs = 0;
	fdf->view.zs = 0;
	fdf->view.map_xcenter = 0;
	fdf->view.map_ycenter = 0;
	fdf->view.zoom = 1.0;
	fdf->img.img = NULL;
	fdf->img.addr = NULL;
	fdf->img.bpp = 0;
	fdf->img.ll = 0;
	fdf->img.endian = 0;
	fdf->wtitle = NULL;
	fdf->wwidth = 0;
	fdf->wheight = 0;
	fdf->mwidth = 0;
	fdf->mheight = 0;
	fdf->redraw = 1;
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

// exits the program and printf and error context message
void	fdf_exit_failure(void)
{
	perror("[EXIT] fdf_setup()");
	exit(EXIT_FAILURE);
}

// does nothing :)
// used with ft_lstclear so that it won't free the content
void	do_nothing(void *ptr)
{
	(void)ptr;
}
