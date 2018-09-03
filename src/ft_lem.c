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

int		ft_count_2(int x, t_ways *tmp, int i)
{
	while (tmp)
	{
		if (tmp->way)
		{
			i += x - tmp->dif > 0 ? 0 : 1;
			if (x - tmp->dif <= 0)
				tmp->count = 1;
		}
		tmp = tmp->next;
	}
	return (i);
}

int		ft_count(t_ways *tmp, int i, t_lem_in *lem, int min)
{
	int x;
	int tab;

	while (tmp)
	{
		if (tmp->way)
			i++;
		tmp->count = 0;
		tmp = tmp->next;
	}
	if (!i)
		return (0);
	tab = (lem->nb_ant + _DIF) / i;
	if (tab < 0)
		x = lem->nb_ant / i + _DIF / i;
	else
		x = tab;
	x += (lem->nb_ant % i + tab % i) % i ? 1 : 0;
	i -= ft_count_2(x, lem->ways, 0);
	return (i);
}

int		ft_sum_dif(t_lem_in *lem, int min, t_ways *tmp, int rez)
{
	tmp = lem->ways;
	while (tmp)
	{
		if (tmp->way && !tmp->count)
		{
			tmp->dif = tmp->lenght - min;
			rez += tmp->dif;
		}
		tmp = tmp->next;
	}
	return (rez);
}

int		ft_put_nb_ants(t_ways *ways, int x, t_ways *tmp, int i)
{
	tmp = ways;
	while (tmp)
	{
		if (tmp->way)
		{
			tmp->nb_ants = x - tmp->dif > 0 ? x - tmp->dif : 0;
			tmp->nb_ant_tmp = tmp->nb_ants;
			i += tmp->nb_ants;
		}
		tmp = tmp->next;
	}
	return (i);
}

void	ft_lem(t_lem_in *lem)
{
	int x;
	int min;
	int tab;
	int nb_ways;

	min = ft_get_min(2147483647, lem->ways);
	if (!(nb_ways = ft_count(lem->ways, 0, lem, min)))
		exit(_ERR("no ways", lem));
	tab = (lem->nb_ant + _DIF) / nb_ways;
	if (tab < 0)
		x = lem->nb_ant / nb_ways + _DIF / nb_ways;
	else
		x = tab;
	x += (lem->nb_ant % nb_ways + tab % nb_ways) % nb_ways ? 1 : 0;
	if (ft_put_nb_ants(lem->ways, x, NULL, 0) < lem->nb_ant)
		ft_put_nb_ants(lem->ways, x + 1, NULL, 0);
	if (lem->d)
	{
		ft_debuger(lem, NULL, NULL);
		exit(lem->l ? _L : 0);
	}
}
