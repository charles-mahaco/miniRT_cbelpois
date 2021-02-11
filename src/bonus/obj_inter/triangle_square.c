/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_square.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:40:24 by charles           #+#    #+#             */
/*   Updated: 2020/11/12 17:40:26 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int		inter_triangle2(t_triangle *tr, t_vect pt, t_vect n)
{
	t_vect edge[3];
	t_vect c[3];

	edge[0] = vectsub(tr->p1, tr->p0);
	edge[1] = vectsub(tr->p2, tr->p1);
	edge[2] = vectsub(tr->p0, tr->p2);
	c[0] = vectsub(pt, tr->p0);
	c[1] = vectsub(pt, tr->p1);
	c[2] = vectsub(pt, tr->p2);
	if (dot(n, crossp(edge[0], c[0])) > -0.001f &&
		dot(n, crossp(edge[1], c[1])) > -0.001f &&
		dot(n, crossp(edge[2], c[2])) > -0.001f)
		return (1);
	return (0);
}

int		inter_triangle(t_ray d, t_object *obj)
{
	t_vect	n;
	float	t;
	t_vect	pt;

	n = crossp(vectsub(obj->triangle.p1, obj->triangle.p0),
		vectsub(obj->triangle.p2, obj->triangle.p0));
	if (fabs(dot(d.dir, n)) > 0.00001f)
	{
		t = dot(vectsub(obj->triangle.p0, d.orig), n) / dot(d.dir, n);
		if (t >= 0.00001f)
		{
			pt = vectadd(d.orig, vectmult(d.dir, (double)t));
			if (inter_triangle2(&obj->triangle, pt, n) == 1)
			{
				n = (dot(d.dir, n) > 0) ? vectmult(n, -1) : n;
				obj->p = pt;
				obj->n = normalize(n);
				obj->t = t;
				return (1);
			}
		}
	}
	return (0);
}

int		square_dot(t_vect *corner, t_vect p, t_vect n)
{
	float o1;
	float o2;
	float o3;
	float o4;

	o1 = dot(crossp(vectsub(corner[0], p), vectsub(corner[1], p)), n);
	o2 = dot(crossp(vectsub(corner[1], p), vectsub(corner[2], p)), n);
	o3 = dot(crossp(vectsub(corner[2], p), vectsub(corner[3], p)), n);
	o4 = dot(crossp(vectsub(corner[3], p), vectsub(corner[0], p)), n);
	if ((o1 >= 0 && o2 >= 0 && o3 >= 0 && o4 >= 0) ||
		(o1 < 0 && o2 < 0 && o3 < 0 && o4 < 0))
		return (1);
	return (0);
}

int		inter_square(t_object *obj, float t, t_vect p)
{
	t_vect corner[4];

	corner[0] = (t_vect){obj->square.p0.x - obj->square.height / 2,
		obj->square.p0.y + obj->square.height / 2, obj->square.p0.z};
	corner[1] = (t_vect){obj->square.p0.x + obj->square.height / 2,
		obj->square.p0.y + obj->square.height / 2, obj->square.p0.z};
	corner[2] = (t_vect){obj->square.p0.x + obj->square.height / 2,
		obj->square.p0.y - obj->square.height / 2, obj->square.p0.z};
	corner[3] = (t_vect){obj->square.p0.x - obj->square.height / 2,
		obj->square.p0.y - obj->square.height / 2, obj->square.p0.z};
	if (square_dot(corner, p, obj->square.n))
	{
		obj->t = t;
		obj->p = p;
		obj->n = normalize(obj->square.n);
		return (1);
	}
	return (0);
}

int		inter_plane_square(t_ray d, t_object *obj)
{
	t_vect	p0l0;
	float	t;
	float	denom;
	t_vect	p;

	obj->square.n = normalize(obj->square.n);
	denom = dot(d.dir, obj->square.n);
	if (fabs(denom) > 0.00001f)
	{
		p0l0 = vectsub(obj->square.p0, d.orig);
		t = dot(p0l0, obj->square.n) / denom;
		if (t >= 0.00001f)
		{
			p = vectadd(d.orig, vectmult(d.dir, t));
			return (inter_square(obj, t, p));
		}
	}
	return (0);
}
