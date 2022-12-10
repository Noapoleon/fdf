/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:02:44 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/10 18:22:53 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Exits mlx_loop if escape key is pressed
int	key_press_h(int keycode, t_fdf *fdf)
{
	if (keycode == 'r')
		model_rotate(fdf, 1);
	else if (keycode == 'e')
		model_rotate(fdf, -1);
	else if (keycode == 'f')
		model_flatten(fdf);
	else if (keycode == '1' || keycode == '2')
		model_set_proj(fdf, keycode);
	else if (keycode == KEY_ESC)
	{
		fdf_terminate(fdf);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	mouse_press_h(int button, int x, int y, t_fdf *fdf)
{
	if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
		model_zoom(fdf, button);
	else if (button == MOUSE_LEFT)
	{
		fdf->view.move = 1;
		fdf->view.mov_start[0] = x;
		fdf->view.mov_start[1] = y;
	}
//	else if (button == MOUSE_RIGHT)
//	{
//		fdf->view.rotate = 1;
//		fdf->view.rot_start[0] = x;
//		fdf->view.rot_start[1] = y;
//	}
	return (0);
}

int	mouse_release_h(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (button == MOUSE_LEFT)
		fdf->view.move = 0;
//	if (button == MOUSE_RIGHT)
//		fdf->view.rotate = 0;
	return (0);
}

int	mouse_move_h(int x, int y, t_fdf *fdf)
{
	if (fdf->view.move)
		model_move(fdf, x, y);
//	if (fdf->view.rotate)
//		model_rotate(fdf, x, y);
	return (0);
}
