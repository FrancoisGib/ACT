<style>
#header {
   display: flex;
   justify-content: space-between;
}
.text-center {
   text-align: center;
}
</style>

<h2 id="header"><span>ACT</span> <span>Diviser pour Régner : la ligne des toits</span><span>TP1</span></h2>

<p class="text-center"><strong>GIBIER François  |  MAZURE Antoine</strong></p>

### Q1)

#### 1.1)

- (2, 0)(2, 5)(4, 4)(4, 7)(5, 7)(5, 0)

  Cette polyligne n'est pas une ligne de toits car une seule coordonnée peut changer entre deux points. Ici on passe de (2, 5) à (4, 4) ce qui n'est pas une ligne horizontale ou verticale.

</br>

- (2, 0)(1, 4)(4, 4)(4, 7)(5, 7)(5, 0)

  Cette polyligne n'est pas une ligne de toits car pareil qu'à la une, on ne peut pas passer directement de (2, 0) à (1, 4), il faudrait un point intermédiaire (2, 4) ou (1, 0).

</br>

- (2, 0)(2, 5)(4, 5)(4, 7)(5, 7)(5, 0)

  Cette polyligne est une ligne de toits.

</br>

- (2, 0)(2, 5)(4, 5)(4, 7)(5, 7)(6, 7)(5, 0)

  Cette polyligne n'est pas une ligne de toits car on passe de (6, 7) à (5, 0) directement (cf: 1 et 2).

</br>

- (2, 0)(2, 5)(4, 5)(4, 8)(4, 7)(5, 7)(5, 0)

  Cette polyligne n'est pas une ligne de toits, le point (4, 7) ne peut pas exister car on a déjà un point en (4, 7) avec le segment (4, 5)-(4, 8), on ne peut pas monter puis redescendre sur la même abscisse.

#### 1.2)

Pour qu'une polyligne soit une ligne de toits, il faut que:

- L'ordonnée du premier et du dernier point soit 0.
- Qu'une seule des deux coordonnées ne change entre chacun des points.
- Les points doivent être triés selon les x croissants.
- Il ne doit pas y avoir 3 points consécutifs sur la même abscisse ou ordonnée.

#### 1.3)

(1, 1)(5, 13)(9, 20)(12, 27)(16, 3)(19, 0)(22, 3)(25, 0) est à la base
(1, 0)(1, 1)(5, 1)(5, 13)(9, 13)(9, 20)(12, 20)(12, 27)(16, 27)(16, 3)(19, 3)(19, 0)(22, 0)(22, 3)(25, 3)(25, 0)

Pour passer de la représentation classique à la représentation compacte il faut:

- Supprimer le premier point (il indique seulement l'abscisse du premier toit car l'ordonnée est forcément 0, or le second point l'indique aussi).
- Ensuite, on supprime tous les points modifiant l'absisse.

Il faut donc supprimer tous les points d'indice pairs.


### Q2)

On prend comme taille de la fenêtre de visualisation w (largeur) et h (hauteur).

On itère sur toute la table de dimension w * h et on doit vérifier si la case fait partie d'une ligne de toits en itérant sur les triplets.
On aurait donc w * h * n opérations pour remplir la table de booléens, soit une complexité de θ(n).

Ensuite pour parcourir "intelligemment" cette table, on doit partir de l'origine de la table (0, 0) et on longe l'axe des abscisses vers la droite jusqu'à arriver à la première case occupée. 
Ensuite, on monte jusqu'à arriver à un zéro, ce qui signifie que l'on doit aller à droite, enfin dès qu'on arrive à un zéro, on doit d'abord tenter de monter pour vérifier si il y a un toit plus haut, sinon on doit redescendre.
Et on répète ce processus jusqu'à arriver à la fin de la table, soit le point (w, 0).

Pour généraliser, on part de l'origine:
- 1) On longe l'axe des abscisses vers la droite.
- 2) Dès qu'on trouve une case occupée :
      - Si la case du dessus est occupée, on longe l'axe des ordonnées vers le haut.
      - Sinon on longe l'axe vers le bas.
