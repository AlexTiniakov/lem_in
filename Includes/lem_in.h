/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otiniako <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 17:06:20 by otiniako          #+#    #+#             */
/*   Updated: 2018/07/02 17:06:21 by otiniako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# define _ERR write(1, "ERROR\n", 6)
# define _A !(tmp->r2 = ft_get_r(s[1], lem))
# include "libft.h"

typedef struct		s_lem_in
{
	int				s : 1;
	int				e : 1;
	int				nb_ant;
	struct s_room	*begin;
	struct s_room	*end;
	struct s_room	*rooms;
	struct s_link	*links;
	struct s_ways	*ways;
}					t_lem_in;

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	int				deep;
	int				nb_ant;
	int				lem_nb;
	int				is_ant : 1;
	int				is_in_way : 1;
	int				checked : 1;
	int				nb_links;
	struct s_room	**linked_to;
	struct s_room	*next;
}					t_room;

typedef struct		s_link
{
	t_room			*r1;
	t_room			*r2;
	struct s_link	*next;
}					t_link;

typedef struct		s_way
{
	t_room			*room;
	struct s_way	*next;
}					t_way;

typedef struct		s_ways
{
	int				nb_ants;
	int				nb_ant_tmp;
	int				nb_ant_is;
	int				lenght;
	int				dif;
	t_way			*way;
	struct s_ways	*next;
}					t_ways;

typedef struct		s_turn
{
	t_room			*room;
	struct s_turn	*next;
}					t_turn;

int					main(int ac, char **av);
int					ft_comment(char *str, t_lem_in *lem);
int					ft_strisdigit(char *str);
int					ft_del_av(char **s);
t_room				*ft_get_r(char *str, t_lem_in *lem);
void				ft_rooms_links(t_lem_in *lem);
void				ft_ways(t_lem_in *lem, int i);
t_turn				*ft_put_down(t_turn *turn, t_room *room, int i);
t_room				*ft_get_front(t_turn **turn);
void				ft_sort(t_room *room);
void				ft_lem(t_lem_in *lem);
void				ft_go(t_lem_in *lem);
int					ft_count_links(t_room *tmp, t_link *links, int j, int i);
int					ft_check_repeat(t_lem_in *lem, t_link *tmp);
void				ft_tool_1(t_room *tmp, t_lem_in *lem, char **s);
void				ft_tool_2(t_way *tab, t_ways *ways, t_room	*tmp);
int					ft_check_name(char **s, t_lem_in *lem);

#endif
