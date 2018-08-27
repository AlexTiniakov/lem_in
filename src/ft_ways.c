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
/*
void bfs(int u) {
  used[u] = true;
  queue<int> q;
  q.push(u);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = 0; i < (int) g[u].size(); i++) {
      int v = g[u][i];
      if (!used[v]) {
        used[v] = true;
        q.push(v);
      }
    }
  }
}
void bfs(int u) {
  used[u] = true;
  p[u] = u;
  dist[u] = 0;
  queue<int> q;
  q.push(u);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = 0; i < (int) g[u].size(); i++) {
      int v = g[u][i];
      if (!used[v]) {
        used[v] = true;
        p[v] = u;
        dist[v] = dist[u] + 1;
        q.push(v);
      }
    }
  }
}

void	ft_add_to_way(t_way *all, t_roon *room)
{
	{
				tmp = all;
				all = (t_way *)malloc(sizeof(t_way));
				all->room = begin->linked_to[i];
				all->room->deep = j;
				all->next = tmp;
			}
}
*/
int		ft_check_room(t_room *begin, char *end, int deep)
{
	int i;

	i = -1;
	begin->checked = 1;
	begin->deep = deep;
	if (!ft_strcmp(begin->name, end))
		return (1);
	while (++i < begin->nb_links)
	{
		if (!begin->linked_to[i]->checked || !ft_strcmp(begin->linked_to[i]->name, end))
		{
			if (ft_check_room(begin->linked_to[i], end, deep + 1) == 1)
				return (0);
		}
	}
	return (0);
}

void	ft_ways(t_lem_in *lem)
{
	t_room *tmp;
	t_link *tab;
	int i;
/*	int i;
	int j;
	int k;

	i = -1;
	k = -1;
	lem->way = (t_way **)malloc(sizeof(t_way *) * begin->nb_links);
	while (++i < lem->begin->nb_links)
	{
		lem->way[i] = NULL;
		if((j = ft_check_room(lem->begin->linked_to[i], lem->end->name)) >= 0)
			lem->way[++k] = lem->begin->linked_to[i];
	}

*/
/*	lem->ways = (t_ways *)malloc(sizeof(t_ways));
//	lem->begin->deep = 0;
	lem->way->room = lem->begin;
	lem->way->next = NULL;
*/	ft_check_room(lem->begin, lem->end->name, 0);
	tmp = lem->rooms;
	while (tmp)
	{
		ft_printf("name: '%s', deep: %i, nb_links: %i ", tmp->name, tmp->deep, tmp->nb_links);
		i = -1;
		while (++i < tmp->nb_links)
			ft_printf("%i=%s  ", i, tmp->linked_to[i]->name);
		ft_printf("\n");
		tmp = tmp->next;
	}
	tab = lem->links;
	while (tab)
	{
		ft_printf("%s<-->%s\n", tab->r1->name, tab->r2->name);
		tab = tab->next;
	}
}