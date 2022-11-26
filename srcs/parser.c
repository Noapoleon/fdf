/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 23:30:07 by nlegrand          #+#    #+#             */
/*   Updated: 2022/11/26 16:16:57 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	parse_map(t_map *map, char *path)
{
	t_list	*lines;

	if (read_map(map, path, &lines) == -1)
		return (-1);
	if (fill_map(map, &lines) == -1)
		return (ft_lstclear(&lines, free), -1);
	return (0);
}

// reads the map at 'path' line by line and sets map height
int	read_map(t_map *map, char *path, t_list **lines)
{
	char	*line;
	t_list	*tmp;

	*lines = NULL;
	map->fd = open(path, O_RDONLY);
	if (map->fd == -1)
		return (ft_dprintf(2, "[ERROR] Failed to open map file.\n"), -1);
	map->width = 0;
	map->height = 0;
	while (1)
	{
		line = get_next_line(map->fd);
		if (line == NULL)
			break ;
		cap_hex(line);
		tmp = parse_line(map, line);
		if (tmp == NULL)
			return (ft_dprintf(2, "[ERROR] Failed parsing map line #%d.\n",
			map->height + 1), ft_lstclear(lines, free), -1);
		ft_lstadd_front(lines, tmp);
		++(map->height);
	}
	return (0);
}


int	fill_map(t_map *map, t_list **lines)
{
	t_list	*curr;
	int		h;

	map->m = malloc(sizeof(size_t **) * map->height); // fill map
	if (map->m == NULL)
		return (-1);
	curr = *lines;
	h = map->height;
	while (h--)
	{
		map->m[h] = curr->content;
		curr = curr->next;
	}
	ft_lstclear(lines, NULL); // probably won't work
	return (0);
}
