/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 19:39:05 by nlegrand          #+#    #+#             */
/*   Updated: 2022/11/28 21:56:03 by nlegrand         ###   ########.fr       */
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
#ifndef WIN_WIDTH
 #define WIN_WIDTH 800
#endif
#ifndef WIN_HEIGHT
 #define WIN_HEIGHT 800
#endif
#ifndef WIN_TITLE
 #define WIN_TITLE "Test window"
#endif

// Key IDs
# define K_ESCAPE	0xff1b

// Vertex Bit Masks
#define M_COL	0x00ffffff
#define M_COLR	0x00ff0000
#define M_COLG	0x0000ff00
#define M_COLB	0x000000ff
#define HEX_SET	"0123456789abcdef"

typedef struct s_fdf	t_fdf;
typedef struct s_window t_window;
typedef struct s_map	t_map;
typedef struct s_vertex	t_vertex;

struct s_fdf
{
	void		*id;
	t_window	*win;
	t_map		*map;
};
struct s_window
{
	void	*id;
	char	*title;
	int		width;
	int		height;
};
struct s_map
{
	int			fd;
	int			width;
	int			height;
	t_vertex	**vs;
};
// OMFG IM SO FUCKING STUPID I FORGOT TO STORE THE X AND Y TOOO (maybe i don't need to actually, we'll see)
// ALSO COLOR SHOULD BE STORED AS AN INT
struct s_vertex
{
	int x;
	int y;
	int	z;
	int	c;
};

// FDF UTILS
void	fdf_setup(t_fdf *fdf, t_window *win, t_map *map);
void	win_init(t_window *win, int width, int height, char *title);
void	fdf_terminate(t_fdf *fdf);

// HOOK UTILS
int		set_hooks(t_fdf *fdf);
int		key_hook(int keycode, void *param);

// PARSER
int		parse_map(t_map *map, char *path);
int		parse_map_lines(t_map *map, t_list **lines);
int		parse_line(t_map *map, t_list *tmp, char *line);
int		fill_map(t_map *map, t_list *lines);

// PARSER 2
int		count_vertices(char *line);
void	set_color(t_vertex *vertex, char **line);
void	destroy_map(t_map *map);
void	do_nothing(void *ptr);

// BRESENHAM
void	plot_line(t_fdf *fdf, t_vertex v0, t_vertex v1);
void	plot_line_low(t_fdf *fdf, t_vertex *v0, t_vertex *v1);
void	plot_line_high(t_fdf *fdf, t_vertex *v0, t_vertex *v1);
int		abso(int x);

// TEST UTILS
void	show_map(t_map *map);
void	line_test(t_fdf *fdf);

#endif
