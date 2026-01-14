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

/* ===================== JULIA ===================== */

int	julia(double z_re, double z_im, t_complex *data)
{
	t_fractal	*f;
	double		tmp;
	int			i;

	f = (t_fractal *)data;
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

/* ================== MANDELBROT =================== */

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
