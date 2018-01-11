\echo Use "CREATE EXTENSION coordconv" to load this file. \quit

CREATE OR REPLACE FUNCTION fk52gall(double precision, double precision)
        RETURNS double precision
        AS 'MODULE_PATHNAME', 'pgfk52gall'
        LANGUAGE C IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION fk52galb(double precision, double precision)
        RETURNS double precision
        AS 'MODULE_PATHNAME', 'pgfk52galb'
        LANGUAGE C IMMUTABLE STRICT;

CREATE OR REPLACE FUNCTION gal2fk5ra(double precision, double precision)
        RETURNS double precision
        AS 'MODULE_PATHNAME', 'pggal2fk5ra'
        LANGUAGE C IMMUTABLE STRICT;
CREATE OR REPLACE FUNCTION gal2fk5dec(double precision, double precision)
        RETURNS double precision
        AS 'MODULE_PATHNAME', 'pggal2fk5dec'
        LANGUAGE C IMMUTABLE STRICT;

