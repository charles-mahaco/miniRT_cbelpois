/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 12:51:59 by charles           #+#    #+#             */
/*   Updated: 2020/12/15 12:52:05 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		parsing(t_scene *scene, int argc, char **argv)
{
	ft_memset(scene, 0, sizeof(t_scene));
	scene->error.error_type = NULL;
	if (argc == 3 && (!ft_strcmp(argv[2], "-save") || !ft_strcmp(argv[2],
		"--save") || !ft_strcmp(argv[2], "–save")))
		scene->save_bmp = 1;
	if (argc == 1)
	{
		scene->error.error_type = "Error 1: Missing .rt file argument\n";
		return (0);
	}
	else if (argc == 2 || scene->save_bmp)
	{
		if (!rt_parsing(scene, argv))
			return (0);
	}
	else
	{
		scene->error.error_type = "Error 2: Invalid arguments\n";
		return (0);
	}
	scene->curr_cam = 0;
	scene->pos_img = 0;
	scene->ray.orig = scene->cam[scene->curr_cam].orig;
	return (1);
}

void	check_file4(t_scene *sc)
{
	if (sc->nb_a > 1 || !sc->nb_a || !sc->nb_cam || sc->nb_r > 1 || !sc->nb_r)
	{
		if (sc->nb_a > 1 || sc->nb_r > 1)
			sc->error.error_type = "Error 6: more than one 'R' or 'A'\n";
		else
			sc->error.error_type = "Error 7: missing 'R', 'A' or 'c'\n";
	}
	sc->lights = ft_calloc(sc->nb_light + 1, sizeof(t_light));
	sc->objects = ft_calloc(sc->nb_object + 1, sizeof(t_object));
	sc->cam = ft_calloc(sc->nb_cam + 1, sizeof(t_camera));
}

void	check_file3(t_scene *sc, char *str, int i)
{
	while (str[i])
	{
		if ((str[i] < 47 || str[i] > 58) && (str[i] != 44 && str[i] != 46
		&& str[i] != 45 && str[i] != ' ' && str[i] != '\n' && str[i] != '\r'
		&& str[i] != '\t' && str[i] != '\v' && str[i] != '\f'))
			sc->error.error_type = "Error 3: wrong character\n";
		if ((i >= 1 && (str[i] == 44 && ((str[i - 1] < 47 || str[i - 1] > 58) ||
			((str[i + 1] < 47 || str[i + 1] > 58) && str[i + 1] != 45)))) ||
			(str[i] == 46 && ((str[i - 1] < 47 || str[i - 1] > 58) ||
			(str[i + 1] < 47 || str[i + 1] > 58))) ||
			(str[i] == 45 && str[i - 1] == 45))
			sc->error.error_type = "Error 4: wrong formatting1\n";
		i++;
	}
}

void	check_file2(t_scene *sc, char *data_type)
{
	if (!ft_strcmp(data_type, "c"))
		sc->nb_cam++;
	else if (!ft_strcmp(data_type, "pl") || !ft_strcmp(data_type, "sp")
		|| !ft_strcmp(data_type, "cy") || !ft_strcmp(data_type, "tr")
		|| !ft_strcmp(data_type, "sq"))
		sc->nb_object++;
	else if (!ft_strcmp(data_type, "l"))
		sc->nb_light++;
	else if (!ft_strcmp(data_type, "R"))
		sc->nb_r++;
	else if (!ft_strcmp(data_type, "A"))
	{
		sc->nb_light++;
		sc->nb_a++;
	}
	else
		sc->error.error_type = "Error 5: wrong object type\n";
}

void	has_n_param(t_scene *sc, char *str, int nb)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\t' || str[i] == '\v' || str[i] == '\f'))
			i++;
		if (!str[i])
			break ;
		while (str[i] && (str[i] != ' ' && str[i] != '\n' && str[i] != '\r'
		&& str[i] != '\t' && str[i] != '\v' && str[i] != '\f'))
			i++;
		j++;
	}
	if (j != nb)
		sc->error.error_type = "Error 9: wrong number of parameters\n";
}
