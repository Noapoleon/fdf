/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:13:50 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/12 20:23:19 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Reads the map and fills map struct with a 2D array of t_vertex
int	parse_map(t_fdf *fdf, char *path)
{
	t_list	*lines;
	int		fd;

	if (open_map(&fd, path) == -1)
		return (ft_dprintf(2, MAP_FAIL_OPEN), -1);
	lines = NULL;
	if (parse_map_lines(fdf, fd, &lines) == -1)
	{
		close(fd);
		ft_dprintf(2, MAP_FAIL_READ);
		return (ft_lstclear(&lines, &free), -1);
	}
	if (fill_map(fdf, lines) == -1)
	{
		close(fd);
		ft_lstclear(&lines, &free);
		return (ft_dprintf(2, MAP_FAIL_FILL), -1);
	}
	close(fd);
	ft_lstclear(&lines, do_nothing);
	return (0);
}

// Opens the map file while checking some prerequisites like if the path points
// to an fdf map
int	open_map(int *fd, char *path)
{
	const size_t	path_len = ft_strlen(path);

	if (path_len < 4 || ft_strnstr(path + path_len - 4, ".fdf", 4) == NULL)
		return (ft_dprintf(2, MAP_FAIL_FDF), -1);
	*fd = open(path, O_DIRECTORY);
	if (*fd > -1)
		return (ft_dprintf(2, MAP_FAIL_DIR), -1);
	*fd = open(path, O_RDONLY);
	if (*fd < 0)
		return (ft_dprintf(2, MAP_FAIL_FD), -1);
	return (0);
}

// Reads the map line by line growing the chained list and calculates the map's
// height.
int	parse_map_lines(t_fdf *fdf, int fd, t_list **lines)
{
	char	*line;
	t_list	*tmp;

	fdf->mwidth = 0;
	fdf->mheight = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		tmp = ft_lstnew(NULL);
		if (tmp == NULL)
			return (ft_dprintf(2, MAP_FAIL_TMP), free(line), -1);
		if (parse_line(fdf, tmp, line) == -1)
			return (ft_dprintf(2, MAP_FAIL_LINE, fdf->mheight + 1),
				free(line), free(tmp), -1);
		ft_lstadd_front(lines, tmp);
		free(line);
		++(fdf->mheight);
	}
	return (0);
}

// Parses each vertex from the map line and sets the first line's number
// of vertices as the map's width.
// If subsequent map lines do not match this width it will be considered as bad
// map formatting and parsing will stop.
int	parse_line(t_fdf *fdf, t_list *tmp, char *line)
{
	int			i;
	t_vertex	*varr;

	if (fdf->mwidth == 0)
		fdf->mwidth = count_vertices(line);
	varr = malloc(sizeof(t_vertex) * fdf->mwidth);
	if (varr == NULL)
		return (ft_dprintf(2, MAP_FAIL_VERTEX), -1);
	i = 0;
	while (*line && *line != '\n')
	{
		while (*line == ' ')
			++line;
		varr[i].z = ft_atoi(line);
		while (*line == '-' || (*line >= '0' && *line <= '9'))
			++line;
		set_color(varr + i, &line);
		++i;
		while (*line && *line == ' ')
			++line;
	}
	return ((tmp->content = varr), 0);
}

// Creates the 2D array from the chained list
int	fill_map(t_fdf *fdf, t_list *lines)
{
	t_list	*curr;
	int		height;

	fdf->map = malloc(sizeof(t_vertex *) * fdf->mheight);
	if (fdf->map == NULL)
		return (ft_dprintf(2, MAP_FAIL_MAP), -1);
	height = fdf->mheight;
	curr = lines;
	while (height--)
	{
		fdf->map[height] = curr->content;
		curr = curr->next;
	}
	return (0);
}
