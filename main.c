/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 18:35:00 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/09 23:35:04 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdlib.h>

int		main(int ac, char **av)
{
	t_tetri *begin;
	t_tetri *ptr;
	int		map_size;

	begin = NULL;
	map_size = 2;
	ptr = NULL;
	if (ac == 2)
	{
		if (set_list_if_valid_input(av[1], &begin) <= 0)
			ft_putstr("error\n");
		else
		{
			ptr = begin;
			ft_putstr("Success\n");
			while (get_tetri_height(begin) > map_size || get_tetri_len(begin) > map_size)
				map_size++;
			while (!solver(begin, ptr, map_size))
			{
				map_size++;
			}
		}
	}
	while (ptr != NULL)
	{
		ts_print_tetri(ptr, map_size);
		ptr = ptr->next;
		ft_putchar('\n');
	}
	print_result(begin, map_size);
	tetri_del(&begin);
	//else
	//	PRINT_USAGE
	//ft_strdel(&tmp);
	return (0);
}

int		solver(t_tetri *begin, t_tetri *ptr, int map_size)
{
	if (ptr != NULL)
	{
		if (!conflict(begin, ptr, map_size))
		{
			if (solver(begin, ptr->next, map_size) == 0)
			{
				if (try_next(begin, ptr, map_size) <= 0)
					return (0);
				return (solver(begin, ptr->next, map_size));
			}
			else
				return (1);
		}
		else
		{
			if (try_next(begin, ptr, map_size) <= 0)
				return (0);
			return(solver(begin, ptr, map_size));
		}
	}
	return (1);
}

int		conflict(t_tetri *begin, t_tetri *current, int map_size)
{
	t_tetri *ptr;
	int i;
	int j;

	ptr = begin;
	i = 0;
	j = 0;
	(void)map_size;
	if (begin == current)
		return (0);
	while (ptr != current)
	{
		while (i < 8)
		{
			while (j < 8)
			{
				if (ptr->coord[j] == current->coord[i] && ptr->coord[j + 1] == current->coord[i + 1])
					return (1);
				j += 2;
			}
			j = 0;
			i += 2;
		}
		ptr = ptr->next;
		i = 0;
		j = 0;
	}
	return (0);
}

int		try_next(t_tetri *begin, t_tetri *current, int map_size)
{
	int i;

	(void)begin;

	i = 0;
	if (current->length >= map_size && current->height < map_size)
	{
		reset_y_pos(current);
		while (i < 8)
		{
			current->coord[i] += 1;
			i += 2;
		}
		current->length = 2;
		current->height++;
		return (1);
	}
	else if (current->length < map_size)
	{
		while (i < 8)
		{
			current->coord[i + 1]++;
			i += 2;
		}
		current->length++;
		return (1);
	}
	current->coord = reset_tetri_position(current->coord);
	current->height = get_tetri_height(current);
	current->length = get_tetri_len(current);
	return (-1);
}

void	reset_y_pos(t_tetri *tetri)
{
	int i;
	int tmp;

	i = 1;
	tmp = tetri->coord[1];
	while (i < 8)
	{
		if (tetri->coord[i] < tmp)
			tmp = tetri->coord[i];
		i += 2;
	}
	i = 1;
	while (i < 8)
	{
		tetri->coord[i] -= tmp;
		i += 2;
	}
}

int		get_tetri_len(t_tetri *tetri)
{
	int i;
	int tmp;

	i = 0;
	tmp = tetri->coord[i + 1];
	while (i < 8)
	{
		if (tetri->coord[i + 1] > tmp)
			tmp = tetri->coord[i + 1];
		i += 2;
	}
	return (tmp + 1);
}

int		get_tetri_height(t_tetri *tetri)
{
	int i;
	int tmp;

	i = 0;
	tmp = tetri->coord[i];
	while (i < 8)
	{
		if (tetri->coord[i] > tmp)
			tmp = tetri->coord[i];
		i += 2;
	}
	return (tmp + 1);
}

void	print_result(t_tetri *list, int map_size)
{
	int i;
	int j;
	t_tetri *ptr;
	char print;

	i = 0;
	j = 0;
	ptr = list;
	print = 0;
	while (i < map_size)
	{
		while (j < map_size)
		{
			print = find_block_at_coord(list, i, j);
			if (print == 0)
				ft_putchar('.');
			else
				ft_putchar(print);
			j++;
		}
		ft_putchar('\n');
		i++;
		j = 0;
	}
}

char	find_block_at_coord(t_tetri *list, int x, int y)
{
	int i;

	i = 0;
	while (list != NULL)
	{
		while (i < 8)
		{
			if (list->coord[i] == x && list->coord[i + 1] == y)
				return (list->name);
			i += 2;
		}
		i = 0;
		list = list->next;
	}
	return (0);
}
