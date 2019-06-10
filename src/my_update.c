/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   my_update.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmartins <nmartins@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/10 20:02:05 by nmartins       #+#    #+#                */
/*   Updated: 2019/06/11 01:11:12 by nmartins      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libgfx.h>
#include "my_update.h"
#include "state.h"

void	update(t_gfx_state *st)
{
	t_state	*mst;

	mst = st->user_state;
	if (st->key_state[KC_PLUS])
		mst->zoom_level /= 1.05;
	if (st->key_state[KC_MINUS])
		mst->zoom_level *= 1.05;
	mst->camera_position.x -= 0.05 * st->key_state[KC_A] * mst->zoom_level;
	mst->camera_position.x += 0.05 * st->key_state[KC_D] * mst->zoom_level;
	mst->camera_position.y -= 0.05 * st->key_state[KC_W] * mst->zoom_level;
	mst->camera_position.y += 0.05 * st->key_state[KC_S] * mst->zoom_level;
	(void)st;
}
