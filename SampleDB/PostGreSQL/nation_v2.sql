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
  country_name VARCHAR(50),
  area INTEGER NOT NULL,
  country_code2 CHAR(2) NOT NULL,
  country_code3 CHAR(3) NOT NULL,
  region_id INT NOT NULL,
  CONSTRAINT countries_country_code2_key UNIQUE (country_code2),
  CONSTRAINT countries_country_code3_key UNIQUE (country_code3),
  CONSTRAINT countries_region_id_fkey
    FOREIGN KEY (region_id) REFERENCES regions(region_id)
    ON DELETE RESTRICT
    ON UPDATE CASCADE,
  CONSTRAINT countries_area_check CHECK (area >= 1),
  CONSTRAINT countries_code2_upper_check CHECK (country_code2 = upper(country_code2))
);

CREATE TABLE languages (
  language_id SERIAL PRIMARY KEY,
  language VARCHAR(50) NOT NULL
);

CREATE INDEX countries_region_id_idx ON countries(region_id);
