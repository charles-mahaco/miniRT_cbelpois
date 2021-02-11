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

#include "minirt_bonus.h"

t_vect	specular_comp(t_scene scene, t_ray ray, t_ray ray_light, int a)
{
	t_vect	spec;
	t_vect	light_dir;
	t_vect	reflection_dir;
	float	spec_dot;

	spec = (t_vect){0};
	if (scene.objects[scene.a_def].spe_mat)
		return ((t_vect){0});
	light_dir = normalize(vectsub(scene.lights[a].pos_light, ray_light.orig));
	reflection_dir = vectsub(ray.dir, vectmult(scene.objects[scene.a_def].n,
					2 * dot(ray.dir, scene.objects[scene.a_def].n)));
	spec_dot = fmax(dot(reflection_dir, light_dir), 0);
	if (spec_dot)
		spec = vectmult(scene.lights[a].color,
				scene.objects[scene.a_def].spec_rate * pow(spec_dot, 7) *
				scene.lights[a].ratio);
	return (spec);
}

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
			int_pix = vectadd(int_pix, specular_comp(sc, r, sc.ray_light, a));
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

t_vect	diffuse_light_ray(t_scene scene)
{
	double	r[2];
	t_vect	dir_rand_local;
	t_vect	tangent[2];
	t_vect	dir_alea;

	r[0] = ((float)rand() / (float)(RAND_MAX)) * 0.75;
	r[1] = ((float)rand() / (float)(RAND_MAX)) * 0.75;
	dir_rand_local = (t_vect){cos(2 * M_PI * r[0]) * sqrt(1 - r[1]),
		sin(2 * M_PI * r[0]) * sqrt(1 - r[1]), sqrt(r[1])};
	tangent[0] = normalize(crossp(scene.objects[scene.a_def].n,
		(t_vect){(((float)rand() / (float)(RAND_MAX)) * 1) - 0.5,
			(((float)rand() / (float)(RAND_MAX)) * 1) - 0.5,
			(((float)rand() / (float)(RAND_MAX)) * 1) - 0.5}));
	tangent[1] = crossp(tangent[0], scene.objects[scene.a_def].n);
	dir_alea = vectadd(vectadd(vectmult(scene.objects[scene.a_def].n,
		dir_rand_local.z), vectmult(tangent[0], dir_rand_local.x)),
		vectmult(tangent[1], dir_rand_local.y));
	return (dir_alea);
}

t_vect	diffuse_light_on(t_scene scene, t_vect int_pix)
{
	t_vect	dir_alea;
	t_ray	ray_alea;

	dir_alea = diffuse_light_ray(scene);
	ray_alea = (t_ray){vectadd(scene.objects[scene.a_def].p,
		vectmult(scene.objects[scene.a_def].n, 0.01)), dir_alea,
				(t_vect){0}};
	return (vectadd(int_pix, vectdiv(get_color(ray_alea,
			scene, scene.nb_rebound - 1), 1.25)));
}
