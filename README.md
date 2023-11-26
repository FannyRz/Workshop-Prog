# 🐣 S1 | Prog: Workshop

----

# 💨 Rapport de la semaine - Workshop de programmation et algorithmie 💨
Du 20 au 24 novembre 2023
**Par Muracciole Lisa et Ruiz Fanny**

----

## ⭐ onlyGreen
![image](./images/logo.png) ![image](./output/01_onlyGreen.png)

## ⭐ changeRedBlue
![image](./images/logo.png) ![image](./output/02_changeRedBlue.png)

## ⭐ blackAndWhite
![image](./images/logo.png) ![image](./output/03_blackAndWhite.png)
**Explication**
Pour ce programme, le principe était de faire la moyenne des trois couleurs de chaque pixel et de réappliquer cette moyenne à chacune des trois couleurs : elles s'équilibrent et donnent du gris.

## ⭐negative
![image](./images/logo.png) ![image](./output/04_negative.png)
**Explication**
Nous avons pris le complément à 1 des trois couleurs de chaque pixel.

## ⭐ gradient
![image](./images/blackRectangle.png) ![image](./output/05_gradient.png)
**Explication**
Le principe est de parcourir l'image sur les lignes et colonnes et "d'éclaircir" chaque pixel au fur et à mesure que x augmente.

**NB :** Une autre façon de faire : utiliser la valeur précédente en incrémentant (en faisant attention à faire démarrer x à 1).

```cpp
image.pixel(x, y).r += image.pixel(x-1, 0).r + 1.f/(image.width() -1);
```

## ⭐⭐ mirror
![image](./images/logo.png) ![image](./output/06_mirror1.png)

### *mirror1*
**Explication**
Pour ce programme, il s'agit d'utiliser la fonction *reverse* (de la librairie *algorithm*), qui permet d'inverser les tableaux (le premier élément devient le dernier, et ainsi de suite).

Nous en avions entendu parler en TD et nous nous sommes dit que cela pouvait s'avérer utile, du fait qu'une image est considérée comme un tableau. C'était également une bonne occasion de se familiariser avec.

Nous n'avons pas sû comment s'en servir directement car nous ne comprenions pas ce que signifiait myvector.begin() dans la documentation (on pensait que c'était spécifique à l'exemple). Puis, on a cru que simplement utiliser reverse sur toute l'image pouvait fonctionner. Or, il fallait le faire ligne par ligne pour avoir un résultat en miroir horizontal, d'où l'ajout d'un *for* qui s'incrémente d'une longueur de ligne. 

### *mirror2*
**Explication**
On parcourt seulement la partie gauche de l'image qu'on a divisé à la moitié de la longueur de l'image. Puis, on inverse la couleur deux à deux des pixels qui sont symétriques par rapport à l'axe du milieu.

## ⭐⭐ noise
![image](./images/logo.png) ![image](./output/07_noise.png)
**Explication**
Pour ce programme, il fallait d'abord scruter l'indice : *"Remplacez quelques pixels au hasard par une couleur aléatoire"*.

Il fallait donc :
- Indiquer à la machine des coordonnées aléatoires pour un pixel, c'est-à-dire x et y aléatoires;
- Modifier sa couleur de façon aléatoire, c'est-à-dire remplacer les valeurs color.r, color.v et color.b par des valeurs aléatoires.

Ainsi, 
`int x = random_int(0, image.width())` et  `int y = random_int(0, image.height())` permettent de prendre une valeur aléatoire de x et y sans dépasser de l'image (x pas plus grand qu'une ligne, y pas plus grand qu'une colonne);

`image.pixel(x, y).r = random_float(0, 1);)` applique une valeur aléatoire au niveau de rouge (on fait de même pour le niveau de vert et de bleu).

Pour répéter cette opération un grand nombre de fois, on inclus ce bout de code dans un *for*. 

A la v1, le programme demandait le niveau de bruit (`noiseLvl`) à l'utilisateur, à l'aide d'un `std::cin`. 
Puis, pour que les tests successifs soient plus rapides, on initialise la valeur de `noiseLvl` de façon aléatoire.

## ⭐⭐ rotation90
![image](./images/logo.png) ![image](./output/08_rotation90.png)
**Explication**
On créé une image ayant pour format la longueur du logo en hauteur et inversement. Pour chaque pixel du logo, on le place sur le canvas par des calculs génériques.

