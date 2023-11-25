# 🐣 S1 | Prog: Workshop

----

# Rapport de la semaine Workshop de programmation et algorithmie
semaine 20 novembre 2023
**Par Muracciole Lisa et Ruiz Fanny**

----

## ⭐ OnlyGreen
![image](./images/logo.png) ![image](./output/01_onlyGreen.png)

## ⭐ changeRedBlue
![image](./images/logo.png) ![image](./output/02_changeRedBlue.png)

## ⭐ blackAndWhite
![image](./images/logo.png) ![image](./output/03_blackAndWhite.png)

## ⭐negative
![image](./images/logo.png) ![image](./output/04_negative.png)

## ⭐ gradient
![image](./images/blackRectangle.png) ![image](./output/05_gradient.png)

## ⭐⭐ mirror
![image](./images/logo.png) ![image](./output/06_mirror1.png)

### *mirror1*

### *mirror2*
Pour ce programme, j'ai choisi d'utiliser la fonction *reverse* (de la librairie *algorithm*), qui permet d'inverser les tableaux (le premier élément devient le dernier, et ainsi de suite).

J'en avait entendu parler en TD et je me suis dit que cela pouvait s'avérer utile, du fait qu'une image est considérée comme un tableau. Je me suis dit que c'était également une bonne occasion de me familiariser avec.

Je n'ai pas sû m'en servir directement car je ne comprenais pas ce que signifiait myvector.begin() dans la documentation (je pensais que c'était spécifique à l'exemple). Puis, j'ai cru que simplement utiliser reverse sur toute l'image pouvait fonctionner. Or, il fallait le faire ligne par ligne pour avoir un résultat en miroir horizontal, d'où le fait que j'ai ajouté un *for* qui s'incrémente d'une longueur de ligne. 

## ⭐⭐ noise
![image](./images/logo.png) ![image](./output/07_noise.png)

Pour ce programme, j'ai d'abord scruté l'indice : *"Remplacez quelques pixels au hasard par une couleur aléatoire"*.

Il fallait donc :
- Indiquer à la machine des coordonnées aléatoires pour un pixel, c'est-à-dire x et y aléatoires;
- Modifier sa couleur de façon aléatoire, c'est-à-dire remplacer les valeurs color.r, color.v et color.b par des valeurs aléatoires.

Ainsi, 
`int x = random_int(0, image.width())` et  `int y = random_int(0, image.height())` permettent de prendre une valeur aléatoire de x et y sans dépasser de l'image (x pas plus grand qu'une ligne, y pas plus grand qu'une colonne);

`image.pixel(x, y).r = random_float(0, 1);)` applique une valeur aléatoire au niveau de rouge (on fait de même pour le niveau de vert et de bleu).

Pour répéter cette opération un grand nombre de fois, j'ai inclus ce bout de code dans un *for*. 
A la v1, le programme demandait le niveau de bruit (`noiseLvl`) à l'utilisateur, à l'aide d'un `std::cin`. 
Puis, pour que les tests successifs soient plus rapides, j'ai décidé d'initialiser la valeur de `noiseLvl` de façon aléatoire.

##rotation90
![image](./images/logo.png) ![image](./output/08_rotation90.png)
##RBGSplit
![image](./images/logo.png) ![image](./output/09_RGBSplit.png)

## ⭐⭐ brightness
![image](./images/photo.jpg) 
![image](./output/10_brightnessLighten.png) ![image](./output/10_brightnessDarken.png)

Pour ce programme, il fallait :

- Mettre au carré les valeurs du vert, rouge et bleu s'il on voulait assombrir l'image;
- Prendre la fonction symétrique a x² par rapport à f(x) = x, soit racine carrée, et l'appliquer à chaque pixel de l'image s'il on voulait l'éclaircir.

C'est pourquoi j'ai utilisé un *for* pour changer les trois composantes de chaque pixel et un *switch* qui demande à l'utilisateur une valeur selon son choix (assombrir / éclaircir).

##disk
![image](./images/blackImagePhoto.png) ![image](./output/11_disk.png)
##circle
![image](./images/blackImagePhoto.png) ![image](./output/12_circle.png)
##rosace
![image](./images/blackImagePhoto.png) ![image](./output/13_rosace.png)

## ⭐⭐ mosaic
![image](./images/logo.png) ![image](./output/14_mosaic.png)

Pour ce programme, je commence par créer un canvas de 5 fois la hauteur et 5 fois la largeur (car on veut répliquer 5*5 fois l'image, cependant on pourrait aussi mettre n'importe quel entier).

Puis, je parcours l'image d'entrée sur les x et y avec deux *for*. Ces deux for sont implémentés dans deux autres *for* qui vont eux parcourir les colonnes et lignes de la mosaïque (une colonne = une hauteur d'image et une ligne = une longueur d'image, il y en a donc 5 de chaque). 

Avec ces quatres *for* imbriqués, j'assigne la valeur d'un pixel de l'image d'entrée à la position x et y à un pixel du canvas d'une une ligne et une colonne donnée, à la position x et y. 
L'image se réplique alors à l'identique sur chaque ligne et chaque colonne.

**NB :** au départ, mosaicCanvasRow se nommait mosaicCanvasX, le *for* était écrit ainsi

```cpp
for (int mosaicCanvasX{0}; mosaicCanvasX < 5*image.width(); mosaicCanvasX+=image.width())
```

(et idem pour les colonnes).

Or, pour le programme *mirrorMosaic*, cela m'a fortement mis des bâton dans les roues car à chaque tour, la valeur mosaicCanvasX tombait sur une valeur paire, ce qui empêchait l'impression des miroirs horizontaux. J'ai donc utilisé le code qu'il y a actuellement pour *mirrorMosaic*, et l'ai plus tard ré-implémenté dans *mosaic* histoire d'harmoniser le tout, optimiser le programme et montrer les ressemblances entre les deux

## ⭐⭐⭐ mirrorMosaic
![image](./images/logo.png) ![image](./output/15_mirrorMosaic.png)

Pour ce programme, on réutilise le même principe que *mosaic*. 
La différence réside dans un "aiguillage" qui va indiquer au programme où placer son curseur de départ avant de lire et recopier l'image d'entrée. Cela influe sur le sens de l'image recopiée dans la case du canvas.

**NB :** J'ai essayé au début d'utiliser à nouveau *reverse*, pour inverser chaque ligne paire puis chaque colonne paire, sans succès. Cependant, j'ai vu plus tard que l'on pouvait définir un miroir horizontal, vertical et double (en appliquant plusieurs fois *reverse* ou en modifiant *mirror1*), puis l'appeler en fonction du numéro de colonne et de ligne.

## ⭐⭐⭐ glitch
![image](./images/logo.png) ![image](./output/16_glitch.png)
##fractal
![image](./images/blackImagePhoto.png) ![image](./output/17_fractal.png)
##vortex
![image](./images/logo.png) ![image](./output/18_vortex.png)
##tramage
![image](./images/photo.jpg) ![image](./output/19_tramage.png)
##normalisation
![image](./images/photo_faible_contraste.jpg) ![image](./output/20_normalisation.png) A CHANGER
##convolutions
![image](./images/logo.png) ![image](./output/21_convolutions.png)
###algoGeneriqueDeConvolutions
##filtresSeparables
![image](./images/logo.png) ![image](./output/23_filtresSeparables.png)
##differenceDeGaussienne
![image](./images/photo.jpg) ![image](./output/24_differenceDeGaussienne.png)