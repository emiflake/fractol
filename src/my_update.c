/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   my_update.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmartins <nmartins@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/10 20:02:05 by nmartins       #+#    #+#                */
/*   Updated: 2019/06/26 15:27:43 by nmartins      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libgfx.h>
#include "my_update.h"
#include "state.h"

void	update_mouse(t_gfx_state *st)
{
	t_state			*mst;
	static t_point	prev_pos;
	const int		delta_x = st->mouse_state.mouse_pos.x - prev_pos.x;
	const int		delta_y = st->mouse_state.mouse_pos.y - prev_pos.y;


	mst = st->user_state;
	if (st->mouse_state.button_state[MC_LEFT])
	{
		mst->camera_position.x -= delta_x * mst->zoom_level / 1000;
		mst->camera_position.y -= delta_y * mst->zoom_level / 1000;
	}
	prev_pos = st->mouse_state.mouse_pos;
}

void	update(t_gfx_state *st)
{
	t_state	*mst;

	mst = st->user_state;
	if (st->key_state[KC_PLUS])
		mst->zoom_level /= 1.05;
	if (st->key_state[KC_MINUS])
		mst->zoom_level *= 1.05;
	mst->camera_position.x +=
		-0.05 * st->key_state[KC_A] * mst->zoom_level
		+ 0.05 * st->key_state[KC_D] * mst->zoom_level;
	mst->camera_position.y +=
		-0.05 * st->key_state[KC_W] * mst->zoom_level
		+ 0.05 * st->key_state[KC_S] * mst->zoom_level;
	update_mouse(st);
	(void)st;
}
