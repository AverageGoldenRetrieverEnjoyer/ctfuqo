CREATE DATABASE IF NOT EXISTS icadb;
USE icadb;

CREATE TABLE IF NOT EXISTS Projects (
  id INT AUTO_INCREMENT PRIMARY KEY,
  name VARCHAR(255),
  affected_ppl INT,
  clearance TEXT
);

INSERT INTO Projects (name, affected_ppl, clearance) VALUES
('oragon', 53, 'reliability'),
('athena', 5, 'secret'),
('thor', 10, 'reliability'),
('zeus', 5, 'top secret'),
('hercule', 35, 'secret'),
('poseidon', 15, 'top secret'),
('shiba', 1, 'top secret'),
('oeil de faucon', 70, 'secret'),
('hades', 3, 'top secret'),
('apolon', 20, 'top secret'),
('medusa', 50, 'reliability'),
('hermes', 15, 'secret');

CREATE TABLE IF NOT EXISTS Departments (
  id INT AUTO_INCREMENT PRIMARY KEY,
  name VARCHAR(255),
  location VARCHAR(255)
);

INSERT INTO Departments (name, location) VALUES
('fraise', 'can'),
('banane', 'usa'),
('kiwi', 'italie'),
('ananas', 'france'),
('orange', 'mexique'),
('coco', 'civ');

CREATE TABLE IF NOT EXISTS Tasks (
  id INT AUTO_INCREMENT PRIMARY KEY,
  title VARCHAR(255),
  content TEXT
);

CREATE TABLE IF NOT EXISTS Users (
  id INT AUTO_INCREMENT PRIMARY KEY,
  title VARCHAR(255),
  content TEXT
);

CREATE TABLE IF NOT EXISTS Secrets (
  id INT AUTO_INCREMENT PRIMARY KEY,
  flag TEXT,
  project_id INT,
  CONSTRAINT fk_secret_project FOREIGN KEY (project_id) REFERENCES Projects(id) ON DELETE SET NULL ON UPDATE CASCADE
);

INSERT INTO Secrets (flag, project_id) VALUES
('flag{110c952c-8503-4bce-906f-21f30e1df2b4}', 7),
('flag{847590cc-4a26-4b72-9635-8fd84ada8c2a}', 2),
('flag{a3f1d9e2-2b6c-4f1a-8c3d-5b2e7f9a0c11}', 5),
('flag{7b6e2c10-9f34-4a77-9bde-3c8f1a2b4d55}', 1),
('flag{d02a5b8f-0c22-4d3e-8f12-6a7b9c0d1e2f}', 8),
('flag{5e1c3a4b-73d0-4b2f-9a11-8d4e2f6c7b88}', 6),
('flag{3c9b7f01-aa12-4e6d-8b33-2f4c5a6d7e90}', 3),
('flag{f8a0b1c2-4d55-4c33-9eaa-11bb22cc33dd}', 4);