**❗Problèmes❗**
Au début, le logo tournait de 90 degré dans l'autre sens, ce qui signifie que l'écriture IMAC se retrouvait à gauche de l'image et non à droit comme nous le voulions. Ceci s'explique par le fait que nous ne savions pas que l'origine du repère (0,0) est placé non pas en haut à gauche de l'image mais bien en bas à gauche de l'image, tel un repère orthonormé en maths.


## ⭐⭐ RBGSplit
![image](./images/logo.png) ![image](./output/09_RGBSplit.png)
**Explication**
On parcourt tous les pixels de notre image. Puis pour chaque pixel nous prenons la couleur rouge du pixel situé 30 pixels à sa droite, son propre vert et le bleu du pixel situé 30 pixels à sa gauche. Le choix du chiffre 30 est totalement arbitraire, nous pouvons prendre n'importe quelle valeur en pratique.   

**❗Attention❗**
Il faut faire attention au cas des 30 premières et dernières colonnes de notre image. En effet, pour éviter un débordement de l'image lors de `image.pixel(x-30,y)` et `image.pixel(x+30,y)` il faut gérer ces 2 cas d'une autre manière. 
Pour ce faire, pour le cas des 30 premières colonnes, nous avons dit que tous les pixels en dehors de l'image prennent le rouge du premier pixel de la ligne sur laquelle ils sont : `result.pixel(x,y).r = image.pixel(0,y).r;`. De même pour les 30 dernières colonnes de l'image, nous avons dit que tous les pixels en dehors de l'image prennent le bleu du dernier pixels de la ligne sur laquelle ils sont : `result.pixel(x,y).b = image.pixel(299,y).b;`.

## ⭐⭐ brightness
![image](./images/photo.jpg) 
![image](./output/10_brightnessLighten.png) ![image](./output/10_brightnessDarken.png)
**Explication**
Pour ce programme, il fallait :

- Mettre au carré les valeurs du vert, rouge et bleu s'il on voulait assombrir l'image;
- Prendre la fonction symétrique a x² par rapport à f(x) = x, soit racine carrée, et l'appliquer à chaque pixel de l'image s'il on voulait l'éclaircir.

C'est pourquoi nous avons utilisé un *for* pour changer les trois composantes de chaque pixel et un *switch* qui demande à l'utilisateur une valeur selon son choix (assombrir / éclaircir).

## ⭐⭐ disk
![image](./images/blackImagePhoto.png) ![image](./output/11_disk.png)
**Explication**
Pour cette fonction, nous avons utilisé le calcul de la distance entre deux points : $$\sqrt{(x-centerX)^2*(y-centerY)^2}$$
avec (x,y) les coordonnées d'un pixel et (centerX,centerY) les coordonnées du centre du cercle. En utilisant cette formule, il suffit de dire que les pixels ayant une distance à l'origine du cercle plus petite ou égale à cette distance sont compris dans le cercle et deviennent donc blanc.
De plus, nous avez fait en sort que la personne lançant le programme puisse choisir la grandeur du disque.   

*Remarque : on début on avait directement pris les coordonnées (250,250) au lieu de (centerX, centerY) car notre image noire dans notre cas fait 500x500. Mais pour rendre notre programme plus dynamique, nous avons décider de s'adapter à tout format d'image noire et de pouvoir prendre pour origine de notre cercle n'importe quel point pour pouvoir tracer un cercle n'importe où sur l'image.*

## ⭐ circle
![image](./images/blackImagePhoto.png) ![image](./output/12_circle.png)
**Explication**
Au niveau du raisonnement pour cette fonction, on s'est dit qu'on allait tracer 2 cercles, un ayant pour rayon 100 et un autre ayant pour rayon 100 moins l'épaisseur du cercle souhaitez et seuls les pixels appartenant seulement au plus grand cercle deviennent blanc. 
Pour ce faire, on parcourt tous les pixels de l'image et pour chaque pixel, on regarde si sa distance à l'origine est comprise entre le rayon du plus grand cercle et celui du plus petit cercle.   

*Remarque : Le choix du rayon 100 pour le plus grand cercle est totalement arbitraire.*

## ⭐⭐⭐ rosace
![image](./images/blackImagePhoto.png) ![image](./output/13_rosace.png)
**Explication**
Nous avons commencé par tracer le cercle ayant pour origine la milieu de l'image en utilisant la fonction **circle**. Ensuite, nous avons utilisé une boucle *for* allant de 1 à 6 afin de tracer à chaque itération l'un des 6 cercles autour du cercle central.   

