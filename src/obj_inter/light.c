/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 14:50:03 by charles           #+#    #+#             */
/*   Updated: 2020/11/12 14:50:05 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect	get_shadow(t_scene sc, t_ray r, int a, float *shadows)
{
	t_vect	int_pix;
	float	dot_p;

	int_pix = (t_vect){0};
	dot_p = dot(sc.ray_light.dir, sc.objects[sc.a_def].n) /
		getnorm2(vectsub(sc.lights[a].pos_light, sc.objects[sc.a_def].p));
	if (inter_shadow(sc, sc.lights[a].pos_light, shadows, sc.ray_light)
		&& sc.objects[sc.a_def].spe_mat != 1)
		int_pix = vectmult(vectdiv(sc.objects[sc.a_def].rgb, M_PI),
			(float)3000 * shadows[1] * fmin(255, fmax(0, fabs(dot_p))));
	else
	{
		r.s_rgb = vectmult(r.s_rgb, sc.lights[a].ratio);
		if (sc.objects[sc.a_def].flat_mat == 1 && !shadows[0])
			int_pix = vectadd(int_pix, vectmult(vectdiv(r.s_rgb, M_PI),
				8000 * fmin(255, fmax(0, fabs(dot_p)))));
		else if (!shadows[0])
		{
			if (sc.objects[sc.a_def].spe_mat != 1)
				int_pix = vectadd(int_pix, vectmult(vectdiv(r.s_rgb, M_PI),
					8000 * fmin(255, fmax(0, dot_p))));
		}
	}
	return (int_pix);
}

t_vect	get_light(t_scene scene, int a_def, t_vect int_pix, t_ray ray)
{
	int		a;
	float	shadows[2];

	a = -1;
	shadows[0] = 0;
	shadows[1] = 0.6;
	while (scene.lights[++a].type)
	{
		scene.ray_light = (t_ray){vectadd(scene.objects[a_def].p,
			vectmult(scene.objects[a_def].n, 0.001)),
			normalize(vectsub(scene.lights[a].pos_light,
			scene.objects[a_def].p)), (t_vect){0}};
		ray.s_rgb = (t_vect)set_surface_color(scene, ray, a);
		if (scene.lights[a].type == 7)
			int_pix = vectadd(int_pix, get_shadow(scene, ray, a, shadows));
		else if (scene.lights[a].type == 6)
			int_pix = vectadd(int_pix,
					vectmult(ray.s_rgb, scene.lights[a].ratio));
	}
	return (int_pix);
}
