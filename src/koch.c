/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   koch.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmartins <nmartins@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/25 19:28:53 by nmartins       #+#    #+#                */
/*   Updated: 2019/06/25 20:31:36 by nmartins      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "const.h"
#include "fractals.h"
#include "state.h"

void			koch(t_gfx_state *st, t_vec2 p1, t_vec2 p2, int times)
{
	t_vec2			p3;
	t_vec2			p4;
	t_vec2			p5;
	const double	theta = M_PI / 3.0;
	t_line			l;
 
	if (times > 0)
	{
		p3 = (t_vec2){(2 * p1.x + p2.x) / 3, (2 * p1.y + p2.y) / 3};
		p5 = (t_vec2){(2 * p2.x + p1.x) / 3, (2 * p2.y + p1.y) / 3};
		p4 = (t_vec2){p3.x + (p5.x - p3.x) * cos(theta) +
			(p5.y - p3.y) * sin(theta),
			p3.y - (p5.x - p3.x) * sin(theta) + (p5.y - p3.y) * cos(theta)};
 
		koch(st, p1, p3, times - 1);
		koch(st, p3, p4, times - 1);
		koch(st, p4, p5, times - 1);
		koch(st, p5, p2, times - 1);
	}
	else
	{
		l = mk_line(demote_vec2(p1), demote_vec2(p2));
		gfx_line(st, st->buffer, l, 0x000000);
	}
}


void			render_koch(t_gfx_state *st)
{
	const t_state	*mst = st->user_state;
	int w;
	int h;
	int r;

	w = WIN_WIDTH * mst->zoom_level;
	h = WIN_HEIGHT * mst->zoom_level;
	r = 10;
	(void)mst;	
	gfx_fill_trgt(st, st->buffer, 0xFFFFFF);
	koch(st,
		mk_vec2(0, WIN_HEIGHT),
		mk_vec2(WIN_WIDTH, WIN_HEIGHT),
		r);
}
