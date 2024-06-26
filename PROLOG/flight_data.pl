:- set_flag(print_depth, 1000).

get_flight_data(1,10,
    [[1,2,3,7],[2,3,6],[9,10],[4,6],[5,10],[5,8],[3,6,9],[4,9,10],
     [1,7,9],[3,5],[3,4],[7,9,10],[1,4,8],[6],[3,7,8],[2,5,6],[1,10]],
    [10,20,30,40,20,12,25,34,56,4,34,56,24,34,32,17,40]).

get_flight_data(2,10,
    [[1,2,5,8],[3,2],[3,6,9],[10,5,2],[9,8,6,3],[1,7],[4,7,10],[4]],
    [10,20,25,10,40,10,20,15]).

get_flight_data(3,10,
    [[6,9],[7,9,10],[1,2,4,5],[3,6,8],[2,5,8],[1,3,4,7,10]],
    [32,40,21,32,10,28]).

get_flight_data(4,16,
    [[1,5,11],[5,12],[6,10,11],[7,10,12],[2,9,15,16],[6,11],[8,9],[2,15],
     [4,13],[1,16],[4,8,14],[3,6,13],[7,10],[3,14],[5,11]],
    [2,7,1,3,1,9,11,4,6,4,2,1,10,5,1]).

get_flight_data(5,13,
    [[1,13],[8,12],[5,6,7,8],[4,13],[3,4,5],[5,11],[1,5,11],[1,3,5,7,9],
     [11,12],[1],[9,10,11],[6,8,11],[1,3,5,6,7,8],[10,12,13],
     [2,9,10,11,12],[1,2,3,4,5,6,7,8,9,10,11,12,13],[3,4],[3,6,13],
     [1,2,3,4],[2,4,6,8,10],[13],[2,7,9],[8,9],[6,10],[1,12,13],[2,9],
     [4,7,10],[12],[2,7],[12,13]],
    [1,9,10,40,4,4,2,10,20,1,7,5,20,6,30,60,3,16,2,1,7,2,5,5,3,5,7,1,2,9]).

get_flight_data(6,30,
    [[1,3,5,7,9,11,13,15],[21,22,23,24],[25,26,27],[4,5,6],[6,25],[2,29],
     [22,23,24],[1,15,30],[2,16,29],[1,2,3,4],[6,20,25],[8,23],
     [17,19,21,23,25,27,29],[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,
      18,19,20,21,22,23,24,25,26,27,28,29,30],
     [8,22,23],[3,17,28],[4,18,27],[26,27,28,29,30],[11,12,13,14,15],
     [10,12,13],[21,22,23,24,25],[17,18,19,20],[11,20],[14,17],[7,8,9],
     [13,14,15],[16,17,18],[16,18,20,22,24,26,28,30],[2,4,6,8,10,12,14],
     [4,27],[5,19,26],[5,6,7,8],[16,17,18,19,20],[9,11,14],[1,30],[1,2,3],
     [10,11,12],[19,20,21],[7,21,24],[28,29,30],[6,7,8,9,10],[7,24],
     [3,28],[1,2,3,4,5],[9,10,11,12],[13,14,15,16],[29,30],[9,22],[5,26],
     [12,19],[15,16],[13,18],[25,26,27,28],[10,21]],
    [1,10,20,6,5,6,19,45,60,11,15,15,10,400,17,1,2,12,52,19,14,9,16,14,18,
     3,13,4,5,40,5,5,50,26,7,9,31,17,25,35,50,2,2,5,6,7,12,19,4,51,24,5,
     11,31]).

get_flight_data(I, N, PairingList, CostList) :-
   datafile(I, DataFile),
   open(DataFile, read, Stream),
   read_token(Stream, N, integer),
   read_token(Stream, M, integer),
   read_token(Stream, _, _),
   read_token(Stream, _, _),
   read_token(Stream, _, _),
   read_pairings_costs(Stream, M, PairingList, CostList),
   close(Stream).

read_pairings_costs(_, 0, [], []).
read_pairings_costs(Stream, M, [Pairing|PairingList], [Cost|CostList]) :-
   M > 0,
   read_token(Stream, Cost, integer),
   read_token(Stream, K, integer),
   read_token(Stream, _, _),
   read_token(Stream, _, _),
   read_token(Stream, _, _),
   read_pairing(Stream, K, Pairing),
   M1 is M-1,
   read_pairings_costs(Stream, M1, PairingList, CostList).

read_pairing(_, 0, []).
read_pairing(Stream, K, [Flight|Pairing]) :-
   K > 0,
   read_token(Stream, Flight, integer),
   K1 is K-1,
   read_pairing(Stream, K1, Pairing).

datafile(7, 'acsdata/acs197x17').
datafile(8, 'acsdata/acs294x19').
datafile(9, 'acsdata/acs404x19').
datafile(10, 'acsdata/acs434x24').
datafile(11, 'acsdata/acs467x31').
datafile(12, 'acsdata/acs577x25').
datafile(13, 'acsdata/acs619x23').
datafile(14, 'acsdata/acs626x27').
datafile(15, 'acsdata/acs711x19').
datafile(16, 'acsdata/acs685x22').