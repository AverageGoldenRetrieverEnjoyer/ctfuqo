# Le mot de passe du joueur de tic-tac-toe

**Category:** reverse

**Difficulty:** easy / medium

**Points:** [100/200/300/400/500] ???

**Author:** Nicolas Audette

## Description

Plusieurs joueurs se sont connectés pour jouer à jeu de tic-tac-toe.

Serez-vous capable de trouver leurs mots de passe?

## Solution

### Overview
Ce défi illustre comment désassembler un programme C ou C++ pour y lire différentes informations.

Dans la vraie vie, on ne trouverait évidemment pas des mots de passe, mais peut-être d'autres informations sensibles comme une adresse web.

### Steps
Voir solution.md

### Flag
`flag{dess455emb14ge_pr0gr4mme_C}`

## Deployment
Pas de déploiement spécial à faire; Simplement distribuer l'exécutable.

## Files

- `src/` - Code source
- `solution/` - Solution
- `deploy/` - Exécutable

## Learning Objectives

What participants will learn by solving this challenge:
- Utiliser un désassembleur
- Naviguer dans du code assembleur

## Hints

### Indice 1 (Coût: 1/3 des points?)
Nous cherchons les mots de passe des utilisateurs du programme et nous n'avons aucun autre fichier que l'exécutable. Les mots de passe doivent donc s'y trouver, ce qui signifie que nous devons le désassembler ou le décompiler.

Ce programme a été écrit en C. Il serait très difficile de retrouver un code source lisible et utilisable en le décompilant. Il est préférable de seulement le désassembler

Essaie donc d'utiliser le désassembleur radare2! Pour ce faire, entre la commande suivante:
```bash
r2 -AA tic-tac-toe
```
Tu te retrouveras alors face à la ligne de commande radare2. Tu peux entrer `help` pour voir les commandes de base ou `?` pour voir une liste plus complète.

Tu peux entrer `v` pour ouvrir les "panneaux visuels" de radare2, une interface plus intuitive et facile à comprendre.

### Indice 2 (Coût: Totalité des points)
Nous cherchons un mot de passe caché dans l'exécutable, fort probablement sous forme de string. Regardons la liste des variables globales du programme (elle se trouve dans le panneau en bas à droite des panneaux visuels).

On remarque rapidement un objet nommé `obj.utilisateurs`. C'est un très bon indice. Navigue jusqu'à son adresse (en cliquant dessus ou en entrant les commandes `s 0x43a4`, puis à nouveau `v`). L'objet est maintenant affiché dans le panneau de gauche. Tu y trouveras sûrement ce que tu cherches.

## Testing Checklist

- [ ] Exécutable désassemblable via `r2 tic-tac-toe`
- [ ] Flag is obtainable following the solution steps
- [ ] Challenge description is clear and not misleading
- [ ] Solution writeup is complete and accurate
- [ ] Seulement l'exécutable est dictribué
