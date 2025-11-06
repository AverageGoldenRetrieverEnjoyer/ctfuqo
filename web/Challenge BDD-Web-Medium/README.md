# CTF Challenge : Blind SQL Injection

## Objectif
Trouvez le flag caché dans la base de données en utilisant une technique de **Blind SQL Injection Boolean-based**.

## Difficulté : MEDIUM

## Lancer le challenge

### Prérequis
- Docker Desktop installé

### Démarrage

docker-compose up --build


Puis ouvrir : [**http://localhost:5001**](http://localhost:5001)

## 🔍 À propos du challenge

Cette application recherche des utilisateurs par ID. Contrairement aux injections SQL classiques, **aucune donnée n'est affichée directement**.

Vous devez exploiter les **réponses binaires** (utilisateur trouvé ✅ / non trouvé ❌) pour extraire des informations de la base de données.

## Indices

1. **Testez des conditions logiques** : `1 AND 1=1` vs `1 AND 1=2`
2. La base de données contient une **table cachée** avec un secret
3. Utilisez `SUBSTR()` pour extraire les données **caractère par caractère**
4. Les requêtes conditionnelles renvoient TRUE ou FALSE
5. SQLite stocke les métadonnées dans une table système

## Concepts clés

- **Blind SQL Injection** : Pas d'erreur SQL visible, pas de données affichées
- **Boolean-based** : Exploitation basée sur des réponses VRAI/FAUX
- **Extraction par force brute** : Tester chaque caractère un par un

## Format du flag
`FLAG{...}`

## Outils recommandés

- **Manuel** : Testez dans le navigateur
- **SQLMap** : `sqlmap -u "http://localhost:5001/search?id=1" --dbs`
- **Script Python** : Automatisation personnalisée

## 🛑 Arrêter le challenge

docker-compose down

**Catégorie :** Web - SQL Injection  
**Temps estimé :** 30-60 minutes

Bon courage ! 🎉