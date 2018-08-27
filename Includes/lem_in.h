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
# include "libft.h"

typedef struct		s_lem_in
{
	int				s : 1;
	int				e : 1;
	int				nb_ant;//+
	//int				nb_room;
	//int				nb_links;
	struct s_room	*begin;//+
	struct s_room	*end;//+
	struct s_room	*rooms;//+
	struct s_link	*links;//+
	struct s_way	**way;
	struct s_ways	*ways;
}					t_lem_in;

typedef struct		s_room
{
	char			*name;//+
	int				x;//+
	int				y;//+
	int				deep;
	int				is_in_way;
	int				checked : 1;
	int				nb_links;//+
	struct s_room	**linked_to;//+
	struct s_room	*next;//+
}					t_room;

typedef struct		s_link
{
	t_room			*r1;
	t_room			*r2;
	struct s_link	*next;
}					t_link;

typedef struct		s_linked
{
	t_room			*room;
	struct s_linked	*next;
}					t_linked;

typedef struct		s_way
{
	t_room			*room;
	struct s_way	*next;
}					t_way;

typedef struct		s_ways
{
	t_way			*way;
	struct s_ways	*next_way;
}					t_ways;

int					main(int ac, char **av);
int					ft_comment(char *str, t_lem_in *lem);
int					ft_strisdigit(char *str);
int					ft_del_av(char **s);
t_room				*ft_get_r(char *str, t_lem_in *lem);
void				ft_rooms_links(t_lem_in *lem);
void				ft_ways(t_lem_in *lem);

#endif
