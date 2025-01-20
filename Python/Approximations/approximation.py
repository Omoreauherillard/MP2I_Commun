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
    while abs(term) > 1e-25:
        term *= x/n
        result += term
        n += 1 
    return result, n

    
def sqrt_test(x):
    if x < 0:
        raise ValueError("racine negative")
    if x == 0:
        return 0, 0
    g = x/2
    it = 0

    while it < 10 and abs(g * g - x) > 1e-15:
        g = (g + x /g) / 2
        it = it+1
    return g, it


def ln_test(x) : 
    if x <= 0:
        raise ValueError(f"ln({x}) = is undefined")
    #initialisation
    y = x if x > 1 else 1

    it = 0
    while it < 20 and abs(exp(y) - x) > 1e-15:
        y = y - (exp(y) - x) / exp(y)
        it += 1
        print(f"y = {y}\t\tx = {x}")
    return y, it



k = 5000
limit = 100
X = np.linspace(0.0000001, limit, 10000)
Real = np.exp(X)


Approx1 = []
Approx2 = []

Error1 = []
Error2 = []

Iterations1 = []

for i in range(len(X)):
    res1, it1 = exp(X[i])

    Approx1.append(res1)
    Approx2.append(sin_chebyshev(X[i]))

    Error1.append(Real[i] - Approx1[i])
    Error2.append(Real[i] - Approx2[i])

    Iterations1.append(it1)


# tracé des fonctions
plt.figure(1, figsize=(15,6))


plt.subplot(1, 3, 1)
plt.plot(X, Approx1, '-', color='r', label='Approximation')
#plt.plot(X, Approx2, '-', color='g', label='Tchebichev')
plt.plot(X, Real, ':', color='b', label='Numpy')
plt.legend()
plt.xlabel('X', loc='right')
plt.ylabel('Y', loc='top')
plt.title("Graphe de la fonction")




# tracé des fonctions erreurs
plt.subplot(1, 3, 2)
plt.plot(X, Error1, ':', color='r', label='Erreur')
#plt.plot(X, Error2, '-', color='g', label='Tchebichev')
plt.legend()
plt.xlabel('X', loc='right')
plt.ylabel('Y', loc='top')
plt.title("Graphe de l'erreur")

# tracé du nombre d'itération
plt.subplot(1, 3, 3)
plt.plot(X, Iterations1, ':', color='r', label='Itérations')
#plt.plot(X, iterations2, ':', color='g', label='Tchebichev')
plt.legend()
plt.title("graphe du nb d'itération")
plt.xlabel('X', loc='right')
plt.ylabel("nb d'itérations", loc='top')


plt.show()
