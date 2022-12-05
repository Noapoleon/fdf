/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:44:31 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/05 19:31:34 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <sys/stat.h>
# include <fcntl.h>

# define WIN_WIDTH	800
# define WIN_HEIGHT	600
# define WIN_TITLE	"fdf"
# define HEX_SET	"0123456789abcdef"
# define M_COL		0x00ffffff
# define M_COLT		0xff000000
# define M_COLR		0x00ff0000
# define M_COLG		0x0000ff00
# define M_COLB		0x000000ff


# define USAGE		"Usage: %s <filename> [case_size z_size]\n"
# define MLX_ERROR	"[ERROR] Failed to establish connection to X server.\n"
# define VIEW_ERROR	"[ERROR] Failed to set view properties.\n"
# define WIN_ERROR	"[ERROR] Failed to create window.\n"

// Map Error Messages
# define MAP_ERROR			"[ERROR] Failed to parse map.\n"
# define MAP_FAIL_OPEN		"[ERROR] Failed to open map.\n"
# define MAP_FAIL_READ		"[ERROR] Failed to read map.\n"
# define MAP_FAIL_FILL		"[ERROR] Failed to fill map.\n"
# define MAP_FAIL_FDF		"[ERROR] File is not a .fdf map.\n"
# define MAP_FAIL_DIR		"[ERROR] Path leads to a directory.\n"
# define MAP_FAIL_FD		"[ERROR] Invalid fd.\n"
# define MAP_FAIL_TMP		"[ERROR] Failed tmp malloc.\n"
# define MAP_FAIL_LINE		"[ERROR] Failed to parse line #%d.\n"
# define MAP_FAIL_VERTEX	"[ERROR] Failed to malloc vertex array.\n"
# define MAP_FAIL_MAP		"[ERROR] Faile to malloc map.\n"

typedef struct s_fdf	t_fdf;
typedef struct s_vertex	t_vertex;
typedef struct s_view	t_view;
typedef struct s_imgbuf	t_imgbuf;

struct	s_imgbuf
{
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
};
struct s_view
{
	double	x;
	double	y;
	double	z;
	int		c_size;
	int		z_size;
	double	zoom;
};
struct	s_vertex
{
	int	x;
	int	y;
	int	z;
	int	c;
};
struct s_fdf
{
	void		*mlx;
	void		*win;
	t_vertex	**map;
	t_view		view;
	t_imgbuf	img;

	char		*wtitle;
	int			wwidth;
	int			wheight;
	int			mwidth;
	int			mheight;
};

// UTILS
void	fdf_setup(t_fdf *fdf, int ac, char **av);
int		fdf_view_setup(t_fdf *fdf, int ac, char **av);
int		fdf_win_setup(t_fdf* fdf);
// UTILS 2
void	fdf_zero_init(t_fdf *fdf);
void	fdf_destroy_map(t_fdf *fdf);
void	fdf_terminate(t_fdf *fdf);
void	fdf_exit_failure(void);
void	do_nothing(void *ptr);

// PARSER
int		parse_map(t_fdf *fdf, char *path);
int		open_map(int *fd, char *path);
int		parse_map_lines(t_fdf *fdf, int fd, t_list **lines);
int 	parse_line(t_fdf *fdf, t_list *tmp, char *line);
int		fill_map(t_fdf *fdf, t_list *lines);
// PARSER 2
int		count_vertices(char *line);
void	set_color(t_vertex *vertex, char **lines);

#endif
