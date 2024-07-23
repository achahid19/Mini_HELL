/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:00:17 by akajjou           #+#    #+#             */
/*   Updated: 2024/07/23 20:20:42 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniHell.h"
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdbool.h>

char	*get_env_value(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

// Function to set an environment variable's value
void	set_env(t_env *env, const char *key, const char *value)
{
	t_env	*new_env;
	
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			free(env->value);
			env->value = ft_strdup(value);
			return ;
		}
		env = env->next;
	}
	new_env = (t_env *)malloc(sizeof(t_env));
	new_env->key = ft_strdup(key);
	new_env->value = ft_strdup(value);
	new_env->next = g_global.e;
	g_global.e = new_env;
}

static void	change_pwd(t_env *envs, const char *old_pwd, const char *pwd)
{
	set_env(envs, "OLDPWD", old_pwd);
	set_env(envs, "PWD", pwd);
}

t_bool	check_directory(char *dir)
{
	struct stat	info;

	if (access(dir, F_OK) == -1)
		return (error("cd", "No such file or directory"), false);
	if (stat(dir, &info) == -1)
		return (error("cd", NULL), false);
	if (!S_ISDIR(info.st_mode))
		return (error("cd", "Not a directory"), false);
	if (access(dir, R_OK | X_OK) == -1)
		return (error("cd", "Permission denied"), false);
	return (true);
}

t_bool	check_cd(char **av, char *old_pwd)
{
	if (av[1] != NULL)
	{
		if (av[2])
			return (error("cd", "too many arguments"), false);
		if (!getcwd(old_pwd, PATH_MAX))
			return (error("cd", "getcwd failed"), false);
	}
	return (true);
}

t_bool	ft_cd(char **av)
{
	char		old_pwd[PATH_MAX];
	char		new_pwd[PATH_MAX];
	char *home;

	if (check_cd(av, old_pwd) == false)
		return (false);
	if (!av[1])
	{
		home = get_env_value(g_global.e, "HOME");
		if (!home)
			return (error("cd", "HOME not set"), false);
		ft_strcpy(new_pwd, home);
		return (1);
	}
	else
	{
		ft_strcpy(new_pwd, av[1]);
		if (!check_directory(new_pwd))
			return (false);
	}
	if (chdir(new_pwd) == -1)
		return (error("cd", new_pwd), false);
	if (!getcwd(new_pwd, PATH_MAX))
		return (error("cd", "getcwd failed"), false);
	return (change_pwd(g_global.e, old_pwd, new_pwd), 1);
}
