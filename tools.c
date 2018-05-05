/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 20:53:53 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/05 18:00:50 by bopopovi         ###   ########.fr       */
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
