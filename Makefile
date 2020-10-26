#Filename: Makefile 
#Authors: Christopher Fong, Raydi Tjuandi, Gavin Limchayseng 
#Date: 10/17/20 
#Revised: 10/25/20 

# Compiler
CC = $(CXX)

# Parameters

#AIRPORT_CLIENT = places_server
AIRPORT_SERVER = airport_server

PLACES_CLIENT = places_client
PLACES_SERVER = places_server 

AIRPORT_SOURCES_CLNT.c = 
AIRPORT_SOURCES_CLNT.h = 
AIRPORT_SOURCES_SVC.c = 
AIRPORT_SOURCES_SVC.h = 
AIRPORT_SOURCES.x = airports.x 

PLACES_SOURCES_CLNT.c = 
PLACES_SOURCES_CLNT.h = 
PLACES_SOURCES_SVC.c = 
PLACES_SOURCES_SVC.h = 
PLACES_SOURCES.x = places.x

AIRPORT_TARGETS_SVC.c = airports_svc.c airports_server.c airports_xdr.c 
AIRPORT_TARGETS_CLNT.c = airports_clnt.c airports_xdr.c
AIRPORT_TARGETS = airports.h airports_xdr.c airports_clnt.c airports_svc.c airports_server.c

PLACES_TARGETS_SVC.c = places_svc.c places_server.c places_xdr.c airports_clnt.c airports_xdr.c
PLACES_TARGETS_CLNT.c = places_clnt.c places_client.c places_xdr.c airports_xdr.c
PLACES_TARGETS = places.h places_xdr.c places_clnt.c places_svc.c places_client.c places_server.c airports.h airports_clnt.c airports_xdr.c

#AIRPORT and PLACES objects.

AIRPORT_OBJECTS_CLNT = $(AIRPORT_SOURCES_CLNT.c:%.c=%.o)  $(AIRPORT_TARGETS_CLNT.c:%.c=%.o)
AIRPORT_OBJECTS_SVC = $(AIRPORT_SOURCES_SVC.c:%.c=%.o) $(AIRPORT_TARGETS_SVC.c:%.c=%.o)

PLACES_OBJECTS_CLNT = $(PLACES_SOURCES__CLNT.c:%.c=%.o) $(PLACES_TARGETS_CLNT.c:%.c=%.o)
PLACES_OBJECTS_SVC = $(PLACES_SOURCES__SVC.c:%.c=%.o) $(PLACES_TARGETS_SVC.c:%.c=%.o)

# Compiler flags 

CFLAGS += -g -I/usr/include/tirpc
LDLIBS += -ltirpc

# Targets 

all : $(AIRPORT_SERVER) $(PLACES_CLIENT) $(PLACES_SERVER)

#$(AIRPORT_OBJECTS_CLNT) : $(AIRPORT_SOURCES_CLNT.c) $(AIRPORT_SOURCES_CLNT.h) $(AIRPORT_TARGETS_CLNT.c) 

$(PLACES_OBJECTS_CLNT) : $(PLACES_SOURCES_CLNT.c) $(PLACES_SOURCES_CLNT.h) $(PLACES_TARGETS_CLNT.c) 

$(AIRPORT_OBJECTS_SVC) : $(AIRPORT_SOURCES_SVC.c) $(AIRPORT_SOURCES_SVC.h) $(AIRPORT_TARGETS_SVC.c) 

$(PLACES_OBJECTS_SVC) : $(PLACES_SOURCES_SVC.c) $(PLACES_SOURCES_SVC.h) $(PLACES_TARGETS_SVC.c) 

#$(AIRPORT_CLIENT) : $(AIRPORT_OBJECTS_CLNT) 
#	$(LINK.c) -o $(AIRPORT_CLIENT) $(AIRPORT_OBJECTS_CLNT) $(LDLIBS) 

$(PLACES_CLIENT) : $(PLACES_OBJECTS_CLNT) 
	$(LINK.c) -o $(PLACES_CLIENT) $(PLACES_OBJECTS_CLNT) $(LDLIBS) 

$(AIRPORT_SERVER) : $(AIRPORT_OBJECTS_SVC) 
	$(LINK.c) -o $(AIRPORT_SERVER) $(AIRPORT_OBJECTS_SVC) $(LDLIBS)

$(PLACES_SERVER) : $(PLACES_OBJECTS_SVC) 
	$(LINK.c) -o $(PLACES_SERVER) $(PLACES_OBJECTS_SVC) $(LDLIBS)

 clean:
	 $(RM) core $(AIRPORT_OBJECTS_CLNT) $(PLACES_OBJECTS_CLNT)  $(AIRPORT_OBJECTS_SVC) $(PLACES_OBJECTS_SVC) $(AIRPORT_SERVER) $(PLACES_SERVER)  $(PLACES_CLIENT)