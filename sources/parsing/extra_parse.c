/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymane <aymane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 06:55:10 by akajjou           #+#    #+#             */
/*   Updated: 2024/07/15 15:05:20 by aymane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

int     semicolon_checker(token_ptr tokens_list)
{
    token_ptr   tmp;
    
    tmp = tokens_list;
    while (tmp)
    {
        if (ft_strchr(tmp->token, ';') != NULL && tmp->token_type != 3)
        {
            ft_putstr_fd("minishell: syntax error near unexpected token `;'\n", 2);
            return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}

int     backslash_checker(token_ptr tokens_list)
{
    token_ptr   tmp;
    
    tmp = tokens_list;
    while (tmp)
    {
        if (ft_strchr(tmp->token, '\\') != NULL)
        {
            ft_putstr_fd("minishell: syntax error near unexpected token `\\'\n", 2);
            return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}
/*
int     parentheses_checker2(token_ptr tokens_list)
{
    token_ptr   tmp;
    
    tmp = tokens_list;
    while (tmp)
    {
        if (ft_strchr(tmp->token, '(') != NULL && tmp->token_type != 3)
        {
            
        }
    
        tmp = tmp->next;
    }
    return 0;
}*/

int		parentheses_checker(token_ptr tokens_list)
{
	token_ptr	tmp;
	int			open;
	int			close;

	tmp = tokens_list;
	open = 0;
	close = 0;
	while (tmp)
	{
		if (ft_strchr(tmp->token, '(') != NULL && tmp->token_type != 3)
			open++;
		if (ft_strchr(tmp->token, ')') != NULL && tmp->token_type != 3)
			close++;
		tmp = tmp->next;
	}
	if (open != close)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `('\n", 2);
		return 1;
	}
	return 0;
}
int     ft_env_search(char *tmp, t_env *envp)
{
    int i;

    i = 0;
    while (tmp[i] && tmp[i] == '$')
        i++;
    if (tmp[i] == '\0')
        return 1;
    while (envp)
    {
        if (ft_strncmp(tmp + i, envp->key, ft_strlen(tmp) - i) == 0)
            return 0;
        envp = envp->next;
    }
    return 1;
}

void    ft_expand_know(char *line, t_env *envp)
{
    int i;

    i = 0;
    while (line[i] && line[i] == '$')
        i++;
    while (envp)
    {
        if (ft_strncmp(line + i, envp->key, ft_strlen(line) - i) == 0)            
            break;
        envp = envp->next;
    }
    free(line);
    line = ft_strdup(envp->value);   
}

char    *ft_last_line(char **line_split)
{
    int i;
    char *new_line;

    i = 0;
    new_line = NULL;
    while (line_split[i])
    {
        new_line = ft_strjoin(new_line, line_split[i]);   
        i++;
    }
    return (new_line);
}

char    *ft_expand_heredoc(char *line, t_env *envp)
{
    int i;
    int d;
    char **line_split;
    char *new_line;
    
    line_split = ft_advanced_split(line);
    i = 0;
    while (line_split[i])
    {
        d = 0;
        while (line_split[i][d])
        {
            if (line_split[i][d] == '$')
            {
                if (ft_env_search(line_split[i], envp) == 0)
                    ft_expand_know(line_split[i], envp);
                else
                    line_split[i] = ft_strdup("");
            }
            d++;
        }
        i++;
    }
    new_line = ft_last_line(line_split);
    return new_line;
}


