/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_go.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otiniako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 22:34:46 by otiniako          #+#    #+#             */
/*   Updated: 2018/08/28 22:34:47 by otiniako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void	ft_move_all(t_ways *ways, t_lem_in *lem)
{
	int i;
	t_way *tmp;
	int j;

	while (ways)
	{
		//ft_printf("1.1\n");
		if (ways->way)
		{
			i = -1;
			//ft_printf("j = %i\n", ways->nb_ant_is);
			j = ways->nb_ant_is;
			while (++i < j)
			{
				//ft_printf("i = %i; j = %i\n", i, j);
				tmp = ways->way->next;
				//ft_printf("ways->way->room->name: %s\n", ways->way->room->name);
				while (tmp && tmp->next && !tmp->room->nb_ant && ft_strcmp(lem->end->name, tmp->next->room->name))
				{
					//ft_printf("-->%s\n", tmp->room->name);
					tmp = tmp->next;
				}
				//ft_printf("-->%s\n", tmp->room->name);
				while (tmp && tmp->next && tmp->next->room->nb_ant == 1 && ft_strcmp(lem->end->name, tmp->next->room->name))
				{
					//ft_printf("1.5\n");
					tmp = tmp->next;
				}
				//ft_printf("1.6\n");
				//ft_printf("-->%s\n", tmp->room->name);
				if (tmp->room->nb_ant && tmp->next)// && ft_strcmp(lem->end->name, tmp->next->room->name))
				{
					tmp->room->nb_ant--;
					tmp->next->room->nb_ant++;
					tmp->next->room->lem_nb = tmp->room->lem_nb;
					ft_printf("L%i-%s ", tmp->room->lem_nb, tmp->next->room->name);
				}
				if (!ft_strcmp(lem->end->name, tmp->next->room->name))
						ways->nb_ant_is--;
				/*
				if (!ft_strcmp(lem->end->name, tmp->next->room->name))
				{
					tmp->room->nb_ant--;
					tmp->next->room->nb_ant++;
				}*/
			//	ft_printf("lem->end->nb_ant = %i\n", lem->end->nb_ant);
			}
		}
		ways = ways->next;
	}
}

void	ft_check_start(t_lem_in *lem, t_ways *ways)
{
	int i;
	t_way *tmp;
	
	while (ways)
	{
		if (ways->way && ways->nb_ant_tmp && lem->begin->nb_ant)
		{
			lem->begin->nb_ant--;
			ways->nb_ant_tmp--;
			ways->way->next->room->nb_ant++;
			if (ft_strcmp(lem->end->name, ways->way->next->room->name))
				ways->nb_ant_is++;
			ways->way->next->room->lem_nb = lem->nb_ant - lem->begin->nb_ant;
			ft_printf("L%i-%s ", ways->way->next->room->lem_nb, ways->way->next->room->name);
		}
		ways = ways->next;
	}
}

void	ft_go(t_lem_in *lem)
{
	int nb_ant;

	nb_ant = lem->nb_ant;
	lem->begin->nb_ant = lem->nb_ant;
	while (lem->end->nb_ant != nb_ant)
	{
		ft_move_all(lem->ways, lem);
		//ft_printf("1\n");
		ft_check_start(lem, lem->ways);
		ft_printf("\n");
	}

	/*t_ways	*tmp;

	tmp = lem->ways;
	while (tmp)
	{
		if (tmp->way)
		{
			if (tmp->nb_ants)
			{
				lem->nb_ant--;
				tmp->way->next->room->nb_ant++;
			}
		}
		tmp = tmp->next;
	}*/
}