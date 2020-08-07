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

int		ft_ins(t_dot dot)
{
	double	lim;

	lim = 2.0;
	if (dot.x < lim && dot.x > -lim && dot.y < lim && dot.y > -lim)
		return (1);
	return (0);
}

int		ft_julia(t_dot dot, t_dot jconst, int wnditer)
{
	t_dot	cp;
	double	tmp;
	int		iter;

	iter = 0;

	cp.x = dot.x;
	cp.y = dot.y;
	while (iter < wnditer && ft_ins(cp))
	{
		tmp = cp.x;
		cp.x = cp.x * cp.x - cp.y * cp.y + jconst.x;
		cp.y = 2 * tmp * cp.y + jconst.y;
		iter++;
	}
	if (ft_ins(cp))
		return (BACKGROUND);
	else if (iter > 0 && iter < 50)
		return (rgb_to_int(10, 0 + (2 * iter), 0 + 3 * iter));
	else
		return (rgb_to_int(50 + (1 * iter), 0 + (2 * iter), 50 + 2 * iter));
}
