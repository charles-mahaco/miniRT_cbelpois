/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spheres_mat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 17:11:31 by charles           #+#    #+#             */
/*   Updated: 2020/11/13 17:11:32 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_vect	sphere_mirror(t_ray r, t_scene scene, int a_def, int nb_rebound)
{
	t_vect	dir_mirror;
	t_ray	ray_mirror;

	dir_mirror = (t_vect)(vectsub(r.dir, vectmult(
		vectmult(scene.objects[a_def].n,
		dot(scene.objects[a_def].n, r.dir)), 2)));
	ray_mirror = (t_ray){vectadd(scene.objects[a_def].p,
		vectmult(scene.objects[a_def].n, 0.01)), dir_mirror, (t_vect){0}};
	return (vectmult(get_color(ray_mirror, scene, nb_rebound - 1), 0.8));
}

t_vect	sphere_trans(t_scene sc, t_ray r, t_vect int_p, int nb_r)
{
	double	n[2];
	t_vect	n_trans;
	double	radical;
	t_ray	r_ref;

	n[0] = 1;
	n[1] = 1.3;
	n_trans = sc.objects[sc.a_def].n;
	if (dot(r.dir, n_trans) > 0)
	{
		n[0] = 1.3;
		n[1] = 1;
		n_trans = vectmult(sc.objects[sc.a_def].n, -1);
	}
	radical = 1 - pow((n[0] / n[1]), 2) * (1 - pow(dot(r.dir, n_trans), 2));
	if (radical > 0)
	{
		r_ref = (t_ray){vectsub(sc.objects[sc.a_def].p,
			vectmult(n_trans, 0.01)), vectsub(vectmult(vectsub(r.dir,
			vectmult(n_trans, dot(r.dir, n_trans))), n[0] / n[1]),
			vectmult(n_trans, sqrt(radical))), (t_vect){0}};
		int_p = vectdiv(sphere_mirror(r, sc, sc.a_def, nb_r), 6);
		return (vectadd(int_p, vectdiv(get_color(r_ref, sc, nb_r - 1), 1.25)));
	}
	return (int_p);
}
