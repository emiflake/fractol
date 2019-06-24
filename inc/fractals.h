/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractals.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmartins <nmartins@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/10 18:26:02 by nmartins       #+#    #+#                */
/*   Updated: 2019/06/24 23:09:53 by nmartins      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTALS_H
# define FRACTALS_H

# include <libgfx.h>

typedef enum	e_fractal_type
{
	FRACTAL_JULIA,
	FRACTAL_MANDLEBROT,
}				t_fractal_type;

/*
** In general, a fractal must consist of a function like this
*/
typedef struct	s_julia_spec
{
	double zoom;
	t_vec2 offset;
	t_vec2 c;
}				t_julia_spec;

void	render_julia(t_gfx_state *st);
int		fract_julia(t_gfx_state *st, t_vec2 *pos, t_julia_spec *spec);

/*
** In general, a fractal must consist of a function like this
*/
typedef struct	s_mandlebrot_spec
{
	double zoom;
	t_vec2 offset;
}				t_mandlebrot_spec;

void	render_mandlebrot(t_gfx_state *st);
double	fract_mandlebrot(t_gfx_state *st, t_vec2 *pos, t_mandlebrot_spec *spec);

#endif
