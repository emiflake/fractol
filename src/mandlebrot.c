/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mandlebrot.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmartins <nmartins@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/11 15:30:55 by nmartins       #+#    #+#                */
/*   Updated: 2019/06/25 20:01:23 by nmartins      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <pthread.h>

#include "const.h"
#include "fractals.h"
#include "state.h"

#define MAX_ITERATION 100

static void		dispatch_colorization(
	t_gfx_state *st,
	t_vec2 *p,
	double colorizer)
{
	const t_state	*mst = st->user_state;
	const long		epoch = mst->shift ? gfx_get_current_epoch() : 0;

	if (colorizer == -1)
		gfx_blit_pixel(st, st->buffer, demote_vec2(*p), 0x00);
	else
		gfx_blit_pixel(st, st->buffer, demote_vec2(*p),
			gfx_color_from_rgb(gfx_hsl2rgb(mk_hsl(
				fmod(colorizer * 20.0 + epoch / 25, 360), 0.7, 0.7))));
}

void			*render_mandlebrot_segment(void *vconf)
{
	const t_mandlebrot_segment_conf	*conf = vconf;
	const t_mandlebrot_spec			sp = conf->mspec;
	double							res;
	t_vec2							p;

	p.x = conf->pos.x;
	while (p.x - conf->pos.x < conf->size.width)
	{
		p.y = conf->pos.y;
		while (p.y - conf->pos.y < conf->size.height)
		{
			res = fract_mandlebrot(conf->st, &p, (t_mandlebrot_spec*)&sp);
			dispatch_colorization(conf->st, &p, res);
			p.y++;
		}
		p.x++;
	}
	return (NULL);
}

#define SEGMENT_COUNT 100

void			render_mandlebrot(t_gfx_state *st)
{
	const t_state				*mst = st->user_state;
	t_mandlebrot_spec			sp;
	t_mandlebrot_segment_conf	conf[SEGMENT_COUNT];
	pthread_t					threads[SEGMENT_COUNT];
	size_t						i;

	i = 0;
	sp.zoom = mst->zoom_level;
	sp.offset = mst->camera_position;
	while (i < SEGMENT_COUNT)
	{
		conf[i].mspec = sp;
		conf[i].pos = mk_point(0, i * (WIN_HEIGHT / SEGMENT_COUNT));
		conf[i].size = mk_dimensions(WIN_WIDTH, WIN_HEIGHT / SEGMENT_COUNT);
		conf[i].st = st;
		pthread_create(&threads[i], NULL, render_mandlebrot_segment, &conf[i]);
		i++;
	}
	i = 0;
	while (i < SEGMENT_COUNT)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

double			fix_iter(double zx, double zy, double iter)
{
	const double	log_zn = log(zx * zx + zy * zy) / 2.0;
	const double	nu = log(log_zn / log(2.0)) / log(2.0);

	return (iter + 1.0 - nu);
}

double			fract_mandlebrot(
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
	else
		return (-1);
	return (iteration);
	(void)st;
}
