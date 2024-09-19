# -------------------------------------------------QUESTION 4 : Fusion ligne -------------------------------------
import sys
import time
import os
import matplotlib.pyplot as plt

def lectFichier(fichier):
    with open(fichier, 'r') as file:
        n = int(file.readline().strip())
        listImmeuble = list()
        for line in file:
            listImmeuble.append([int(x) for x in line.strip().split()])
    return createLign(n, list(filter(None, listImmeuble)))

# on ouvre notre
def ouvertureDossier():

    dossier = 'LigneDesToits/'  # Ou le chemin où sont tes fichiers .txt

    taillesImmeubles = []
    temps = []

    # Parcourir chaque fichier d'immeubles dans notre dossier
    for filename in os.listdir(dossier):
        if filename.endswith('.txt'):
            filepath = os.path.join(dossier, filename)
            
            # Lire la liste d'immeubles
            n , immeubles = lectFichier(filepath)
            taille = n
            
            # Mesurer le temps d'exécution de create_ligne
            debut = time.time()
            res = createLign(n, immeubles)
            fin = time.time()

            print('\n')
            print(res)
            print('\n')
            
            # Calculer le temps écoulé
            duree = fin - debut
            
            # Ajouter les résultats aux listes
            taillesImmeubles.append(taille)
            temps.append(duree)

        # Tracer le graphique
    plt.figure(figsize=(10, 6))
    plt.plot(taillesImmeubles, temps, marker='o', linestyle='-', color='b')
    plt.xlabel('Nombre d\'immeubles')
    plt.ylabel('Temps d\'exécution (secondes)')
    plt.title('Temps d\'exécution de create_ligne en fonction du nombre d\'immeubles')
    plt.grid(True)
    plt.show()



def createLign ( n, listImmeuble) :
    if n == 1:
            immeuble = listImmeuble[0]
            return [(immeuble[0], immeuble[1]), (immeuble[2], 0) ]
    else :
        size = n//2
        print("size", size)
        ligneToit1 = createLign(size, listImmeuble[:size])
        ligneToit2 = createLign(size, listImmeuble[size:])
        print("ligne1", ligneToit1, size)
        print("ligne2", ligneToit2, n - size)
        return fusionLigns(ligneToit1, ligneToit2)


def fusionLigns(list1, list2):
    print(list1, list2, "debut")
    i = 0  # curseur de la ligne de toit 1
    j = 0  # curseur de la ligne de toit 2
    resultLign = []
    h1, h2 = 0, 0  # hauteurs actuelles pour chaque ligne de toit
    current = [None, 0]

    while i < len(list1) and j < len(list2):
        x1, y1 = list1[i]
        x2, y2 = list2[j]

        # Comparer les abscisses des deux points
        if x1 < x2:
            x = x1
            h1 = y1  # mise à jour de la hauteur de la ligne 1
            i += 1

        elif x1 > x2:
            x = x2
            h2 = y2  # mise à jour de la hauteur de la ligne 2
            j += 1            

        else:
            # Les deux lignes ont la même abscisse
            x = x1
            h1 = y1
            h2 = y2
            i += 1
            j += 1

        y = max(h1, h2)
        current[0] = x
        current[1] = y
        print(y, "y", current[1])
        if current[1] != y:
            resultLign.append(current)
        

    # Ajouter les éléments restants de list1 ou list2
    while i < len(list1):
        x, h1 = list1[i]
        if h1 != current[1]:
            resultLign.append((x, h1))
            current[1] = h1
        i += 1

    while j < len(list2):
        x, h2 = list2[j]
        if h2 != current[1]:
            resultLign.append((x, h2))
            current[1] = h2
        j += 1

    print(resultLign, "fin")
    return resultLign

if __name__ == '__main__':
    print(lectFichier(sys.argv[1]))
    #ouvertureDossier()
    #createLign(8, [[10, 4, 20], [20, 4, 22], [15, 5, 23], [17, 4, 24], [24, 10, 100], [40, 8, 90], [8, 2, 120], [130, 7, 140]])
    

