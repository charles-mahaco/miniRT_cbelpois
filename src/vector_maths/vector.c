/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 19:12:30 by charles           #+#    #+#             */
/*   Updated: 2020/11/10 19:13:31 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect	vectsub(t_vect v1, t_vect v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return (v1);
}

t_vect	vectadd(t_vect v1, t_vect v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return (v1);
}

t_vect	vectmult(t_vect v1, float num)
{
	v1.x *= num;
	v1.y *= num;
	v1.z *= num;
	return (v1);
}

t_vect	vectsmult(t_vect v1, t_vect v2)
{
	v1.x *= v2.x;
	v1.y *= v2.y;
	v1.z *= v2.z;
	return (v1);
}

t_vect	vectdiv(t_vect v1, float num)
{
	v1.x /= num;
	v1.y /= num;
	v1.z /= num;
	return (v1);
}
