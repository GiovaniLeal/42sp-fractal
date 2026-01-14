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
/* funcao responsável por validar se a string passada represensa um numero 
decimal,para que posteriormente seja convertida. No projeto tem a funcao de 
validar as entradas						 */
/* ************************************************************************** */
int	is_float(const char *str)
{
	int	i;
	int	has_digit;
	int	has_dot;

	i = 0;
	has_digit = 0;
	has_dot = 0;
	if (!str || str[0] == '\0')
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			has_digit = 1;
		else if (str[i] == '.' && !has_dot)
			has_dot = 1;
		else
			return (0);
		i++;
	}
	return (has_digit);
}


/* ************************************************************************** */
/* 			  FT_ATOF		                  */
/* Funçao responsável por converter a string recebida como parametro 
	em numero decimal. */
/* ************************************************************************** */
double	ft_atof(const char *str)
{
	double	result;
	double	decimal;
	int		sign;

	result = 0.0;
	decimal = 1.0;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		result = result * 10.0 + (*str++ - '0');
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			decimal *= 0.1;
			result += (*str - '0') * decimal;
			str++;
		}
	}
	return (result * sign);
}

