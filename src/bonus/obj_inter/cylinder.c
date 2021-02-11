/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:46:24 by charles           #+#    #+#             */
/*   Updated: 2020/11/12 17:46:25 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_vect	find_normal(t_vect p, t_cylinder *c)
{
	t_vect	mop;
	t_vect	mp;
	float	b;
	t_vect	n;

	mop = vectsub(p, c->p0);
	b = dot(mop, c->n);
	mp = vectmult(c->n, b);
	n = normalize(vectsub(mop, mp));
	return (n);
}

float	cylinder_delta(t_ray d, t_object *object, float *a1)
{
	t_vect	v1;
	t_vect	v2;
	t_vect	mo;
	float	a[3];

	mo = vectsub(d.orig, object->cylinder.p0);
	v1 = (vectsub(mo, vectmult(object->cylinder.n,
			dot(mo, object->cylinder.n))));
	v2 = (vectsub(d.dir, vectmult(object->cylinder.n,
			dot(d.dir, object->cylinder.n))));
	a[0] = dot(v2, v2);
	a[1] = 2 * dot(v1, v2);
	a[2] = dot(v1, v1) - (object->cylinder.radius * object->cylinder.radius);
	*a1 = find_t0(a[0], a[1], a[2]);
	return ((a[1] * a[1]) - (4 * a[0] * a[2]));
}

int		inter_disk(t_ray d, t_object *obj, t_vect p)
{
	t_vect	p0l0;
	float	t;
	float	demom;

	demom = dot(d.dir, obj->cylinder.n);
	if (fabs(demom) > 0.00001f)
	{
		p0l0 = vectsub(p, d.orig);
		t = dot(p0l0, obj->cylinder.n) / demom;
		if (t >= 0.00001f)
		{
			obj->p = vectadd(d.orig, vectmult(d.dir, t));
			if (sqrt(dot(vectsub(obj->p, p), vectsub(obj->p, p))) <=
				obj->cylinder.radius)
			{
				if (t < obj->t)
				{
					obj->n = normalize(obj->cylinder.n);
					obj->t = t;
					return (1);
				}
			}
		}
	}
	return (0);
}

int		inter_cap(t_ray d, t_object *object)
{
	t_vect	p1;
	int		has_inter;

	has_inter = 0;
	p1 = vectadd(object->cylinder.p0,
		vectmult(object->cylinder.n, object->cylinder.height));
	object->cylinder.n = vectmult(object->cylinder.n, -1);
	if (inter_disk(d, object, object->cylinder.p0))
		has_inter = 1;
	object->cylinder.n = vectmult(object->cylinder.n, -1);
	if (inter_disk(d, object, p1))
		has_inter = 1;
	return (has_inter);
}

int		inter_cylinder(t_ray d, t_object *object)
{
	float delta;
	float a;
	float b;

	a = 0.0;
	object->cylinder.n = normalize(object->cylinder.n);
	delta = cylinder_delta(d, object, &a);
	if (delta >= 0.0f && a > 0)
	{
		object->p = vectadd(d.orig, vectmult(d.dir, a));
		object->n = find_normal(object->p, &object->cylinder);
		b = dot(vectsub(object->p, object->cylinder.p0), object->cylinder.n);
		if (b > 0 && b < object->cylinder.height)
		{
			object->t = a;
			return (1);
		}
		else
			return (inter_cap(d, object));
	}
	return (0);
}
