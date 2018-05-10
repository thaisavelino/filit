/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 18:05:31 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/10 15:28:26 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/*
** Stock each tetris coordinates in list from file
** Returns a negative value if an error is encountered
*/
int			set_list_if_valid_input(char *file, t_tetri **list)
{
	t_tetri		*tetri;
	char		buffer[BUFF_SIZE];
	int			count_tetri;
	int			read_size;
	int			fd;

	count_tetri = 0;
	read_size = 0;
	if ((fd = open(file, O_RDONLY)) > 0)
	{
		while ((read_size = read_file_to_buffer(fd, buffer, read_size)))
		{
			if ((tetri = get_tetri_if_valid(buffer)) && count_tetri < 26)
			{
				tetri->name = 'A' + count_tetri++;
				tetri_push(list, tetri);
			}
			else
				return (-1);
		}
		close(fd);
	}
	if (fd < 0 || read_size < 0)
		return (-1);
	return (1);
}

/*
** Returns a newly created tetri containing it's blocks coordinates
** Returns NULL if an error is encountered
*/
t_tetri		*get_tetri_if_valid(char buffer[BUFF_SIZE])
{
	int		i;
	int		count_junctions;
	int		count_blocks;
	int		coord[8];

	i = 0;
	count_junctions = 0;
	count_blocks = 0;
	while (buffer[i])
	{
		if (buffer[i] != '.' && buffer[i] != '#' && buffer[i] != '\n')
			return (NULL);
		else if ((i + 1) % 5 == 0 && buffer[i] != '\n')
			return (NULL);
		else if (buffer[i] == '#')
		{
			coord[count_blocks * 2] = i / 5;
			coord[(count_blocks++ * 2) + 1] = i % 5;
			count_junctions += get_junctions(buffer, i);
		}
		i++;
	}
	if (count_blocks == 4 && (count_junctions == 6 || count_junctions == 8))
		return (new_tetri(coord));
	return (NULL);
}

/*
** Returns the number of junctions for a given block
*/
int		get_junctions(char *buffer, int pos)
{
	int		count_junctions;


	count_junctions = 0;
	if (pos <= 13 && buffer[pos + 5] == '#')
		count_junctions++;
	if (pos >= 5 && buffer[pos - 5] == '#')
		count_junctions++;
	if (pos >= 1 && buffer[pos - 1] == '#')
		count_junctions++;
	if (pos <= 18 && buffer[pos + 1] == '#')
		count_junctions++;
	return (count_junctions);
}

/*
** Read next tetri from file to buffer
** Returns number of bytes read or a negative value in case of error
*/
int		read_file_to_buffer(int fd, char buffer[BUFF_SIZE], int prev_bytes)
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
