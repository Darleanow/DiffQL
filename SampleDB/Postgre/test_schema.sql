-- Fichier de test au format pg_dump --schema-only
-- Couvre : types variés, PK, FK, UNIQUE, CHECK, INDEX, DEFAULT, auto_increment (SERIAL)

CREATE TABLE public.continents (
    continent_id integer NOT NULL,
    name character varying(255) NOT NULL
);

CREATE TABLE public.regions (
    region_id integer NOT NULL,
    name character varying(100) NOT NULL,
    continent_id integer NOT NULL
);

CREATE TABLE public.countries (
    country_id integer NOT NULL,
    name character varying(100),
    area numeric(10,2) NOT NULL,
    national_day date DEFAULT NULL,
    country_code2 character(2) NOT NULL,
    country_code3 character(3) NOT NULL,
    is_active boolean DEFAULT true,
    population bigint,
    gdp double precision,
    description text,
    region_id integer NOT NULL,
    CONSTRAINT countries_check_area CHECK ((area > (0)::numeric))
);

CREATE TABLE public.country_stats (
    stat_id integer NOT NULL,
    country_id integer NOT NULL,
    year integer NOT NULL,
    gdp_value numeric(15,2),
    recorded_at timestamp without time zone DEFAULT now()
);

-- Sequences (SERIAL columns)
CREATE SEQUENCE public.continents_continent_id_seq
    AS integer START WITH 1 INCREMENT BY 1 NO MINVALUE NO MAXVALUE CACHE 1;

CREATE SEQUENCE public.regions_region_id_seq
    AS integer START WITH 1 INCREMENT BY 1 NO MINVALUE NO MAXVALUE CACHE 1;

CREATE SEQUENCE public.countries_country_id_seq
    AS integer START WITH 1 INCREMENT BY 1 NO MINVALUE NO MAXVALUE CACHE 1;

CREATE SEQUENCE public.country_stats_stat_id_seq
    AS integer START WITH 1 INCREMENT BY 1 NO MINVALUE NO MAXVALUE CACHE 1;

-- Attach sequences → marks columns as auto_increment
ALTER TABLE ONLY public.continents
    ALTER COLUMN continent_id SET DEFAULT nextval('public.continents_continent_id_seq'::regclass);

ALTER TABLE ONLY public.regions
    ALTER COLUMN region_id SET DEFAULT nextval('public.regions_region_id_seq'::regclass);

ALTER TABLE ONLY public.countries
    ALTER COLUMN country_id SET DEFAULT nextval('public.countries_country_id_seq'::regclass);

ALTER TABLE ONLY public.country_stats
    ALTER COLUMN stat_id SET DEFAULT nextval('public.country_stats_stat_id_seq'::regclass);

-- Primary keys (via ALTER TABLE, comme pg_dump les génère)
ALTER TABLE ONLY public.continents
    ADD CONSTRAINT continents_pkey PRIMARY KEY (continent_id);

ALTER TABLE ONLY public.regions
    ADD CONSTRAINT regions_pkey PRIMARY KEY (region_id);

ALTER TABLE ONLY public.countries
    ADD CONSTRAINT countries_pkey PRIMARY KEY (country_id);

ALTER TABLE ONLY public.country_stats
    ADD CONSTRAINT country_stats_pkey PRIMARY KEY (stat_id);

-- Unique constraints
ALTER TABLE ONLY public.countries
    ADD CONSTRAINT countries_country_code2_key UNIQUE (country_code2);

ALTER TABLE ONLY public.countries
    ADD CONSTRAINT countries_country_code3_key UNIQUE (country_code3);

-- Foreign keys
ALTER TABLE ONLY public.regions
    ADD CONSTRAINT regions_continent_fk FOREIGN KEY (continent_id)
        REFERENCES public.continents(continent_id) ON DELETE CASCADE;

ALTER TABLE ONLY public.countries
    ADD CONSTRAINT countries_region_fk FOREIGN KEY (region_id)
        REFERENCES public.regions(region_id) ON DELETE RESTRICT ON UPDATE NO ACTION;

ALTER TABLE ONLY public.country_stats
    ADD CONSTRAINT country_stats_country_fk FOREIGN KEY (country_id)
        REFERENCES public.countries(country_id) ON DELETE CASCADE;

-- Indexes
CREATE INDEX idx_countries_name ON public.countries USING btree (name);
CREATE UNIQUE INDEX idx_countries_code2 ON public.countries USING btree (country_code2);
CREATE INDEX idx_stats_country_year ON public.country_stats USING btree (country_id, year);