- 3) Dès qu'on arrive sur une case inoccupée, on répète le processus.

À chaque changement de direction, on ajoute un point à la liste de points de la ligne de toits (si on veut la version compacte de la ligne de toits, on ajoute que les points quand on s'apprête à aller à droite).

La complexité du parcours n'est donc plus entièrement liée au nombre de bâtiments mais plutôt à la longueur totale de la ligne de toits qu'on peut appeler l (cependant le nombre total d'opérations dépendra toujours du nombre de toits car il va impliquer plus de changements de directions).

On aurait donc w * h * n + l calculs soit une complexité totale de θ(n + l).

Cette méthode est facile à implémenter mais est très coûteuse en mémoire car on doit avoir une table de w * h cases de booléens.
De plus, pour poser les bâtiments, on doit parcourir toute la table et ce en itérant sur les triplets, ce qui est loin d'être optimal.
Enfin, nous n'avons pas besoin de poser les toits sur une grille pour connaître les points de la ligne de toits, parcourir toute la ligne de toits est donc très coûteux et inutile.


### Q3)

Pour chacun des triplets:
  Si la liste est vide: on insert les deux point (x1, y1) et (x2, 0)
  Sinon:
    On parcourt le tableau des points tant que x1 > x':

    Si x1 == x' alors on garde l'ordonnée la plus haute.

    Si x1 < x' alors on ajoute le point (x1, y1) et on modifie le point suivant en (x', y1)

    Ensuite, pour les deux cas, il faut regarder si le second point en abscisse x2 passe par des toits, si c'est le cas alors il faut supprimer tous les points ayant des ordonnées inférieures à y1 par y1.

    Sinon c'est qu'on arrive à la fin et on a juste à insérer les deux points.

### Q4)

Pour fusionner deux lignes, il faut itérer sur ces lignes jusqu'à ce que l'une ou l'autre soit vide.
Dès que l'une des deux lignes est vide, on ajoute les derniers points de l'autre ligne non vide.
Il faut stocker la hauteur courante des deux lignes pour savoir si les lignes de toits se traversent.
On initialise donc ces deux hauteurs h1 et h2 à 0.

On a ensuite 3 cas:
  Si x1 < x2:
    - alors l'abscisse sera x1
    - on update h1 et on passe au prochain point de la première ligne.

  Si x1 > x2:
    - alors l'abscisse sera x2
    - on update h2 et on passe au prochain point de la deuxième ligne.

  Sinon:
    - l'abscisse est la même donc x1 ou x2
    - on update h1 et h2 et on passe au prochain point dans les deux lignes.

  On doit ensuite vérifier que le point précédent ne possède pas la même ordonnée que le nouveau point
  Si y_precedent != y_new:
    - on ajoute le nouveau point avec pour ordonnée max(h1, h2)
  Sinon: (exemple: précédent = (3, 7), nouveau = (5, 7))
    - on ajoute pas le nouveau point

### Q5)

Equation de recurrence : 

$  
T(n) = 
     \begin{cases}
       1 & \text{si } n = 1 \\
       n + 2T(\frac{n}{2}) & \text{sinon}
     \end{cases}
$

D'après le master theorem :

$\log_2 2 = 1$ on est dans le cas $d = \log_b a$, on a donc une complexité en $O(n \log n)$

On a en réalité un peu moins que $2n \log_2 n$ calculs (sans compter les opérations de comparaisons des points dans l'algorithme de fusion)

On se rapproche beaucoup plus de $2n \log n$ car l'algorithme de fusion fait disparaitre certains points des lignes, ce qui fait qu'on ne re parcourt pas certains points dans les fusions plus grandes. On aurait réellement $2n \log_2 n$ calculs dans le pire des cas (que tous les points aient une abscisse différente).

![Courbes](courbes.png)
