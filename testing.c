/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 17:14:50 by bopopovi          #+#    #+#             */
/*   Updated: 2018/05/04 20:22:49 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <unistd.h>

void	ts_print_tetri_map(char *buff)
{
	write(1, buff, BUFF_SIZE);
	//ft_putstr_npr(buff);
}
