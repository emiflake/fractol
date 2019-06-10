/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   state.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmartins <nmartins@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/10 19:41:51 by nmartins       #+#    #+#                */
/*   Updated: 2019/06/10 19:44:21 by nmartins      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"

void			init_state(t_state *st, int argc, char **argv)
{
	st->zoom_level = 1;
	(void)argc;
	(void)argv;
}
