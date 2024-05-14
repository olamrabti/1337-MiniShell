
#include "parse.h"
#include "../minishell.h"

char *ft_getvalue(char *key, t_env *env, t_addr **addr)
{
    while (env)
    {
        if (ft_strncmp(key, env->key, ft_strlen(env->key)) == 0)
            return (gc_strdup(env->value, addr));
        env = env->next;
    }
    return (NULL);
}
int get_key(char *line, int i, int j)
{
    j = 1;
    while ((line[i + j]) && (ft_isalnum(line[i + j]) || line[i + j] == '$' || line[i + j] == '_' || line[i + j] == '?'))
    {

        j++;
        if (j == 2 && (line[i + j - 1] == '$' || line[i + j - 1] == '?'))
            break;
        else if (j == 2 && ft_isdigit(line[i + j - 1]))
            break;
        else if (j > 2 && line[i + j - 1] == '$')
        {
            j--;
            break;
        }
    }
    // printf("j = %d\n", j);
    return j;
}

char *ft_expand(char *key, t_env *env, t_addr **addr)
{
    char *value;

    if (ft_strncmp(key, "$_", ft_strlen(key)) == 0)
        return key;
    if (ft_strncmp(key, "$$", ft_strlen(key)) == 0)
        return key;
    // if (ft_strncmp(key, "$?", ft_strlen(key)) == 0)
    //     return strdup : ft_itoa(exitstatus);
    if (key && (ft_strlen(key) == 1 || ft_isdigit(key[1])))
        return (gc_strdup("", addr));
    value = ft_getvalue(key + 1, env, addr);
    // remmember to free it before give it the new strdup value
    if (!value)
        return (gc_strdup("", addr));
    return (value);
}

void expand_all(t_list **list, t_env *env, t_addr **addr)
{
    t_list *curr;
    char *tmp;
    char **splitted;
    int i;

    curr = *list;
    splitted = NULL;
    i = 0;
    while (curr)
    {
        if (curr->prv && curr->prv->type == H_DOC)
        {
            if (curr->type != LTRAL && curr->type != W_SPACE)
                curr->type = WORD;
            curr = curr->nxt;
        }
        else if (curr->type == Q_DOLLAR)
        {
            tmp = ft_expand(curr->value, env, addr);
            curr->value = tmp;
            if (*tmp)
                curr->type = WORD;
            else
                curr->type = NF_VAR;
        }
        else if (curr->type == _DOLLAR)
        {
            tmp = ft_expand(curr->value, env, addr);
            splitted = ft_split_sp(tmp, addr);
            if (splitted && (!splitted[0] || !splitted[1]))
            {
                curr->value = tmp;
                delete_node(curr->prv);
            }
            while (splitted[i])
            {
                if (splitted[i][0])
                {
                    node_add_middle(curr, create_node(splitted[i], WORD, addr));
                    curr = curr->nxt;
                    // if (!i)
                    // {
                    //     curr->value = tmp;
                    //     delete_node(curr->prv);
                    // }
                    if (splitted[i + 1] && splitted[i + 1][0])
                    {
                        node_add_middle(curr, create_node(gc_strdup(" ", addr), W_SPACE, addr));
                        curr = curr->nxt;
                    }
                }
                i++;
            }

            // this is not the final shit :

            // if (*tmp)
            //     curr->type = WORD;
            // else
            //     curr->type = NF_VAR;
        }
        if (curr)
            curr = curr->nxt;
    }
}