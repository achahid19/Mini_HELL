/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymane <aymane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:33:36 by aymane            #+#    #+#             */
/*   Updated: 2024/07/13 18:43:03 by aymane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniHell.h"

t_env  *init_env(char** env) 
{
    if (env == NULL) {
        return NULL; // Handle empty environment
    }

    t_env* head = NULL;
    t_env* tail = NULL;  // Track the tail for efficient insertion

    int i = 0;
    while (env[i] != NULL) {
        char* key_value_pair = env[i];

        // Split key and value
        char* delimiter = strchr(key_value_pair, '=');
        if (delimiter == NULL) {
            // Handle invalid key-value pair without equal sign
            fprintf(stderr, "Warning: Invalid key-value pair in environment: %s\n", key_value_pair);
            i++;
            continue;
        }

        *delimiter = '\0';  // Terminate key string
        char* key = key_value_pair;
        char* value = delimiter + 1;

        // Create a new node for the linked list
        t_env* new_node = (t_env*)malloc(sizeof(t_env));
        if (new_node == NULL) {
            fprintf(stderr, "Error: Failed to allocate memory for linked list node\n");
            return NULL; // Handle memory allocation error
        }

        // Allocate memory for key and value (avoid dangling pointers)
        new_node->key = malloc(strlen(key) + 1);
        if (new_node->key == NULL) {
            free(new_node); // Free allocated node memory on key allocation failure
            fprintf(stderr, "Error: Failed to allocate memory for key\n");
            return NULL;
        }
        new_node->value = malloc(strlen(value) + 1);
        if (new_node->value == NULL) {
            free(new_node); // Free allocated node and key memory on value allocation failure
            free(new_node->key);
            fprintf(stderr, "Error: Failed to allocate memory for value\n");
            return NULL;
        }

        // Copy key and value to the new node
        strcpy(new_node->key, key);
        strcpy(new_node->value, value);

        // Restore delimiter (optional for further processing)
        *delimiter = '=';

        // Insert the new node at the beginning (efficient with tail)
        new_node->next = head;
        if (head == NULL) {  // First node becomes both head and tail
            tail = new_node;
        }
        head = new_node;

        i++;
    }

    return head;
}