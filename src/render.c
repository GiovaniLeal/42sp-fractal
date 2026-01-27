/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 21:37:50 by giodos-s          #+#    #+#             */
/*   Updated: 2026/01/10 21:37:50 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* ************************************************************************** */
/*  		               PUT_PIXEL                                  */
/* ************************************************************************** */
void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr
		+ (y * img->line_len)
		+ (x * (img->bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}

/* ************************************************************************** */
/*  		                GET_COLOR                                 */
/* ************************************************************************** */

int	get_color(int iter)
{
	double	x;
	double	t;
	int		red;
	int		green;
	int		blue;

	if (iter == MAX_ITER)
		return (0x000000);
	x = fmod(((double)iter / MAX_ITER) * 2.5, 1.0);
	red = 9 * (1 - x) * (x * x * x) * 255;
	green = 15 * ((1 - x) * (1 - x)) * (x * x) * 255;
	blue = 8.5 * ((1 - x) * (1 - x) * (1 - x)) * x * 255;
	if (iter < MAX_ITER * 0.15)
	{
		t = (double)iter / (MAX_ITER * 0.15);
		red = (1 - t) * ORANGE_R + t * red;
		green = (1 - t) * ORANGE_G + t * green;
		blue = (1 - t) * ORANGE_B + t * blue;
	}
	return ((red << 16) | (green << 8) | blue);
}

/* ************************************************************************** */
/*  		                CALC_POSITION	                            */
/* ************************************************************************** */
double	calc_position(t_app *app, int max_position, int init_position)
{
	return ((init_position - max_position / 2.0)
		* (4.0 / max_position)
		/ app->fractal.zoom);
}

/* ************************************************************************** */
/*  		                    RENDER_FRACTAL 	                  */
/* ************************************************************************** */
void	render_fractal(t_app *app)
{
	int		width;
	int		height;
	double	real_nb;
	double	img_nb;
	int		iter;

	height = 0;
	while (height < app->view.height)
	{
		width = 0;
		while (width < app->view.width)
		{
			real_nb = calc_position(app, app->view.width, width)
				+ app->fractal.offset_x;
			img_nb = -calc_position(app, app->view.height, height)
				+ app->fractal.offset_y;
			if (app->fractal.type == MANDELBROT)
				iter = mandelbrot(real_nb, img_nb);
			else
				iter = julia(real_nb, img_nb, &app->fractal);
			put_pixel(app->view.img, width, height, get_color(iter));
			width++;
		}
		height++;
	}
}

/* ************************************************************************** */
/*  		              RENDER           	                  */
/* ************************************************************************** */
void	render(t_app *app)
{
	render_fractal(app);
	mlx_put_image_to_window(
		app->mlx,
		app->win,
		app->view.img->img, 0, 0
		);
}
