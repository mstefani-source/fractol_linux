/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_fractal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 17:58:23 by mstefani          #+#    #+#             */
/*   Updated: 2020/07/30 18:09:35 by mstefani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

t_dot 	ft_add(t_dot c1, t_dot c2)
{
	return ((t_dot){c1.x + c2.x, c1.y + c2.y});
}

t_dot	ft_quadro(t_dot c1)
{
	t_dot res;

	res.x = c1.x * c1.x - c1.y * c1.y;
	res.y = 2 * c1.x * c1.y;
	return (res);
}

int 	ft_inside(t_dot dot)
{
	double lim;

	lim = 2.0;
	if (dot.x < lim && dot.x > -lim && dot.y < lim && dot.y > -lim)
		return (1);
	return (0);
}

int		ft_mb(t_dot dot, int wnditer)
{
	t_dot 	cp;
	int		iter = 0;

	cp.x = 0;
	cp.y = 0;
	while (iter < wnditer && ft_inside(cp))
	{
		cp = ft_add(ft_quadro(cp), dot);
		iter++;
	}
	if (ft_inside(cp))
		return(BACKGROUND);
	else if (iter > 0 && iter < 50)
		return(rgb_to_int(10,0+ (2 * iter) ,0 + 3 * iter));
	else
		return(rgb_to_int(50+ (1 * iter),0 + (2 * iter) ,50 + 2 * iter));
}

int		ft_julia(t_dot dot, t_dot jconst, int wnditer)
{
	t_dot 	cp;
	double 	tmp;
	int		iter;

	iter = 0;
	cp.x = dot.x;
	cp.y = dot.y;

	while (iter < wnditer && ft_inside(cp))
	{
		tmp = cp.x;
		cp.x = cp.x * cp.x - cp.y * cp.y + jconst.x;
		cp.y = 2 * tmp * cp.y + jconst.y;
		iter++;
	}
	if (ft_inside(cp))
		return(BACKGROUND);
	else if (iter > 0 && iter < 50)
		return(rgb_to_int(10,0 + (2 * iter) ,0 + 3 * iter));
	else
		return(rgb_to_int(50 + (1 * iter),0 + (2 * iter) ,50 + 2 * iter));
}

void 		*thread_function(void *func)
{
	int 	*image;
	int 	i;
	double 	x;
	double 	y;
	t_wnd 	*wnd;

	wnd = (t_wnd *)func;
	wnd->stepx = wnd->len_x / WX;
	wnd->stepy = wnd->len_y / WY;
	y = wnd->starty - wnd->sty * wnd->stepy;
	image = (int *) (wnd->data_addr);
	while (wnd->sty < wnd->endy)
	{
		i = 0;
		x = wnd->startx;
		while (i < WX)
		{
			x = x + wnd->stepx;
			switch (wnd->type)
			{
				case '1': image[i+wnd->sty * WX] = ft_mb((t_dot) {x, y}, wnd->iter);
				break;
				case '2': image[i+wnd->sty * WX] = ft_julia((t_dot){x, y}, wnd->juli_const, wnd->iter);
				break;
				default: mlx_destroy_image(wnd->ptr,wnd->img);
			}
			i++;
		}
		y = y - wnd->stepy;
		wnd->sty++;
	}
	return (NULL);
}

void		ft_multi_thread(t_wnd *scene)
{
	pthread_t	id[NUM_THREAD];
	t_wnd		data[NUM_THREAD];
	int			n;

	n = 0;
	while (n < NUM_THREAD)
	{
		data[n] = *scene;
		data[n].sty = n * WY / NUM_THREAD;
		data[n].endy = (n + 1) * WY / NUM_THREAD;
		pthread_create(&id[n], NULL, thread_function, &data[n]);
		n += 1;
	}
	n = 0;
	while (n < NUM_THREAD)
	{
		pthread_join(id[n], NULL);
		n += 1;
	}
}

void 	ft_draw_fractal(t_mlx *mlx)
{
	ft_multi_thread(mlx->wnd);
	mlx_put_image_to_window(mlx->wnd->ptr, mlx->wnd->wnd, mlx->wnd->img, 0, 0);
}
