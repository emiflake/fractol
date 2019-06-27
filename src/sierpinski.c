/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sierpinski.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmartins <nmartins@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/25 14:17:20 by nmartins       #+#    #+#                */
/*   Updated: 2019/06/27 13:49:34 by nmartins      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "const.h"
#include "fractals.h"
#include "state.h"

void			triangle(t_gfx_state *st, int x, int y, int size)
{
	const t_state	*mst = st->user_state;
	const long		epoch = mst->shift ? gfx_get_current_epoch() : 0;
	int				color;
	t_line			line;

	color = gfx_color_from_rgb(gfx_hsl2rgb(mk_hsl(
		fmod(epoch / 25, 360), 0.5, 0.5)));
	line.a = mk_point(x - size / 2, y + size / 2);
	line.b = mk_point(x + size / 2, y + size / 2);
	gfx_line(st, st->buffer, line, color);
	line.a = mk_point(x, y - size / 2);
	line.b = mk_point(x + size / 2, y + size / 2);
	gfx_line(st, st->buffer, line, color);
	line.a = mk_point(x, y - size / 2);
	line.b = mk_point(x - size / 2, y + size / 2);
	gfx_line(st, st->buffer, line, color);
}

void			sierpinski(t_gfx_state *st, double x, double y, double size)
{
	if (size > 50)
	{
		sierpinski(st, x + size / 4.0, y + size / 4.0, size / 2.0);
		sierpinski(st, x, y - size / 4.0, size / 2.0);
		sierpinski(st, x - size / 4.0, y + size / 4.0, size / 2.0);
	}
	if (x < 0 || x > WIN_WIDTH || y < 0 || y > WIN_HEIGHT)
		return ;
	triangle(st, x, y, size);
}

void			render_sierpinski(t_gfx_state *st)
{
	const t_state	*mst = st->user_state;
	const t_vec2	middle = mk_vec2(WIN_WIDTH / 2, WIN_HEIGHT / 2);

	(void)middle;
	gfx_fill_trgt(st, st->buffer, 0xFFFFFF);
	sierpinski(st,
		WIN_WIDTH / 2 - mst->camera_position.x / mst->zoom_level * 500,
		WIN_HEIGHT / 2 - mst->camera_position.y / mst->zoom_level * 500,
		5000 / mst->zoom_level);
}
