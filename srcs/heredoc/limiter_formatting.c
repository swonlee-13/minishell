#include "minishell.h"

char	*limiter_formatting(char *data)
{
	char	*res;

	if (data[0] == '"')
		res = ft_strtrim(data, "\"");
	else if (data[0] == '\'')
		res = ft_strtrim(data, "'");
	else
		res = ft_strdup(data);
	free(data);
	return (res);
}
