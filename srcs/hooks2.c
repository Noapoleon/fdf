/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:02:44 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/13 00:42:28 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Binds keypresses to functions
int	key_press_h(int keycode, t_fdf *fdf)
{
	if (keycode == 'r')
		model_relief(fdf);
	else if (keycode == 'f')
		model_view_focus(fdf);
	else if (keycode == 'h')
		model_toggle_height(fdf);
	else if (keycode != 0 && ft_strchr("wsik", keycode))
		model_scale_amp(fdf, keycode);
	else if (keycode >= '1' && keycode <= '3')
		model_set_proj(fdf, keycode);
	else if (keycode == KEY_ESC)
	{
		fdf_terminate(fdf);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

// Uses move movements and clicks to enable movement and rotation modes
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
	else if (button == MOUSE_RIGHT)
	{
		fdf->view.rotate = 1;
		fdf->view.rot_start = x;
	}
	return (0);
}

// Disables rotation and movement modes when the buttons are released
int	mouse_release_h(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (button == MOUSE_LEFT)
		fdf->view.move = 0;
	if (button == MOUSE_RIGHT)
		fdf->view.rotate = 0;
	return (0);
}

// Captures mouse coordinates and updates variables in view struct for movement
// and rotation
int	mouse_move_h(int x, int y, t_fdf *fdf)
{
	if (fdf->view.move)
		model_move(fdf, x, y);
	if (fdf->view.rotate)
		model_rotate(fdf, x);
	return (0);
}
