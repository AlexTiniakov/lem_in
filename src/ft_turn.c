/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_turn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otiniako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 12:20:56 by otiniako          #+#    #+#             */
/*   Updated: 2018/08/28 12:21:02 by otiniako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

t_room	*ft_get_front(t_turn **turn)
{
	t_room *tmp;
	t_turn *tab;

	if (!(*turn))
		return (NULL);
	tmp = (*turn)->room;
	tab = (*turn)->next;
	ft_memdel((void **)&(*turn));
	*turn = tab;
	return (tmp);
}

t_turn	*ft_put_down(t_turn *turn, t_room *room, int i)
{
	t_turn *tab;
	t_turn *tmp;

	tab = turn;
	tmp = (t_turn *)malloc(sizeof(t_turn));
	tmp->room = room;
	tmp->room->deep = i;
	tmp->room->checked = 1;
	tmp->next = NULL;
	if (tab)
	{
		while (tab && tab->next)
			tab = tab->next;
		tab->next = tmp;
	}
	else
		turn = tmp;
	return (turn);
}

void ft_sort(t_room *room)
{
	int i;
	int j;
	int k;
	t_room *tmp;

	i = -1;
	while (++i < room->nb_links - 1)
	{
		j = room->nb_links - i - 1;
		k = -1;
		while (++k < j)
		{
			if (room->linked_to[k]->deep > room->linked_to[k + 1]->deep)
			{
				tmp = room->linked_to[k];
				room->linked_to[k] = room->linked_to[k + 1];
				room->linked_to[k + 1] = tmp;
			}
		}
	}
}