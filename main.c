/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmikaeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 10:36:33 by bmikaeli          #+#    #+#             */
/*   Updated: 2015/06/02 10:36:34 by bmikaeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh2.h"

void		parse2(char *line, t_sh2 *all)
{
	char	**split;
	int		pathnb;

	if (!ft_strcmp(line, "exit"))
		exit(1);
	else if (!ft_strncmp(line, "cd ", 3))
		do_cd(line, all);
	else if (!ft_strncmp(line, "setenv ", 7))
		ft_setenv(line, all);
	else if (!ft_strcmp(line, "env"))
		print_env(all);
	else if (!ft_strncmp(line, "unsetenv ", 9))
		ft_unsetenv(ft_strsplit(line, ' ')[1], all);
	else if (ft_strcmp(line, ""))
	{
		split = ft_strsplit(line, ' ');
		pathnb = isexist(split[0], all);
		if (pathnb != -1)
			exec(split, all, pathnb);
		else
			ft_putendl("command not found");
	}
}


/* Read characters from the pipe and echo them to stdout. */
void read_from_pipe (int file)
{
    FILE *stream;
    int c;
    stream = fdopen (file, "r");
    while ((c = fgetc (stream)) != EOF)
        putchar (c);
    fclose (stream);
}

/* Write some random text to the pipe. */

void write_to_pipe (int file)
{
    FILE *stream;
    stream = fdopen (file, "w");
    fprintf (stream, "hello, world!\n");
    fprintf (stream, "goodbye, world!\n");
    fclose (stream);
}


void		parse(char *line, t_sh2 *all)
{
	char	**allcmd;
	int		i;

	i = 0;
	allcmd = ft_strsplit(line, ';');
	while (allcmd != NULL && allcmd[i] && ft_strtrim(allcmd[i])[0])
	{
        if(ft_strstr(allcmd[i] , "|") != NULL)
        {
            char **split = ft_strsplit(allcmd[i], '|');

            int fds[2];
            pid_t pid;
            pipe(fds);

            /* Create the child process. */
            pid = fork ();
            if (pid == (pid_t) 0)
            {
                /* This is the child process.
                   Close other end first. */
                close (fds[1]);
//                parse2(split[1], all);
                read_from_pipe (fds[0]);
            }
            else
            {
                /* This is the parent process.
                   Close other end first. */
                close (fds[0]);

                parse2(split[0], all);
//                write_to_pipe(fds[1]);
            }
        }
		else if(ft_strstr(allcmd[i], ">>") != NULL)
		{
            char **split = ft_strsplit(allcmd[i], '>');
            if(split[1])
            {
                ft_putendl(split[1]);
                int sortie = open(ft_strtrim(split[1]), O_RDWR | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH);
                int old = dup(1);
                dup2(sortie, 1);
                parse2(split[0], all);
                close(sortie);
                dup2(old, 1);
            }
            else
            {
                ft_putendl("No output filename specified");
            }
        }
		else if(ft_strstr(allcmd[i], ">") != NULL)
		{
			char **split = ft_strsplit(allcmd[i], '>');
            if(split[1])
            {
                int sortie = open(ft_strtrim(split[1]), O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH);
                int old = dup(1);
                dup2(sortie, 1);
                parse2(split[0], all);
                close(sortie);
                dup2(old, 1);
            }
            else
            {
                ft_putendl("No output filename specified");
            }
		}
        else if(ft_strstr(allcmd[i], "<") != NULL)
		{
			char **split = ft_strsplit(allcmd[i], '<');
            if(split[1])
            {
                int entree = open(ft_strtrim(split[1]), O_RDONLY);
                int old = dup(0);
                dup2(entree, 0);
                parse2(split[0], all);
                close(entree);
                dup2(old, 0);
            }
            else
            {
                ft_putendl("No input filename or command specified");
            }
		}
        else if(ft_strstr(allcmd[i], "<<") != NULL)
        {
            char **split = ft_strsplit(allcmd[i], '>');
            ft_putendl(split[1]);
            int sortie = open(ft_strtrim(split[1]), O_RDWR | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH);
            int old = dup(1);
            dup2(sortie, 1);
            parse2(split[0], all);
            close(sortie);
            dup2(old, 1);
        }
		else
		{
			parse2(allcmd[i], all);
		}
		i++;
	}
}

char		*trimline(char *line)
{
	char	*ret;
	int		i;
	int		j;

	ret = ft_strlen(line) ? malloc(sizeof(char *) * ft_strlen(line) + 1)
		: malloc(500);
	i = 0;
	j = 0;
	while (line && line[i])
	{
		if ((line[i] == ' ' || line[i] == '\t') && ret[j - 1] == ' ')
		{
			i++;
			continue;
		}
		if (line[i] == '\t')
			ret[j] = ' ';
		else
			ret[j] = line[i];
		j++;
		i++;
	}
	ret[j] = '\0';
	return (ret);
}

int			main(int ac, char **av, char **env)
{
	char	*line;
	t_sh2	all;

    (void)ac;
	(void)av;
	if (env[0] == NULL)
	{
		ft_putendl("Env null");
		exit(-1);
	}
	all.env = env;
	line = NULL;
	getpath(&all);
	all.path[0] = ft_strsub(all.path[0], 5, ft_strlen(all.path[0]) - 5);
	ft_putstr("bmikaeli $> ");
	while (get_next_line(1, &line))
	{
		line = ft_strtrim(line);
		line = trimline(line);
		parse(line, &all);
		ft_putstr("bmikaeli $> ");
	}
	return (0);
}
