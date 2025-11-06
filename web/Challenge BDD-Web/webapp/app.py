from flask import Flask, render_template, request
import sqlite3

app = Flask(__name__)

# Initialiser la base de données
def init_db():
    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    
    # Table visible publiquement
    c.execute('''CREATE TABLE IF NOT EXISTS products (
                    id INTEGER PRIMARY KEY,
                    name TEXT,
                    price REAL
                )''')
    
    # Table cachée avec le flag
    c.execute('''CREATE TABLE IF NOT EXISTS secret_admin_table (
                    id INTEGER PRIMARY KEY,
                    username TEXT,
                    flag TEXT
                )''')
    
    # Insérer des données visibles
    c.execute("DELETE FROM products")
    c.execute("INSERT INTO products VALUES (1, 'Ordinateur', 999.99)")
    c.execute("INSERT INTO products VALUES (2, 'Souris', 29.99)")
    c.execute("INSERT INTO products VALUES (3, 'Clavier', 79.99)")
    
    # Insérer le flag caché
    c.execute("DELETE FROM secret_admin_table")
    c.execute("INSERT INTO secret_admin_table VALUES (1, 'admin', 'FLAG{Mass0n_Lover}')")
    
    conn.commit()
    conn.close()

@app.route('/')
def index():
    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    c.execute("SELECT * FROM products")
    products = c.fetchall()
    conn.close()
    return render_template('index.html', products=products)

@app.route('/search', methods=['GET'])
def search():
    query = request.args.get('q', '')
    
    # Vulnérabilité intentionnelle pour le CTF
    # Les joueurs doivent découvrir la table cachée
    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    
    try:
        # Query vulnérable (ne PAS faire en production!)
        sql = f"SELECT * FROM products WHERE name LIKE '%{query}%'"
        c.execute(sql)
        results = c.fetchall()
        conn.close()
        return render_template('index.html', products=results, search_query=query)
    except Exception as e:
        conn.close()
        return f"Erreur: {str(e)}"

if __name__ == '__main__':
    init_db()
    app.run(host='0.0.0.0', port=5000, debug=True)
