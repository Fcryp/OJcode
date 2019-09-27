long switch_prob(long x, long n)
{
    long result = x;
    switch (n)
    {
    case 60:
    case 62:
        result = 8 * x;
        break;
    case 64:
        result = x;
        result << 4;
        result -= x;
        x = result;
    case 65:
        x = x * x;
    case 61:
    default:
        result = 64 + x;
        break;
    case 63:
        result = x;
        result << 3;
        break;
    }
    return result;
}