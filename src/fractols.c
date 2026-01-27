/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractols.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 17:10:46 by giodos-s          #+#    #+#             */
/*   Updated: 2026/01/01 17:10:46 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* ************************************************************************** */
/*                                FRACTOLS.C                                  */
/*                                                                            */
/*  All fractals in this project are based on the complex equation:           */
/*                                                                            */
/*                       z(n+1) = z(n)² + c                                   */
/*                                                                            */
/*  Where:                                                                    */
/*    - z is a complex number (z = z_re + z_im * i)                           */
/*    - c is a constant complex number                                        */
/*                                                                            */
/*  The difference between fractals lies in how z and c are defined:          */
/*                                                                            */
/*  MANDELBROT:                                                               */
/*    - z always starts at 0 (z = 0 + 0i)                                     */
/*    - c is the current point in the complex plane (screen pixel)            */
/*    - each pixel defines a different value of c                             */
/*                                                                            */
/*  JULIA:                                                                    */
/*    - z starts at the current point in the complex plane (screen pixel)     */
/*    - c is a fixed value provided by the user                               */
/*    - changing c generates different Julia sets                             */
/*                                                                            */
/*  The iteration loop runs until:                                            */
/*    - |z|² > 4  (the point diverges)                                        */
/*    - or MAX_ITER is reached (iteration limit)                              */
/*                                                                            */
/*  The returned value represents how many iterations were needed             */
/*  for the point to diverge and is later used for coloring.                  */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                 JULIA.C                                    */
/* ************************************************************************** */
int	julia(double z_re, double z_im, t_fractal *f)
{
	double		tmp;
	int			i;

	i = 0;
	while (z_re * z_re + z_im * z_im <= 4 && i < MAX_ITER)
	{
		tmp = z_re * z_re - z_im * z_im + f->julia_complex->real_nb;
		z_im = 2 * z_re * z_im + f->julia_complex->imaginary_nb;
		z_re = tmp;
		i++;
	}
	return (i);
}

/* ************************************************************************** */
/*                              MANDELBROT.C                                  */
/* ************************************************************************** */
int	mandelbrot(double c_re, double c_im)
{
	double	z_re;
	double	z_im;
	double	tmp;
	int		i;

	z_re = 0.0;
	z_im = 0.0;
	i = 0;
	while (z_re * z_re + z_im * z_im <= 4 && i < MAX_ITER)
	{
		tmp = z_re * z_re - z_im * z_im + c_re;
		z_im = 2 * z_re * z_im + c_im;
		z_re = tmp;
		i++;
	}
	return (i);
}
