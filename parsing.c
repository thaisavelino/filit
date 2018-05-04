/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 18:05:31 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/05 01:40:38 by bpopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

t_tetri		*parse_input(char *file)
{
	char		buff[BUFF_SIZE];
	int			fd;
	int			tetri_count;
	t_tetri		*list;
	t_tetri		*tetri;
	int			bytes;

	tetri_count = 0;
	bytes = 21;
	if ((fd = open(file, O_RDONLY)) <= 0)
		return (NULL);
	list = NULL;
	ft_bzero(buff, BUFF_SIZE);
	while ((bytes = get_input(fd, buff, bytes)))
	{
		if (bytes < 0)
			return (NULL);
		ts_print_tetri_map(buff);
		if (tetri_count >= 27)
			return (NULL);
		if (!(tetri = get_tetri(buff, tetri_count++, fd)))
			return (NULL);
		tetri_push(&list, tetri);
		ft_bzero(buff, BUFF_SIZE);
	}
	close(fd);
	return (list);
}

t_tetri		*get_tetri(char buff[BUFF_SIZE], int tetri_count, int fd)
{
	t_tetri	*tetri;
	int		coord[8];
	int		blocks;
	int		contact;
	int		i;

	(void)fd;

	contact = 0;
	i = 0;
	blocks = 0;
	tetri = NULL;
	while (i < 21)
	{
		if (((i && (i + 1) % 5 == 0) || i == 20))
		{
			if (i != 20)
			{
				if (buff[i] != '\n')
					return (NULL);
			}
		}
		else if ((buff[i] && buff[i] != '.' && buff[i] != '#'))
		{
			return (NULL);
		}
		if (buff[i] == '#')
		{
			contact += ft_count_touch(buff, i);
			set_coord(coord, blocks++, i);
		}
		i++;
	}
	if (blocks != 4 || (contact != 6 && contact != 8))
		return (NULL);
	trim_offset(coord);
	tetri = new_tetri(coord, 'A' + tetri_count);
	return (tetri);
}

/*
** Find lowest x and y coordinates, substract every x and y coordinates from it
*/
int		*trim_offset(int *coord)
{
	int i;
	int x;
	int y;

	i = 0;
	x = 3;
	y = 3;
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

void	set_coord(int *coord, int blocks, int pos)
{
	coord[blocks * 2] = pos / 5;
	coord[(blocks * 2) + 1] = pos % 5;
}

/*
**
*/
int		get_input(int fd, char buff[BUFF_SIZE], int prev_bytes)
{
	int		bytes;
	char	tmp;

	bytes = read(fd, &(*buff), BUFF_SIZE - 1);
	if (bytes == 0 && prev_bytes == 21)
		return (-1);
	if (read(fd, &tmp, 1))
	{
		if (tmp != '\n')
			return (-1);
		bytes++;
	}
	buff[bytes] = '\0';
	return (bytes);
}

int		ft_count_touch(char *buff, int i)
{
	int	touch;

	touch = 0;
	if (i <= 13 && buff[i + 5] == '#')
		touch++;
	if (i >= 5 && buff[i - 5] == '#')
		touch++;
	if (i >= 1 && buff[i - 1] == '#')
		touch++;
	if (i <= 18 && buff[i + 1] == '#')
		touch++;
	if (!(touch == 1 || touch == 2 || touch == 3))
		return (-1);
	return (touch);
}
