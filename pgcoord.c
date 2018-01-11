#include "postgres.h"
#include "fmgr.h"

/* For PostgreSQL versions >= 8.2 */
#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif
/* End of Postgres stuff */


extern void fk52gal (double *, double *);
extern void gal2fk5 (double *, double *);

/* Postgres functions */
Datum pgfk52gall(PG_FUNCTION_ARGS);
Datum pgfk52galb(PG_FUNCTION_ARGS);
Datum pggal2fk5ra(PG_FUNCTION_ARGS);
Datum pggal2fk5dec(PG_FUNCTION_ARGS);

PG_FUNCTION_INFO_V1(pgfk52gall);
Datum pgfk52gall(PG_FUNCTION_ARGS)
{
	float8 ra = PG_GETARG_FLOAT8(0);
	float8 dec = PG_GETARG_FLOAT8(1);
	
	fk52gal(&ra,&dec);
	PG_RETURN_FLOAT8(ra);
}
PG_FUNCTION_INFO_V1(pgfk52galb);
Datum pgfk52galb(PG_FUNCTION_ARGS)
{
	float8 ra = PG_GETARG_FLOAT8(0);
	float8 dec = PG_GETARG_FLOAT8(1);
	
	fk52gal(&ra,&dec);
	PG_RETURN_FLOAT8(dec);
}	


Datum pggal2fk5ra(PG_FUNCTION_ARGS);
Datum pggal2fk5dec(PG_FUNCTION_ARGS);

PG_FUNCTION_INFO_V1(pggal2fk5ra);
Datum pggal2fk5ra(PG_FUNCTION_ARGS)
{
	float8 ra = PG_GETARG_FLOAT8(0);
	float8 dec = PG_GETARG_FLOAT8(1);
	
	gal2fk5(&ra,&dec);
	PG_RETURN_FLOAT8(ra);
}
PG_FUNCTION_INFO_V1(pggal2fk5dec);
Datum pggal2fk5dec(PG_FUNCTION_ARGS)
{
	float8 ra = PG_GETARG_FLOAT8(0);
	float8 dec = PG_GETARG_FLOAT8(1);
	
	gal2fk5(&ra,&dec);
	PG_RETURN_FLOAT8(dec);
}	