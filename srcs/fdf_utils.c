/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 21:12:00 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/01 18:01:27 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_setup(t_fdf *fdf, int ac, char **av)
{
	if (ac != 2 && ac != 4)
	{
		ft_printf(USAGE, av[0]);
		exit(EXIT_FAILURE);
	}
	fdf->id = mlx_init();
	if (fdf->id == NULL)
		(perror("fdf_setup[fdf init]"), exit(EXIT_FAILURE));
	if (parse_map(fdf, av[1]) == -1)
		(perror("fdf_setup[map]"), exit(EXIT_FAILURE));
	fdf->win = mlx_new_window(fdf->id, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (fdf->win == NULL)
		(perror("fdf_setup[win]"), exit(EXIT_FAILURE));
	set_fdf_options(fdf, ac, av);
	fdf->buf.img = mlx_new_image(fdf->id, fdf->wwidth, fdf->wheight);
	fdf->buf.addr = mlx_get_data_addr(fdf->buf.img, &(fdf->buf.bpp),
			&(fdf->buf.ll), &(fdf->buf.endian));
}

void set_fdf_options(t_fdf *fdf, int ac, char **av)
{
	set_fdf_defaults(fdf);
	if (ac == 4)
	{
		fdf->csize = ft_atoi(av[2]);
		fdf->zsize = ft_atoi(av[3]);
		if (fdf->csize <= 0)
			fdf->csize = WIN_WIDTH / fdf->mwidth;
	}
}

void	set_fdf_defaults(t_fdf *fdf)
{
	fdf->wwidth = WIN_WIDTH;
	fdf->wheight = WIN_HEIGHT;
	fdf->csize = 20;
	if (fdf->csize * fdf->mwidth > WIN_WIDTH)
		fdf->csize = WIN_WIDTH / fdf->mwidth;
	// IF DEFAULT CELL SIZE OF 20 WILL CLIP MAP ON THE Y AXIS IS NEEDS TO BE
	// ADJUSTED (ACTUALLY MAYBE NOT SOME MAPS ARE CUT OFF ON THE FDF EXE FROM
	// THE INTRA)
	// IT LOOKS LIKE THE CS IS ALSO ADJUSTED BASED ON THE SIZE OF THE MAP
	// ALSO THE BOTTOM CORNER LOOKS LIKE IT'S ALWAYS AT THE BOTTOM OF THE SCREEN
	fdf->zsize = fdf->csize;
	// -1 of some sort to be done here, if not is will be slightly off center
	fdf->xoff = fdf->wwidth / 2 - (fdf->mwidth - 1) * fdf->csize / 2;
	fdf->yoff = fdf->wheight / 2 - (fdf->mheight - 1) * fdf->csize / 2;
	fdf->wwidth = WIN_WIDTH;
	fdf->wheight = WIN_HEIGHT;
	// OMFG THE WINDOW WIDTH AND SIZE ARE ALSO CHANGED BASED ON THE MAP UP
	// TO A CERTAIN POINT
	// UPON FURTHER TESTING IT LOOKS LIKE THE WINDOW SIZE IS DETERMINED BY THE
	// BY SIZE THE MAP WILL TAKE WITH ITS DEFAULT SETTINGS (which change
	// depending on the map)
	fdf->title = WIN_TITLE;

	fdf->mtr[0] = M_SQRT1_2;
	fdf->mtr[1] = M_SQRT1_2;
	fdf->mtr[2] = -M_SQRT1_2;
	fdf->mtr[3] = M_SQRT1_2;


	// event the intra's example fdf executable has weird behavior and window
	// default sizing so let's establish some rules of our own
	// - window width and size will be set so that it fits the model entirely
	// - if the window resizing will be too big (define too big) for the screen
	//   limit at an arbitrary resolution but still center the model
}


void	terminate_fdf(t_fdf *fdf)
{
	mlx_destroy_window(fdf->id, fdf->win);
	destroy_map(fdf);
}

int	abso(int a)
{
	if (a >= 0)
		return (a);
	return (-a);
}

