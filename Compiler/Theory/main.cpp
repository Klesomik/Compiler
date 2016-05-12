int gcd (int a, int b);

int main ()
{
    gcd (10, 0);

    return 0;
}

int gcd (int a, int b)
{
    if (a < 0) a = -a;
    if (b < 0) b = -b;

    if (a == 0) return b;
    if (b == 0) return a;

    while (a != b)
    {
        if (a > b)
            a = a - b;

        else
            b = b - a;
    }

    return a;
}
