import os
import time
import uuid
import secrets
from flask import Flask, jsonify, request, render_template_string

app = Flask(__name__)

# --- Challenge Configuration ---
# The flag to be given upon success
FLAG = os.environ.get("FLAG", "CTF{y0u_b3at_th3_cl0ck_scR1pt_k1dd13}")

# The time window (in seconds) allowed to solve the challenge
TIME_LIMIT = 0.5  # 500 milliseconds

# This will store active challenges in memory
# Format: { "user_id": {"target": "...", "start_time": ...} }
active_challenges = {}

# --- Simple Frontend ---
@app.route('/')
def index():
    """Serves a simple HTML page explaining the challenge."""
    html = """
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Chrono-Key Challenge</title>
        <link href="https://cdn.tailwindcss.com" rel="stylesheet">
        <style>
            body { font-family: 'Inter', sans-serif; }
        </style>
    </head>
    <body class="bg-gray-900 text-gray-200 min-h-screen flex items-center justify-center">
        <div class="bg-gray-800 p-8 rounded-lg shadow-2xl max-w-2xl w-full text-center">
            <h1 class="text-4xl font-bold text-cyan-400 mb-4">Chrono-Key Challenge</h1>
            <p class="text-lg mb-6">Our system is too fast for you. Prove us wrong.</p>
            <div class="bg-gray-700 p-6 rounded-lg text-left font-mono">
                <p class="text-gray-400 mb-2">// 1. Get your challenge:</p>
                <p class="text-green-400 mb-4">GET /api/challenge</p>
                <p class="text-gray-400 mb-2">// 2. Solve it... if you can.</p>
                <p class="text-green-400 mb-4">POST /api/solve</p>
                <p class="text-gray-400">// Good luck. The clock is ticking.</p>
            </div>
        </div>
    </body>
    </html>
    """
    return render_template_string(html)

# --- API Endpoints ---
@app.route('/api/challenge', methods=['GET'])
def get_challenge():
    """
    Generates a new challenge (target string and user ID)
    and records the start time.
    """
    user_id = str(uuid.uuid4())
    target_string = secrets.token_hex(16)
    start_time = time.time()

    # Store the challenge
    active_challenges[user_id] = {
        "target": target_string,
        "start_time": start_time
    }

    return jsonify({
        "user_id": user_id,
        "target": target_string
    }), 200

@app.route('/api/solve', methods=['POST'])
def solve_challenge():
    """
    Validates a challenge submission.
    Checks time, user ID, and target string.
    """
    data = request.get_json()
    if not data:
        return jsonify({"error": "Invalid JSON payload."}), 400

    user_id = data.get('user_id')
    submission = data.get('submission')

    if not user_id or not submission:
        return jsonify({"error": "Missing user_id or submission."}), 400

    # 1. Check if challenge exists
    challenge = active_challenges.get(user_id)
    if not challenge:
        return jsonify({"error": "Invalid or expired user_id."}), 400

    # 2. Check the time
    elapsed_time = time.time() - challenge['start_time']
    if elapsed_time > TIME_LIMIT:
        # Clean up the expired challenge
        del active_challenges[user_id]
        return jsonify({"error": "You were too slow!", "elapsed": f"{elapsed_time:.4f}s"}), 400

    # 3. Check the submission
    if submission != challenge['target']:
        # Clean up, they failed
        del active_challenges[user_id]
        return jsonify({"error": "Incorrect submission."}), 400

    # 4. Success!
    # Clean up the solved challenge
    del active_challenges[user_id]
    return jsonify({"flag": FLAG}), 200

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
