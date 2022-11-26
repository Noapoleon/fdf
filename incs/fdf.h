/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 19:39:05 by nlegrand          #+#    #+#             */
/*   Updated: 2022/11/26 16:14:29 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/stat.h>
# include <fcntl.h>

// Window Settings
#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define WIN_TITLE "Test window"

// Key IDs
# define K_ESCAPE	0xff1b

// Vertex Bit Masks
# define M_ZPOS	0x00000000ffffffff
# define M_COL	0xffffffff00000000
# define M_COLR	0xff00000000000000
# define M_COLG	0x00ff000000000000
# define M_COLB	0x0000ff0000000000
# define M_COLA	0x000000ff00000000
# define HEX_SET	"0123456789ABCDEF"

typedef struct s_nlgw	t_nlgw;
typedef struct s_map	t_map;
typedef struct s_vertex	t_vertex;
struct s_nlgw
{
	void	*id;
	void	*window;
	int		width;
	int		height;
	char	*title;
};
struct s_map
{
	int				fd;
	int				width; // -1 by default ?? (for now it'll be 0)
	int				height;
	unsigned long	**m;
};
//struct s_vertex
//{
//	int z;
//	int col;
//};

// FDF UTILS
int		set_hooks(t_nlgw *nlgw);
int		key_hook(int keycode, void *nlgw);

// NLGW
int		nlgw_setup(t_nlgw *nlgw, int width, int height, char *title);
void	nlgw_terminate(t_nlgw *nlgw);

// PARSER
int		parse_map(t_map *map, char *path);
int		read_map(t_map *map, char *path, t_list **lines);
int		fill_map(t_map *map, t_list **lines);

// PARSER 2
t_list			*parse_line(t_map *map, const char *line);
int				parse_vertex(char *s, unsigned long *vertex);
int				get_map_width(char **arr);
unsigned int	hextoui(char *s);
void			cap_hex(char *s);

#endif
