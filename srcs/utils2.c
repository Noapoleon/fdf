/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:14:52 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/05 19:20:21 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Initializes every variable of the fdf struct to avoid freeing the an
// uninitialized pointer with fdf_terminate
void	fdf_zero_init(t_fdf *fdf)
{
	fdf->mlx = NULL;
	fdf->win = NULL;
	fdf->map = NULL;
	fdf->view.x = 0.0;
	fdf->view.y = 0.0;
	fdf->view.z = 0.0;
	fdf->view.c_size = 0;
	fdf->view.z_size = 0;
	fdf->view.zoom = 0.0;
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
	if (fdf->img.img)
		mlx_destroy_image(fdf->mlx, fdf->img.img);
	if (fdf->win)
		mlx_destroy_window(fdf->mlx, fdf->win);
	if (fdf->mlx)
		mlx_destroy_display(fdf->mlx);
	if (fdf->map)
		fdf_destroy_map(fdf);
}

// exits the program and printf and error context message
void	fdf_exit_failure(void)
{
	perror("Error -> fdf_setup():");
	exit(EXIT_FAILURE);
}

// does nothing :)
// used with ft_lstclear so that it won't free the content
void	do_nothing(void *ptr)
{
	(void)ptr;
}
