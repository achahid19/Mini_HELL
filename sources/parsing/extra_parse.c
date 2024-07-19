/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymane <aymane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 06:55:10 by akajjou           #+#    #+#             */
/*   Updated: 2024/07/19 18:10:19 by aymane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"


int	parentheses_checker(token_ptr tokens_list)
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
		return (1);
	}
	return (0);
}
int	ft_env_search(char *tmp, t_env *envp)
{
	int	i;
	int len;

	i = 1;
	if (tmp[i] == '\0')
		return (1);
	while (envp)
	{
		if (ft_strlen(tmp) - 1 > ft_strlen(envp->key))
			len = ft_strlen(tmp) - 1;
		else
			len = ft_strlen(envp->key);
		if (ft_strncmp(tmp + i, envp->key, len) == 0)
			return (0);
		envp = envp->next;
	}
	return (1);
}

void	ft_expand_know(char **line, t_env *envp)
{
	int flag = 0;

	while (envp)
	{
		if (ft_strncmp(*(line) + 1, envp->key, ft_strlen(envp->key) ) == 0)
		{
			flag = 1;
			break ;
		}
		envp = envp->next;
	}
	free(*line);
	if (flag == 1)
	*line = ft_strdup(envp->value);
}

char	*ft_last_line(char **line_split)
{
	int		i;
	char	*new_line;

	int f= 0;
	int d = 0;
	i = 0;
	new_line = NULL;
	while (line_split[i])
	{
		new_line = ft_strjoin(new_line, line_split[i]);
		i++;
	}
	return (new_line);
}
void 		ft_free_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*ft_expand_heredoc(char *line, t_env *envp)
{
	int		i;
	int		d;
	char	**line_split;
	char	*new_line = NULL;

	line_split = ft_advanced_split(line);
	i = 0;
	while (line_split[i])
	{
		d = 0;
		while (line_split[i][d])
		{
	
			if (line_split[i][d] == '$' && line_split[i][d + 1] != '\0')
			{
				if (line_split[i][d + 1] == '?')
				{
					free(line_split[i]);
					if (g_global.status == 256)
						g_global.status = 127;
					else if (g_global.status == 768)
						g_global.status = 1;
					else if (g_global.status == 32256)
						g_global.status = 126;
					else if (g_global.status == 512)
						g_global.status = 2;
					line_split[i] = ft_itoa(g_global.status);
				}
				else if (ft_env_search(line_split[i], envp) == 0) 
					ft_expand_know(&line_split[i], envp);
				else
					line_split[i] = ft_strdup("");
			}
			d++;
		}
		i++;
	}
	new_line = ft_last_line(line_split);
	// ft_free_array(line_split);
	return (new_line);
}



