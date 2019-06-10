/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   state.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmartins <nmartins@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/02 20:48:59 by nmartins       #+#    #+#                */
/*   Updated: 2019/06/11 01:09:10 by nmartins      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_H
# define STATE_H

# include <libgfx.h>
# include "fractals.h"

typedef struct	s_state
{
	float			zoom_level;
	t_vec2			camera_position;

	t_fractal_type	fractal;
}				t_state;

void			init_state(t_state *st, int argc, char **argv);

#endif
