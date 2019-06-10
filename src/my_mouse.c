/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   my_mouse.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmartins <nmartins@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/02 20:21:39 by nmartins       #+#    #+#                */
/*   Updated: 2019/06/10 17:16:08 by nmartins      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libgfx.h>
#include <libft.h>
#include "state.h"

int	mousepress(int button_code, int x, int y, t_gfx_state *st)
{
	(void)x;
	(void)y;
	gfx_mouse_state_down(&st->mouse_state, button_code);
	return (0);
}

int	mouserelease(int button_code, int x, int y, t_gfx_state *st)
{
	(void)x;
	(void)y;
	gfx_mouse_state_up(&st->mouse_state, button_code);
	return (0);
}

int	mousemove(int x, int y, t_gfx_state *st)
{
	gfx_mouse_update_position(&st->mouse_state, x, y);
	return (0);
}
