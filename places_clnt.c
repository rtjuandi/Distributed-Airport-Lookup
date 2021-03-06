/* Filename: places_clnt.c */
/* Authors: Christopher Fong, Raydi Tjuandi, Gavin Limchayseng */
/* Date: 10/17/20 */
/* Revised: 10/25/20 */

/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "places.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

places_ret *
places_query_1(specified_city_state *argp, CLIENT *clnt)
{
	static places_ret clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, PLACES_QUERY,
		(xdrproc_t) xdr_specified_city_state, (caddr_t) argp,
		(xdrproc_t) xdr_places_ret, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}
