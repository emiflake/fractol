/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractals.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmartins <nmartins@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/10 18:26:02 by nmartins       #+#    #+#                */
/*   Updated: 2019/06/25 19:27:49 by nmartins      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTALS_H
# define FRACTALS_H

# include <libgfx.h>

typedef enum	e_fractal_type
{
	FRACTAL_JULIA,
	FRACTAL_MANDLEBROT,
	FRACTAL_SIERPINSKI,
	FRACTAL_KOCH
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

/*
** This struct exists for multi threading
*/
typedef struct	s_julia_segment_conf
{
	t_gfx_state		*st;
	t_dimensions	size;
	t_point			pos;
	t_julia_spec	jspec;
}				t_julia_segment_conf;

void			render_julia(t_gfx_state *st);
int				fract_julia(t_gfx_state *st, t_vec2 *pos, t_julia_spec *spec);

/*
** In general, a fractal must consist of a function like this
*/
typedef struct	s_mandlebrot_spec
{
	double zoom;
	t_vec2 offset;
}				t_mandlebrot_spec;

/*
** This struct exists for multi threading
*/
typedef struct	s_mandlebrot_segment_conf
{
	t_gfx_state			*st;
	t_dimensions		size;
	t_point				pos;
	t_mandlebrot_spec	mspec;
}				t_mandlebrot_segment_conf;

void			render_mandlebrot(t_gfx_state *st);
double			fract_mandlebrot(
					t_gfx_state *st,
					t_vec2 *pos,
					t_mandlebrot_spec *spec);

void			render_sierpinski(t_gfx_state *st);
void			render_koch(t_gfx_state *st);

#endif
