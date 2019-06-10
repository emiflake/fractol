/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   events.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmartins <nmartins@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/02 20:18:06 by nmartins       #+#    #+#                */
/*   Updated: 2019/05/02 20:47:30 by nmartins      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# include <libgfx.h>

int	render(t_gfx_state *st);
int	keypress(int key_code, t_gfx_state *st);
int	keyrelease(int key_code, t_gfx_state *st);
int	mousepress(int button_code, int x, int y, t_gfx_state *st);
int	mouserelease(int button_code, int x, int y, t_gfx_state *st);
int	mousemove(int x, int y, t_gfx_state *st);
int	close(t_gfx_state *st);
int	expose(t_gfx_state *st);

#endif
