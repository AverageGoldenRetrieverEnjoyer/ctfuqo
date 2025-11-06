from flask import Flask, render_template, request
import sqlite3

app = Flask(__name__)

# Initialiser la base de données
def init_db():
    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    
    # Table visible avec des utilisateurs
    c.execute('''CREATE TABLE IF NOT EXISTS users (
                    id INTEGER PRIMARY KEY,
                    username TEXT,
                    email TEXT
                )''')
    
    # Table cachée avec le flag (sans indice cette fois)
    c.execute('''CREATE TABLE IF NOT EXISTS admin_secrets (
                    id INTEGER PRIMARY KEY,
                    secret_key TEXT,
                    flag TEXT
                )''')
    
    # Insérer des utilisateurs visibles
    c.execute("DELETE FROM users")
    c.execute("INSERT INTO users VALUES (1, 'alice', 'alice@example.com')")
    c.execute("INSERT INTO users VALUES (2, 'bob', 'bob@example.com')")
    c.execute("INSERT INTO users VALUES (3, 'charlie', 'charlie@example.com')")
    
    # Insérer le flag caché
    c.execute("DELETE FROM admin_secrets")
    c.execute("INSERT INTO admin_secrets VALUES (1, 'master_key', 'FLAG{Zyw0o>D0nk}')")
    
    conn.commit()
    conn.close()

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/search', methods=['GET'])
def search():
    user_id = request.args.get('id', '')
    
    if not user_id:
        return render_template('index.html', message="Veuillez entrer un ID utilisateur")
    
    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    
    try:
        # Vulnérabilité Blind SQL Injection
        # La requête ne retourne RIEN, juste un booléen
        sql = f"SELECT * FROM users WHERE id = {user_id}"
        c.execute(sql)
        result = c.fetchone()
        conn.close()
        
        # Réponse binaire (Boolean-based)
        if result:
            return render_template('index.html', 
                                 message="✅ Utilisateur trouvé !",
                                 success=True)
        else:
            return render_template('index.html', 
                                 message="❌ Aucun utilisateur avec cet ID",
                                 success=False)
    
    except Exception as e:
        conn.close()
        # Pas d'affichage d'erreur SQL (blind)
        return render_template('index.html', 
                             message="❌ Requête invalide",
                             success=False)

if __name__ == '__main__':
    init_db()
    app.run(host='0.0.0.0', port=5000, debug=True)
