/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractol.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmartins <nmartins@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/29 19:32:58 by nmartins       #+#    #+#                */
/*   Updated: 2019/06/25 13:47:59 by nmartins      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libgfx.h>
#include <libft.h>
#include <stdio.h>
#include <pthread.h>
#include "events.h"
#include "const.h"
#include "state.h"

int	destroy_state(t_gfx_state *st)
{
	t_state *mst;

	mst = st->user_state;
	return (0);
}

int	main(int argc, char **argv)
{
	t_gfx_state	st;
	t_hooks		hooks;
	t_state		state;

	init_state(&state, argc, argv);
	ft_memset(&st, 0, sizeof(t_gfx_state));
	ft_memset(&hooks, 0, sizeof(t_hooks));
	st.user_state = &state;
	if (gfx_mk_state(&st, mk_dimensions(WIN_WIDTH, WIN_HEIGHT),
		"Fractol") == -1)
		return (EXIT_FAILURE);
	hooks.keypress = keypress;
	hooks.keyrelease = keyrelease;
	hooks.close = close;
	hooks.expose = expose;
	hooks.render = render;
	hooks.mousemove = mousemove;
	hooks.mousepress = mousepress;
	hooks.mouserelease = mouserelease;
	hooks.free = destroy_state;
	gfx_register_hooks(&st, hooks);
	gfx_loop(&st);
	gfx_free_state(&st);
	getchar();
	return (EXIT_SUCCESS);
}
