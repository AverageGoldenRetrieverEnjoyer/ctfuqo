# Solution du défi "désassembler un programme C"

## Méthode 1: Utiliser les panneaux visuels radare2 (solution officielle)

### 1. Exécuter le programme
Commençons par exécuter le programme pour avoir une idée générale de ce qu'il fait.
```bash
./tic-tac-toe
```
Il s'agit d'un jeu de tic tac toe qui exige un nom d'utilisateur et un mot de passe pour jouer.

Il n'y a pas d'autre fichiers que l'exécutable, donc les identifiants sont sûrement hardcodés dans l'exécutable.

Pour quitter l'exécutable, on peut entrer Ctrl-C.

### 2. Désassembler le programme avec radare2
```bash
r2 -AA tic-tac-toe
```
Cela nous mène à la ligne de commande de radare2.

On peut entrer ```help``` pour afficher la liste des commandes de base et ```?``` pour voir la liste complète.

### 3. Ouvrir les panneaux visuels
Pour cette méthode, nous utiliserons les panneaux visuels de radare2, accessibles en entrant ```v```.

Les "panneaux visuels" sont une interface de type TUI (Terminal User Interface), c'est-à-dire que le terminal au complet sera utilisé pour afficher de l'information de manière interactive. Il est même possible d'utiliser la souris.

Notre terminal est maintenant divisé en 3 zones: 
- L'exécutable désassemblé à gauche
- La liste des fonctions en haut à droite
- Les variables globales en bas à droite

Observons les 2 dernières pour voir si nous pouvons y trouver quelque chose de spécial.

### 4. Remarquer l'objet ```utilisateurs```
La liste des fonctions ne contient rien de vraiment intéressant.

Par contre, dans la section des variables globales, on remarque une variable nommée ```obj.utilisateurs```. C'est une très bonne piste.

### 5. Suivre la piste de l'objet ```utilisateurs```

L'adresse de l'objet ```utilisateurs``` est inscrite juste à côté de son nom, et si on clique dessus, le panneau de gauche nous amène au bon endroit dans l'exécutable désassemblé.

 On voit que l'objet commence par la string ```"Xavier"```, ce qui semble prometteur. Descendons un peu plus bas pour voir si on peut trouver son mot de passe.

On peut effectivement y trouver une string qui ressemble drôlement à un mot de passe. Continuons de descendre.

On trouve quelques autres utilisateurs ainsi que leurs mots de passe, jusqu'à ce qu'on arrive à l'utilisateur ```"Vincent"```, lequel a notre flag comme mot de passe.

---
## Méthode 2: Utiliser la ligne de commande radare2
### 1. Exécuter le programme
Commençons par exécuter le programme pour avoir une idée générale de ce qu'il fait.
```bash
./tic-tac-toe
```
Il s'agit d'un jeu de tic tac toe qui exige un nom d'utilisateur et un mot de passe pour jouer.

Il n'y a pas d'autre fichiers que l'exécutable, donc les identifiants sont sûrement hardcodés dans l'exécutable.

Pour quitter l'exécutable, on peut entrer Ctrl-C.

### 2. Désassembler le programme avec radare2
```bash
r2 -AA tic-tac-toe
```
Cela nous mène à la ligne de commande de radare2.

On peut entrer ```help``` pour afficher la liste des commandes de base et ```?``` pour voir la liste complète.

### 3. Observer la liste des fonctions
Essayons de voir s'il y aurait un indice assez évident à trouver.

```afl``` nous  donne la liste des fonctions utilisées dans ce programme ainsi que leur adresse.

### 4. Regarder la fonction ```main()```
Il n'y a pas grand-chose d'intéressant jusqu'à maintenant... Allons voir s'il y a quelque chose dans la fonction ```main()```.
```
s main
pdf
```
Ces commandes nous montrent la fonction désassemblée. Voyons voir s'il y a quelque chose d'intéressant ici...

Si on regarde le texte en rouge à droite, quelque chose devrait nous sauter aux yeux au début de la fonction: Il y est écrit ```0x4020 ; Xavier``` à 2 reprises, entrecoupées d'un ```int strcmp(const char *s1, const char *s2)```.

On devine que ce code doit vérifier le nom d'utilisateur, et probablement aussi le mot de passe. Cela a du sens, puisque c'est la première chose qu'avait fait le programme lorsque nous l'avions exécuté.

C'est une piste intéressante, regardons de plus près: On voit que ```"Xavier"``` correspond à ```obj.utilisateurs```, ce qui semble confirmer notre hypothèse.

### 5. Suivre la piste de l'objet "utilisateurs"
Nous savons que l'objet ```utilisateurs``` est situé à l'adresse ```0x4020```. Naviguons jusqu'à cette adresse.
```
s 0x4020
```
Regardons ce qui se trouve à cette adresse.
```
pd
```
On voit donc que l'objet commence bel et bien par la string ```"Xavier"``` et qu'il est effectivement référencé par ```main()```.

Nous ne voyons qu'une partie de l'objet, donc imprimons plus long pour en voir le reste. Peut-être pourrons-nous trouver son mot de passe.
```
pd 200
```

On trouve après ```"Xavier"``` une string qui ressemble drôlement à un mot de passe, puis un autre nom d'utilisateur. Essayons d'afficher l'objet au complet.
```
pd 500
```

On trouve vers la fin de l'objet l'utilisateur ```"Vincent"```, lequel a notre flag comme mot de passe.

---
## Méthode 3: Rechercher avec radare2 (Je voudrais bien la faire disparaître, celle-là...)
### 1. Exécuter le programme
Commençons par exécuter le programme pour avoir une idée générale de ce qu'il fait.
```bash
./tic-tac-toe
```
Il s'agit d'un jeu de tic tac toe qui exige un nom d'utilisateur et un mot de passe pour jouer.

Il n'y a pas d'autre fichiers que l'exécutable, donc les identifiants sont sûrement hardcodés dans l'exécutable.

Pour quitter l'exécutable, on peut entrer Ctrl-C.

### 2. Désassembler le programme avec radare2
```bash
r2 -AA tic-tac-toe
```
Cela nous mène à la ligne de commande de radare2.

On peut entrer ```help``` pour afficher la liste des commandes de base et ```?``` pour voir la liste complète.

### 3. Chercher la string ```flag```
Nous cherchons un flag de format ```flag{...}```. Voyons si on peut le trouver dans une string du programme.
```
/ flag
```
Nous avons effectivement un résultat! Par contre, le flag n'est pas affiché au complet.

### 4. Naviguer jusqu'au flag et l'afficher
Nous ne voyons pas l'intégralité du flag, mais ce n'est pas grave, puisque nous avons son adresse (```0x43a4```). Il suffit de nous y rendre et d'afficher la string qui s'y trouve.
```
s 0x43a4
pd 1
```

---
## Notes:

### La méthode 3 est trop facile.

#### 1.1 Essayer une attaque de type buffer overflow
Cela ne fonctionne pas, cette vulnérabilité n'est pas présente dans ce programme.

#### 2.1 Utiliser objdump
Cela ne révèle rien d'utile.

#### 2.2 Utiliser un autre outil de désassemblage
Il est sûrement possible de suivre les étapes suivantes avec un autre outil de désassemblage que radare2, mais je n'ai pas pu le tester.