/*** File wcscon.c
 *** March 30, 2010
 *** Doug Mink, Harvard-Smithsonian Center for Astrophysics
 *** Some subroutines are based on Starlink subroutines by Patrick Wallace
 *** Copyright (C) 1995-2010
 *** Smithsonian Astrophysical Observatory, Cambridge, MA, USA

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.
    
    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Correspondence concerning WCSTools should be addressed as follows:
           Internet email: dmink@cfa.harvard.edu
           Postal address: Doug Mink
                           Smithsonian Astrophysical Observatory
                           60 Garden St.
                           Cambridge, MA 02138 USA
 */
 
#include <math.h>
#include <ctype.h>
#include <string.h>


/*  l2,b2 system of galactic coordinates
    p = 192.25       ra of galactic north pole (mean b1950.0)
    q =  62.6        inclination of galactic to mean b1950.0 equator
    r =  33          longitude of ascending node
    p,q,r are degrees */

/*  Equatorial to galactic rotation matrix
    The eulerian angles are p, q, 90-r
	+cp.cq.sr-sp.cr     +sp.cq.sr+cp.cr     -sq.sr
	-cp.cq.cr-sp.sr     -sp.cq.cr+cp.sr     +sq.cr
	+cp.sq              +sp.sq              +cq		*/

static
double jgal[3][3] =
	{{-0.054875539726,-0.873437108010,-0.483834985808},
	{0.494109453312,-0.444829589425, 0.746982251810},
	{-0.867666135858,-0.198076386122, 0.455983795705}};

#define degrad(x)	((x)*M_PI/180.)
#define raddeg(x)	((x)*180./M_PI)




static void s2v3 (double rra, double rdec, double r, double pos[3]);
static void v2s3 ( double pos[3], double *rra, double *rdec, double *r);
void fk52gal (double *dtheta, double *dphi);
void gal2fk5 (double *dtheta, double *dphi);


/* Convert right ascension, declination, and distance to
   geocentric equatorial rectangular coordinates */

static void
s2v3 (
  double rra,	/* Right ascension in radians */
  double rdec,	/* Declination in radians */
  double r,	/* Distance to object in same units as pos */
  double pos[3]	/* x,y,z geocentric equatorial position of object (returned) */
)
{
    pos[0] = r * cos (rra) * cos (rdec);
    pos[1] = r * sin (rra) * cos (rdec);
    pos[2] = r * sin (rdec);

    return;
}


/* Convert geocentric equatorial rectangular coordinates to
   right ascension, declination, and distance */

static void
v2s3 (
  double pos[3],	/* x,y,z geocentric equatorial position of object */
  double *rra,	/* Right ascension in radians (returned) */
  double *rdec,	/* Declination in radians (returned) */
  double *r	/* Distance to object in same units as pos (returned) */
  )
{
    double x,y,z,rxy,rxy2,z2;

    x = pos[0];
    y = pos[1];
    z = pos[2];

    *rra = atan2 (y, x);

    /* Keep RA within 0 to 2pi range */
    if (*rra < 0.0)
	*rra = *rra + (2.0 * M_PI);
    if (*rra > 2.0 * M_PI)
	*rra = *rra - (2.0 * M_PI);

    rxy2 = x*x + y*y;
    rxy = sqrt (rxy2);
    *rdec = atan2 (z, rxy);

    z2 = z * z;
    *r = sqrt (rxy2 + z2);

    return;
}


void
fk52gal (
  double *dtheta,	/* J2000 right ascension in degrees
		   Galactic longitude (l2) in degrees (returned) */
  double *dphi	/* J2000 declination in degrees
		   Galactic latitude (b2) in degrees (returned) */
)
/* Rotation matrices by P.T.Wallace, Starlink eqgal and galeq, March 1986 */

/*  Input equatorial coordinates are J2000 FK5.
    Use gal2fk4() if converting from B1950 FK4 coordinates.
    Reference: Blaauw et al, MNRAS,121,123 (1960) */
{
    double pos[3],pos1[3],r,dl,db,rl,rb,rra,rdec,dra,ddec;
    int i;

    /*  Spherical to cartesian */
    dra = *dtheta;
    ddec = *dphi;
    rra = degrad (dra);
    rdec = degrad (ddec);
    r = 1.0;
    s2v3 (rra,rdec,r,pos);

    /*  Rotate to galactic */
    for (i = 0; i < 3; i++) {
	pos1[i] = pos[0]*jgal[i][0] + pos[1]*jgal[i][1] + pos[2]*jgal[i][2];
	}

    /*  Cartesian to spherical */
    v2s3 (pos1,&rl,&rb,&r);

    dl = raddeg (rl);
    db = raddeg (rb);
    *dtheta = dl;
    *dphi = db;

    return;
}


/*--- Transform IAU 1958 galactic coordinates to J2000 equatorial coordinates */

void
gal2fk5 (
  double *dtheta,	/* Galactic longitude (l2) in degrees
		   J2000.0 ra in degrees (returned) */
  double *dphi	/* Galactic latitude (b2) in degrees
		   J2000.0 dec in degrees (returned) */
)
/*  Output equatorial coordinates are J2000.
   Use gal2fk4() to convert to B1950 coordinates.
    Reference: Blaauw et al, MNRAS,121,123 (1960) */

{
    double pos[3],pos1[3],r,dl,db,rl,rb,rra,rdec,dra,ddec;
    int i;

    /*  Spherical to Cartesian */
    dl = *dtheta;
    db = *dphi;
    rl = degrad (dl);
    rb = degrad (db);
    r = 1.0;
    s2v3 (rl,rb,r,pos);

    /*  Rotate to equatorial coordinates */
    for (i = 0; i < 3; i++) {
	    pos1[i] = pos[0]*jgal[0][i] + pos[1]*jgal[1][i] + pos[2]*jgal[2][i];
	    }

    /*  Cartesian to Spherical */
    v2s3 (pos1,&rra,&rdec,&r);
    dra = raddeg (rra);
    ddec = raddeg (rdec);
    *dtheta = dra;
    *dphi = ddec;

    return;
}
