
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
    if (!value)
        return (gc_strdup("", addr));
    return (value);
}

void is_after_red(t_list *curr, t_addr **addr)
{
    t_list *temp;

    temp = curr;
    if (temp->prv)
        temp = temp->prv;
    while (temp && temp->type == W_SPACE)
        temp = temp->prv;
    if (temp && (temp->type == RED_IN || temp->type == RED_OUT || temp->type == RED_OUT_APPEND))
    {
        printf(" %s :ambiguous redirect\n", curr->value);
        while (temp && temp->type != PIPE && temp->type != NULL_TOKEN)
        {
            temp->type = RM;
            temp = temp->prv;
        }
        if (temp && ( temp->type == PIPE || temp->type == NULL_TOKEN ))
        {
            node_add_middle(temp, create_node(NULL, NULL_TOKEN, addr));
            temp = temp->nxt->nxt;
        }
        while (temp)
        {
            if (temp->type == PIPE)
            {
                temp->type = RM;
                break;
            }
            temp->type = RM;
            temp = temp->nxt;
        }
    }
}

void ft_split_value(t_list *curr, char *value, t_addr **addr)
{
    char **splitted;
    int i;

    i = 0;
    splitted = ft_split_sp(value, addr);
    if (splitted && !splitted[0])
    {
        is_after_red(curr, addr);
        delete_node(curr);
    }
    else
    {
        while (splitted[i])
        {
            node_add_middle(curr, create_node(splitted[i], WORD, addr));
            curr = curr->nxt;
            if (i == 0)
                delete_node(curr->prv);
            if (splitted[i + 1] && splitted[i + 1][0])
            {
                node_add_middle(curr, create_node(gc_strdup(" ", addr), W_SPACE, addr));
                curr = curr->nxt;
            }
            i++;
        }
    }
}
// it works properly so far, but maybe this function should be in syntax check !
void find_delimiter(t_list *list)
{
    t_list *temp;

    temp = list;
    if (temp->nxt)
        temp = temp->nxt;
    while (temp && temp->type == W_SPACE)
        temp = temp->nxt;
    if (temp && temp->type == Q_DOLLAR)
        temp->type = LTRAL;
    if (temp && temp->type == _DOLLAR)
        temp->type = WORD;
}

void expand_all(t_list **list, t_env *env, t_addr **addr)
{
    t_list *curr;

    curr = *list;
    while (curr)
    {
        if (curr && curr->type == H_DOC)
            find_delimiter(curr);
        else if (curr->type == Q_DOLLAR)
        {
            curr->value = ft_expand(curr->value, env, addr);
            curr->type = WORD;
        }
        else if (curr->type == _DOLLAR)
            ft_split_value(curr, ft_expand(curr->value, env, addr), addr);
        if (curr)
            curr = curr->nxt;
    }
}
