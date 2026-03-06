-- PostgreSQL DDL -- converted from MariaDB nation2 schema

DROP TABLE IF EXISTS country_languages CASCADE;
DROP TABLE IF EXISTS country_stats CASCADE;
DROP TABLE IF EXISTS cities CASCADE;
DROP TABLE IF EXISTS countries CASCADE;
DROP TABLE IF EXISTS regions CASCADE;
DROP TABLE IF EXISTS continents CASCADE;
DROP TABLE IF EXISTS languages CASCADE;
DROP TABLE IF EXISTS guests CASCADE;
DROP TABLE IF EXISTS vips CASCADE;
DROP TABLE IF EXISTS region_areas CASCADE;

-- ── continents ────────────────────────────────────────────────────────────────

CREATE TABLE continents (
    continent_id SERIAL       NOT NULL,
    name         VARCHAR(255) NOT NULL,
    area         DECIMAL(10,2) DEFAULT NULL,
    PRIMARY KEY (continent_id)
);

-- ── regions ───────────────────────────────────────────────────────────────────

CREATE TABLE regions (
    region_id    SERIAL       NOT NULL,
    name         VARCHAR(100) NOT NULL,
    continent_id INTEGER      NOT NULL,
    PRIMARY KEY (region_id),
    CONSTRAINT regions_ibfk_1
        FOREIGN KEY (continent_id) REFERENCES continents (continent_id)
);

CREATE INDEX idx_regions_continent ON regions (continent_id);

-- ── countries ─────────────────────────────────────────────────────────────────

CREATE TABLE countries (
    country_id    SERIAL      NOT NULL,
    name          VARCHAR(50) DEFAULT NULL,
    area          REAL        NOT NULL,
    capital       VARCHAR(100) DEFAULT NULL,
    national_day  DATE        DEFAULT NULL,
    country_code2 CHAR(2)     NOT NULL,
    country_code3 CHAR(3)     NOT NULL,
    region_id     INTEGER     NOT NULL,
    PRIMARY KEY (country_id),
    CONSTRAINT fk_countries_region
        FOREIGN KEY (region_id) REFERENCES regions (region_id) ON DELETE CASCADE
);

CREATE UNIQUE INDEX idx_countries_code2  ON countries (country_code2);
CREATE UNIQUE INDEX idx_countries_code3  ON countries (country_code3);
CREATE        INDEX idx_countries_region ON countries (region_id);

-- ── cities ────────────────────────────────────────────────────────────────────

CREATE TABLE cities (
    city_id    SERIAL       NOT NULL,
    name       VARCHAR(100) NOT NULL,
    country_id INTEGER      NOT NULL,
    population INTEGER      DEFAULT NULL,
    PRIMARY KEY (city_id),
    CONSTRAINT fk_city_country
        FOREIGN KEY (country_id) REFERENCES countries (country_id)
);

-- ── languages ─────────────────────────────────────────────────────────────────

CREATE TABLE languages (
    language_id SERIAL      NOT NULL,
    language    VARCHAR(50) NOT NULL,
    PRIMARY KEY (language_id)
);

-- ── country_languages ─────────────────────────────────────────────────────────

CREATE TABLE country_languages (
    id          SERIAL  NOT NULL,
    country_id  INTEGER NOT NULL,
    language_id INTEGER NOT NULL,
    official    BOOLEAN NOT NULL,
    PRIMARY KEY (id),
    CONSTRAINT country_languages_ibfk_1
        FOREIGN KEY (country_id)  REFERENCES countries  (country_id),
    CONSTRAINT country_languages_ibfk_2
        FOREIGN KEY (language_id) REFERENCES languages  (language_id)
);

CREATE UNIQUE INDEX uq_country_lang        ON country_languages (country_id, language_id);
CREATE        INDEX idx_country_lang_lang  ON country_languages (language_id);

-- ── country_stats ─────────────────────────────────────────────────────────────

CREATE TABLE country_stats (
    country_id     INTEGER       NOT NULL,
    year           INTEGER       NOT NULL,
    population     INTEGER       DEFAULT NULL,
    gdp            DECIMAL(20,2) DEFAULT NULL,
    gdp_per_capita DECIMAL(15,2) DEFAULT NULL,
    PRIMARY KEY (country_id, year),
    CONSTRAINT country_stats_ibfk_1
        FOREIGN KEY (country_id) REFERENCES countries (country_id)
);

-- ── guests ────────────────────────────────────────────────────────────────────

CREATE TABLE guests (
    guest_id INTEGER      NOT NULL,
    name     VARCHAR(100) NOT NULL,
    PRIMARY KEY (guest_id)
);

-- ── region_areas ──────────────────────────────────────────────────────────────

CREATE TABLE region_areas (
    region_name VARCHAR(100)  NOT NULL,
    region_area DECIMAL(15,2) NOT NULL,
    PRIMARY KEY (region_name)
);

-- ── vips ──────────────────────────────────────────────────────────────────────

CREATE TABLE vips (
    vip_id INTEGER      NOT NULL,
    name   VARCHAR(100) NOT NULL,
    PRIMARY KEY (vip_id)
);
