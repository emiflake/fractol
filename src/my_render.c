/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   my_render.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmartins <nmartins@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/03 19:03:36 by nmartins       #+#    #+#                */
/*   Updated: 2019/06/27 13:44:34 by nmartins      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libgfx.h>
#include <math.h>
#include <libft.h>
#include "const.h"
#include "state.h"
#include "render.h"
#include "fractals.h"
#include "my_update.h"

/*
** TODO: Polyfil with ft_printf (coming soon)
*/

void			debug_info(t_gfx_state *st)
{
	const int		fps = gfx_get_fps(1);
	char			*dst;

	dst = ft_itoa(fps);
	ft_strreplace(&dst, ft_strjoin(dst, " FPS"));
	mlx_string_put(st->mlx_ptr, st->win_ptr, 50, 80, 0x00, dst);
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
	if (mst->fractal == FRACTAL_SIERPINSKI)
		render_sierpinski(st);
	if (mst->fractal == FRACTAL_KOCH)
		render_koch(st);
	gfx_blit_image(st, st->buffer, mk_point(0, 0));
	debug_info(st);
}
