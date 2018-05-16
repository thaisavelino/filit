/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 20:53:53 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/16 19:36:47 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdlib.h>

/*
** Push a given tetri to the end of the list
*/
void		tetri_push(t_tetri **alist, t_tetri *list)
{
	t_tetri	*ptr;

	if (*alist == NULL)
		*alist = list;
	else
	{
		ptr = *alist;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = list;
	}
}

/*
** Returns a newly allocated tetri and set it's name according to it's number
*/
t_tetri		*new_tetri(int *coord, int tetri_nbr)
{
	t_tetri	*new;

	if (!(new = (t_tetri*)malloc(sizeof(*new))))
		return (NULL);
	new->next = NULL;
	if (coord == NULL)
		new->coord = NULL;
	else
	{
		if (!(new->coord = ft_memalloc(sizeof(*coord) * 8)))
			return (NULL);
		reset_tetri_position(coord);
		new->coord = ft_memcpy(new->coord, coord, sizeof(*coord) * 8);
	}
	new->name = 'A' + tetri_nbr;
	return (new);
}

/*
** Free the whole list of tetri and it's contents
*/
void		tetri_del(t_tetri **alst)
{
	t_tetri	*lst;
	t_tetri	*ptr;

	lst = *alst;
	while (lst)
	{
		ptr = lst->next;
		free(lst->coord);
		free(lst);
		lst = ptr;
	}
	*alst = NULL;
}

/*
** Set tetri coordinates in relation to it's first block
** Rather than the map it was read from
*/
int			*reset_tetri_position(int *coord)
{
	int		i;
	int		x;
	int		y;

	i = 0;
	x = coord[i];
	y = coord[i + 1];
	while (i < 8)
	{
		if (coord[i] < x)
			x = coord[i];
		if (coord[i + 1] < y)
			y = coord[i + 1];
		i += 2;
	}
	i = 0;
	while (i < 8)
	{
		if (x > 0)
			coord[i] -= x;
		if (y > 0)
			coord[i + 1] -= y;
		i += 2;
	}
	return (coord);
}

/*
** Allocate/Reallocate and fill map for a given size
*/
char		*create_map(char *map, int size)
{
	int		i;

	i = 1;
	if (map != NULL)
		ft_strdel(&map);
	if (!(map = ft_strnew(((size + 1) * (size)) + 1)))
		return (NULL);
	while (i < ((size + 1) * (size)) + 1)
	{
		if (i % (size + 1) == 0 && i != 0)
			map[i - 1] = '\n';
		else
			map[i - 1] = '.';
		i++;
	}
	map[i] = '\0';
	return (map);
}
