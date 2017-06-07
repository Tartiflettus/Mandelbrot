# Mandelbrot

Projet totalement inutile d'un point du vue extérieur, mais sacrément satisfaisant!

J'ai toujours pensé qu'implémenter des approximations mathématiques était galère quand on ne s'y connait pas trop... Mais pas forcément!

J'ai implémenté le calcul de l'ensemble de Mandelbrot uniquement à partir de 2 définitions de Wikipédia:
- celle qui définit la suite par récurrence.
- celle de la barrière du module égal à 2.

J'ai pour objectif de donner une implémentation (pas) trop lente du calcul de l'ensemble à partir de ces 2 définitions.

Le choix du langage ? C++, pourquoi ?
C'est l'occasion de commencer à s'approprier ce langage, que j'apprécie bien que je ne le maîtrise pas. :(

Caractéristiques de l'implémentation:
- calcul itératif des points dans l'ensemble. Le nombre d'itérations définit la précision.
- utilisation de nuances de couleur pour indiquer à quel moment les points sont considérés "sortis" de l'ensemble
- différents types possibles pour la précision des nombres complexes. (Choix à la compilation)
- possibilité d'utiliser le parallélisme de la machine. (choix au lancement avec "-p")

Manuel:
Ce n'est qu'une démonstration. On peut seulement affiner le résultat.

- flèche haut: itération + 1
- flèche gauche: itération + 50
- flèche droite: itération * 2

Lancement:
Lancer avec l'option "-p" pour utiliser le mode parallèle.
Lancer avec l'option "-s" sinon.

2e argument (optionnel) : nombre entier positif représentant le nombre de nuances de couleurs.
