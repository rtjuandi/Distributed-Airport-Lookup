/* Filename: aiports.h */
/* Authors: Christopher Fong, Raydi Tjuandi, Gavin Limchayseng */
/* Date: 10/17/20 */
/* Revised: 10/25/20 */

/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _AIRPORTS_H_RPCGEN
#define _AIRPORTS_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif

#define MAX_NAME 64
#define STATE_MAX 3
#define CODE_MAX 4
#define ERR_MAX 256

struct sLocation {
	double latitude;
	double longitude;
};
typedef struct sLocation sLocation;

struct sAirport {
	char *code;
	char *name;
	sLocation loc;
	double distance;
};
typedef struct sAirport sAirport;

struct sAirportList {
	sAirport ap;
	struct sAirportList *next;
};
typedef struct sAirportList sAirportList;

struct airports_ret {
	int err;
	union {
		sAirportList *sAL;
		char *error_msg;
	} airports_ret_u;
};
typedef struct airports_ret airports_ret;

#define AIRPORTS_PROG 0x82874581
#define AIRPORTS_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define GET_AIRPORTS 1
extern  airports_ret * get_airports_1(sLocation *, CLIENT *);
extern  airports_ret * get_airports_1_svc(sLocation *, struct svc_req *);
extern int airports_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
define GET_AIRPORTS 1
extern  airports_ret * get_airports_1();
extern  airports_ret * get_airports_1_svc();
extern int airports_prog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_sAirportList (XDR *, sAirportList*);
extern  bool_t xdr_sLocation (XDR *, sLocation*);
extern  bool_t xdr_sAirport (XDR *, sAirport*);
extern  bool_t xdr_airports_ret (XDR *, airports_ret*);

#else /* K&R C */
extern bool_t xdr_sAirportList ();
extern bool_t xdr_sLocation ();
extern bool_t xdr_sAirport ();
extern bool_t xdr_airports_ret ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_AIRPORTS_H_RPCGEN */