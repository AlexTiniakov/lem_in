/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otiniako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 19:39:59 by otiniako          #+#    #+#             */
/*   Updated: 2018/08/28 19:40:00 by otiniako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int		ft_get_min(t_ways *ways, int min, t_ways *tmp)
{
	while (tmp)
	{
		if (tmp->way)
			min = min < tmp->lenght ? min : tmp->lenght;
		tmp = tmp->next;
	}
	return (min);
}

int		ft_count(t_ways *tmp, int i)
{
	while (tmp)
	{
		if (tmp->way)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int		ft_sum_dif(t_lem_in *lem, int min, t_ways *tmp, int rez)
{
	tmp = lem->ways;
	while (tmp)
	{
		if (tmp->way)
		{
			tmp->dif = tmp->lenght - min;
			rez += tmp->dif;
		}
		tmp = tmp->next;
	}
	return (rez);
}

void	ft_put_nb_ants(t_ways *ways, int x, t_ways *tmp)
{
	tmp = ways;
	while (tmp)
	{
		if (tmp->way)
		{
			tmp->nb_ants = x - tmp->dif;
			tmp->nb_ant_tmp = tmp->nb_ants;
		}
		tmp = tmp->next;
	}
}

void	ft_lem(t_lem_in *lem)
{
	int x;
	int min;
	int tab;
	int nb_ways;

	min = ft_get_min(lem->ways, 2147483647, lem->ways);
	if (!(nb_ways = ft_count(lem->ways, 0)))
		exit (_ERR);
	tab = (lem->nb_ant + ft_sum_dif(lem, min, lem->ways, 0));
	x = tab / nb_ways;
	x += tab % nb_ways ? 1 : 0;
	ft_put_nb_ants(lem->ways, x, NULL);
}
