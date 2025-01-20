import matplotlib.pyplot as plt
import numpy as np

def arctan_precise_optimized(x, epsilon=1e-10):
    """
    Approximation optimisée de arctan(x) dans [-1, 1].
    Méthode de la Série de MacLaurin pour arctan(x)
    """
    if not -1 <= x <= 1:
        return (2*((x > 0) - 0.5))*(np.pi/2 )- arctan_precise_optimized(1/x, epsilon)
    
    term = x  # Premier terme
    result = term
    n = 1
    x2 = x * x  # Précalcul de x^2 pour éviter les puissances répétées
    
    while abs(term) > epsilon:
        term *= -x2  # Évite de recalculer x^(2n+1) en utilisant la puissance précédente
        result += term / (2*n + 1)
        n += 1
    
    return result





def reduce_angle(x):
    """
    Réduction de l'angle dans l'intervalle [-pi, pi].
    """
    x = x % (2 * np.pi)  # Réduction à [0, 2*pi]
    if x > np.pi:  # Réduction à [-pi, pi]
        x -= 2 * np.pi
    return x

def sin_optimized(x, epsilon=1e-10):
    """
    Calcul optimisé de sin(x) avec réduction des calculs intermédiaires.
    """
    x = reduce_angle(x)
    term = x  # Premier terme
    result = term
    n = 1
    x2 = x * x  # Précalcul de x^2
    while abs(term) > epsilon:
        term *= -x2 / ((2 * n) * (2 * n + 1))  # Utilisation de la puissance précédente et de la factorielle
        result += term
        n += 1
    return result

def cos_optimized(x, epsilon=1e-10):
    """
    Calcul optimisé de cos(x) avec réduction des calculs intermédiaires.
    """
    x = reduce_angle(x)
    term = 1  # Premier terme
    result = term
    n = 1
    x2 = x * x  # Précalcul de x^2
    while abs(term) > epsilon:
        term *= -x2 / ((2 * n - 1) * (2 * n))  # Utilisation de la puissance précédente et de la factorielle
        result += term
        n += 1
    return result




def sin_chebyshev(x):
    """
    Approximation rapide de sin(x) pour x dans [-pi, pi] à l'aide de polynômes.
    """
    x = reduce_angle(x)
    if abs(x) > np.pi / 4:
        # Réduction supplémentaire pour la précision
        return np.copysign(np.sqrt(1 - cos_chebyshev(x)**2), x)
    # Approximation polynomiale
    return x - (x**3) / 6 + (x**5) / 120

def cos_chebyshev(x):
    """
    Approximation rapide de cos(x) pour x dans [-pi, pi] à l'aide de polynômes.
    """
    x = reduce_angle(x)
    if abs(x) > np.pi / 4:
        # Réduction supplémentaire pour la précision
        return sin_chebyshev(np.pi / 2 - abs(x))
    # Approximation polynomiale
    return 1 - (x**2) / 2 + (x**4) / 24



def asin_optimized(x) :
    if abs(x) != 1:
        x -= int(x)
    elif x == 1:
        return np.pi / 2
    else:
        return -np.pi / 2
        
    
    term = x
    result = term
    x2 = x * x
    n = 1
    
    while abs(term) > 1e-15:
        term *= x2 * ((2*n - 1) * (2*n)) / (4*n*n)
        result += term / (2*n + 1)
        n += 1
    return result

def acos(x) :
    return np.pi/2 - asin_optimized(x)


def exp(x) : 
    
    if x < 0:
        return 1/exp(-x)
    
    term = 1
    result = term
    n = 1
    while abs(term) > 1e-12:
        term *= x/n
        result += term
        n += 1 
    return result


# Test des fonctions
# Test rapide
x = 186  # Exemple
epsilon = 1e-15  # Précision

sin_value = sin_chebyshev(x)
cos_value = cos_chebyshev(x)
sin_value2 = sin_optimized(x, epsilon)
cos_value2 = cos_optimized(x, epsilon)

print(f"sin({x}) ≈ {sin_value}")
print(f"cos({x}) ≈ {cos_value}")
print(f"sin({x}) ≈ {sin_value2}")
print(f"cos({x}) ≈ {cos_value2}")







k = 50000
limit = 100
X = np.linspace(-limit, limit, 10000)
Real = np.sin(X)

Approx1 = []
Approx2 = []

Error1 = []
Error2 = []

for i in range(len(X)):
    Approx1.append(sin_optimized(X[i], epsilon))
    Approx2.append(sin_chebyshev(X[i]))

    Error1.append(Real[i] - Approx1[i])
    Error2.append(Real[i] - Approx2[i])


# tracé des fonctions
plt.figure(1, figsize=(6,5))
plt.plot(X, Approx1, '-', color='r', label='Maclaurin')
plt.plot(X, Approx2, '-', color='g', label='Tchebichev')
plt.plot(X, Real, ':', color='b', label='Numpy')
plt.legend()
plt.xlabel('X', loc='right')
plt.ylabel('Y', loc='top')

# tracé des fonctions erreurs
plt.figure(2, figsize=(6,5))
plt.plot(X, Error1, ':', color='r', label='Maclaurin')
#plt.plot(X, Error2, '-', color='g', label='Tchebichev')
plt.legend()
plt.xlabel('X', loc='right')
plt.ylabel('Y', loc='top')



plt.show()
