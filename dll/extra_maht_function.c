#include "../MY_LIB/extra_math_function.h"

#if defined(_WIN32) || defined(__CYGWIN__)
	#define DLL_API __declspec(dllexport)
#elif defined(__GNUC__) || defined(__clang__)
	#define DLL_API __attribute__((visibility("default")))
#else
	#define DLL_API
#endif

DLL_API bool dll_is_integer(double x)
{
	return is_integer(x);
}

DLL_API bool dll_is_zero(const double x)
{
	return is_zero(x);
}

DLL_API double dll_logarithm(const double base, const double expression)
{
	return logarithm(base, expression);
}

DLL_API double dll_permutations(int n, int r)
{
	return permutations(n, r);
}

DLL_API double dll_combinations(int n, int r)
{
	return combinations(n, r);
}

DLL_API double dll_coth(double x)
{
	return coth(x);
}

DLL_API double dll_arccoth(double x)
{
	return arccoth(x);
}

DLL_API double dll_arcsec(double x)
{
	return arcsec(x);
}

DLL_API double dll_arcsech(double x)
{
	return arcsech(x);
}

DLL_API double dll_csch(double x)
{
	return csch(x);
}

DLL_API double dll_arccsc(double x)
{
	return arccsc(x);
}

DLL_API double dll_arccsch(double x)
{
	return arccsch(x);
}

DLL_API double dll_lambertw_real(double z)
{
	return lambertw_real(z);
}

DLL_API int dll_gcd(int a, int b)
{
	return gcd(a, b);
}

DLL_API int dll_lcm(int a, int b)
{
	return lcm(a, b);
}

DLL_API int dll_hcf(int a, int b)
{
	return hcf(a, b);
}

DLL_API double dll_gamma_function(double n)
{
	return gamma_function(n);
}

DLL_API unsigned long long dll_factorial(int n)
{
	return factorial(n);
}

DLL_API int dll_estimate_upper_bound(int n)
{
	return estimate_upper_bound(n);
}

DLL_API int dll_generate_nth_prime(int n)
{
	return generate_nth_prime(n);
}

DLL_API int dll_fibonacci(int n)
{
	return fibonacci(n);
}

DLL_API bool dll_prime_checker(const int number)
{
	return prime_checker(number);
}

DLL_API double dll_sigmoid(const double x)
{
	return sigmoid(x);
}

int main(int argc, char const *argv[])
{
    return 0;
}