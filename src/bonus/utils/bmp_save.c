/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 13:18:18 by charles           #+#    #+#             */
/*   Updated: 2020/11/12 13:18:23 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	fill_bmp_data(t_scene *scene, t_vect color_def, int i, int j)
{
	scene->data.bmp_img[(j * 3) + (3 * scene->res.width * i) + 2] =
	fmin(255, (int)color_def.x);
	scene->data.bmp_img[(j * 3) + (3 * scene->res.width * i) + 1] =
	fmin(255, (int)color_def.y);
	scene->data.bmp_img[(j * 3) + (3 * scene->res.width * i) + 0] =
	fmin(255, (int)color_def.z);
	scene->pos_img = (j * 4) + (1 * scene->data.size_line * i);
	scene->data.img_data[scene->pos_img++] = fmin(255, (int)color_def.z);
	scene->data.img_data[scene->pos_img++] = fmin(255, (int)color_def.y);
	scene->data.img_data[scene->pos_img++] = fmin(255, (int)color_def.x);
	scene->data.img_data[scene->pos_img] = 0;
}

void	get_bmpfileheader(int width, int height, int *fd)
{
	int				filesize;
	int				i;
	unsigned char	bmpfileheader[14];

	i = -1;
	while (++i < 14)
		bmpfileheader[i] = 0;
	filesize = 54 + 3 * width * height;
	bmpfileheader[0] = 'B';
	bmpfileheader[1] = 'M';
	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize >> 8);
	bmpfileheader[4] = (unsigned char)(filesize >> 16);
	bmpfileheader[5] = (unsigned char)(filesize >> 24);
	bmpfileheader[10] = (unsigned char)54;
	write(*fd, bmpfileheader, 14);
}

void	get_bmpinfoheader(int width, int height, int *fd)
{
	int				i;
	unsigned char	bmpinfoheader[40];

	i = -1;
	while (++i < 40)
		bmpinfoheader[i] = 0;
	bmpinfoheader[0] = (unsigned char)40;
	bmpinfoheader[4] = (unsigned char)(width);
	bmpinfoheader[5] = (unsigned char)(width >> 8);
	bmpinfoheader[6] = (unsigned char)(width >> 16);
	bmpinfoheader[7] = (unsigned char)(width >> 24);
	bmpinfoheader[8] = (unsigned char)(height);
	bmpinfoheader[9] = (unsigned char)(height >> 8);
	bmpinfoheader[10] = (unsigned char)(height >> 16);
	bmpinfoheader[11] = (unsigned char)(height >> 24);
	bmpinfoheader[12] = (unsigned char)1;
	bmpinfoheader[14] = (unsigned char)24;
	write(*fd, bmpinfoheader, 40);
}

int		save_bmp_image(char *bmp_img, int width, int height)
{
	int				fd;
	int				i;
	unsigned char	bmppad[3];

	ft_memset(bmppad, 0, 3);
	i = -1;
	if ((fd = open("img1.bmp", O_RDWR | O_CREAT, 0666)) < 0)
	{
		write(1, "Error opening file", 18);
		return (0);
	}
	get_bmpfileheader(width, height, &fd);
	get_bmpinfoheader(width, height, &fd);
	while (++i < height)
	{
		write(fd, bmp_img + (width * (height - i - 1) * 3), 3 * width);
		write(fd, bmppad, (4 - (width * 3) % 4) % 4);
	}
	close(fd);
	free(bmp_img);
	return (1);
}
