/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 15:21:36 by charles           #+#    #+#             */
/*   Updated: 2020/12/22 15:21:38 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rendering(t_scene *scene)
{
	int		i;
	int		j;
	t_vect	color_def;

	i = -1;
	while (++i < scene->res.height)
	{
		j = -1;
		while (++j < scene->res.width)
		{
			color_def = antialiasing_off(scene->ray, *scene, i, j);
			fill_bmp_data(scene, color_def, i, j);
		}
		if (!scene->save_bmp)
			mlx_put_image_to_window(scene->data.mlx_ptr, scene->data.mlx_win,
				scene->data.img_ptr, 0, 0);
	}
}

int		refresh_hook(t_scene *scene)
{
	mlx_put_image_to_window(scene->data.mlx_ptr, scene->data.mlx_win,
				scene->data.img_ptr, 0, 0);
	return (0);
}

int		key_hook(int keycode, t_scene *sc)
{
	if (keycode == 99)
	{
		if (sc->curr_cam < sc->nb_cam - 1)
			sc->curr_cam++;
		else
			sc->curr_cam = 0;
		sc->data.bmp_img = NULL;
		sc->data.bmp_img = (char *)malloc(3 * sc->res.width *
			sc->res.height + 1);
		rendering(sc);
	}
	if (keycode == 65307)
		close_button(sc);
	return (0);
}

int		data_init(t_scene *scene)
{
	t_data	data;

	if ((data.mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if (!scene->save_bmp)
		if ((data.mlx_win = mlx_new_window(data.mlx_ptr, scene->res.width,
			scene->res.height, "Hello world")) == NULL)
			return (EXIT_FAILURE);
	data.img_ptr = mlx_new_image(data.mlx_ptr, scene->res.width,
		scene->res.height);
	data.img_data = mlx_get_data_addr(data.img_ptr, &data.bpp,
		&data.size_line, &data.endian);
	data.bmp_img = NULL;
	data.bmp_img = (char *)malloc(3 * scene->res.width * scene->res.height + 1);
	scene->data = data;
	return (1);
}

int		main(int argc, char *argv[])
{
	t_scene		scene;

	if (parsing(&scene, argc, argv) && !scene.error.error_type)
		if (!data_init(&scene))
			scene.error.error_type = "Error 0: Error initializing data\n";
	if (scene.error.error_type != NULL)
	{
		write(1, scene.error.error_type, ft_strlen(scene.error.error_type));
		close_button(&scene);
		return (0);
	}
	rendering(&scene);
	if (scene.save_bmp == 1)
		save_bmp_image(scene.data.bmp_img, scene.res.width, scene.res.height);
	else
	{
		free(scene.data.bmp_img);
		mlx_hook(scene.data.mlx_win, 33, 0, close_button, &scene);
		mlx_key_hook(scene.data.mlx_win, key_hook, &scene);
		mlx_loop_hook(scene.data.mlx_ptr, refresh_hook, &scene);
		mlx_loop(scene.data.mlx_ptr);
	}
	close_button(&scene);
	return (EXIT_SUCCESS);
}
