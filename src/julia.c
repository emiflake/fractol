/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   julia.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmartins <nmartins@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/10 18:28:29 by nmartins       #+#    #+#                */
/*   Updated: 2019/06/10 20:39:11 by nmartins      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libgfx.h>

#include "const.h"
#include "fractals.h"
# include <stdio.h>

#define MAX_ITERATION 100

int		fract_julia(t_gfx_state *st, t_vec2 *pos, t_julia_spec *spec)
{
	double	zx;
	double	zy;
	size_t	iteration;
	double	tmp;

	zx = pos->x / 1600.0 * 7 - 2.0;
	zy = pos->y / 900.0 * 4.0 - 2.0;
	iteration = 0;
	while (zx * zx + zy * zy < 4 && iteration < MAX_ITERATION)
	{
		tmp = zx * zx - zy * zy;
		zy = 2 * zx * zy + ((double)st->mouse_state.mouse_pos.y / WIN_HEIGHT - 0.5) * 2.5;
		zx = tmp + ((double)st->mouse_state.mouse_pos.x / WIN_WIDTH - 0.5) * 2.5;
		iteration++;
	}
	if (iteration == MAX_ITERATION)
		return (-1);
	else
		return (iteration);
	(void)st;
	(void)spec;
}
