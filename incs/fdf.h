/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:44:31 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/07 16:06:18 by nlegrand         ###   ########.fr       */
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
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>

# define WIN_MAX_WIDTH 1800
# define WIN_MAX_HEIGHT 1000
# define WIN_TITLE	"fdf"
# define HEX_SET	"0123456789abcdef"
# define M_COL		0x00ffffff
# define M_COLT		0xff000000
# define M_COLR		0x00ff0000
# define M_COLG		0x0000ff00
# define M_COLB		0x000000ff


# define USAGE		"Usage: %s <filename> [case_size z_size]\n"
# define MLX_ERROR	"[ERROR] Failed to establish connection to X server.\n"
# define MAP_ERROR			"[ERROR] Failed to parse map.\n"
# define VIEW_ERROR	"[ERROR] Failed to set view properties.\n"
# define WIN_ERROR	"[ERROR] Failed to create mlx window.\n"
# define IMG_ERROR	"[ERROR] Failed to craete mlx image.\n"

// Map Error Messages
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
typedef struct s_grad	t_grad;
typedef struct s_coord	t_coord;

struct s_coord
{
	int	cs_zoom;
	int	zs_zoom;
	int	xcenter;
	int	ycenter;
	int	xmap;
	int	ymap;
};
struct	s_grad
{
	int	dc;
	int	dp;
	int	og_p;
};
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
	double	i[3];
	double	j[3];
	double	k[3];
	int		xoff;
	int		yoff;
	int		cs;
	int		zs;
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
	int			redraw;
};

// SETUP
void	fdf_setup(t_fdf *fdf, int ac, char **av);
int		fdf_win_setup(t_fdf *fdf);
int		fdf_view_setup(t_fdf *fdf, int ac, char **av);
int		fdf_img_setup(t_fdf *fdf);

// UTILS
void	fdf_vars_init(t_fdf *fdf);
void	fdf_destroy_map(t_fdf *fdf);
void	fdf_terminate(t_fdf *fdf);
void	fdf_exit_failure(void);
void	do_nothing(void *ptr);
// UTILS 2
void	set_vector_3d(double v[3], double x, double y, double z);
int		abso(int a);
void	clear_img(t_fdf *fdf, int col);

// HOOKS
void	set_hooks(t_fdf *fdf);
int		close_esc(int keycode, t_fdf *fdf);
int		close_cross(t_fdf *fdf);
int		zoom_map(int button, int x, int y, t_fdf *fdf);
int		loop_hook(t_fdf *fdf);

// PROJECT
void	plot_map(t_fdf *fdf);
void	calc_coords(t_fdf *fdf);
void	calc_iso(t_fdf *fdf, t_vertex *v, t_coord *coord);

// BRESENHAM
void	plot_line(t_fdf *fdf, t_vertex *v0, t_vertex *v1);
void	plot_line_low(t_fdf *fdf, t_vertex v0, t_vertex v1);
void	plot_line_high(t_fdf *fdf, t_vertex v0, t_vertex v1);
void	my_pixel_put(t_fdf *fdf, int x, int y, int col);
int		grad_col(t_grad *grad, t_vertex *v0, t_vertex *v1, int pos);

// PARSER
int		parse_map(t_fdf *fdf, char *path);
int		open_map(int *fd, char *path);
int		parse_map_lines(t_fdf *fdf, int fd, t_list **lines);
int 	parse_line(t_fdf *fdf, t_list *tmp, char *line);
int		fill_map(t_fdf *fdf, t_list *lines);
// PARSER 2
int		count_vertices(char *line);
void	set_color(t_vertex *vertex, char **lines);

// TEST UTILS
void	bres_grad_test(t_fdf *fdf);
void	dot_test(t_fdf *fdf);

#endif
