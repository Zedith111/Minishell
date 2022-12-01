#include <stdio.h>
#include <stdlib.h>



int get_quote_length(char *str, char sep)
{
	int i = 1;
	while (str[i] != '\0')
	{
		if (str[i] == sep)
		{
			return (i + 1);
		}
			
		i ++;
	}
	
	return (-1);
}

char	*process_input(char *str)
{
	int		i;
	char	*process;
	int		j;

	i = 0;
	while (*str == ' ' || *str == '\t')
		str ++;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\t')
			break ;
		else if (str[i] == 39 || str[i] == 34)
		{
			i = get_quote_length(str, str[i]);
			break;
		}
		i ++;
	}
	process = malloc (i + 1);
	j = 0;
	while (j <i)
	{
		process[j] = str[j];
		j++;
	}
	process[j] = '\0';
	printf("process value is %s\n", process);
	if (str[i] == '\0')
		return (NULL);
	else
		return (str + i);
}

//process(char *original_string, int length to process)

int main()
{
	char *str = "   'a	bc'	def ghi";
	char *remain = process_input(str);

	while (remain != NULL)
	{
		remain = process_input(remain);
	}
	
}