/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 19:39:05 by nlegrand          #+#    #+#             */
/*   Updated: 2022/11/30 23:49:09 by nlegrand         ###   ########.fr       */
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
# include <math.h>

// FDF Options
# define USAGE "Usage: %s <filename> [case_size z_size]\n"
# ifndef WIN_WIDTH
#  define WIN_WIDTH 1000
# endif
# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 800
# endif
# ifndef WIN_TITLE
#  define WIN_TITLE "Feel D'Oeux Faire"
# endif

// Key IDs
# define K_ESCAPE	0xff1b

// Vertex Bit Masks
#define M_COL	0x00ffffff
#define M_COLR	0x00ff0000
#define M_COLG	0x0000ff00
#define M_COLB	0x000000ff
#define HEX_SET	"0123456789abcdef"

typedef struct s_fdf	t_fdf;
typedef struct s_vertex	t_vertex;

struct s_fdf
{
	void		*id;
	void		*win;
	int			wwidth;
	int			wheight;
	char		*title;
	t_vertex	**vs;
	int			fd;
	int			mwidth;
	int			mheight;
	int			csize;
	int			zsize;
	int			xoff;
	int			yoff;
	double		mtr[4];
};
// OMFG IM SO FUCKING STUPID I FORGOT TO STORE THE X AND Y TOOO (maybe i don't need to actually, we'll see)
// ALSO COLOR SHOULD BE STORED AS AN INT
struct s_vertex
{
	// maybe store original screen coordinates somewhere here
	// perhaps even in x and y directly as they can easily be recovered from
	// iterating over the map again and aren't usually useful
	int x;
	int y;
	int	z;
	int	c;
};

// FDF UTILS
void	fdf_setup(t_fdf *fdf, int ac, char **av);
void	set_fdf_options(t_fdf *fdf, int ac, char **av);
void	set_fdf_defaults(t_fdf *fdf);
void	terminate_fdf(t_fdf *fdf);

// HOOK UTILS
int		set_hooks(t_fdf *fdf);
int		key_hook(int keycode, void *param);

// PARSER
int		parse_map(t_fdf *fdf, char *path);
int		open_map(t_fdf *fdf, char *path);
int		parse_map_lines(t_fdf *fdf, t_list **lines);
int		parse_line(t_fdf *fdf, t_list *tmp, char *line);
int		fill_map(t_fdf *fdf, t_list *lines);

// PARSER 2
int		count_vertices(char *line);
void	set_color(t_vertex *vertex, char **line);
void	destroy_map(t_fdf *fdf);
void	do_nothing(void *ptr);

// BRESENHAM
void	plot_line(t_fdf *fdf, t_vertex *v0, t_vertex *v1);
void	plot_line_low(t_fdf *fdf, t_vertex v0, t_vertex v1);
void	plot_line_high(t_fdf *fdf, t_vertex v0, t_vertex v1);
int		abso(int a);

// TEST UTILS
void	show_map(t_fdf *fdf);
void	plot_neighbours(t_fdf *fdf, int x, int y);
void	map_lines_test(t_fdf *fdf);
void	line_test(t_fdf *fdf);

#endif
