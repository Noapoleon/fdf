/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 01:56:49 by nlegrand          #+#    #+#             */
/*   Updated: 2022/11/30 22:51:19 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	count_vertices(char *line)
{
	int	i;

	while (*line && *line == ' ')
		++line;
	i = 0;
	while (*line)
	{
		++i;
		while (*line && *line != ' ')
			++line;
		while (*line && *line == ' ')
			++line;
	}
	return (i);
}

void	set_color(t_vertex *vertex, char **line)
{
	unsigned int	x;
	char			*s;

	s = *line + 3;
	x = 0;
	while (*s && ((*s >= '0' && *s <= '9') || (*s >= 'a' && *s <= 'f')
			|| (*s >= 'A' && *s <= 'F')))
	{
		*s += (*s >= 'A' && *s <= 'F') * 32;
		x = x * 16 + ((ft_strchr(HEX_SET, *s) - HEX_SET));
		++s;
	}
	vertex->c = x & M_COL;
	*line = s;
}

// Frees the 2D array of the map struct
void	destroy_map(t_fdf *fdf)
{
	int	y;

	y = 0;
	while (y < fdf->mheight)
		free(fdf->vs[y++]);
	free(fdf->vs);
}

void	do_nothing(void *ptr)
{
	(void)ptr;
}
