/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 23:06:48 by giodos-s          #+#    #+#             */
/*   Updated: 2026/01/10 23:06:48 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* ************************************************************************** */
/*  			FRACTAL_NAME			        */
/* 	Returns the window title based on the fractal type.                 */
/* ************************************************************************** */
static char	*fractal_name(enum e_fractal_type type)
{
	if (type == MANDELBROT)
		return ("42SP - MANDELBROT FRACTOL");
	if (type == JULIA)
		return ("42SP - JULIA FRACTOL");
	return ("42SP - FRACTOL");
}

/* ************************************************************************** */
/* 		 	   IMAGE_INIT	                            */
/*      Initializes the MLX image and retrieves its memory address.           */
/* ************************************************************************** */
void	image_init(t_app *app)
{
	app->view.img = malloc(sizeof(t_img));
	if (!app->view.img)
		clean_exit(app);
	app->view.img->img = mlx_new_image(
		app->mlx,
		app->view.width,
		app->view.height
	);
	if (!app->view.img->img)
		clean_exit(app);
	app->view.img->addr = mlx_get_data_addr(
		app->view.img->img,
		&app->view.img->bits_per_pixel,
		&app->view.img->line_len,
		&app->view.img->endian
	);
}


/* ************************************************************************** */
/* 		 	  FRACTAL_INIT	                            */
/* 		Initializes default fractal parameters.                   */
/* ************************************************************************** */
void	fractal_init(t_fractal *f)
{
	f->zoom = 1.0;
	f->offset_x = 0.0;
	f->offset_y = 0.0;
}

/* ************************************************************************** */
/* 		 	   APP_INIT	                            */
/* Initializes the MLX context, window, image and fractal state.              */
/* ************************************************************************** */
int	app_init(t_app *app)
{
	app->mlx = mlx_init();
	if (!app->mlx)
		return (0);

	app->view.width = WIN_WIDTH;
	app->view.height = WIN_HEIGHT;
	app->win = mlx_new_window(
		app->mlx,
		app->view.width,
		app->view.height,
		fractal_name(app->fractal.type)
	);
	if (!app->win)
		clean_exit(app);
	image_init(app);
	fractal_init(&app->fractal);
	return (1);
}

