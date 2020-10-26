/* Filename: places_server.c */
/* Authors: Christopher Fong, Raydi Tjuandi, Gavin Limchayseng */
/* Date: 10/17/20 */
/* Revised: 10/25/20 */


/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "places.h"
#include "airports.h"
// #include "trie.h"
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>

#define alpha_size 26
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
#define INDEX_TO_CHAR(n) ("abcdefghijklmnopqrstuvwxyz"[n])

using namespace std;

airports_ret* airports_prog_1(char *host, sLocation loc);

struct TrieNode* root = nullptr;

struct TrieReturnStatus {
	bool error;
	string message;
	TrieNode* root;
};

struct TrieNode {
    bool endOfString;
    sLocation loc;
    TrieNode *children[alpha_size];
};

struct ReturnValue {
    bool error;
    std::string value; 
    sLocation loc;
};

/* Create a new Trie Node and Return it */
struct TrieNode *createNode() {
    TrieNode *newNode = new TrieNode;
    newNode -> endOfString = false;

    for(int i = 0; i < alpha_size; i++) {
        newNode -> children[i] = nullptr; /* Initialize null for all children */
    }

    return newNode;
}

void insert(string key, sLocation loc, TrieNode *root) {   
    TrieNode *crawl = root;

   /* Removes any spaces in the string and make it lower case*/
    key.erase( remove( key.begin(), key.end(), ' ' ), key.end() );
    transform(key.begin(), key.end(), key.begin(), ::tolower);

    for(int i = 0; i < key.length(); i++) {
        int charIndex = key[i] - 'a';

        /* Character not in Node's children */
        if(!crawl -> children[charIndex]) {
            /* Create a new Node */
            crawl -> children[charIndex] = createNode();
        }

        crawl = crawl -> children[charIndex];
    }

    crawl -> endOfString = true; /* Mark as end of word */
    crawl -> loc = loc; /* Put in location */
}

/* 
    Finds closest prefix for a given string
    Returns Struct type ReturnValue containing
    Bool error -> Check if func able to find word or not
    String Value -> Either the location string or the reason why the func can't find the string
    
    Used this so it is easier to handle on the client
/**/
struct ReturnValue find(string query, TrieNode *root) {
    TrieNode *crawl = root;
    int level;
    string stringBuild = "";

    ReturnValue retVal; /* Houses return value */

    /* Removes any spaces in the string and make it lower case*/
    query.erase( remove( query.begin(), query.end(), ' ' ), query.end() );
    transform(query.begin(), query.end(), query.begin(), ::tolower);

    int n = query.length();

    for(level = 0; level < n; level++) {
        int index = CHAR_TO_INDEX(query[level]);

        if (!crawl -> children[index]){
            retVal.error = true;
            retVal.value = "Trie Error: Query not in Trie.";
            return retVal;
        }

        stringBuild.push_back(query[level]);
        crawl = crawl -> children[index];
    }
	
    /* Continue Traversing Trie */

    while(crawl) {
        /* If end of word, return */
        bool isWord = (crawl -> endOfString == true);

        if (isWord) {
            retVal.error = false;
            retVal.value = stringBuild;
            retVal.loc = crawl -> loc;
            return retVal;
        }

        /* Else Check if curr Node has more than one children */
        /* More than one possibility */
        int childrenCount = 0;
        int nextIndex;

        for(int i = 0; i < alpha_size; i++) {
            if (crawl -> children[i]) {
                childrenCount++;
                nextIndex = i;
            }
        }

        /* Returns, asking for user to refine value if more than one children */
        if (childrenCount > 1) {
            retVal.error = true;
            retVal.value = "Trie Error: Please refine search.";
            return retVal;
        }

        /* Add word to string and crawl to next children */
        stringBuild.push_back(INDEX_TO_CHAR(nextIndex));
		crawl = crawl -> children[nextIndex];

    }

    /* At This point the function should have returned a value */
    /* On an odd case it did not, return unexpected Error */
    retVal.error = true;
    retVal.value = "Trie Error: Unexpected Error occurred.";

