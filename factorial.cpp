int factorial(int n)
{
  if (n <= 1)
  {
    return 1;
  }
  int result = 1;
  for (int i = 1; i <= n; i++)
  {
    result *= i;
  }
  return result;
}
