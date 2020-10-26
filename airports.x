/* Filename: airport_places.x */
/* Authors: Christopher Fong, Raydi Tjuandi, Gavin Limchayseng */
/* Date: 10/17/20 */
/* Revised: 10/25/20 */

/* Store latitude and longitude data */
struct sLocation {
    double latitude;
    double longitude;
};

/* Stores airport information */
struct sAirport {
	string code<CODE_MAX>;
	string name<MAX_NAME>;
	sLocation loc;
	double distance;
};

/* DATA STRUCTURES */
struct sAirportList{
    sAirport ap;        
	sAirportList* next; 
}; 

union airports_ret switch(int err) {
    case 0:
		sAirportList* sAL;	
	default:
		string error_msg<ERR_MAX>;
};


/* IDL PROGRAMS */
program AIRPORTS_PROG {
	version AIRPORTS_VERS {
		airports_ret GET_AIRPORTS(sLocation) = 2;
    } = 1;
} = 0x82874581;	

