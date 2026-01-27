/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 12:55:17 by giodos-s          #+#    #+#             */
/*   Updated: 2026/01/01 12:55:17 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* ************************************************************************** */
/*  		              PRINT_USAGE	                            */
/* ************************************************************************** */
void	print_usage(void)
{
	ft_printf(
		"+-------------------------------------------+\n"
		"|         Usage: ./fractol <fractal>        |\n"
		"+-------------------------------------------+\n"
		"+-----------| Available fractals |----------+\n"
		"|                                           |\n"
		"|                 mandelbrot                |\n"
		"|                 julia [x y]               |\n"
		"+-------------------------------------------+\n"
		"|             Julia Set Examples            |\n"
		"|                                           |\n"
		"| ./fractol julia -0.4 0.6                  |\n"
		"| ./fractol julia 0.285 0.01                |\n"
		"| ./fractol julia -0.8 0.156                |\n"
		"+-------------------------------------------+\n"
		);
}

/* ************************************************************************** */
/*  		              PARSE_ARGS	                            */
/* ************************************************************************** */
int	parse_args(int ac, char **av, t_fractal *fractal)
{
	if (ac == 2 && !ft_strncmp(av[1], "mandelbrot", 11))
	{
		fractal->type = MANDELBROT;
		fractal->julia_complex = NULL;
		return (1);
	}
	if (ac == 4 && !ft_strncmp(av[1], "julia", 6))
	{
		if (!is_float(av[2]) || !is_float(av[3]))
			return (0);
		fractal->type = JULIA;
		fractal->julia_complex = malloc(sizeof(t_complex));
		if (!fractal->julia_complex)
			return (0);
		fractal->julia_complex->real_nb = ft_atof(av[2]);
		fractal->julia_complex->imaginary_nb = ft_atof(av[3]);
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*  		               MAIN 	                            */
/* ************************************************************************** */
int	main(int ac, char **av)
{
	t_app	app;

	ft_bzero(&app, sizeof(t_app));
	if (!parse_args(ac, av, &app.fractal))
	{
		print_usage();
		return (1);
	}
	if (!app_init(&app))
		return (EXIT_FAILURE);
	render(&app);
	hooks_init(&app);
	mlx_loop(app.mlx);
	return (0);
}