**❗La difficulté❗**
Le point le plus difficile de cette fonction a été de savoir à l'avance les coordonnées des origines de chacun de ces 6 cercles. En regardant de plus près, on se rend compte que chaque origine correspond à un multiple de $$\frac{2\pi}{6}$$ Ainsi, l'abcisse de ces origines correspondent à `cos(i*((2*pi)/6))` et les ordonnées correspondent à `sin(i*((2*pi)/6)` avec i allant de 1 à 6. Enfin, il reste à convertir ces coordonnées polaires en coordonnées cartésiennes. Pour ce faire, on utilise ces formules :   

$$\text{Coordonnées polaires (r, θ) → Coordonnées cartésiennes }(x, y) :
$$ $$x = r × cos (θ)$$  $$y = r × sin (θ)$$
Et comme nous avons pris 100 comme rayon on obtient donc `image.width()/2 + 100*cos(i*((2*pi)/6))` et `image.height()/2 + 100*sin(i*((2*pi)/6))`.
Le `image.width()/2` et le `image.heigth()/2` permettent de se placer au milieu de l'image avant de rajouter les coordonnées cartésiennes.

## ⭐⭐ mosaic
![image](./images/logo.png) ![image](./output/14_mosaic.png)
**Explication**
Pour ce programme, nous commençons par créer un canvas de 5 fois la hauteur et 5 fois la largeur (car on veut répliquer 5*5 fois l'image, cependant on pourrait aussi mettre n'importe quel entier).

Puis, nous parcourons l'image d'entrée sur les x et y avec deux *for*. Ces deux for sont implémentés dans deux autres *for* qui vont eux parcourir les colonnes et lignes de la mosaïque (une colonne = une hauteur d'image et une ligne = une longueur d'image, il y en a donc 5 de chaque). 

Avec ces quatres *for* imbriqués, nous assignons la valeur d'un pixel de l'image d'entrée à la position x et y à un pixel du canvas d'une une ligne et une colonne donnée, à la position x et y. 
L'image se réplique alors à l'identique sur chaque ligne et chaque colonne.

**NB :** au départ, mosaicCanvasRow se nommait mosaicCanvasX, le *for* était écrit ainsi

```cpp
for (int mosaicCanvasX{0}; mosaicCanvasX < 5*image.width(); mosaicCanvasX+=image.width())
```

(et idem pour les colonnes).

Or, pour le programme *mirrorMosaic*, cela m'a fortement mis des bâton dans les roues car à chaque tour, la valeur mosaicCanvasX tombait sur une valeur paire, ce qui empêchait l'impression des miroirs horizontaux. J'ai donc utilisé le code qu'il y a actuellement pour *mirrorMosaic*, et l'ai plus tard ré-implémenté dans *mosaic* histoire d'harmoniser le tout, optimiser le programme et montrer les ressemblances entre les deux.

## ⭐⭐⭐ mirrorMosaic
![image](./images/logo.png) ![image](./output/15_mirrorMosaic.png)
**Explication**
Pour ce programme, on réutilise le même principe que *mosaic*. 
La différence réside dans un "aiguillage" qui va indiquer au programme où placer son curseur de départ avant de lire et recopier l'image d'entrée. Cela influe sur le sens de l'image recopiée dans la case du canvas.

**NB :** Nous avons essayé au début d'utiliser à nouveau *reverse*, pour inverser chaque ligne paire puis chaque colonne paire, sans succès. Cependant, nous avons vu plus tard que l'on pouvait définir un miroir horizontal, vertical et double (en appliquant plusieurs fois *reverse* ou en modifiant *mirror1*), puis l'appeler en fonction du numéro de colonne et de ligne.

## ⭐⭐⭐ glitch
![image](./images/logo.png) ![image](./output/16_glitch.png)
**Explication**
Pour ce programme, nous avons repris le principe de la fonction swap pour échanger un rectangle d’une longueur et hauteur aléatoire avec un autre rectangle de même dimensions pris aléatoirement dans l’image. 
Nous définissons donc un point de départ du rectangle en x et en y, un point de départ de l'autre rectangle, puis nous échangeons chaque pixel en parcourant les x et y avec un *for*. 

