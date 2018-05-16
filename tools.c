/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 20:53:53 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/16 13:45:04 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdlib.h>

void	tetri_push(t_tetri **alist, t_tetri *list)
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

t_tetri	*new_tetri(int *coord)
{
	t_tetri *new;

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
	new->name = 0;
	return (new);
}

void	tetri_del(t_tetri **alst)
{
	t_tetri *lst;
	t_tetri *ptr;

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
** Reset tetri position to zero by finding lowest x and y coordinates
*/
int		*reset_tetri_position(int *coord)
{
	int i;
	int x;
	int y;

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

char	*create_map(char *map, int size)
{
	int i;

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
