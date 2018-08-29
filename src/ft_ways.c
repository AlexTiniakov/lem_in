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

void		ft_check_room(t_room *begin, char *end, t_lem_in *lem)
{
	/*int i;

	i = -1;
	begin->checked = 1;
	if (!ft_strcmp(begin->name, end))
		return (1);
	while (++i < begin->nb_links)
	{
		if (!begin->linked_to[i]->checked ||
		!ft_strcmp(begin->linked_to[i]->name, end))
		{
			begin->linked_to[i]->deep = deep;
			if (ft_check_room(begin->linked_to[i], end, deep + 1) == 1)
				return (0);
		}
	}
	return (0);*/
	static t_turn *turn = NULL;
	int j;
	t_room *tmp;
	t_turn *tab;
	
	turn = ft_put_down(turn, lem->begin, 0);
//	ft_printf("1turn--->%s\n", turn ? turn->room->name : "NULL");
	while ((tmp = ft_get_front(&turn)))
	{
		j = -1;
		//ft_printf("2turn--->%s\n", turn ? turn->room->name : "NULL");		
		//ft_printf("tmp--->%s\n", tmp->name);
		while (++j < tmp->nb_links)
		{
			//ft_printf("%s->linked_to[%i]--->%s; checked = %i\n", tmp->name, j, tmp->linked_to[j]->name, tmp->linked_to[j]->checked);
			if (!tmp->linked_to[j]->checked && ft_strcmp(tmp->linked_to[j]->name, end))
				turn = ft_put_down(turn, tmp->linked_to[j], 1 + tmp->deep);
				
			//ft_printf("%s-->%s\n", turn->room->name, turn->next ? turn->next->room->name : "NULL");
		//	ft_printf("tmp->linked_to[%i]--->%s; checked = %i\n", j, tmp->linked_to[j]->name, tmp->linked_to[j]->checked);
		/*	tab = turn;
			while (tab)
			{
				ft_printf("--->%s", tab->room->name);
				tab = tab->next;
			}
			ft_printf("\n");*/
		}
	}
}

t_room *ft_get_room(t_room *room, int i)
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

void	ft_find_way(t_ways *ways, t_room *room, t_room *begin)
{
	t_room *tmp;
	t_way *tab;

	tmp = room;
	ways->lenght = 1;
	while (tmp && tmp->deep > 0)
	{
		tab = ways->way;
		ways->way = (t_way *)malloc(sizeof(t_way));
		ways->way->room = tmp;
		tmp->is_in_way = 1;
		ways->way->next = tab;
		ways->lenght++;
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
	ways->way = (t_way *)malloc(sizeof(t_way));
	ways->way->room = begin;
	ways->way->next = tab;
}

void	ft_ways(t_lem_in *lem)
{
	t_room *tmp;
	t_link *tab;
	t_ways *tmp1;
	t_way *w;
	int i;

	i = -1;
	
	ft_check_room(lem->begin, lem->end->name, lem);
	tmp = lem->rooms;
	while (tmp)
	{
		ft_printf("name: '%s', deep: %i, nb_links: %i ",
		tmp->name, tmp->deep, tmp->nb_links);
		i = -1;
		while (++i < tmp->nb_links)
			ft_printf("%i=%s  ", i, tmp->linked_to[i]->name);
		ft_printf("\n");
		tmp = tmp->next;
	}
/*	tab = lem->links;
	while (tab)
	{
		ft_printf("%s<-->%s\n", tab->r1->name, tab->r2->name);
		tab = tab->next;
	}*/
//
	lem->ways = NULL;
	i = -1;
	
	ft_sort(lem->end);
	while (++i < lem->end->nb_links)
	{
		if (lem->end->linked_to[i]->deep > 0 ||
		!ft_strcmp(lem->end->linked_to[i]->name, lem->begin->name))
		{
			tmp1 = lem->ways;
			lem->ways = (t_ways *)malloc(sizeof(t_ways));
			lem->ways->way = (t_way *)malloc(sizeof(t_way));
			lem->ways->way->room = lem->end;
			lem->ways->way->next = NULL;
			ft_find_way(lem->ways, lem->end->linked_to[i], lem->begin);
			lem->ways->next = tmp1;
		}
	}
//
	/*tmp1 = lem->ways;
	while (tmp1)
	{
		w = tmp1->way;
		while (w)
		{
			ft_printf("%7s-->", w->room->name);
			w = w->next;
		}
		if (tmp1->way)
			ft_printf(" len:%2i, dif:%2i, nb_ant:%2i\n", tmp1->lenght, tmp1->dif, tmp1->nb_ants);
		tmp1 = tmp1->next;
	}*/
}