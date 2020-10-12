#include "get_next_line.h"

int     ft_strlen(char *str)
{
    int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char    *ft_strjoin(char *remains, char *buffer)
{
    char *array;
    unsigned int size;
    int i;
    int j;

    if (!remains && !buffer)
        return (NULL);
    size = ft_strlen(remains) + ft_strlen(buffer);
    if (!(array = (char *)malloc(sizeof(char) * (size + 1))))
        return (NULL);
    i = 0;
    j = 0;
    if (remains != NULL)
    {
        while (remains[i] != '\0') 
        {
            array[j] = remains[i];
            i++;
            j++;
        }
        i = 0;
    }
    while (buffer[i] != '\0')
    {
        array[j] = buffer[i];
        i++;
        j++;
    }
    array[size] = '\0';
    free((void *)remains);
    return (array);
}

char    *push_line(char *remains)
{
    int i;
    char *array;

    i = 0;
    while (remains[i] && remains[i] != '\n')
        i++;
    if (!(array = (char *)malloc(sizeof(char) * (i + 1))))
        return (NULL);
    i = 0;
    while (remains[i] != '\0' && remains[i] != '\n')
    {
        array[i] = remains[i];
        i++;
    }
    array[i] = '\0';
    return (array);
}

char    *cut_next_line(char *remains)
{
    int i;
    int j;
    char *array;

    i = 0;
    j = 0;
    while (remains[i] && remains[i] != '\n')
        i++;
    if (!remains[i])
    {
        free(remains);
        return (NULL);
    }
    if (!(array = (char *)malloc(sizeof(char) * (ft_strlen(remains) - i + 1))))
        return (NULL);
    i++;
    while (remains[i])
    {
        array[j] = remains[i];
        i++;
        j++;
    }
    array[j] = '\0';
    free(remains);
    return (array);
}

int     get_next_line(char **line)
{
    char buffer[BUFFER_SIZE + 1];
    static char *remains;
    int count;
    int fd;
    fd = 0;
	
	count = 1;
	int i;

    if (!line)
        return (-1);
    while (count != 0)
    {
        i = 0;
		if ((count = read(fd, buffer, BUFFER_SIZE)) == (-1))
            return (-1);
        buffer[count] = '\0';
        remains = ft_strjoin(remains, buffer);
		while (remains[i] != '\n')
		{
			break;
			i++;
		}
    }
    *line = push_line(remains);
    remains = cut_next_line(remains);

	if(remains != NULL)
		return (1);
    return((count == 0) ? 0 : -1);
}
/*
int main(void)
{
	int		r;
	char	*line;
	int fd = open("test.txt", O_RDONLY);
	line = NULL;
	while ((r = get_next_line(fd, &line)) > 0)
	{
		printf("(%s)\n", line);
		printf("retour = (%d)\n",r);
		free(line);
	}
	printf("(%s)", line);
	printf("retour = (%d)\n",r);
	free(line);
}
*/