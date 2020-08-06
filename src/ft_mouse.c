/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mouse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skale <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 20:58:07 by skale             #+#    #+#             */
/*   Updated: 2020/07/30 18:14:36 by mstefani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int		ft_mouse_move(int x, int y, t_mlx *mlx)
{
	double r;
	double a;

	r = 0.7885;
	a = ((double)x / WX ) * 2 * PI;
	mlx->wnd->juli_const.x = r * cos(a);
	mlx->wnd->juli_const.y =  r * sin(a);
	ft_draw_fractal(mlx);
	return (0);
}

int		ft_mouse_pressed(int butm, int x, int y, t_mlx *mlx)
{
	double deltax;
	double deltay;

	deltax = mlx->wnd->len_x * 0.1;
	deltay = mlx->wnd->len_y * 0.1;
	if (butm == 5 && INSIDE(x, y))
	{
		mlx->wnd->len_x = mlx->wnd->len_x * 0.9;
		mlx->wnd->len_y = mlx->wnd->len_y * 0.9;
		mlx->wnd->startx = mlx->wnd->startx + deltax * ((double)x/(WX - 1));
		mlx->wnd->starty = mlx->wnd->starty - deltay * ((double)y/(WY - 1));
	}
	if (butm == 4 && INSIDE(x, y) && mlx->wnd->len_y < 2)
	{
		mlx->wnd->len_y = mlx->wnd->len_y * 1.1;
		mlx->wnd->len_x = mlx->wnd->len_x * 1.1;
		mlx->wnd->startx = mlx->wnd->startx - deltax * ((double)x/(WX - 1));
		mlx->wnd->starty = mlx->wnd->starty + deltay * ((double)y/(WY - 1));
	}
	ft_draw_fractal(mlx);
	return (0);
}