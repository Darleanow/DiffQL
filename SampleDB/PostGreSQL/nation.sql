DROP TABLE IF EXISTS country_languages;
DROP TABLE IF EXISTS countries;
DROP TABLE IF EXISTS languages;
DROP TABLE IF EXISTS regions;
DROP TABLE IF EXISTS continents;

CREATE TABLE continents (
  continent_id SERIAL PRIMARY KEY,
  name VARCHAR(255) NOT NULL
);

CREATE TABLE regions (
  region_id SERIAL PRIMARY KEY,
  name VARCHAR(100) NOT NULL,
  continent_id INT NOT NULL,
  CONSTRAINT regions_continent_id_fkey
    FOREIGN KEY (continent_id) REFERENCES continents(continent_id)
    ON DELETE RESTRICT
    ON UPDATE CASCADE
);

CREATE TABLE countries (
  country_id SERIAL PRIMARY KEY,
  name VARCHAR(50),
  area NUMERIC(10,2) NOT NULL,
  national_day DATE,
  country_code2 CHAR(2) NOT NULL,
  country_code3 CHAR(3) NOT NULL,
  region_id INT NOT NULL,
  CONSTRAINT countries_country_code2_key UNIQUE (country_code2),
  CONSTRAINT countries_country_code3_key UNIQUE (country_code3),
  CONSTRAINT countries_region_id_fkey
    FOREIGN KEY (region_id) REFERENCES regions(region_id)
    ON DELETE RESTRICT
    ON UPDATE CASCADE
);

CREATE TABLE languages (
  language_id SERIAL PRIMARY KEY,
  language VARCHAR(50) NOT NULL
);

CREATE TABLE country_languages (
  country_id INT NOT NULL,
  language_id INT NOT NULL,
  official BOOLEAN NOT NULL,
  CONSTRAINT country_languages_pkey PRIMARY KEY (country_id, language_id),
  CONSTRAINT country_languages_country_id_fkey
    FOREIGN KEY (country_id) REFERENCES countries(country_id)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT country_languages_language_id_fkey
    FOREIGN KEY (language_id) REFERENCES languages(language_id)
    ON DELETE RESTRICT
    ON UPDATE CASCADE
);

CREATE INDEX countries_region_id_idx ON countries(region_id);
CREATE INDEX country_languages_language_id_idx ON country_languages(language_id);

INSERT INTO continents (name) VALUES
('North America'), ('Europe'), ('Asia');

INSERT INTO regions (name, continent_id) VALUES
('Caribbean', 1),
('Western Europe', 2),
('Eastern Asia', 3);

INSERT INTO countries (name, area, national_day, country_code2, country_code3, region_id) VALUES
('Canada', 9970610.00, '1867-07-01', 'CA', 'CAN', 1),
('France', 551500.00, '1789-07-14', 'FR', 'FRA', 2),
('Japan', 377829.00, NULL, 'JP', 'JPN', 3);

INSERT INTO languages (language) VALUES
('English'), ('French'), ('Japanese');

INSERT INTO country_languages (country_id, language_id, official) VALUES
(1, 1, true),
(2, 2, true),
(3, 3, true);
