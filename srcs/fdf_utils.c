/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 21:12:00 by nlegrand          #+#    #+#             */
/*   Updated: 2022/11/25 23:22:09 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	set_hooks(t_nlgw *nlgw)
{
	mlx_key_hook(nlgw->window, &key_hook, nlgw);
	return (0);
}

int	key_hook(int keycode, void *nlgw)
{
	if (keycode == K_ESCAPE)
	{
		nlgw_terminate(nlgw);
		exit(EXIT_SUCCESS);
	}
	return (0);
}
