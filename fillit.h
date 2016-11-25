/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 13:56:49 by jwalsh            #+#    #+#             */
/*   Updated: 2016/11/25 14:01:28 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# define USAGE "usage: ./fillit source_file"
# define CHAR_EMPTY '.'
# define CHAR_FULL '#'
# define T_SIZE (T_WIDTH * T_HEIGHT)
# define T_WIDTH (4 + 1) // due to the \n
# define T_HEIGHT (4)
# define T_MAX 26
# define MAX_BUFFER_SIZE (T_SIZE + 1) * T_MAX


# include "./Libft/libft.h"
# include <fcntl.h>

# include <stdio.h>    ////////////////////////////////

typedef struct	s_pt
{
	short	x;
	short	y;
}				t_pt;

/* Obsolete
typedef struct	s_minmax_pts
{
	t_pt	max;
	t_pt	min;
}				t_minmax_pts;
*/

typedef struct	s_map
{
	short		**m;
	short		size; //current size of map
	short		i; //index of ts
	short		total; //total number of tetrimimos
	//t_pt	c; //coords we are currently on
}				t_map;

typedef struct	s_tetrimino
{
	t_pt	*pts; //four pts
	short	i; // index of tetrimino
	short	x;
	short	y; //coords where tetrimino was placed or to be placed.
}				t_tetrimino;

int				fillit(char *fd);

/*** Reading Input ***/
char			*read_file(char *av);

/*** Checking Input Validity ***/
t_tetrimino		*check_validity(char *input, short num); // calls the below functionsi // check.c
short			check_input_length(char *t, short num); // checks if length is valid // check.c
short			check_t_format(char **ts);
char			**t_split(char *s, short num); // puts each tetrimino in his own string // t_split.c
short			check_full_char(char **ts); // check if each tetrimino shape is valid // check.c
short			check_pattern(char *t, short i, short *connections); // inside check_full_num // check.c
t_tetrimino		*set_tetriminos(char **ts, short num); // each tetri is now saved as 4 coords x, y // tetri_trim.c
void			get_reference(char *t, t_pt *ref); // looks for max and min coords of the tetri // tetri_trim.c
//void			reset_pts(t_pt *ref); // set original value of coords // tetri_trim.c
t_tetrimino		set_points(char *ts, t_pt ref); // sets the coordinatates of its four points // tetri_trim.c
void			display_usage(void); //displays the USAGE and returns 0 //error.c
void			display_error_message(); //displays an error message and returns 0// error.c

/*** Solving Mqp ***/
t_map			solve(t_tetrimino *ts, short size, short num); // calls the below functions // solve.c
short			get_first_size(short nb); // find the potentially smallest size for the map // map.c
short			gen_map(t_map *m, short size, short num); // generates map // map.c
short			fill_map(t_map *m, t_tetrimino *ts); // tries to fill it using place and remove // solve.c
short			place_t(t_map *m, t_tetrimino *ts); // calls update map if success // solve.c
short			update_map(t_map *m, t_tetrimino *ts); // update coordonates using increment_t_coords // solve.c
void			increment_t_coords(t_tetrimino *ts, t_map *m); // t_coords // points.c
void			remove_t(t_map *m, t_tetrimino *ts); // solve.c

/*** Display Final Map ***/
void			reset_map(t_map *m, t_tetrimino *ts); // reset map to original if failed to fill // map.c
void			reset_t_coords(t_tetrimino *ts); // resets previously saved coords // points.c
char			**get_final_map(t_map *m, t_tetrimino *ts); // allocates memory to a double char array and sets // map.c
void			set_char(char **result, t_tetrimino *ts); // replaces # with letter // map.c
void			print_result(char **m, t_map *map); // print the final result with \n // print.c

/*** Debugging ***/
//void			print_t(char **t); // debug_functions.c
//void			print_t_structs(t_tetrimino *t); // debug_functions.c
//void			print_t_map(t_map m); // displays the map of t_map->m // debug_functions.c
//void			print_t_structs(t_tetrimino *ts);

#endif
