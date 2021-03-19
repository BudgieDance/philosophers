#include "philo_one.h"

size_t	ft_strlen(const char *s)
{
	size_t count;

	count = 0;
	while (s[count] != '\0')
	{
		count++;
	}
	return (count);
}

int		ft_atoi(const char *nptr)
{
	int sign;
	int number;

	sign = 1;
	number = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		number = 10 * number + (*nptr - 48);
		nptr++;
	}
	number = number * sign;
	return (number);
}

int		ft_len(int n)
{
	int length;

	length = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		length++;
		n = n * -1;
	}
	while (n)
	{
		length++;
		n = n / 10;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	char	*pointer;
	int		len;
	int		sign;

	sign = 1;
	len = ft_len(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		n = n * -1;
		sign = 0;
	}
	pointer = (char*)malloc(sizeof(char) * (len + 1));
	if (pointer == NULL)
		return (NULL);
	pointer[len--] = '\0';
	while (len >= 0)
	{
		pointer[len--] = n % 10 + 48;
		n = n / 10;
	}
	if (sign == 0)
		pointer[0] = '-';
	return (pointer);
}

void	ft_putstr(char *s)
{
	if (!s)
		return ;
	write(1, s, ft_strlen(s));
}
