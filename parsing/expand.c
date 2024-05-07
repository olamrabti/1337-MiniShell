
#include "parse.h"
#include "../minishell.h"

char *ft_getvalue(char *key, t_env *env)
{
    while (env)
    {
        if (ft_strncmp(key, env->key, ft_strlen(env->key)) == 0)
            return (ft_strdup(env->value));
        env = env->next;
    }
    return (NULL);
}
int get_key(char *line, int i, int j)
{
    j = 1;
    while ((line[i + j]) && (ft_isalnum(line[i + j])\
     || line[i + j] == '$' || line[i + j] == '_' || line[i + j] == '?'))
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
    return j;
}

char *ft_expand(char *key, t_env *env)
{
    char *value;

    if (ft_strncmp(key, "$_", ft_strlen(key)) == 0)
        return key;
    if (ft_strncmp(key, "$$", ft_strlen(key)) == 0)
        return key;
    // if (ft_strncmp(key, "$?", ft_strlen(key)) == 0)
    //     return strdup : ft_itoa(exitstatus);
    if (key && (ft_strlen(key) == 1 || ft_isdigit(key[1])))
        return (ft_strdup(""));
    value = ft_getvalue(key + 1, env);
    // remmember to free it before give it the new strdup value
    if (!value)
        return (ft_strdup(""));
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
            if (curr->type != _LTRAL && curr->type != W_SPACE)
                curr->type = _WORD;
            curr = curr->nxt;
        }
        else if (curr->type == Q_DOLLAR)
        {
            tmp = ft_expand(curr->value, env);
            curr->value = tmp;
            if (*tmp)
                curr->type = _WORD;
            else
                curr->type = NF_VAR;
        }
        else if (curr->type == _DOLLAR)
        {
            tmp = ft_expand(curr->value, env);
            splitted = ft_split_sp(tmp);
            while(splitted[i])
            {
                if(splitted[i][0])
                {
                    node_add_middle(curr, create_node(splitted[i], _WORD, addr));
                    curr = curr->nxt;
                    if (!i)
                        delete_node(curr->prv);
                    if (splitted[i + 1] && splitted[i + 1][0])
                    {
                        node_add_middle(curr, create_node(ft_strdup(" "), W_SPACE, addr));
                        curr = curr->nxt;
                    }
                }
                i++;
            }
            // curr->value = tmp;
            if (*tmp)
                curr->type = _WORD;
            else
                curr->type = NF_VAR;
        }
        if(curr)
            curr = curr->nxt;
    }
}