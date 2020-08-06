/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_win.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 17:59:19 by mstefani          #+#    #+#             */
/*   Updated: 2020/07/30 18:12:57 by mstefani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int		ft_key_win(int key, t_mlx *mlx)
{
	if (key == ESC_KEY)
	{
		mlx_destroy_window(mlx->wnd->ptr, mlx->wnd->wnd);
		free(mlx->wnd->img);
		free(mlx->wnd->ptr);
		free(mlx->wnd);
		free(mlx);
		exit(0);
	}
	if (key == PLUSITER)
		mlx->wnd->iter += 10;
	if (key == MINUSITER)
		mlx->wnd->iter -= 10;
	ft_draw_fractal(mlx);
	return (0);
}
