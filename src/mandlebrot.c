/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mandlebrot.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmartins <nmartins@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/11 15:30:55 by nmartins       #+#    #+#                */
/*   Updated: 2019/06/11 18:57:05 by nmartins      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libgfx.h>
#include <math.h>

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

void			render_mandlebrot(t_gfx_state *st)
{
	const t_state		*mst = st->user_state;
	t_mandlebrot_spec	sp;
	int					res;
	t_vec2				p;

	sp.zoom = mst->zoom_level;
	sp.offset = mst->camera_position;
	p.x = 0;
	while (p.x < WIN_WIDTH)
	{
		p.y = 0;
		while (p.y < WIN_HEIGHT)
		{
			res = fract_mandlebrot(st, &p, &sp);
			dispatch_colorization(st, &p, res);
			p.y++;
		}
		p.x++;
	}
}

double			fix_iter(double zx, double zy, double iter)
{
	const double	log_zn = log(zx * zx + zy + zy) / 2.0;
	const double	nu = log(log_zn / log(2)) / log(2);

	return (iter + 1 - nu);
}

int				fract_mandlebrot(
	t_gfx_state *st,
	t_vec2 *pos,
	t_mandlebrot_spec *spec)
{
	t_vec2	z;
	t_vec2	p;
	double	iteration;
	double	tmp;

	z.x = pos->x / WIN_WIDTH * spec->zoom - spec->zoom / 2 + spec->offset.x;
	z.y = pos->y / WIN_HEIGHT * spec->zoom - spec->zoom / 2 + spec->offset.y;
	p = mk_vec2(0, 0);
	iteration = 0;
	while (p.x * p.x + p.y * p.y <= (1 << 16) && iteration < MAX_ITERATION)
	{
		tmp = p.x * p.x - p.y * p.y + z.x;
		p.y = 2 * p.x * p.y + z.y;
		p.x = tmp;
		iteration++;
	}
	if (iteration < MAX_ITERATION)
		iteration = fix_iter(p.x, p.y, iteration);
	return (iteration);
	(void)st;
}
