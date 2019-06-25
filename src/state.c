/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   state.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nmartins <nmartins@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/10 19:41:51 by nmartins       #+#    #+#                */
/*   Updated: 2019/06/25 19:28:43 by nmartins      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"
#include <libft.h>

static const t_fract_kvp g_lookup[] = {
	{ "julia", FRACTAL_JULIA },
	{ "mandlebrot", FRACTAL_MANDLEBROT },
	{ "sierpinski", FRACTAL_SIERPINSKI },
	{ "koch", FRACTAL_KOCH },
};

void			show_options(void)
{
	size_t i;

	i = 0;
	while (i < sizeof(g_lookup) / sizeof(t_fract_kvp))
	{
		ft_putstr("- ");
		ft_putendl(g_lookup[i].key);
		i++;
	}
}

int				find_fractal(t_state *st, int argc, char **argv)
{
	int		i;
	size_t	j;

	i = 0;
	while (i < argc)
	{
		j = 0;
		while (j < sizeof(g_lookup) / sizeof(t_fract_kvp))
		{
			if (ft_strcmp(g_lookup[j].key, argv[i]) == 0)
			{
				st->fractal = g_lookup[j].index;
				return (0);
			}
			j++;
		}
		i++;
	}
	return (-1);
}

void			usage(char *exe_name)
{
	ft_putstr("Usage: ");
	ft_putstr(exe_name);
	ft_putstr(" <fractal name> --rainbow/-r\n");
}

int				has_flag(char *kw, int argc, char **argv)
{
	int i;

	i = 0;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], kw) == 0)
			return (1);
		i++;
	}
	return (0);
}

void			init_state(t_state *st, int argc, char **argv)
{
	st->shift = has_flag("--rainbow", argc, argv)
		|| has_flag("-r", argc, argv);
	st->zoom_level = 1;
	if (find_fractal(st, argc, argv) == -1)
	{
		usage(argv[0]);
		ft_putendl("Please choose a valid fractal from the list:");
		show_options();
		exit(0);
	}
}
