/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   my_misc_events.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmartins <nmartins@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/02 20:46:55 by nmartins       #+#    #+#                */
/*   Updated: 2019/06/03 19:30:23 by nmartins      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libgfx.h>
#include <stdio.h>

int	close(t_gfx_state *st)
{
	(void)st;
	gfx_free_state(st);
	exit(0);
	return (0);
}

/*
** Window: *appears*
** owo what's this
*/

int	expose(t_gfx_state *st)
{
	(void)st;
	return (0);
}
