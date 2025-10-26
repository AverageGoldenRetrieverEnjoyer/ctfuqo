Prog Challenge: Chrono-Key

Category: Prog / Pwn
Difficulty: Easy / Medium

Description

Our new "Chrono-Key" authentication system is state-of-the-art! It's so fast, no human could possibly keep up. We guarantee it's unbreakable by conventional means.

Prove us wrong.

Service: http://<your-challenge-ip>:5000

Objective

Write a script to interact with the service API, get a challenge, and solve it within the extremely short time limit to retrieve the flag.

API Endpoints:

GET /api/challenge

This endpoint starts the challenge.

Response:

{
  "target": "a1b2c3d4e5f6...",
  "user_id": "abc-123-xyz-789..."
}


You will receive a unique user_id and a target string. The clock starts now.

POST /api/solve

This endpoint is where you submit your solution. You must send a JSON payload.

Request Body:

{
  "user_id": "<your-user_id-from-challenge>",
  "submission": "<the-target-string-from-challenge>"
}


Success Response (if fast enough!):

{
  "flag": "CTF{y0u_b3at_th3_cl0ck_scR1pt_k1dd13}"
}


Failure Responses:

{"error": "You were too slow!"}


{"error": "Incorrect submission."}


{"error": "Invalid or expired user_id."}


Hint: You might need to use a persistent HTTP session to be fast enough.

Flag Format: CTF{...}