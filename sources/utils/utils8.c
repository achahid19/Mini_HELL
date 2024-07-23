/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 21:54:04 by akajjou           #+#    #+#             */
/*   Updated: 2024/07/23 22:18:38 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"

void	change_pwd(t_env *envs, const char *old_pwd, const char *pwd)
{
	set_env(envs, "OLDPWD", old_pwd);
	set_env(envs, "PWD", pwd);
}

void	handler(int signum)
{
	write(STDOUT, "\n", 1);
	write(STDOUT, "kssh$ ", 6);
	(void)signum;
}

void	ft_sort_env(t_env *env)
{
	t_env	*tmp;
	t_env	*tmp2;
	char	*key;
	char	*value;

	tmp = env;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_strcmp(tmp->key, tmp2->key) > 0)
			{
				key = tmp->key;
				value = tmp->value;
				tmp->key = tmp2->key;
				tmp->value = tmp2->value;
				tmp2->key = key;
				tmp2->value = value;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}

t_bool	is_valid_identifier(char c, int i)
{
	if (i == 0)
	{
		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
			return (true);
	}
	else
	{
		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
			|| (c >= '0' && c <= '9') || c == '_')
			return (true);
	}
	return (false);
}

char	*ft_key(char *variable)
{
	char	*key;
	int		i;

	i = 0;
	while (variable[i] && variable[i] != '=' && !(variable[i] == '+'
			&& variable[i + 1] == '='))
		i++;
	key = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (variable[i] && variable[i] != '=' && !(variable[i] == '+'
			&& variable[i + 1] == '='))
	{
		key[i] = variable[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}
