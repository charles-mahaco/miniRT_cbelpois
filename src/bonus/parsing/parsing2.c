/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 15:58:52 by charles           #+#    #+#             */
/*   Updated: 2020/12/15 15:58:54 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	create_light(t_scene *sc, char *data, char *data_type, int *i)
{
	t_light light;

	ft_memset(&light, 0, sizeof(t_light));
	if (!ft_strcmp(data_type, "A"))
	{
		light.type = 6;
		has_n_param(sc, data, 3);
	}
	else
	{
		has_n_param(sc, data, 4);
		light.type = 7;
		light.pos_light = ft_atov(sc, data, i);
	}
	light.ratio = fmin(1, fmax(0, ft_atof(data, i)));
	light.color = ft_vect_range(ft_atov(sc, data, i), 0, 255);
	sc->lights[sc->nb_light - 1] = light;
	sc->nb_light--;
}

void	create_sphere(t_scene *sc, char *data, int *i)
{
	t_object	obj;
	t_sphere	sp;

	ft_memset(&obj, 0, sizeof(t_object));
	ft_memset(&sp, 0, sizeof(t_sphere));
	has_n_param(sc, data, 6);
	sp.center = ft_atov(sc, data, i);
	sp.radius = fmax(0, ft_atof(data, i));
	obj.rgb = ft_vect_range(ft_atov(sc, data, i), 0, 255);
	sp.transparent = (int)fmin(1, fmax(0, ft_atof(data, i)));
	sp.mirror = (int)fmin(1, fmax(0, ft_atof(data, i)));
	obj.spe_mat = sp.mirror || sp.transparent ? 1 : 0;
	obj.sphere = sp;
	obj.type = 2;
	obj.spec_rate = 0.6;
	sc->objects[sc->nb_object-- - 1] = obj;
}

void	create_plane(t_scene *sc, char *data, int *i)
{
	t_object	obj;
	t_plane		pl;

	ft_memset(&obj, 0, sizeof(t_object));
	ft_memset(&pl, 0, sizeof(t_plane));
	has_n_param(sc, data, 4);
	pl.p0 = ft_atov(sc, data, i);
	pl.n = ft_vect_range(ft_atov(sc, data, i), -1, 1);
	obj.rgb = ft_vect_range(ft_atov(sc, data, i), 0, 255);
	obj.plane = pl;
	obj.type = 1;
	obj.flat_mat = 1;
	obj.spec_rate = 0.4;
	sc->objects[sc->nb_object-- - 1] = obj;
}

void	create_cylinder(t_scene *sc, char *data, int *i)
{
	t_object	obj;
	t_cylinder	cy;

	ft_memset(&cy, 0, sizeof(t_cylinder));
	ft_memset(&obj, 0, sizeof(t_object));
	has_n_param(sc, data, 6);
	cy.p0 = ft_atov(sc, data, i);
	cy.n = ft_vect_range(ft_atov(sc, data, i), -1, 1);
	cy.radius = fmax(0, ft_atof(data, i));
	cy.height = fmax(0, ft_atof(data, i));
	obj.rgb = ft_vect_range(ft_atov(sc, data, i), 0, 255);
	obj.cylinder = cy;
	obj.type = 3;
	obj.spec_rate = 1.0;
	sc->objects[sc->nb_object - 1] = obj;
	sc->nb_object--;
}

void	create_square_triangle(t_scene *sc, char *data, char *data_type, int *i)
{
	t_object	obj;
	t_square	sq;
	t_triangle	tr;

	ft_memset(&obj, 0, sizeof(t_object));
	has_n_param(sc, data, 5);
	if (data_type[0] == 's')
	{
		sq.p0 = ft_atov(sc, data, i);
		sq.n = ft_vect_range(ft_atov(sc, data, i), -1, 1);
		sq.height = fmax(0.01, ft_atof(data, i));
		obj.square = sq;
		obj.type = 4;
	}
	else
	{
		tr.p0 = ft_atov(sc, data, i);
		tr.p1 = ft_atov(sc, data, i);
		tr.p2 = ft_atov(sc, data, i);
		obj.triangle = tr;
		obj.type = 5;
	}
	obj.rgb = ft_vect_range(ft_atov(sc, data, i), 0, 255);
	obj.flat_mat = 1;
	sc->objects[sc->nb_object-- - 1] = obj;
}
