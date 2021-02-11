/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 15:06:40 by charles           #+#    #+#             */
/*   Updated: 2020/12/22 15:06:43 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vect	set_surface_color(t_scene scene, t_ray ray, int a)
{
	ray.s_rgb.x = (scene.objects[scene.a_def].rgb.x >
			scene.lights[a].color.x) ? scene.lights[a].color.x :
			scene.objects[scene.a_def].rgb.x;
	ray.s_rgb.y = (scene.objects[scene.a_def].rgb.y >
			scene.lights[a].color.y) ? scene.lights[a].color.y :
			scene.objects[scene.a_def].rgb.y;
	ray.s_rgb.z = (scene.objects[scene.a_def].rgb.z >
			scene.lights[a].color.z) ? scene.lights[a].color.z :
			scene.objects[scene.a_def].rgb.z;
	return (ray.s_rgb);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

t_vect	ft_vect_range(t_vect v, float low, float high)
{
	v.x = fmin(high, fmax(low, v.x));
	v.y = fmin(high, fmax(low, v.y));
	v.z = fmin(high, fmax(low, v.z));
	return (v);
}

size_t	ft_strlen(const char *s)
{
	unsigned int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*n;
	size_t	i;

	i = 0;
	if (count == 0 || size == 0)
		return (NULL);
	n = malloc(size * count);
	while (i < (size * count))
	{
		((char*)n)[i] = 0;
		i++;
	}
	return (n);
}
