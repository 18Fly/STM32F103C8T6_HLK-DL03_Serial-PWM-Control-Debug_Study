int atoi(unsigned char *str, unsigned char length)
{
    int tmp  = 0;
    int mult = 1;
    while (length--) {
        tmp += (*(str + length) - '0') * mult;
        mult *= 10;
    }
    return tmp;
}