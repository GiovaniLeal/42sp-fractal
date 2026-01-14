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
/*  		               PUT_PIXEL                          				  */
/* 	Escreve a cor de um pixel diretamente na memoria da imagem			      */
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
/*  		                GET_COLOR                   				      */
/* Seta as cores de renderizaçao de acordo com o numero de interacoes         */
/* ************************************************************************** */

int	get_color(int iter)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (iter == MAX_ITER)
		return (0x000000);
	t = (double)iter / MAX_ITER;
	r = (int)(sin(6.28318 * t + 4) * 127 + 128);
	g = (int)(sin(6.28318 * t + 2) * 127 + 128);
	b = (int)(sin(6.28318 * t + 1) * 127 + 128);
	return ((r << 16) | (g << 8) | b);
}

/* ************************************************************************** */
/*  		                CALC_POSITION	                   				  */
/* calcula a posicao relativa centralizada								      */
/* ************************************************************************** */

double	calc_position(t_app *app, int max_position, int init_position)
{
	return ((init_position - max_position / 2.0) * (4.0 / app->view.width)
		/ app->fractal.zoom);
}

/* ************************************************************************** */
/*  		                    RENDER_FRACTAL 	                   			  */
/*             Escreve diretamente na memória da imagem 				      */
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
			img_nb = calc_position(app, app->view.height, height)
				+ app->fractal.offset_y;
			if (app->fractal.type == MANDELBROT)
				iter = mandelbrot(real_nb, img_nb);
			else
				iter = julia(real_nb, img_nb, app->fractal.julia_complex);
			put_pixel(app->view.img, width, height, get_color(iter));
			width++;
		}
		height++;
	}
}

/* ************************************************************************** */
/*  		                        RENDER 	                                  */
/* Chama funcoes responsáveis por iniciar a imagem e renderiza-la na janela   */
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
