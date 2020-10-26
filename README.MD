## Summary

A Three-Tiered Client Server System to serve user's airport lookup using RPCgen.

Members: 
- Gavin Limchayseng: KD Tree, RPC
- Raydi Tjuandi: Trie, RPC
- Christopher Fong: KD Tree, RPC

### `places_client`
- Entry point
- User queries a city, state.
- RPC calls `places_server` with specified city, state, and host.
- Returns 5 closest airports to the user's given location.

### `places_server`
- Acts as client for `airport_server`.
- Trie is used to search up specified location or its prefix.
- If an ambiguity occurs where a prefix could have multiple results, return the call to the client.
- Returns call to client with appropriate error message if an error occurs.
- RPC calls `airports_server` with lat/lon of queried city to get 5 closest airports.

### `airports_server`
- KD tree is used to efficiently get K-Nearest-Neighbors.
- RPC returns 5 closest airports to the `places_server` request.

## Run
make
./airports_server &
./places_server localhost &
./places_client localhost <city> <state>


