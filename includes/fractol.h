/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 11:31:49 by giodos-s          #+#    #+#             */
/*   Updated: 2025/12/31 11:31:49 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

/* INCLUDES ------------------------------------------------------------------*/
# include <math.h>
# include "mlx.h"
# include "libft.h"
# include "ft_printf.h"

/* CONFIG --------------------------------------------------------------------*/
# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define MAX_ITER 200
# define ESC 65307
# define ORANGE_R 30
# define ORANGE_G 3
# define ORANGE_B 48

/* STRUCTS -------------------------------------------------------------------*/
typedef struct s_img
{
	int			bits_per_pixel;
	int			line_len;
	int			endian;
	void		*img;
	char		*addr;
}	t_img;

typedef struct s_complex
{
	double	real_nb;
	double	imaginary_nb;
}	t_complex;

typedef enum e_fractal_type
{
	MANDELBROT,
	JULIA
}	t_fractal_type;

typedef struct s_fractal
{
	t_fractal_type	type;
	t_complex		*julia_complex;
	double			zoom;
	double			offset_x;
	double			offset_y;
}	t_fractal;

typedef struct s_viewport
{
	int		width;
	int		height;
	t_img	*img;
}	t_viewport;

typedef struct s_app
{
	void		*mlx;
	void		*win;
	t_viewport	view;
	t_fractal	fractal;
}	t_app;

/* MAIN.C --------------------------------------------------------------------*/
void	print_usage(void);
int		main(int ac, char **av);
int		parse_args(int nb_arg, char **arg, t_fractal *f);

/* APP_INIT.C ----------------------------------------------------------------*/
int		app_init(t_app *app);
void	image_init(t_app *app);
void	fractal_init(t_fractal *f);

/* RENDER.C   ----------------------------------------------------------------*/
void	put_pixel(t_img *img, int x, int y, int color);
int		get_color(int iter);
double	calc_position(t_app *app, int max_position, int init_position);
void	render_fractal(t_app *app);
void	render(t_app *app);

/* HOOKS.C   -----------------------------------------------------------------*/
void	hooks_init(t_app *app);
int		handle_keypress(int keycode, t_app *vars);
int		clean_exit(t_app *vars);
int		handle_mouse(int button, int x, int y, t_app *f);
int		handle_expose(t_app *app);

/* FRACTOLS.C  ---------------------------------------------------------------*/
int		julia(double z_re, double z_im, t_fractal *f);
int		mandelbrot(double c_re, double c_im);

/* UTILS.C -------------------------------------------------------------------*/
int		is_float(const char *str);
double	ft_atof(const char *str);
#endif