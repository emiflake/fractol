/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   julia.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmartins <nmartins@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/10 18:28:29 by nmartins       #+#    #+#                */
/*   Updated: 2019/06/25 00:31:58 by nmartins      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libgfx.h>
#include <math.h>
#include <stdio.h>
#include <pthread.h>

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
				fmod(colorizer * 25, 360), 0.7, 0.7))));
}

typedef struct	s_julia_segment_conf
{
	t_gfx_state		*st;
	t_dimensions	size;
	t_point			pos;
	t_julia_spec	jspec;
}				t_julia_segment_conf;

void			*render_julia_segment(void *vconf)
{
	const t_julia_segment_conf	*conf = vconf;
	const t_julia_spec			sp = conf->jspec;
	int				res;
	t_vec2			p;

	p.x = conf->pos.x;
	while (p.x - conf->pos.x < conf->size.width)
	{
		p.y = conf->pos.y;
		while (p.y - conf->pos.y < conf->size.height)
		{
			res = fract_julia(conf->st, &p, (t_julia_spec*)&sp);
			dispatch_colorization(conf->st, &p, res);
			p.y++;
		}
		p.x++;
	}
	return (NULL);
}

#define SEGMENT_COUNT 32

void			render_julia(t_gfx_state *st)
{
	const t_state			*mst = st->user_state;
	t_julia_spec			sp;
	t_julia_segment_conf	conf[SEGMENT_COUNT];
	pthread_t				threads[SEGMENT_COUNT];
	size_t					i;

	i = 0;
	while (i < SEGMENT_COUNT)
	{
		sp.c = mk_vec2(
			((double)st->mouse_state.mouse_pos.x / WIN_WIDTH - 0.5) * 2.5,
			((double)st->mouse_state.mouse_pos.y / WIN_HEIGHT - 0.5) * 2.5);
		sp.zoom = mst->zoom_level;
		sp.offset = mst->camera_position;
		conf[i].jspec = sp;
		conf[i].pos = mk_point(0, i * (WIN_HEIGHT / SEGMENT_COUNT));
		conf[i].size = mk_dimensions(WIN_WIDTH, WIN_HEIGHT / SEGMENT_COUNT);
		conf[i].st = st;
		pthread_create(&threads[i], NULL, render_julia_segment, (void*)&conf[i]);
		i++;
	}
	i = 0;
	while (i < SEGMENT_COUNT)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

int				fract_julia(t_gfx_state *st, t_vec2 *pos, t_julia_spec *spec)
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
