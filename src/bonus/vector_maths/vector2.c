/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 19:13:44 by charles           #+#    #+#             */
/*   Updated: 2020/11/10 19:13:47 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

float	dot(t_vect v1, t_vect v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float	getnorm2(t_vect ray)
{
	return ((ray.x * ray.x) + (ray.y * ray.y) + (ray.z * ray.z));
}

t_vect	normalize(t_vect ray)
{
	float length;

	length = sqrt(getnorm2(ray));
	ray.x /= length;
	ray.y /= length;
	ray.z /= length;
	return (ray);
}

t_vect	crossp(t_vect v1, t_vect v2)
{
	t_vect res;

	res.x = (v1.y * v2.z) - (v1.z * v2.y);
	res.y = (v1.z * v2.x) - (v1.x * v2.z);
	res.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (res);
}
