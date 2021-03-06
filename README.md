# Projet de Recherche Opérationnel

## Algorithme de _Branch and Bound_ en C++

Ce programme permet de déterminer, en fonction de certains critères, un ordre optimal de passage des pièces
afin d'atteindre l'objectif qui est de minimiser le coût.

* Une pièce prend un certain temps pour être réalisé (_processing time_).
* Une pièce doit être prête pour une date donnée (_due date_)
* Une pièce entraîne un coût supplémentaire _c_ par unité de retard (_penalty_)

Le principe de l'algorithme repose sur un arbre, avec une racine ainsi que des noeuds enfants.
Chaque noeud est caractérisé par plusieurs attributs:

* une borne inférieur
* un vecteur représentant la solution courante 

## Comment fonctionne l'algorithme ?

* On définit notre noeud _racine_
* On définit une borne supérieur, BS = +infini
* On créé _n_ enfant directs la racine, avec _n_ = nombre de pièces
	* Pour chaque noeuds, évaluer le noeud (calculer sa _borne inférieur_)

Ensuite, relancer l'algorithme sur le noeud avec la plus petite borne inférieur
puis créé ses enfants...

# Compilation du programme
```
git clone git@github.com:rlasvenes/Projet_RO.git
```
```
cd Projet_RO/src
```
```
g++ -std=c++11 *.cpp *.hpp -o RO
```
```
./RO wt4.1.dat
```

Il y a plusieurs fichiers de données disponible, afin de vérifier le bon fonctionnement de l'algorithme.
* wt4.1.dat
* wt40.1.dat
* wt40.2.dat
* wt40.3.dat

# Screenshots

![Screenshot montrant le résultat du programme avec un certains fichier de données](https://github.com/rlasvenes/Projet_RO/blob/master/screenshots/screen1.png "Début du programme")

![À la fin du programme, avec les résultats qui s'affichent](https://github.com/rlasvenes/Projet_RO/blob/master/screenshots/screen2.png "Résultat du programme avec un petit jeu de données; 4 pièces")

![Avec un jeu de données de 40 pièces](https://github.com/rlasvenes/Projet_RO/blob/master/screenshots/screen3.png "Résultat du programme avec 40 pièces")

