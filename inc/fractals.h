/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractals.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmartins <nmartins@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/10 18:26:02 by nmartins       #+#    #+#                */
/*   Updated: 2019/06/10 20:42:06 by nmartins      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTALS_H
# define FRACTALS_H

# include <libgfx.h>

/*
** In general, a fractal must consist of a function like this
*/
typedef struct	s_julia_spec
{
}				t_julia_spec;

int		fract_julia(t_gfx_state *st, t_vec2 *pos, t_julia_spec *spec);

#endif
