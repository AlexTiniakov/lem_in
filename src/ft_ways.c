/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ways.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otiniako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 10:42:43 by otiniako          #+#    #+#             */
/*   Updated: 2018/08/27 10:42:45 by otiniako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void	ft_check_room(char *end, t_lem_in *lem)
{
	static t_turn	*turn = NULL;
	int				j;
	t_room			*tmp;

	turn = ft_put_down(turn, lem->begin, 0, lem);
	while ((tmp = ft_get_front(&turn)))
	{
		j = -1;
		while (++j < tmp->nb_links)
		{
			if (!tmp->linked_to[j]->checked &&
			ft_strcmp(tmp->linked_to[j]->name, end))
				turn = ft_put_down(turn, tmp->linked_to[j], 1 + tmp->deep, lem);
		}
	}
}

t_room	*ft_get_room(t_room *room, int i)
{
	while (++i < room->nb_links)
	{
		if ((room->deep - room->linked_to[i]->deep) == 1 &&
		!room->linked_to[i]->is_in_way)
			return (room->linked_to[i]);
	}
	i = -1;
	while (++i < room->nb_links)
	{
		if ((room->deep - room->linked_to[i]->deep) == 0 &&
		!room->linked_to[i]->is_in_way)
			return (room->linked_to[i]);
	}
	return (NULL);
}

void	ft_find_way(t_ways *ways, t_room *room, t_lem_in *lem, t_way *tab)
{
	t_room	*tmp;

	tmp = room;
	ways->lenght = 1;
	while (tmp && tmp->deep > 0)
	{
		ft_tool_2(ways->way, ways, tmp);
		tmp = ft_get_room(tmp, -1);
	}
	if (!tmp)
	{
		while (ways->way)
		{
			tab = ways->way->next;
			ft_memdel((void **)&ways->way);
			ways->way = tab;
		}
		ways->way = NULL;
		return ;
	}
	tab = ways->way;
	if (!(ways->way = (t_way *)malloc(sizeof(t_way))))
		exit(_ERR("not enough memory", lem));
	ways->way->room = lem->begin;
	ways->way->next = tab;
}

void	ft_ways(t_lem_in *lem, int i)
{
	t_ways	*tmp1;

	ft_check_room(lem->end->name, lem);
	lem->ways = NULL;
	ft_sort(lem->end);
	i = -1;
	while (++i < lem->end->nb_links)
	{
		if (lem->end->linked_to[i]->deep > 0 ||
		!ft_strcmp(lem->end->linked_to[i]->name, lem->begin->name))
		{
			tmp1 = lem->ways;
			if (!(lem->ways = (t_ways *)malloc(sizeof(t_ways))))
				exit(_ERR("not enough memory", lem));
			if (!(lem->ways->way = (t_way *)malloc(sizeof(t_way))))
				exit(_ERR("not enough memory", lem));
			lem->ways->way->room = lem->end;
			lem->ways->way->next = NULL;
			ft_find_way(lem->ways, lem->end->linked_to[i], lem, NULL);
			lem->ways->nb_ant_is = 0;
			lem->ways->next = tmp1;
		}
	}
}
