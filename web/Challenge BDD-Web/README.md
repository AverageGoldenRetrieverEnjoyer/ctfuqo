#CTF Challenge : La Boutique Secrète

## 🎯 Objectif
Trouvez le flag caché dans la base de données de cette application web !


##  Difficulté : EASY 


## Pour lancer le challenge

docker-compose down

### Prérequis
- Docker Desktop installé

### Démarrage

docker-compose up --build

Puis ouvrir : [**http://localhost:5000**](http://localhost:5000)

## 💡 Indices

1. Cette application utilise SQLite
2. Les bases de données ont souvent des **métadonnées** sur leur structure
3. Inspectez le code source HTML de la page
4. Pensez à explorer toutes les tables disponibles

## 🏁 Format du flag
`FLAG{...}`

## 🛑 Arrêter le challenge