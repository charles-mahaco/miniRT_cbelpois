/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 15:59:00 by charles           #+#    #+#             */
/*   Updated: 2020/12/15 15:59:02 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_file(int fd, t_scene *sc, int ret)
{
	char	data_type[2];
	int		j;
	int		i;
	char	*line;

	line = NULL;
	ret = 1;
	while (ret > 0)
	{
		j = 0;
		i = 0;
		ret = get_next_line(fd, &line);
		if (ft_strcmp(line, "") != 0)
		{
			while (line[i] && line[i] != ' ' && j < 2 && line[i] != '\t'
				&& line[i] != '\n')
				data_type[j++] = line[i++];
			data_type[j] = '\0';
			check_file2(sc, data_type);
			check_file3(sc, line, i);
		}
		free(line);
		line = NULL;
	}
	check_file4(sc);
}

int		rt_parsing(t_scene *scene, char **argv)
{
	char	*line;
	int		fd;
	int		ret;
	int		fd2;

	ret = 0;
	if ((fd2 = open(argv[1], O_RDONLY)) < 0)
	{
		scene->error.error_type = "Error 0: Invalid .rt file\n";
		return (0);
	}
	check_file(fd2, scene, ret);
	close(fd2);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (0);
	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		scene_creation(scene, line);
		free(line);
		line = NULL;
	}
	close(fd);
	return (1);
}

void	scene_creation(t_scene *scene, char *line)
{
	char	data_type[2];
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!ft_strcmp(line, ""))
		return ;
	while (line[i] && line[i] != ' ' && j < 2 && line[i] != '\t'
		&& line[i] != '\n')
		data_type[j++] = line[i++];
	data_type[j] = '\0';
	if (!ft_strcmp(data_type, "R") || !ft_strcmp(data_type, "c"))
		create_res_cam(scene, line, data_type, &i);
	else if (!ft_strcmp(data_type, "A") || !ft_strcmp(data_type, "l"))
		create_light(scene, line, data_type, &i);
	else if (!ft_strcmp(data_type, "sp"))
		create_sphere(scene, line, &i);
	else if (!ft_strcmp(data_type, "pl"))
		create_plane(scene, line, &i);
	else if (!ft_strcmp(data_type, "cy"))
		create_cylinder(scene, line, &i);
	else if (!ft_strcmp(data_type, "sq") || !ft_strcmp(data_type, "tr"))
		create_square_triangle(scene, line, data_type, &i);
}

void	create_res_cam(t_scene *sc, char *data, char *data_type, int *i)
{
	t_camera cam;

	if (!ft_strcmp(data_type, "R"))
	{
		has_n_param(sc, data, 3);
		sc->res.width = (int)fmin(1920, fmax(1, ft_atof(data, i)));
		sc->res.height = (int)fmin(1080, fmax(1, ft_atof(data, i)));
		sc->nb_rebound = 4;
	}
	else
	{
		has_n_param(sc, data, 4);
		ft_memset(&cam, 0, sizeof(t_camera));
		cam.orig = ft_atov(sc, data, i);
		cam.orit = ft_vect_range(ft_atov(sc, data, i), -1, 1);
		cam.fov = (2 * tan((int)fmin(180, fmax(0, ft_atof(data, i))) *
			M_PI / 180 / 2));
		sc->cam[sc->curr_cam++] = cam;
	}
}
