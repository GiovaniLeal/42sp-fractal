/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 23:02:05 by giodos-s          #+#    #+#             */
/*   Updated: 2026/01/08 23:02:05 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* ************************************************************************** */
/* 			  IS_FLOAT 		                  */
/* ************************************************************************** */
int	is_float(const char *str)
{
	int	i;
	int	dot;

	i = 0;
	dot = 0;
	if (!str || !*str)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else if (str[i] == '.' && !dot && i > 0 && ft_isdigit(str[i - 1]))
		{
			dot = 1;
			i++;
		}
		else
			return (0);
	}
	return (1);
}

/* ************************************************************************** */
/* 			  FT_ATOF		                 	        */
/* ************************************************************************** */
double	ft_atof(const char *str)
{
	double	result;
	double	decimal;
	int		sign;

	result = 0.0;
	decimal = 1.0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		result = result * 10.0 + (*str++ - '0');
	if (*str == '.')
	{
		while (*++str >= '0' && *str <= '9')
		{
			decimal *= 0.1;
			result += (*str - '0') * decimal;
		}
	}
	return (result * sign);
}
