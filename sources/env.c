/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:33:36 by aymane            #+#    #+#             */
/*   Updated: 2024/07/23 16:27:36 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniHell.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strndup(const char *s1, size_t n)
{
	char	*copy;
	size_t	i;

	copy = (char *)malloc((n + 1) * sizeof(char));
	i = 0;
	while (i < n && s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

t_env	*create_env_node(const char *env_var)
{
	t_env	*new_node;
	char	*delimiter;

	new_node = (t_env *)malloc(sizeof(t_env));
	delimiter = ft_strchr(env_var, '=');
	new_node->key = ft_strndup(env_var, delimiter - env_var);
	new_node->value = ft_strdup(delimiter + 1);
	new_node->next = NULL;
	return (new_node);
}
char **ft_null_env(void)
{
	char	**default_env;
	char	cwd[PATH_MAX];
	char	*pwd;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (NULL);
	default_env = (char **)malloc(sizeof(char *) * 4);
	if (!default_env)
		return (NULL);
	pwd = (char *)malloc(strlen("PWD=") + strlen(cwd) + 1);
	if (!pwd)
	{
		free(default_env);
		return (NULL);
	}
	strcpy(pwd, "PWD=");
	strcat(pwd, cwd);
	default_env[0] = pwd;
	default_env[1] = strdup("SHLVL=1");
	default_env[2] = strdup("_=/usr/bin/env");
	default_env[3] = NULL;
	if (!default_env[1] || !default_env[2])
	{
		free(default_env[0]);
		free(default_env[1]);
		free(default_env[2]);
		free(default_env);
		return (NULL);
	}
	return (default_env);
}

t_env	*init_env(char **env)
{
	t_env	*head;
	t_env	*current;
	t_env	*new_node;
	
	if (env[0] == NULL)
		env = ft_null_env();
	head = NULL;
	current = NULL;
	while (*env)
	{
		new_node = create_env_node(*env);
		if (!head)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		env++;
	}
	return (head);
}
