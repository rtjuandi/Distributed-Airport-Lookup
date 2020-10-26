/* Filename: places._placex */
/* Authors: Christopher Fong, Raydi Tjuandi, Gavin Limchayseng */
/* Date: 10/17/20 */
/* Revised: 10/25/20 */

/* CONSTANTS */
const MAX_NAME      = 64;
const STATE_MAX     = 3;
const CODE_MAX      = 4;
const ERR_MAX       = 256;

/* Store latitude and longitude data */
struct pLocation {
    double latitude;
    double longitude;
};

/* Stores airport information */
struct pAirport {
	string code<CODE_MAX>;
	string name<MAX_NAME>;
	pLocation loc;
	double distance;
};

/* DATA STRUCTURES */
struct pAirportList{
    pAirport ap;        
	pAirportList* next; 
}; 

/* City and State information from Client */
struct specified_city_state {
    string name<MAX_NAME>;
    string state<STATE_MAX>;
	string host<MAX_NAME>;
}; 

union places_ret switch(int err) {
    case 0:
    	pAirportList* pAL;
	default:
		string error_msg<ERR_MAX>;
};

/* IDL PROGRAMS */
program PLACES_PROG {
	version PLACES_VERS {
		places_ret PLACES_QUERY(specified_city_state) = 1;
    } = 1;
} = 0x82838281;	