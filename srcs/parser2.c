/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:31:36 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/09 15:44:16 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Similar to count_words from ft_split but simpler since we already know the
// separator
int	count_vertices(char *line)
{
	int	i;

	while (*line && *line == ' ')
		++line;
	i = 0;
	while (*line && *line != '\n')
	{
		while (*line && *line == ' ')
			++line;
		++i;
		while (*line && *line != ' ')
			++line;
		while (*line && *line == ' ')
			++line;
	}
	return (i);
}

// Sets the color attribute of t_vertex during parsing
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
