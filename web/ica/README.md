# Web Challenge - ICA

**Category:** forensic  
**Difficulty:** easy  
**Points:** 100  
**Author:** CTF Team

## Description

Discover and connect to Poseidon project DB and find the secret key.

Connect to the challenge at: `http://SERVER_IP_ADDRESS:8186`

## Solution

### Overview
This challenge demonstrates a classic web enumeration to discover hidden files/directories within a web page.

### Steps
1. Navigate to the home page `http://SERVER_IP_ADDRESS:8186` and read the message. key points:
```
- Des agent speciaux comme Nikto, gobuster ou dirb pourraient vous être d'une grande aide. À condition de leur fournir toutes les extensions web que vous connaissez ::)

- deployé leur base de donnée sur un port autre que le plus evident
```
2. That means:
- there is a deployed DB but on a different port than 3306
- there is something to discover. Maybe a file, hint about that DB ? 
3. Let's use one of the recommended tools with all the extensions we know : gobuster<br/>`gobuster dir -u http://SERVER_IP_ADDRESS:8186 -w /usr/share/dirbuster/wordlists/directory-list-2.3-medium.txt -x html,php,xml,css`
4. We can see something interesting : **/crack.xml**
5. Let's take a look: `http://SERVER_IP_ADDRESS:8186/crack.xml`
6. Nice. We can see the database configuration: db name, username, password, port,...
```
<all>
<doctrine>
<class>sfDoctrineDatabase</class>
<param>
<dsn>mysql:dbname=icadb;host=SERVER_IP_ADDR;port=8187</dsn>
<profiler>false</profiler>
<username>ica</username>
<password>P@ssw0rd!</password>
<attributes>
<quote_identifier>true</quote_identifier>
</attributes>
</param>
</doctrine>
</all>
```
7. We just have to connect to the DB with the information<br/> `mysql -h SERVER_IP_ADDR -P 8187 -u ica -p`
8. We dig a little deeper and, thanks to the Projects and Secrets tables, we find the flag.
9. YAY!!!!

### Flag
`flag{5e1c3a4b-73d0-4b2f-9a11-8d4e2f6c7b88}`

## Deployment

### Local Testing
```bash
cd deploy
docker compose up -d
```

Access at: `http://localhost:8186`

### Stop the Challenge
```bash
docker compose down
```

## Files

- `src/index.html` - Home page
- `src/style1.css` - Css style of the pages
- `src/core/config/crack.xml` - Vulnerable page containing the DB information
- `deploy/docker-compose.yaml` - Docker deployment configuration
- `deploy/icaDB.sql` - Mysql script for the DB initialisation

## Learning Objectives

- Understanding how a web enumeration works
- Getting familiar with Basic exploitation / access techniques once a surface is found (exposed credentials, misconfigured DB)
