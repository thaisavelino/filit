/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 20:20:10 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/16 22:40:12 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

#include "libft/libft.h"

#define BUFF_SIZE 21
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

typedef struct	s_tetri
{
	int *coord;
	int pos;
	char name;
	struct	s_tetri *next;
}				t_tetri;

/*
** MAIN
*/
int		solve_tetri(t_tetri *list, char *map, int tetri_nbr);
int		backtrack(t_tetri *ptr, char *map, int map_len, int i);
int		conflict(t_tetri *tetri, char *map, int map_len, int pos);
void	put_tetri(t_tetri *tetri, char *map, int map_len, int pos);
/*
** PARSING
*/
int		set_list(char *file, t_tetri **list);
t_tetri	*get_tetri(char buff[BUFF_SIZE], int tetri_nbr);
int		read_file_to_buffer(int fd, char buff[BUFF_SIZE], int prev_bytes);
int		get_junctions(char *buff, int pos);
/*
** TOOLS
*/
void	tetri_push(t_tetri **alist, t_tetri *list);
t_tetri	*new_tetri(int *coord, int tetri_nbr);
void	tetri_del(t_tetri **alst);
int		*reset_tetri_position(int *coord);
char	*create_map(char *map, int size);
/*
** TESTING
*/
void	ts_print_tetri_map(char *buff);
void	ts_print_tetri(t_tetri *tetri, int map_len);
void	print_tetri_color(char *map, t_tetri *tetri, int size, int pos, char *color);
void	print_solution(char *map);

#endif
