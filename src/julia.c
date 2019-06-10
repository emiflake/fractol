/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   julia.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmartins <nmartins@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/10 18:28:29 by nmartins       #+#    #+#                */
/*   Updated: 2019/06/11 01:10:27 by nmartins      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libgfx.h>

#include "const.h"
#include "fractals.h"
#include "state.h"

#define MAX_ITERATION 100

static void		dispatch_colorization(t_gfx_state *st, t_vec2 *p, int colorizer)
{
	(void)st;
	(void)colorizer;
	if (colorizer == -1)
		gfx_blit_pixel(st, st->buffer, demote_vec2(*p), 0x00);
	else
		gfx_blit_pixel(st, st->buffer, demote_vec2(*p),
			gfx_color_from_rgb(gfx_hsl2rgb(mk_hsl(
				colorizer * 10, 0.7, 0.7))));
}

void	render_julia(t_gfx_state *st)
{
	const t_state	*mst = st->user_state;
	t_julia_spec	sp;
	int				res;
	t_vec2			p;

	sp.c = mk_vec2(
		((double)st->mouse_state.mouse_pos.x / WIN_WIDTH - 0.5) * 2.5,
		((double)st->mouse_state.mouse_pos.y / WIN_HEIGHT - 0.5) * 2.5);
	sp.zoom = mst->zoom_level;
	sp.offset = mst->camera_position;
	mst = st->user_state;
	for (p.x = 0; p.x < WIN_WIDTH; p.x++)
	{
		for (p.y = 0; p.y < WIN_HEIGHT; p.y++)
		{
			res = fract_julia(st, &p, &sp);
			dispatch_colorization(st, &p, res);
		}
	}
}

int		fract_julia(t_gfx_state *st, t_vec2 *pos, t_julia_spec *spec)
{
	double	zx;
	double	zy;
	size_t	iteration;
	double	tmp;

	zx = pos->x / WIN_WIDTH * spec->zoom - spec->zoom / 2 + spec->offset.x;
	zy = pos->y / WIN_HEIGHT * spec->zoom - spec->zoom / 2 + spec->offset.y;
	iteration = 0;
	while (zx * zx + zy * zy < 4 && iteration < MAX_ITERATION)
	{
		tmp = zx * zx - zy * zy;
		zy = 2 * zx * zy + spec->c.y;
		zx = tmp + spec->c.x;
		iteration++;
	}
	if (iteration == MAX_ITERATION)
		return (-1);
	else
		return (iteration);
	(void)st;
}
