# ACT 
## TP3: Les propriétés NP, les réductions polynomiales

### GIBIER François  |  MAZURE Antoine

n - log n
xi - n * log c
c - log c
k - log k

Certificat: Affectation de chaque objet à un sac.

Toutes les instances où il existe un xi > c = Non

Tableau d'entiers de taille n avec des entiers de taille moyenne de log v bits. $O(n log v)$ car chaque case de "aff" contient un numéro de sac.

Le certification est donc bien borné polynomialement par la taille des données du problème.

Pour chaque objet o:
    Si T[aff[o]] ou si X[o] > c:
        return False
    sinon:
        T[aff[o]] = True

Pour chaque sac s:
    Si capaciteUtiliseeSac[s] > c:
        return False
return True

Complexité en $𝜃(n + k)$

Q2.1)

Les certificats ont la même chance d'apparaître, cependant, les nombres sont pseudo aléatoires, mais à un instant t, on a la même chance d'obtenir n'importe quelle permutation d'objets.

Q3.1) $k^n$ certificats (on a k choix possibles pour n objects donc $k*k*k*k*k... n fois$)

Q3.2) On peut utiliser l'ordre lexicographique pour énumérer les certificats; Pour 2 objets et 3 sacs, le premier certificat est [0,0], ensuite [0,1], [0,2], [1,0], [1,1], [1,2], [2,0] [2,1], [2,2].

Q3.3) On teste tous les certificats précédents, dans l'ordre lexicographique inversé, jusqu'à trouver un certificat valide, ou arriver au certificat le plus petit.


### 3
3.1)
Si BinPackOpt était P, il existerait un algorithme polynomial pour résoudre BinPackOpt, et donc il existerait aussi un algorithme non-déterministe au plus aussi difficile que BinPackOpt, BinPack par exemple. Donc BinPack serait au plus P.

Pour un algorithme de décision, son algorithme (s'il existe) d'optimisation est au moins aussi difficile.
BinPackOpt est donc au moins aussi difficile que BinPack.
/** Comme BinPack est NP, cela veut dire que BinPackOpt est au moins NP. */

3.2)
On a maximum n (nombre d'objets) sacs, donc on peut seulement itérer de 1 à n pour trouver si une solution est possible.
On serait donc en $O(n*A)$ avec A un algorithme polynomial.

3.3)
