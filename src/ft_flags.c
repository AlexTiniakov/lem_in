/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otiniako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 12:42:14 by otiniako          #+#    #+#             */
/*   Updated: 2018/08/31 12:42:15 by otiniako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void    ft_init_lem(t_lem_in *lem)
{
    lem->s = 0;
    lem->e = 0;
    lem->l = 0;
    lem->v = 0;
    lem->r = 0;
    lem->d = 0;
    lem->u = 0;
    lem->q = 0;
    lem->nb_ant = 0;
    lem->str = ft_strnew(0);
    lem->begin = NULL;
    lem->end = NULL;
    lem->rooms = NULL;
    lem->links = NULL;
    lem->ways = NULL;
}

int    ft_flags(t_lem_in *lem, int ac, char **av, int i)
{
    if (ac > 0 && !ft_strcmp("-l", *av) && (lem->l = 1))
        return (ft_flags(lem, ac - 1, av + 1, i + 1));
    if (ac > 0 && !ft_strcmp("-v", *av) && (lem->v = 1))
        return (ft_flags(lem, ac - 1, av + 1, i + 1));
    if (ac > 0 && !ft_strcmp("-r", *av) && (lem->r = 1))
        return (ft_flags(lem, ac - 1, av + 1, i + 1));
    if (ac > 0 && !ft_strcmp("-d", *av) && (lem->d = 1))
        return (ft_flags(lem, ac - 1, av + 1, i + 1));
    if (ac > 0 && !ft_strcmp("-u", *av) && (lem->u = 1))
        return (ft_flags(lem, ac - 1, av + 1, i + 1));
    if (ac > 0 && !ft_strcmp("-q", *av) && (lem->q = 1))
        return (ft_flags(lem, ac - 1, av + 1, i + 1));
    else
        return (i);
}

void    ft_debuger(t_lem_in *lem, t_ways *tmp1, t_way *w)
{
    write(1, "\nALL WAYS:\n", 11);
    tmp1 = lem->ways;
	while (tmp1)
	{
		w = tmp1->way;
		while (w && w->next)
		{
			ft_printf("%s-->", w->room->name);
			w = w->next;
		}
        if (w && w->room)
            ft_printf("%s", w->room->name);
		if (tmp1->way)
			ft_printf(" len:%2i, dif:%2i, nb_ant:%2i\n", tmp1->lenght, tmp1->dif, tmp1->nb_ants);
		tmp1 = tmp1->next;
    }
}

void    ft_visualiz(t_lem_in *lem, t_ways *tmp1, t_way *w)
{
 //   int i;
    int j;
 //   int k;

    j = 0;
    while (j++ < 6)
    {
        ft_printf("\033[2J\033[%d;%dH", 0, 0);
        tmp1 = lem->ways;
	    while (tmp1)
	    {
	    	w = tmp1->way;
	    	while (w && w->next)
	    	{
	    		ft_printf("%s%s%s%s-%s-%s-%s-%s>\033[m",
                w->room->nb_ant > 0 && (j == 1 || !ft_strcmp(lem->begin->name, w->room->name)) ? "\033[31m" : "\033[92m",
                w->room->name,
                "\033[m",
                w->room->nb_ant > 0 && j == 2 && !(!ft_strcmp(lem->begin->name, w->room->name) && !tmp1->nb_ant_tmp)? "\033[31m" : "\033[92m",
                w->room->nb_ant > 0 && j == 3 && !(!ft_strcmp(lem->begin->name, w->room->name) && !tmp1->nb_ant_tmp)? "\033[31m" : "\033[92m",
                w->room->nb_ant > 0 && j == 4 && !(!ft_strcmp(lem->begin->name, w->room->name) && !tmp1->nb_ant_tmp)? "\033[31m" : "\033[92m",
                w->room->nb_ant > 0 && j == 5 && !(!ft_strcmp(lem->begin->name, w->room->name) && !tmp1->nb_ant_tmp)? "\033[31m" : "\033[92m",
                w->room->nb_ant > 0 && j == 6 && !(!ft_strcmp(lem->begin->name, w->room->name) && !tmp1->nb_ant_tmp)? "\033[31m" : "\033[92m");
	    		w = w->next;
	    	}
            if (w && w->room)
                ft_printf("%s%s%s", w->room->nb_ant > 0 ? "\033[31m" : "\033[92m", w->room->name, "\033[m");
	    	if (tmp1->way)
		    	ft_printf(" nb_ant:%2i\n", tmp1->nb_ants);
            tmp1 = tmp1->next;
        }
       // i = 0;
     //   k = j == 1 ? 200000000 : 50000000;
        usleep(j == 1 ? 200000 : 50000);
    }
}
