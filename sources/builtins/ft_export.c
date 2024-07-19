/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymane <aymane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:32:51 by akajjou           #+#    #+#             */
/*   Updated: 2024/07/19 18:14:44 by aymane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "../../includes/miniHell.h"

void    print_env(t_env *env)
{
    t_env *tmp;

    tmp = env;
    while (tmp)
    {
            printf("declare -x %s=%s\n", tmp->key, tmp->value);
        tmp = tmp->next;
    }
}

t_env       *ft_copy_env(t_env *env)
{
    t_env *tmp;
    t_env *new;
    t_env *head;

    tmp = env;
    new = (t_env *)malloc(sizeof(t_env));
    head = new;
    while (tmp)
    {
        new->key = ft_strdup(tmp->key);
        new->value = ft_strdup(tmp->value);
        if (tmp->next)
        {
            new->next = (t_env *)malloc(sizeof(t_env));
            new = new->next;
        }
        else
            new->next = NULL;
        tmp = tmp->next;
    }
    return (head);
}

void        ft_sort_env(t_env *env)
{
    t_env *tmp;
    t_env *tmp2;
    char *key;
    char *value;

    tmp = env;
    while (tmp)
    {
        tmp2 = tmp->next;
        while (tmp2)
        {
            if (strcmp(tmp->key, tmp2->key) > 0)
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

t_bool is_valid_identifier(char c, int i)
{
    if (i == 0)
    {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
            return true;
    } 
    else 
    {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_')
            return true;
    }
    return false;
}

t_bool ft_export_check(char **av)
{
    int d;
    int i;

    i = 1;
    while (av[i])
    {
        d = 0;
        while (av[i][d] == ' ' || av[i][d] == '\t')
            d++;
        if (!is_valid_identifier(av[i][d], 0))
        {
            printf("minishell: export: `%s': not a valid identifier\n", av[i]);
            return false;
        }
        d++;
        while (av[i][d] && av[i][d] != '=')
        {
            if (!is_valid_identifier(av[i][d], d))
            {
                printf("minishell: export: `%s': not a valid identifier\n", av[i]);
                return false;
            }
            d++;
        }
        i++;
    }
    return true;
}

t_bool is_exported(char *variable, t_env *env)
{
    t_env *tmp;

    tmp = env;
    while (tmp)
    {
        if (strcmp(variable, tmp->key) == 0)
            return true;
        tmp = tmp->next;
    }
    return false;
}

void update_exported_variable(char *variable, t_env *env)
{
    t_env *tmp;

    tmp = env;
    while (tmp)
    {
        if (strcmp(variable, tmp->key) == 0)
        {
            tmp->value = ft_strdup(ft_strchr(variable, '=') + 1);
            break;
        }
        tmp = tmp->next;
    }
}

void add_exported_variable(char *variable, t_var *data)
{
    t_env *new;
    t_env *tmp;

    new = (t_env *)malloc(sizeof(t_env));
    new->key = ft_strdup(ft_strchr(variable, '=') + 1);
    new->value = ft_strdup(ft_strchr(variable, '=') + 1);
    new->next = NULL;
    tmp = data->env;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

t_bool		ft_export(char **av, t_var *data)
{
    t_env *tmp;
    int i;
    
    tmp = ft_copy_env(data->e);
    ft_sort_env(tmp);
    i = 1;
    if (!av[1])
        print_env(tmp);
    
    else
    {
        if (ft_export_check(av) == false)
            return (false);
        while (av[i])
        {
            // Check if the variable is already exported
            if (is_exported(av[i], data->e))
            {
                // Update the value of the existing variable
                update_exported_variable(av[i], data->e);
            }
            else
            {
                // Add the new variable to the exported variables
                add_exported_variable(av[i], data);
            }
            i++;
        }
    }
    return (true);
   
} */