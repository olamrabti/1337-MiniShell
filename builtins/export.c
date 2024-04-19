/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumimoun <oumimoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 03:33:11 by oumimoun          #+#    #+#             */
/*   Updated: 2024/04/19 10:17:04 by oumimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// [ ] var with no value
// [ ] var with value
// [ ] var already exist
// [ ] var with += value


// "export key=value" char*
// valid argument : key=value | key1 key2 keyn | key+=value
while (str[i])
{
    if (str[i]=='=' || (str[i] == '+' && str[i + 1] == '='))
    {
        break;
    }
    i++;
}
if (str[i] == '\0')
{
    // invalid argument
    return ;
} 
else

// invalid argument 

void export_variable(t_env **env, const char *key, const char *value)
{
    t_env *current = *env;

    // Check if the key already exists
    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            // Key already exists, update its value
            free(current->value);
            current->value = strdup(value);
            return;
        }
        current = current->next;
    }

    // Key does not exist, add a new variable
    t_env *new_env = malloc(sizeof(t_env));
    if (new_env == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_env->key = strdup(key);
    new_env->value = strdup(value);
    new_env->next = *env;
    *env = new_env;
}

// Function to remove an environment variable
void unexport_variable(t_env **env, const char *key)
{
    t_env *current = *env;
    t_env *prev = NULL;

    // Find the variable to remove
    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            // Remove the variable from the list
            if (prev == NULL)
            {
                // Variable is at the beginning of the list
                *env = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            // Free memory
            free(current->key);
            free(current->value);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Function to list all exported variables
void list_exported_variables(t_env *env)
{
    printf("Exported variables:\n");
    while (env != NULL)
    {
        printf("%s=%s\n", env->key, env->value);
        env = env->next;
    }
}

// Main function for testing
int main()
{
    t_env *env = NULL;

    // Example usage: exporting variables
    export_variable(&env, "PATH", "/usr/bin:/bin");
    export_variable(&env, "HOME", "/home/user");
    export_variable(&env, "USER", "user123");

    // List exported variables
    list_exported_variables(env);

    // Example usage: unexporting a variable
    unexport_variable(&env, "PATH");

    // List exported variables after unexporting
    printf("\nAfter unexporting PATH:\n");
    list_exported_variables(env);

    return 0;
}
