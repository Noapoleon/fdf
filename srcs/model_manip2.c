/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_manip2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:32:28 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/12 11:49:53 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	model_view_focus(t_fdf *fdf)
{
	fdf->view.zoom = 1.0;
	fdf->view.xmov = 0;
	fdf->view.ymov = 0;
	refresh_view_zoom(fdf);
	refresh_view_move(fdf);
	fdf->redraw = 1;
}
