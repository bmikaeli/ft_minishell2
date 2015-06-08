/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh2.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmikaeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/03 11:14:22 by bmikaeli          #+#    #+#             */
/*   Updated: 2015/06/03 11:14:24 by bmikaeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH2_H
# define FT_SH2_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft/includes/libft.h"
# include <dirent.h>

typedef struct	s_sh2 {
	char		**env;
	char		**path;
}				t_sh2;

int				isexist(char *binarie, t_sh2 *all);

void			getpath(t_sh2 *env);

int				ft_unsetenv(char *todelete, t_sh2 *all);

int				ft_setenv(char *toadd, t_sh2 *all);

void			exec(char **split, t_sh2 *all, int pathnb);

void			execpipe(char **split, char ** split2, t_sh2 *all, int pathnb, int pathnb2);

void			do_cd(char *line, t_sh2 *all);

void			print_env(t_sh2 *all);

#endif
