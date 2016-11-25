/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 11:23:51 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/25 14:01:42 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

/*
 ** Takes a string of chars containing the contents of the read file.
 ** Calls on other functions to check the validity of the input.
 ** Returns an array of validated t_tetrimino structs
 */


t_tetrimino	*check_validity(char *input, short num)
{
	char	**ts;
	short		i;

	i = 0;
	if (check_input_length(input, num) == 0)
		 return (NULL);
	//ft_putstr("Length Valid\n");
	ts = t_split(input, num);

	if (!check_t_format(ts) || !check_full_char(ts))
		return (NULL);
	//print_t(ts);
	//printf("VALID INPUT\n");
	//print_t(ts);
	return (set_tetriminos(ts, num));
}

/*
 ** Checks if there is the right amount of tetriminos.
 ** Checks if the length of the entire file is valid.
 */

short		 check_input_length(char *t, short num)
{
	int	i;
	int	count;;

	i = 0;
	count = 0;
	if (num > T_MAX)
		return (0);
	while (t[i])
	{
		if (t[i] == '\n')
		{
			count++;
			if (count == 5)
			{
				if (t[i - 1] != '\n')
					return(0);
				count = 0;
			}
		}
		i++;
	}
	return ((ft_strlen(t) + 1) % (T_SIZE + 1) == 0);
}

short		check_t_format(char **ts)
{
	short	i;
	short	j;

	i = 0;
	while (ts[i])
	{
		j = 0;
		while (ts[i][j])
		{
			if ((j + 1) % T_WIDTH == 0 && ts[i][j] != '\n')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

/*
 ** Takes an array of tetriminos and checks if the pattern is valid. Conditions:
 ** -each CHAR_FULL char must be next to at least ONE other CHAR_FULL char.
 ** -there must be at least ONE CHAR_FULL char connected with TWO CHAR_FULL
 **  chars. (see connections variable)
 ** Returns 1 if conditions are met, else returns 0.
 */

short		check_full_char(char **ts)
{
	short	i;
	short	j;
	short	n;
	short	connections;

	//ft_putstr("Checking in check_full_num\n");
	i = 0;
	while (ts[i]) //iterate over array of tetriminos
	{
		n = 0;
		j = 0;
		connections = 0;
		while (ts[i][j]) //iterate over chars in tetriminos
		{
			if (ts[i][j] != CHAR_FULL && ts[i][j] != CHAR_EMPTY && ts[i][j] != '\n')
				return (0);
				//printf("Invalid char at ts[%i][%i]: %c\n", i, j, ts[i][j]);
			//printf("Check1\n");
			if (ts[i][j] == CHAR_FULL)
				n += check_pattern(ts[i], j, &connections);
			if (n == 4 && !connections)
					return (0);
			j++;
			//printf("Check2\n");
		}
		//printf("In the %ith tetrimino, n is %i\n", i, n);
		//update_tetrimino(&(ts[i]), i)i
		if (n != 4 || !connections)
			return (0);
		i++;
	}
	//print_t(ts);
	//printf("connections: %i\n", connections);
	return (1);
}

/*
 ** From the char at index i int the tetrimino t, checks if the four spaces
 ** around it, if they exist,  are also CHAR_FULL chars.
 ** Returns 1 if at least one connection is found.
 ** If there are more than one connections, connections is set to 1.
 */

short		check_pattern(char *t, short i, short *connections)
{
	short	connected;

	//printf("Checking connections\n");
	connected = 0;
	if (i - T_WIDTH >= 0 && t[i - T_WIDTH] == CHAR_FULL) //Checks previous line
		connected += 1;
	if (i + T_WIDTH < T_SIZE && t[i + T_WIDTH] == CHAR_FULL) //Checks next line
		connected += 1;
	if (i - 1 > 0 && t[i - 1] == CHAR_FULL) //Checks previous col
		connected += 1;
	if (i + 1 < T_SIZE && t[i + 1] == CHAR_FULL) //Checks next col
		connected += 1;
	if (connected > 1)
		*connections = 1; // if a spot has more than one connection, it has connections.
	if (!connected)
		return (0);
	return (1);
}
