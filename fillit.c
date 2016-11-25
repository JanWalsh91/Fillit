/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 11:40:16 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/25 14:19:53 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		fillit(char *av)
{
	char		*input;
	t_map		map;
	//char**		result;
	t_tetrimino	*ts;
	short		i;

	if (!(input = read_file(av)))
		display_error_message();
	else if (((i = (ft_strlen(input) + 1) / (T_SIZE + 1)) == 0) ||
			((ft_strlen(input) + 1) % (T_SIZE + 1)) != 0)
		display_error_message();
	else if (!(ts = check_validity(input, i)))
		display_error_message();
	//printf("i: %d\n", i);
	else
	{
		ft_strdel(&input);
	//print_t_structs(ts);
	////printf("nu	mber of tetriminos: %i\n", i);
	////printf("first size: %d\n", get_first_	size(i));
		map = solve(ts, get_first_size(i), i);
	////printf("now displ		aying result\n");
	//result = get_final_map(&map, ts);
	////printf("result[		map.size]: %s\n", result[map.size]);
		print_result(get_final_map(&map, ts), &map);
		//free(&map);
	}
	/*i		= -1;
	  while (++i < map.size)
	  ft_putendl(result[i]);*/

	//ft_strdel(result); //freed result in print_result
	return (0);
}

/*
   void	display_usage(void)
   {
   ft_putemdl(USAGE)
   }

   void	display_error_message(void);
   {
   ft_putendl("error");
   }
   */
