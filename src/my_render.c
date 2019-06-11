/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   my_render.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmartins <nmartins@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/03 19:03:36 by nmartins       #+#    #+#                */
/*   Updated: 2019/06/11 16:58:48 by nmartins      ########   odam.nl         */
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


void			debug_info(t_gfx_state *st)
{
	const t_state	*mst = st->user_state;
	const int		fps = gfx_get_fps(1);
	const double	cy = (double)st->mouse_state.mouse_pos.y / WIN_HEIGHT - 0.5;
	const double	cx = (double)st->mouse_state.mouse_pos.x / WIN_WIDTH - 0.5;
	char			*dst;

	/*
	** TODO: Polyfil with ft_printf (coming soon)
	*/
	asprintf(&dst, "c = (%lf, %lf)\n", cx, cy);
	mlx_string_put(st->mlx_ptr, st->win_ptr, 50, 50, 0x00, dst);
	free(dst);
	asprintf(&dst, "%d FPS\n", fps);
	mlx_string_put(st->mlx_ptr, st->win_ptr, 50, 80, 0x00, dst);
	free(dst);
	asprintf(&dst, "Zoom Level: %lf\n", mst->zoom_level);
	mlx_string_put(st->mlx_ptr, st->win_ptr, 50, 110, 0x00, dst);
	free(dst);
}

void			render(t_gfx_state *st)
{
	const t_state	*mst = st->user_state;
	update(st);
	if (mst->fractal == FRACTAL_JULIA)
		render_julia(st);
	if (mst->fractal == FRACTAL_MANDLEBROT)
		render_mandlebrot(st);
	gfx_blit_image(st, st->buffer, mk_point(0, 0));
	debug_info(st);
}
