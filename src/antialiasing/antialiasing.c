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

#include "minirt.h"

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
