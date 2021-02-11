/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 15:07:45 by charles           #+#    #+#             */
/*   Updated: 2020/12/22 15:09:26 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		ft_atoi(const char *str, int *i)
{
	int					signe;
	unsigned long int	digit;

	digit = 0;
	signe = 1;
	while (str[*i] == ' ' || str[*i] == '\n' || str[*i] == '\r'
		|| str[*i] == '\t' || str[*i] == '\v' || str[*i] == '\f')
		(*i)++;
	if (str[*i] == '-' || str[*i] == '+')
	{
		signe = (str[*i] == '-') ? -1 : 1;
		(*i)++;
	}
	while (str[*i] > 47 && str[*i] < 58)
	{
		digit = digit * 10 + (str[*i] - '0');
		(*i)++;
	}
	if (digit > 9223372036854775807)
		return ((signe == -1) ? 0 : -1);
	return (digit * signe);
}

double	ft_atof(const char *str, int *i)
{
	double	unit;
	double	decimal;
	int		j;
	int		signe;

	j = 0;
	while (str[*i] == ' ' || str[*i] == '\n' || str[*i] == '\r'
		|| str[*i] == '\t' || str[*i] == '\v' || str[*i] == '\f')
		(*i)++;
	signe = (str[(*i)] == '-' ? 1 : 0);
	unit = ft_atoi(str, i);
	if (str[*i] == '.')
	{
		(*i)++;
		j = *i;
		decimal = ft_atoi(str, i);
		j = *i - j;
		if (signe)
			unit -= decimal / pow(10, j);
		else
			unit += decimal / pow(10, j);
	}
	return (unit);
}

t_vect	ft_atov(t_scene *sc, const char *str, int *i)
{
	t_vect color;

	color.x = ft_atof(str, i);
	if (str[(*i)] != ',')
		sc->error.error_type = "Error 8: Wrong vector formatting\n";
	(*i)++;
	color.y = ft_atof(str, i);
	if (str[(*i)] != ',')
		sc->error.error_type = "Error 8: Wrong vector formatting\n";
	(*i)++;
	color.z = ft_atof(str, i);
	if (str[(*i)] != ' ' && str[(*i)] != 0 && str[(*i)] != '\f' &&
		str[(*i)] != '\r' && str[(*i)] != '\t' && str[(*i)] != '\v' &&
		str[(*i)] != '\n')
		sc->error.error_type = "Error 4: wrong formatting1\n";
	return (color);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	if (!s1 || !s2)
		return (0);
	ptr1 = (unsigned char*)s1;
	ptr2 = (unsigned char*)s2;
	while (*ptr1 && *ptr2 && *ptr1 == *ptr2)
	{
		ptr1++;
		ptr2++;
	}
	return (*ptr1 - *ptr2);
}

int		close_button(t_scene *sc)
{
	if (!sc->save_bmp && sc->data.mlx_ptr)
		mlx_destroy_window(sc->data.mlx_ptr, sc->data.mlx_win);
	if (sc->objects)
		free(sc->objects);
	if (sc->lights)
		free(sc->lights);
	if (sc->cam)
		free(sc->cam);
	exit(0);
	return (0);
}
