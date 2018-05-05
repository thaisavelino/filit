/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 18:05:31 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/05 16:17:04 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/*
** Stock tetris coordinates in list from file if file is correctly formatted
** Return 1 in case of error
*/
int			get_list_if_file_is_valid(char *file, t_tetri **list)
{
	char		buffer[BUFF_SIZE];
	int			fd;
	int			tetri_count;
	t_tetri		*tetri;
	int			bytes;

	tetri_count = 0;
	bytes = 1;
	if ((fd = open(file, O_RDONLY)) <= 0)
		return (1);
	while ((bytes = get_input(fd, buffer, bytes)) && tetri_count <= 26)
	{
		ts_print_tetri_map(buffer);
		if (!(tetri = get_tetri(buffer, tetri_count++)))
			return (1);
		tetri_push(list, tetri);
	}
	close(fd);
	return (bytes < 0 || tetri_count > 26 ? 1 : 0);
}

t_tetri		*get_tetri(char buffer[BUFF_SIZE], int tetri_count)
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
			if (buffer[i] != '\n')
				return (NULL);
		}
		else if ((buffer[i] && buffer[i] != '.' && buffer[i] != '#'))
			return (NULL);
		if (buffer[i] == '#')
			contact += get_block(buffer, coord, blocks++, i);
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
int		get_block(char *buffer, int *coord, int blocks, int pos)
{
	int		junctions;


	junctions = 0;
	coord[blocks * 2] = pos / 5;
	coord[(blocks * 2) + 1] = pos % 5;
	if (pos <= 13 && buffer[pos + 5] == '#')
		junctions++;
	if (pos >= 5 && buffer[pos - 5] == '#')
		junctions++;
	if (pos >= 1 && buffer[pos - 1] == '#')
		junctions++;
	if (pos <= 18 && buffer[pos + 1] == '#')
		junctions++;
	return (junctions);
}

/*
**
*/
int		get_input(int fd, char buffer[BUFF_SIZE], int prev_bytes)
{
	int		bytes;
	char	tmp;

	ft_bzero(buffer, BUFF_SIZE);
	bytes = read(fd, &(*buffer), BUFF_SIZE - 1);
	if (bytes == 0 && prev_bytes == 21)
		return (-1);
	if (read(fd, &tmp, 1))
	{
		if (tmp != '\n')
			return (-1);
		bytes++;
	}
	buffer[bytes] = '\0';
	return (bytes);
}
