import requests
import time

# --- Configuration ---
# Change this to the target URL
BASE_URL = "http://127.0.0.1:5000"
# ---------------------

CHALLENGE_URL = f"{BASE_URL}/api/challenge"
SOLVE_URL = f"{BASE_URL}/api/solve"

def solve():
    """
    Runs the exploit.
    Uses a requests.Session() to keep the TCP connection open (HTTP Keep-Alive),
    which is much faster than establishing a new connection for each request.
    """
    print(f"Attempting to solve Chrono-Key at {BASE_URL}...")
    
    # Use a session for speed!
    with requests.Session() as s:
        try:
            # 1. Get the challenge
            start_req_time = time.time()
            response = s.get(CHALLENGE_URL)
            response.raise_for_status() # Raise an exception for bad status codes
            
            challenge_data = response.json()
            user_id = challenge_data.get('user_id')
            target = challenge_data.get('target')

            if not user_id or not target:
                print("Error: Did not receive valid challenge data.")
                print(f"Response: {challenge_data}")
                return

            print(f"  Got challenge! UserID: {user_id} | Target: {target[:10]}...")

            # 2. Prepare the solution
            solve_payload = {
                "user_id": user_id,
                "submission": target
            }

            # 3. Send the solution IMMEDIATELY
            solve_response = s.post(SOLVE_URL, json=solve_payload)
            end_req_time = time.time()
            
            solve_data = solve_response.json()

            # 4. Check the result
            if solve_response.status_code == 200 and 'flag' in solve_data:
                print("\n" + "="*30)
                print("  SUCCESS!")
                print(f"  FLAG: {solve_data['flag']}")
                print(f"  Total round-trip time: {(end_req_time - start_req_time):.4f} seconds")
                print("="*30 + "\n")
            else:
                print("\n" + "x"*30)
                print("  FAILURE.")
                print(f"  Server said: {solve_data.get('error', 'Unknown error')}")
                if 'elapsed' in solve_data:
                    print(f"  Server-side time: {solve_data['elapsed']}")
                print(f"  Total round-trip time: {(end_req_time - start_req_time):.4f} seconds")
                print("x"*30 + "\n")

        except requests.exceptions.ConnectionError:
            print(f"Error: Could not connect to {BASE_URL}. Is the server running?")
        except requests.exceptions.RequestException as e:
            print(f"An error occurred: {e}")

if __name__ == "__main__":
    solve()
