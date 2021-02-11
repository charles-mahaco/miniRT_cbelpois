/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 17:08:22 by charles           #+#    #+#             */
/*   Updated: 2020/11/12 17:08:24 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

float	inter_shadow_type(t_scene sc, t_ray ray_light, float t_light_min)
{
	int a;
	int has_inter_light;

	a = -1;
	while (sc.objects[++a].type)
	{
		if (a != sc.a_def)
		{
			sc.objects[a].t = 10E98;
			if (sc.objects[a].type == 1)
				has_inter_light = i_s_p(ray_light, &sc.objects[a].plane);
			else if (sc.objects[a].type == 2)
				has_inter_light = inter_sphere(ray_light, &sc.objects[a]);
			else if (sc.objects[a].type == 3)
				has_inter_light = inter_cylinder(ray_light, &sc.objects[a]);
			else if (sc.objects[a].type == 4)
				has_inter_light = inter_plane_square(ray_light, &sc.objects[a]);
			else if (sc.objects[a].type == 5)
				has_inter_light = inter_triangle(ray_light, &sc.objects[a]);
			if (has_inter_light && sc.objects[a].t < t_light_min)
				t_light_min = sc.objects[a].t;
		}
	}
	return (t_light_min);
}

int		inter_shadow(t_scene sc, t_vect pos_light, float *s, t_ray ray_light)
{
	float t_light_min;
	float d_light_2;

	t_light_min = 10E99;
	t_light_min = inter_shadow_type(sc, ray_light, t_light_min);
	d_light_2 = getnorm2(vectsub(pos_light, sc.objects[sc.a_def].p));
	if (t_light_min < 10E99 && t_light_min * t_light_min < d_light_2)
	{
		s[0] = 1;
		s[1] *= 0.5;
		return (1);
	}
	return (0);
}

float	inter_object_type(t_scene *scene, t_ray r, float min_t)
{
	int has_inter;
	int a;

	a = -1;
	while (scene->objects[++a].type > 0)
	{
		scene->objects[a].t = 10E98;
		has_inter = 0;
		if (scene->objects[a].type == 1)
			has_inter = inter_plane(r, &scene->objects[a]);
		else if (scene->objects[a].type == 2)
			has_inter = inter_sphere(r, &scene->objects[a]);
		else if (scene->objects[a].type == 3)
			has_inter = inter_cylinder(r, &scene->objects[a]);
		else if (scene->objects[a].type == 4)
			has_inter = inter_plane_square(r, &scene->objects[a]);
		else if (scene->objects[a].type == 5)
			has_inter = inter_triangle(r, &scene->objects[a]);
		if (has_inter && scene->objects[a].t < min_t)
		{
			min_t = scene->objects[a].t;
			scene->a_def = a;
		}
	}
	return (min_t);
}

t_vect	get_color(t_ray r, t_scene scene, int nb_rebound)
{
	float	min_t;
	t_vect	int_pix;

	min_t = 10E99;
	int_pix = (t_vect){0, 0, 0};
	if (nb_rebound == 0)
		return ((t_vect){0, 0, 0});
	min_t = inter_object_type(&scene, r, min_t);
	if (min_t < 10E99)
	{
		if (scene.objects[scene.a_def].sphere.transparent == 1)
			int_pix = sphere_trans(scene, r, int_pix, nb_rebound);
		if (scene.objects[scene.a_def].sphere.mirror == 1)
			int_pix = sphere_mirror(r, scene, scene.a_def, nb_rebound);
		if (scene.objects[scene.a_def].type)
			int_pix = get_light(scene, scene.a_def, int_pix, r);
		if (scene.diffuse_light &&
			scene.objects[scene.a_def].sphere.transparent != 1)
			int_pix = diffuse_light_on(scene, int_pix);
	}
	return (int_pix);
}
