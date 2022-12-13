/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:44:31 by nlegrand          #+#    #+#             */
/*   Updated: 2022/12/13 01:04:41 by nlegrand         ###   ########.fr       */
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
# include <math.h>

# define WIN_MAX_WIDTH	1600
# define WIN_MAX_HEIGHT	1000
# define WIN_TITLE		"fdf"
# define HEX_SET		"0123456789abcdef"
# define M_COL			0x00ffffff
# define M_COLT			0xff000000
# define M_COLR			0x00ff0000
# define M_COLG			0x0000ff00
# define M_COLB			0x000000ff
# define KEY_ESC	65307
# define MOUSE_LEFT 1
# define MOUSE_RIGHT 3
# define MOUSE_MIDDLE 2
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5
# define ROT_SPEED 250.0

// ERROR MESSAGES
# define USAGE		"Usage: %s <filename> [case_size z_size]\n"
# define MLX_ERROR	"[ERROR] Failed to establish connection to X server.\n"
# define MAP_ERROR			"[ERROR] Failed to parse map.\n"
# define VIEW_ERROR	"[ERROR] Failed to set view properties.\n"
# define WIN_ERROR	"[ERROR] Failed to create mlx window.\n"
# define IMG_ERROR	"[ERROR] Failed to create mlx image.\n"

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
	void	(*calc_coords)(t_fdf *fdf);
	double	i[2];
	double	j[2];
	int		xoff;
	int		yoff;
	int		move;
	int		xmov;
	int		ymov;
	int		mov_start[2];
	int		rotate;
	int		rot_start;
	double	ri;
	double	amp;
	double	cs_og;
	double	zs_og;
	double	cs;
	double	zs;
	int		map_xcenter;
	int		map_ycenter;
	double	zoom;
	int		relief;
	int		height;
};
struct	s_vertex
{
	double	x;
	double	y;
	double	z;
	int		c;
	int		cols[2];
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
	int			mmin;
	int			mmax;
	int			redraw;
};

// SETUP
void	fdf_setup(t_fdf *fdf, int ac, char **av);
int		fdf_win_setup(t_fdf *fdf);
int		fdf_view_setup(t_fdf *fdf, int ac, char **av);
int		fdf_img_setup(t_fdf *fdf);

// UTILS
void	fdf_vars_init(t_fdf *fdf);
void	view_vars_init(t_view *view);
void	fdf_destroy_map(t_fdf *fdf);
void	fdf_terminate(t_fdf *fdf);
void	fdf_exit_failure(void);
// UTILS 2
void	set_vector_2d(double v[2], double x, double y);
int		abso(int a);
void	clear_img(t_fdf *fdf, int col);
void	do_nothing(void *ptr);
// UTILS 3
void	refresh_view_zoom(t_fdf *fdf);
void	refresh_view_move(t_fdf *fdf);
void	refresh_view_rotate(t_fdf *fdf);
void	get_map_limits(t_fdf *fdf);
void	map_relative_height(t_fdf *fdf);

// HOOKS
void	set_hooks(t_fdf *fdf);
int		destroy_h(t_fdf *fdf);
int		loop_h(t_fdf *fdf);
// HOOKS 2
int		key_press_h(int keycode, t_fdf *fdf);
int		mouse_press_h(int button, int x, int y, t_fdf *fdf);
int		mouse_release_h(int button, int x, int y, t_fdf *fdf);
int		mouse_move_h(int x, int y, t_fdf *fdf);

// MODEL MANIP
void	model_zoom(t_fdf *fdf, int button);
void	model_move(t_fdf *fdf, int x, int y);
void	model_rotate(t_fdf *fdf, int dir);
void	model_relief(t_fdf *fdf);
void	model_set_proj(t_fdf *fdf, int keycode);
// MODEL MANIP 2
void	model_view_focus(t_fdf *fdf);
void	model_scale_amp(t_fdf *fdf, int keycode);
void	model_toggle_height(t_fdf *fdf);

// PROJECT
void	plot_map(t_fdf *fdf);
void	plot_up_left(t_fdf *fdf);
void	plot_down_right(t_fdf *fdf);
int		check_out(t_fdf *fdf, t_vertex *v0, t_vertex *v1);

// PROJECTIONS
void	calc_iso_proj(t_fdf *fdf);
void	calc_mili_proj(t_fdf *fdf);
void	calc_flat_proj(t_fdf *fdf);

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
int		parse_line(t_fdf *fdf, t_list *tmp, char *line);
int		fill_map(t_fdf *fdf, t_list *lines);
// PARSER 2
int		count_vertices(char *line);
void	set_color(t_vertex *vertex, char **lines);

// TEST UTILS
void	bres_grad_test(t_fdf *fdf);
void	dot_test(t_fdf *fdf);

#endif
