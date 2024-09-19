## TP1: Diviser pour Régner : La ligne des toits

### GIBIER François | MAZURE Antoine

### Q1)

Configuration = (m, n, i, j)
Avec :
m la largeur de la tablette
n la hauteur de la tablette
i l'abscisse du carré de la mort
j l'ordonnée du carré de la mort

### Q2)

```
    -3
+1  +2  +1
  -1
     0
```

### Q3)

On itère sur toutes les coupes possibles c'est à dire de (1 à x-1) + (1 à y - 1) avec x la largeur et y la hauteur de la tablette, dépendant du sens de coupe du joueur.

Et donc, pour tout k allant de 1 à (x - 1) ou (y - 1), la nouvelle tablette sera soit (m, n - k) ou (m - k, n), le carré de la mort serait (i - k, j) ou (i, j - k).

On aurait x + y configurations différentes.

### Q4)

$ 1 - \max(succ) $ si $ \forall x \in succ, x >= 0 $
sinon $ 1 - \max(succ) $
