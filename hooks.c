/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 21:25:13 by giodos-s          #+#    #+#             */
/*   Updated: 2026/01/08 21:25:13 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* ************************************************************************** */
/*                               HOOKS INIT                                   */
/* ************************************************************************** */

void	hooks_init(t_app *app)
{
	mlx_key_hook(app->win, handle_keypress, app);
	mlx_mouse_hook(app->win, handle_mouse, app);
	mlx_expose_hook(app->win, handle_expose, app);
	mlx_hook(app->win, 17, 0, clean_exit, app); /* DestroyNotify */
}

/* ************************************************************************** */
/*                               KEYBOARD                                     */
/* ************************************************************************** */
/* ESC encerra o programa */

int	handle_keypress(int keycode, t_app *app)
{
	if (keycode == ESC)
		clean_exit(app);
	return (0);
}

/* ************************************************************************** */
/*                               EXPOSE                                       */
/* ************************************************************************** */
/* Redesenha a imagem quando a janela é exposta */

int	handle_expose(t_app *app)
{
	if (!app || !app->view.img || !app->view.img->img)
		return (0);
	mlx_put_image_to_window(
		app->mlx,
		app->win,
		app->view.img->img,
		0,
		0
	);
	return (0);
}

/* ************************************************************************** */
/*                               CLEAN EXIT                                   */
/* ************************************************************************** */
/* Libera corretamente os recursos e encerra o programa */

int	clean_exit(t_app *app)
{
	if (!app)
		exit(EXIT_SUCCESS);
	if (app->view.img && app->view.img->img)
		mlx_destroy_image(app->mlx, app->view.img->img);
	if (app->win)
		mlx_destroy_window(app->mlx, app->win);
	if (app->mlx)
	{
		mlx_destroy_display(app->mlx);
		free(app->mlx);
	}
	if (app->fractal.julia_complex)
        free(app->fractal.julia_complex);
	exit(EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                               MOUSE                                        */
/* ************************************************************************** */
/* Scroll do mouse controla o zoom centrado no cursor */

int	handle_mouse(int button, int x, int y, t_app *app)
{
	double	zoom_factor;
	double	mouse_re;
	double	mouse_im;

	if (button != 4 && button != 5)
		return (0);

	zoom_factor = (button == 4) ? 1.2 : 0.8;

	mouse_re = (x - app->view.width / 2.0)
		* (4.0 / app->view.width) / app->fractal.zoom
		+ app->fractal.offset_x;

	mouse_im = (y - app->view.height / 2.0)
		* (4.0 / app->view.height) / app->fractal.zoom
		+ app->fractal.offset_y;

	app->fractal.zoom *= zoom_factor;

	app->fractal.offset_x = mouse_re
		- (x - app->view.width / 2.0)
		* (4.0 / app->view.width) / app->fractal.zoom;

	app->fractal.offset_y = mouse_im
		- (y - app->view.height / 2.0)
		* (4.0 / app->view.height) / app->fractal.zoom;

	render_fractal(app);

	mlx_put_image_to_window(
		app->mlx,
		app->win,
		app->view.img->img,
		0,
		0
	);
	return (0);
}


