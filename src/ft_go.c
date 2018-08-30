/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_go.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otiniako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 11:25:10 by otiniako          #+#    #+#             */
/*   Updated: 2018/08/30 11:25:12 by otiniako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void	ft_move(t_way *tmp, t_ways *ways, t_lem_in *lem)
{
	tmp = ways->way->next;
	while (tmp && tmp->next && !tmp->room->nb_ant &&
	ft_strcmp(lem->end->name, tmp->next->room->name))
		tmp = tmp->next;
	while (tmp && tmp->next && tmp->next->room->nb_ant == 1 &&
	ft_strcmp(lem->end->name, tmp->next->room->name))
		tmp = tmp->next;
	if (tmp->room->nb_ant && tmp->next)
	{
		tmp->room->nb_ant--;
		tmp->next->room->nb_ant++;
		tmp->next->room->lem_nb = tmp->room->lem_nb;
		ft_printf("L%i-%s ", tmp->room->lem_nb,
		tmp->next->room->name);
	}
	if (!ft_strcmp(lem->end->name, tmp->next->room->name))
		ways->nb_ant_is--;
}

void	ft_move_all(t_ways *ways, t_lem_in *lem)
{
	int		i;
	int		j;

	while (ways)
	{
		if (ways->way && (j = ways->nb_ant_is))
		{
			i = -1;
			while (++i < j)
				ft_move(ways->way->next, ways, lem);
		}
		ways = ways->next;
	}
}

void	ft_check_start(t_lem_in *lem, t_ways *ways)
{
	int		i;
	t_way	*tmp;

	while (ways && lem->begin->nb_ant)
	{
		if (ways->way && ways->nb_ant_tmp && lem->begin->nb_ant)
		{
			lem->begin->nb_ant--;
			ways->nb_ant_tmp--;
			ways->way->next->room->nb_ant++;
			if (ft_strcmp(lem->end->name, ways->way->next->room->name))
				ways->nb_ant_is++;
			ways->way->next->room->lem_nb = lem->nb_ant - lem->begin->nb_ant;
			ft_printf("L%i-%s ", ways->way->next->room->lem_nb,
			ways->way->next->room->name);
		}
		ways = ways->next;
	}
}

int		ft_go(t_lem_in *lem)
{
	int nb_ant;

	ft_printf("\n");
	nb_ant = lem->nb_ant;
	lem->begin->nb_ant = lem->nb_ant;
	while (lem->end->nb_ant != nb_ant)
	{
		ft_move_all(lem->ways, lem);
		ft_check_start(lem, lem->ways);
		ft_printf("\n");
	}
	return (0);
}