Pour que tout ce code se répète plusieurs fois, nous l'incluons dans un *for* dont le compteur *repetition* s'arrête à un nombre aléatoire *glitchLvl*, de la même manière que pour *noise*.

## ⭐⭐⭐ fractal
![image](./images/blackImagePhoto.png) ![image](./output/17_fractal.png)
**Explication**
Dès le début, on savait que les valeurs intéressantes allaient se trouver entre -2 et 2, c'est pour cela que les 2 boucles *for* sont :
```cpp
    for (float x{-(static_cast<float>(image.width())/200.f)}; x <= (static_cast<float>(image.width())/200.f); x= x+0.01f)
    {
        for (float y{-(static_cast<float>(image.height())/200.f)}; y <= (static_cast<float>(image.height())/200.f); y= y+0.01f)
        {
        }
    }
```
De cette manière là nous ne parcourons que les nombres allant de -2,5 à 2,5 (car l'image fait 500x500) en avançant de 0.1 à chaque itération.Ceci permet de gérer le problème de la transformation de x et y pour qu'ils rentrent dans cet interval.   
Ensuite, on initialise nos deux complexes z et c comme expliqué dans l'énoncé ainsi qu'un compteur. 
Arbitrairement, on a choisi d'itérer 50 fois l'opération `z = z * z + c` avec le compteur qui s'incrément de 1 à chaque itération après vérification de cette condition `std::abs(z) > 2`. Dans le cas où cette condition est vraie, la boucle *for* est interrompue.
Finalement, en fonction de la valeur du compteur, la couleur du pixel varie. Si la boucle *for* a pu faire ses 50 itérations sans problèmes alors le compteur sera à 50 et la couleur du pixel sera blanc sinon le pixel sera une nuance de gris voire sera noir.

## ⭐⭐⭐(⭐) vortex
![image](./images/logo.png) ![image](./output/18_vortex.png)
**Explication**
On parcourt tous les pixels de l'image et pour chacun on calcule sa distance avec le milieu de l'image avec la même formule utilisée dans **disk**. Puis on applique la fonction **rotated**, donné dans l'énoncé, à chaque pixel en calculant l'angle de rotation en fonction de sa distance pour pouvoir permettre d'avoir une rotation de plus en plus importante au fur et à mesure que l'on s'éloigne du centre.
Enfin, il nous reste juste à vérifier que les nouvelles coordonnées du point (x,y) que nous renvoie la fonction **rotated** ne correspond pas un point situé en dehors de l'image avant de modifier l'image *résult*.

## ⭐⭐⭐(⭐) tramage
![image](./images/photo.jpg) ![image](./output/19_tramage.png)
**Explication**
Pour ce programme, nous avons d'abord récupéré les données de la matrice de Bayer et le `const int bayer_n = 4` selon le deuxième lien fourni. 
Ensuite, selon le tutoriel, nous utilisons des if et else pour assigner 0 ou 1 à la valeur d'un pixel, selon sa luminosité + une valeur contenue dans la matrice de bayer. Les % sont utilisés pour ne pas sortir de la matrice, cela sert à avoir un peu d'aléatoire au niveau du rendu. 
Pour parcourir toute l'image, comme pour beaucoup de fonctions, nous incluons le if / else dans deux *for* qui incrémentent x et y jusqu'à la longueur (resp. hauteur) de l'image. 

## ⭐⭐⭐(⭐) normalisation
![image](./images/photo_faible_contraste.jpg) ![image](./output/20_normalisation.png)
**Explication**
Pour normalisation, nous avons tout d'abord initialisé mon pixel le plus sombre à 1 et le plus foncé à 0. Ensuite, nous parcourons l'image pour trouver le pixel le plus foncé de l'image et le plus clair de l'image ( *for* de *for* en x et y, jusque là rien de nouveau).  Nous initialisons ma valeur *deltaValue*, puis, parcours à nouveau l'image pour appliquer une formule à chaque pixel afin de recalibrer chacune des composantes.

## ⭐⭐⭐⭐ convolutions
![image](./images/logo.png) ![image](./output/21_convolutions.png)
*NB : cette fonction correspond au premier jet que nous avons fait avant de voir qu'il nous fallait une fonction plus générale afin de pouvoir faire **netteté**, **contours**, etc. mais surtout **filtres séparables**. Elle ne fonctionne donc que pour le flou avec une matrice carrée.*

**Explication**
Au début, la personne lançant la fonction peut choisir la longueur pour son kernel. *À noter, il faut que cette valeur soit un nombre impair sinon il n'y aura pas de pixel central dans la matrice ce qui pose problème pour le principe du flou.*  
Puis on commence à parcourir tous les pixels de l'image et pour chaque pixel de l'image on parcourt autant de pixels autour de lui que la taille de notre matrice en s'assurant à chaque fois que les pixels ne sont pas en dehors de l'image sinon on les ignore. 
Enfin, à l'aide des 3 variables `red_moy`, `red_moy` et `green_moy` qui correspondent à la somme de chacune des couleurs de tous les pixels de la matrice, on calcule la moyenne de chaque couleur en divisant ces variables par le nombre de pixel dans la matrice. Ces trois moyennes correspondent au couleur du pixel central.

### ⭐⭐⭐⭐ algoGeneriqueDeConvolutions
*NB : Cette fonction est une amélioration de la fonction **convolutions**. Avec cette fonction nous pouvons avoir les même résultats que convolutions.*

**Explication**
Le fonctionnement est exactement le même que **convolutions** à quelques exceptions près.   

Premièrement, nous pouvons prendre en entrée d'autres matrices que des matrices carrées du moment qu'il y est un pixel central. Pour cela il faut vérifier que la longueur fois la hauteur de la matrice est un nombre impair. C'est à cela que sert la première partie de la fonction : 
```cpp
  if((ligneKernel*colonneKernel)%2 == 1){
        float total {0.f}; 
        for(int i{0} ; i<ligneKernel ; i++){
            for(int j{0} ; j<colonneKernel ; j++){
                total = total +  kernel[i][j];
            }
        } 
  }
```   

Deuxièmement, nous avons ajoutez deux variables `indiceLigneMatrice` et`indiceColonneMatrice` nous permettant de nous déplacer dans n'importe quelle matrice.   

Pour finir, nous avons ajouter une dernière condition qui gère le cas où la somme de tous les coefficients de notre kernel vaut 0. Il faut gérer ce cas séparément car nous ne pouvons pas diviser par 0 lors du calcul des moyennes.

## ⭐⭐ filtresSeparables
![image](./images/logo.png) ![image](./output/23_filtresSeparables.png)
**Explication**
Pour cette fonction, nous avons utilisé la fonction précédente. Nous avons commencé par créer une matrice colonne de la même hauteur que celle du kernel et une matrice ligne de la même longueur que celle du kernel. Ensuite, nous avons simplement appliqué 2 fois de suite **algoGeneriqueDeConvolutions** en faisant attention à quelles images nous prenons en entrée et en sortie à chaque appel comme nous avons des références.

## ⭐⭐ differenceDeGaussienne
![image](./images/photo.jpg) ![image](./output/24_differenceDeGaussienne.png)
**Explication**
En paramètre, nous prenons un premier kernel ayant une longueur correspondant à `widthKernel1`. Ensuite, nous créons un deuxième kernel en fonction de la taille du premier kernel afin d'être sûr d'obtenir une deuxième image plus flou que la première. Nous appliquons **filtresSeparables** avec les deux kernels afin d'obtenir les 2 images flous.   

Puis, nous soustrayons l'image la plus flou à la moins flou en utilisant un facteur tau (qu'on demande à la personne lançant le programme de choisir), comme expliquer dans les vidéos, pour avoir un meilleur résultat. 
$$ (1+\tau).G_\sigma-\tau.G_k\sigma $$ Ensuite on met la photo en noir et blanc à l'aide de la fonction **blackAndWhite**.   

Et enfin, suivant si la couleur du pixel est supérieur à un certain coefficient (nous avons pris 2), on le met noir ou blanc.

## ⭐⭐⭐⭐ pixelSorting
![image](./images/logo.png) ![image](./output/25_pixelSorting.png)
**Explication**
Pour ce tri de pixels, nous tout d'abord initialisé une longueur de ligne de pixels que nous voulions trier, puis l'écart entre ces lignes, aléatoirement. Puis, nous parcourons toute mon image en nous décalant à chaque fois d'une longueur de ligne + l'écart. Si nous ne risquons pas de sortir de l'image, le programme trie la rangée, puis assigne une nouvelle valeur aléatoire à l'écart et la longueur de ligne, pour rendre le résultat encore plus aléatoire !