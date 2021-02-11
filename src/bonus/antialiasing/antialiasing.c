/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 13:26:13 by charles           #+#    #+#             */
/*   Updated: 2020/11/12 13:26:16 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_vect	antialiasing_on(t_ray r, t_scene scene, int i, int j)
{
	int		x;
	double	r2;
	double	dev;
	t_vect	color_def;

	x = 0;
	color_def = (t_vect){0, 0, 0};
	while (x++ < scene.nrays)
	{
		r2 = ((float)rand() / (float)(RAND_MAX)) * 1;
		dev = sqrt(-2 * log(((float)rand() / (float)(RAND_MAX)) * 1));
		r.orig = scene.cam[scene.curr_cam].orig;
		r.dir = normalize((t_vect)
				{j - scene.res.width / 2 + 0.5 + dev * cos(2 * M_PI * r2),
				i - scene.res.height / 2 + 0.5 + dev * sin(2 * M_PI * r2),
				-scene.res.width / scene.cam[scene.curr_cam].fov});
		r.dir = x_axis_rot(r.dir, scene.cam[scene.curr_cam].orit.x);
		r.dir = y_axis_rot(r.dir, scene.cam[scene.curr_cam].orit.y);
		r.dir = z_axis_rot(r.dir, scene.cam[scene.curr_cam].orit.z);
		color_def = vectadd(color_def,
			vectdiv(get_color(r, scene, scene.nb_rebound), scene.nrays));
	}
	return (color_def);
}

t_vect	antialiasing_off(t_ray r, t_scene scene, int i, int j)
{
	r.orig = scene.cam[scene.curr_cam].orig;
	r.dir = normalize((t_vect){j - scene.res.width / 2,
			i - scene.res.height / 2, -scene.res.width /
			scene.cam[scene.curr_cam].fov});
	r.dir = x_axis_rot(r.dir, scene.cam[scene.curr_cam].orit.x);
	r.dir = y_axis_rot(r.dir, scene.cam[scene.curr_cam].orit.y);
	r.dir = z_axis_rot(r.dir, scene.cam[scene.curr_cam].orit.z);
	return (get_color(r, scene, scene.nb_rebound));
}

t_vect	filter_sepia(t_vect color_def)
{
	t_vect	int_pix;

	int_pix.x = (color_def.x * 0.393) + (color_def.y * 0.769) +
				(color_def.z * 0.189);
	int_pix.y = (color_def.x * 0.349) + (color_def.y * 0.686) +
				(color_def.z * 0.168);
	int_pix.z = (color_def.x * 0.272) + (color_def.y * 0.534) +
				(color_def.z * 0.131);
	return (int_pix);
}