    return retVal;
}

/* Helper Functions */
TrieReturnStatus build_trie(string fName) {
	TrieReturnStatus retVal;
	retVal.error = false;

	TrieNode* root = createNode();

	ifstream file (fName);
	string line;

	/* Open File */
	if(file.is_open())
	{
		/* Read File line by line */
		while(getline(file, line))
		{
			if (!(164 < line.size() || line.size() < 165)) {
				retVal.error = true;
				retVal.message = "Build Trie Error: Line error in file.";
				return retVal;
			}

			/* Parse info from Line */
			string city = line.substr(9,64); 
			string state = line.substr(0,2);

			double longitude = stod(line.substr(153,10));
			double  latitude = stod(line.substr(143, 10));

			sLocation loc = {latitude, longitude};

			city.erase( remove( city.begin(), city.end(), ' ' ), city.end() );
    		transform(city.begin(), city.end(), city.begin(), ::tolower);

			state.erase( remove( state.begin(), state.end(), ' ' ), state.end() );
    		transform(state.begin(), state.end(), state.begin(), ::tolower);

			string key = state + city;

			insert(key, loc, root); /* Insert query to Trie */
		}
	}
	else
	{
		retVal.error = true;
		retVal.message = "Build Trie Error: Can't open file.";
		return retVal;
	}

	retVal.root = root;
	return retVal;
}

//translates a node to the other RPC server data structure
void translateAirport(sAirportList* &sNode, pAirportList* &pNode)
{
	pNode->ap.code = sNode->ap.code;
	pNode->ap.name = sNode->ap.name;
	pNode->ap.loc.latitude = sNode->ap.loc.latitude;
	pNode->ap.loc.longitude = sNode->ap.loc.longitude;
	pNode->ap.distance = sNode->ap.distance;
}

//Copies the list to the other RPC server data structure
pAirportList* copyList(sAirportList* head)
{
	sAirportList* parser = head;
	pAirportList* root = new pAirportList;
	root->next = nullptr;

	translateAirport(parser, root);
	pAirportList* placer = root;
	
	parser = parser->next;
	while(parser != nullptr){
		placer->next = new pAirportList;
		translateAirport(parser, placer->next);
		placer = placer->next;
		parser = parser->next;
	}
	placer->next = nullptr;

	return root;
}

airports_ret*
airports_prog_1(char *host, sLocation loc)
{
	CLIENT *clnt;
	airports_ret  *result_1;
	sLocation  get_airports_1_arg = loc;

#ifndef	DEBUG
	clnt = clnt_create (host, AIRPORTS_PROG, AIRPORTS_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = get_airports_1(&get_airports_1_arg, clnt);
	if (result_1 == (airports_ret *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */

	return result_1;
}

places_ret *
places_query_1_svc(specified_city_state *argp, struct svc_req *rqstp)
{
	static places_ret result;

	//Builds Trie
	TrieReturnStatus trie_status;
	if(root == nullptr) {
		trie_status = build_trie("places2k.txt");
		//  Check if Trie is successfuly built
		if(trie_status.error) {
			result.err = 1;
			strcpy(result.places_ret_u.error_msg, trie_status.message.c_str());
			return &result;
		}

		root = trie_status.root;
	}
	
	xdr_free((xdrproc_t)xdr_places_ret, &result);

	string city = argp->name;
	string state = argp->state;

	string query = state + city;

	ReturnValue retVal = find(query, root);

	// Check if we are able to retrieve location of query
	if(retVal.error) {
		result.err = 1;

		result.places_ret_u.error_msg = (char *)malloc(60*sizeof(char));
		strcpy(result.places_ret_u.error_msg, retVal.value.c_str());
		
		return &result;
	}

	sLocation loc = retVal.loc;


	//Contacts airport server for list
	airports_ret* airportReturn = airports_prog_1(argp->host, loc);

	//Translates list from sAirport to pAirport
	sAirportList* temp = airportReturn->airports_ret_u.sAL;
	result.err = 0;
	result.places_ret_u.pAL = copyList(temp);

	return &result;
}