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


k = 1000000
limit = 10
X = np.linspace(-limit, limit, 10000)
Real = np.arctan(X)

Approx2 = []

for i in range(len(X)):
    Approx2.append(arctan_precise_optimized(X[i]))
    """Approx2[i] = min(Approx2[i], np.pi/2)
    Approx2[i] = max(Approx2[i], -np.pi/2)"""

plt.plot(X, Approx2, '-', color='g', label='gpt')
plt.plot(X, Real, ':', color='b', label='y=Arctan(x)')
plt.legend()
plt.xlabel('X', loc='right')
plt.ylabel('Y', loc='top')
plt.show()