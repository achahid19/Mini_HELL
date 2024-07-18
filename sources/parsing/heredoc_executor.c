/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:35:58 by akajjou           #+#    #+#             */
/*   Updated: 2024/07/18 15:58:54 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/miniHell.h"

// no expand in ""''
// "" del = enter
// < "". same msj

void   ft_eraser(token_ptr tmp, char *filename)
{
    token_ptr tmp2;
    
    tmp2 = tmp->next;
    if (tmp2->token_type == 0)
        while (tmp2 && tmp2->token_type == 0)
            tmp2 = tmp2->next;
    while (tmp2 && tmp2->token_type != 20)
        node_remover(&tmp2);
    tmp2->token = ft_strdup(filename);
    tmp2 = tmp2->next;
    while (tmp2 && tmp2->token_type != 0 && tmp2->token_type != 1 && tmp2->token_type != 8
    && tmp2->token_type != 9 && tmp2->token_type != 10 && tmp2->token_type != 11)
        node_remover(&tmp2);
    tmp2 = tmp;
    while (tmp2)
    {
        if (tmp2->token_type == 20)
            tmp2->token_type = 2;
        tmp2 = tmp2->next;
    }
}

void    filename_write(token_ptr tokens_list, char *filename, int order)
{
    token_ptr   tmp;

    tmp = tokens_list;
    while (tmp)
    {
        if (tmp->order == order)
        {
            ft_eraser(tmp,filename);
            break;
        }
        tmp = tmp->next;
    }
}

void    new_token_lst(token_ptr tokens_list, int order)
{
    token_ptr   tmp;
    
    tmp = tokens_list;
    while (tmp)
    {
        if (tmp->order == order)
        {
            free(tmp->token);
            tmp->token = ft_strdup("<");
            tmp->token_type = 8;
            return ;
        }
        tmp = tmp->next;
    }
}

char    *get_unique_filename(int i)
{
    char    *filename;

    filename = ft_strdup("/tmp/heredoc_");
    filename = ft_strjoin(filename, ft_itoa(i));
    return (filename);
}

char	*heredoc_storer(char *delimiter, int i, t_env *envp)
{
	char *filename;
	int fd;
	char *line;
    int fd0 = dup(0);
    
	filename = get_unique_filename(i);
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
    signal_handler_heredoc();
	while (1)
	{
		line = readline(">");
        if (line == NULL)
            break;
        if (line[0] == '\0')
        {
            if (ft_strlen(delimiter) == 0)
                return NULL;
            write(fd, "\n", 1);
            continue;
        }
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0 &&
                    ft_strlen(line) == ft_strlen(delimiter))
		{
			free(line);
			break;
		}
        line = ft_expand_heredoc(line, envp);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
    dup2(fd0 , 0);
    close(fd0);
    // free(line);
	return filename;
}
void    ft_enter(token_ptr tokens_list, int i)
{
    token_ptr tmp;
    char *filename;

    filename = get_unique_filename(i);
    tmp = tokens_list;
    while (tmp)
    {
        if (tmp->token_type == 4 || tmp->token_type == 5)
        {
            tmp->token = ft_strdup(filename);
            tmp->token_type = 2;
            break;
        }
        tmp = tmp->next;
    }
}
void	heredoc(token_ptr tmp, token_ptr tokens_list, t_env *envp)
{
	int i;
	char *filename;
    char *test;
	token_ptr tmp2;
    
    i = 0;
    tmp2 = tokens_list;
	while (tmp)
	{
		if (tmp->token_type == 10)
		{
			i++;
            test = ft_delimiter(tokens_list ,tmp->order);
			filename = heredoc_storer(test, i,envp);
			new_token_lst(tokens_list,tmp->order);
            if (filename == NULL)
                ft_enter(tokens_list,i);
            else
			    filename_write(tokens_list, filename, tmp->order);
		}
		tmp = tmp->next;
        
	}
    // free(test);
    // free(filename);
}
