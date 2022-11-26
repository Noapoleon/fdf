/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 15:00:22 by nlegrand          #+#    #+#             */
/*   Updated: 2022/11/26 16:43:38 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// parses the line
t_list	*parse_line(t_map *map, const char *line)
{
	t_list	*tmp;
	char	**arr;
	int		i;

	arr = ft_split(line, ' ');
	tmp = malloc(sizeof(t_list));
	if (arr == NULL || tmp == NULL)
		return (free(arr), free(tmp),
		ft_dprintf(2, "[ERROR] parse_line: Malloc failed.\n"), NULL);
	if (map->width == 0)
		map->width = get_map_width(arr);
	tmp->content = malloc(sizeof(unsigned long) * map->width);
	if (tmp->content == NULL)
		return (free(arr), free(tmp),
		ft_dprintf(2, "[ERROR] parse_line: Malloc failed.\n"), NULL);
	i = 0;
	while (arr[i] && i < map->width)
	{
		if (parse_vertex(arr[i], &(tmp->content)[i]) == -1)
			return (free(arr), ft_lstdelone(tmp, free), NULL);
		++i;
	}
	if (i < map->width || arr[i] != NULL)
		return (free(arr), ft_lstdelone(tmp, free),
		ft_dprintf(2, "[ERROR] parse_line: Wrong width line.\n"), NULL);
	return (free(arr), tmp);
}

int	parse_vertex(char *s, unsigned long *vertex)
{
	*vertex = 0;
	*vertex |= ft_atoi(s);
	s += (*s == '-');
	if (!ft_isdigit(*s))
		return (ft_dprintf(2, "[ERROR] Bad map format height.\n"), -1);
	while (*s && ft_isdigit(*s))
			++s;
	if (*s != ',' && *s != '\0' && *s != '\n')
		return (ft_dprintf(2, "[ERROR] Bad map format separator.\n"), -1);
	if (ft_strnstr(s, ",0x", 3))
	{
		if (*(s + 3) == '\0' || !ft_strchr(HEX_SET, *(s + 3)))
			return (ft_dprintf(2, "[ERROR] Bad map format color.\n"), -1);
		*vertex |= ((unsigned long)hextoui(s + 3) << (sizeof(int) * 8));
		s += 3;
		while (*s && ft_strchr(HEX_SET, *s))
			++s;
	}
	if (*s != '\0' && *s != '\n')
		return (ft_dprintf(2, "[ERROR] Bad map format width.\n"), -1);
	return (0);
}

int	get_map_width(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		++i;
	return (i);
}

unsigned int hextoui(char *s)
{
	unsigned int	x;
	char			*i;

	x = 0;
	i = ft_strchr(HEX_SET, *s);
	while (*s && i)
	{
		x = x * 16 + (i - HEX_SET);
		++s;
		i = ft_strchr(HEX_SET, *s);
	}
	return (x);
}

void	cap_hex(char *s)
{
	while (*s)
	{
		if (*s >= 'a' && *s <= 'f')
			*s -= 32;
		++s;
	}
}
