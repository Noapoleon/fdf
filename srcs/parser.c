/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 10:35:44 by nlegrand          #+#    #+#             */
/*   Updated: 2022/11/28 20:42:48 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Reads the map and fills map struct with a 2D array.
int	parse_map(t_map *map, char *path)
{
	t_list	*lines;

	map->fd = open(path, O_RDONLY);
	if (map->fd == -1)
		return (ft_dprintf(2, "[ERROR] Failed to open map.\n"), -1);
	lines = NULL;
	if (parse_map_lines(map, &lines) == -1)
	{
		ft_dprintf(2, "[ERROR] Failed to read map.\n");
		return (ft_lstclear(&lines, &free), -1);
	}
	if (fill_map(map, lines) == -1)
	{
		ft_lstclear(&lines, &free);
		return (ft_dprintf(2, "[ERROR] Failed to fill map.\n"), -1);
	}
	ft_lstclear(&lines, do_nothing);
	return (0);
}

// Reads the map line by line growing the chained list and calculates the map's
// height.
int	parse_map_lines(t_map *map, t_list **lines)
{
	char	*line;
	t_list	*tmp;

	map->width = 0;
	map->height = 0;
	while (1)
	{
		line = get_next_line(map->fd);
		if (line == NULL)
			break ;
		tmp = ft_lstnew(NULL);
		if (tmp == NULL)
			return (ft_dprintf(2, "[ERROR] Failed tmp malloc.\n")
				, free(line), -1);
		if (parse_line(map, tmp, line) == -1)
			return (ft_dprintf(2, "[ERROR] Failed to parse line #%d.\n"
					, map->height + 1), free(line), free(tmp), -1);
		ft_lstadd_front(lines, tmp);
		free(line);
		++(map->height);
	}
	return (0);
}

// Parses each vertex from the split map line and sets the first line's number
// of splits as the map's width. If subsequent map lines do not match this width
// it will be considered as bad map formatting and parsing will stop here.
int	parse_line(t_map *map, t_list *tmp, char *line)
{
	int			i;
	t_vertex	*varr;

	if (map->width == 0)
		map->width = count_vertices(line);
	varr = malloc(sizeof(t_vertex) * map->width);
	if (varr == NULL)
		return (ft_dprintf(2, "[ERROR] Failed to malloc vertex array."), -1);
	i = 0;
	while (*line && *line != '\n')
	{
		while (*line == ' ')
			++line;
		varr[i].x = i;
		varr[i].y = map->height;
		varr[i].z = ft_atoi(line);
		while (*line == '-' || (*line >= '0' && *line <= '9'))
			++line;
		varr[i].c = 0;
		if (*line == ',')
			set_color(varr + i, &line);
		++i;
	}
	tmp->content = varr;
	return (0);
}

// Creates the 2D array from the chained list.
int	fill_map(t_map *map, t_list *lines)
{
	t_list	*curr;
	int		height;

	map->vs = malloc(sizeof(t_vertex *) * map->height);
	if (map->vs == NULL)
		return (ft_dprintf(2, "[ERROR] Failed to malloc map->m.\n"), -1);
	height = map->height;
	curr = lines;
	while (height--)
	{
		map->vs[height] = curr->content;
		curr = curr->next;
	}
	return (0);
}
