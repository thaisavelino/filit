/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 18:05:31 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/05 03:10:18 by bpopov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int			parse_input(char *file, t_tetri **list)
{
	char		buff[BUFF_SIZE];
	int			fd;
	int			tetri_count;
	t_tetri		*tetri;
	int			bytes;

	tetri_count = 0;
	bytes = 1;
	if ((fd = open(file, O_RDONLY)) <= 0)
		return (1);
	while ((bytes = get_input(fd, buff, bytes)) && tetri_count <= 26)
	{
		ts_print_tetri_map(buff);
		if (!(tetri = get_tetri(buff, tetri_count++)))
			return (1);
		tetri_push(list, tetri);
	}
	close(fd);
	return (bytes < 0 || tetri_count > 26 ? 1 : 0);
}

t_tetri		*get_tetri(char buff[BUFF_SIZE], int tetri_count)
{
	t_tetri	*tetri;
	int		coord[8];
	int		blocks;
	int		contact;
	int		i;

	contact = 0;
	i = 0;
	blocks = 0;
	tetri = NULL;
	while (i < 21)
	{
		if (((i && (i + 1) % 5 == 0)))
		{
			if (buff[i] != '\n')
				return (NULL);
		}
		else if ((buff[i] && buff[i] != '.' && buff[i] != '#'))
			return (NULL);
		if (buff[i] == '#')
			contact += get_block(buff, coord, blocks++, i);
		i++;
	}
	if (blocks != 4 || (contact != 6 && contact != 8))
		return (NULL);
	trim_offset(coord);
	if (!(tetri = new_tetri(coord, 'A' + tetri_count)))
		return (NULL);
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

/*
** Set current block's coordinates and return it's number of junctions
*/
int		get_block(char *buff, int *coord, int blocks, int pos)
{
	int		junctions;


	junctions = 0;
	coord[blocks * 2] = pos / 5;
	coord[(blocks * 2) + 1] = pos % 5;
	if (pos <= 13 && buff[pos + 5] == '#')
		junctions++;
	if (pos >= 5 && buff[pos - 5] == '#')
		junctions++;
	if (pos >= 1 && buff[pos - 1] == '#')
		junctions++;
	if (pos <= 18 && buff[pos + 1] == '#')
		junctions++;
	return (junctions);
}

/*
**
*/
int		get_input(int fd, char buff[BUFF_SIZE], int prev_bytes)
{
	int		bytes;
	char	tmp;

	ft_bzero(buff, BUFF_SIZE);
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
