/* Filename: aiports_xdr.c */
/* Authors: Christopher Fong, Raydi Tjuandi, Gavin Limchayseng */
/* Date: 10/17/20 */
/* Revised: 10/25/20 */

/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "airports.h"

bool_t
xdr_sAirportList (XDR *xdrs, sAirportList *objp)
{
	register int32_t *buf;

	 if (!xdr_sAirport (xdrs, &objp->ap))
		 return FALSE;
	 if (!xdr_pointer (xdrs, (char **)&objp->next, sizeof (sAirportList), (xdrproc_t) xdr_sAirportList))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_sLocation (XDR *xdrs, sLocation *objp)
{
	register int32_t *buf;

	 if (!xdr_double (xdrs, &objp->latitude))
		 return FALSE;
	 if (!xdr_double (xdrs, &objp->longitude))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_sAirport (XDR *xdrs, sAirport *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->code, CODE_MAX))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->name, MAX_NAME))
		 return FALSE;
	 if (!xdr_sLocation (xdrs, &objp->loc))
		 return FALSE;
	 if (!xdr_double (xdrs, &objp->distance))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_airports_ret (XDR *xdrs, airports_ret *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->err))
		 return FALSE;
	switch (objp->err) {
	case 0:
		 if (!xdr_pointer (xdrs, (char **)&objp->airports_ret_u.sAL, sizeof (sAirportList), (xdrproc_t) xdr_sAirportList))
			 return FALSE;
		break;
	default:
		 if (!xdr_string (xdrs, &objp->airports_ret_u.error_msg, ERR_MAX))
			 return FALSE;
		break;
	}
	return TRUE;
}
