/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:34:40 by charles           #+#    #+#             */
/*   Updated: 2020/11/12 17:34:41 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int		i_s_p(t_ray d_ray, t_plane *plane)
{
	t_vect	p0l0;
	float	t;
	float	demom;

	plane->n = normalize(plane->n);
	demom = dot(d_ray.dir, plane->n);
	if (fabs(demom) > 0.00001f)
	{
		p0l0 = vectsub(plane->p0, d_ray.orig);
		t = dot(p0l0, plane->n) / demom;
		if (t >= 0.00001f)
			return (1);
	}
	return (0);
}

float	sphere_delta(t_ray d, t_sphere s, float *b)
{
	float a;
	float c;

	a = 1;
	*b = 2 * dot(d.dir, vectsub(d.orig, s.center));
	c = getnorm2(vectsub(d.orig, s.center)) - s.radius * s.radius;
	return ((*b) * (*b) - 4 * a * c);
}

int		inter_sphere(t_ray d, t_object *object)
{
	float delta;
	float b;
	float t1;
	float t2;

	delta = sphere_delta(d, object->sphere, &b);
	if (delta < 0)
		return (0);
	t1 = (-b - sqrt(delta)) / 2;
	t2 = (-b + sqrt(delta)) / 2;
	if (t2 < 0)
		return (0);
	if (t1 > 0)
		object->t = t1;
	else
		object->t = t2;
	object->p = vectadd(d.orig, vectmult(d.dir, object->t));
	object->n = normalize(vectsub(object->p, object->sphere.center));
	return (1);
}

int		inter_plane(t_ray r, t_object *object)
{
	t_vect	p0l0;
	float	demom;
	float	t;

	object->plane.n = normalize(object->plane.n);
	demom = dot(r.dir, object->plane.n);
	if (fabs(demom) > 0.00001f)
	{
		p0l0 = vectsub(object->plane.p0, r.orig);
		t = dot(p0l0, object->plane.n) / demom;
		if (t >= 0.00001f)
		{
			object->p = vectadd(r.orig, vectmult(r.dir, t));
			object->n = normalize(object->plane.n);
			object->t = t;
			return (1);
		}
	}
	return (0);
}

float	find_t0(float a, float b, float c)
{
	float t0;
	float t1;
	float discr;

	discr = (b * b) - (4 * a * c);
	if (discr == 0.0)
		t0 = -b / (2 * a);
	else
	{
		t0 = (-b + sqrt(discr)) / (2 * a);
		t1 = (-b - sqrt(discr)) / (2 * a);
		if (t0 > t1)
			t0 = t1;
	}
	return (t0);
}
