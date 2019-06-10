/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   my_render.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmartins <nmartins@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/03 19:03:36 by nmartins       #+#    #+#                */
/*   Updated: 2019/06/10 20:42:30 by nmartins      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libgfx.h>
#include <math.h>
#include <libft.h>
#include <stdio.h>
#include "const.h"
#include "state.h"
#include "render.h"
#include "fractals.h"
#include "my_update.h"

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

void			debug_info(t_gfx_state *st)
{
	const int		fps = gfx_get_fps(1);
	const double	cy = (double)st->mouse_state.mouse_pos.y / WIN_HEIGHT - 0.5;
	const double	cx = (double)st->mouse_state.mouse_pos.x / WIN_WIDTH - 0.5;
	char			*dst;

	asprintf(&dst, "c = (%lf, %lf)\n", cx, cy);
	mlx_string_put(st->mlx_ptr, st->win_ptr, 50, 50, 0x00, dst);
	free(dst);
	asprintf(&dst, "%d FPS\n", fps);
	mlx_string_put(st->mlx_ptr, st->win_ptr, 50, 80, 0x00, dst);
	free(dst);
}

void			render(t_gfx_state *st)
{
	t_julia_spec	sp;
	t_vec2			p;
	int				res;

	update(st);
	for (p.x = 0; p.x < WIN_WIDTH; p.x++)
	{
		for (p.y = 0; p.y < WIN_HEIGHT; p.y++)
		{
			res = fract_julia(st, &p, &sp);
			dispatch_colorization(st, &p, res);
		}
	}
	gfx_blit_image(st, st->buffer, mk_point(0, 0));
	debug_info(st);
}
