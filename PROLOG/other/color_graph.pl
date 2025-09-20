:- lib(ic).
:- lib(branch_and_bound).

create_graph(NNodes, Density, Graph) :-
    cr_gr(1, 2, NNodes, Density, [], Graph).

cr_gr(NNodes, _, NNodes, _, Graph, Graph).
cr_gr(N1, N2, NNodes, Density, SoFarGraph, Graph) :-
    N1 < NNodes,
    N2 > NNodes,
    NN1 is N1 + 1,
    NN2 is NN1 + 1,
    cr_gr(NN1, NN2, NNodes, Density, SoFarGraph, Graph).
cr_gr(N1, N2, NNodes, Density, SoFarGraph, Graph) :-
    N1 < NNodes,
    N2 =< NNodes,
    rand(1, 100, Rand),
    (Rand =< Density ->
        append(SoFarGraph, [N1 - N2], NewSoFarGraph)
    ;
        NewSoFarGraph = SoFarGraph),
    NN2 is N2 + 1,
    cr_gr(N1, NN2, NNodes, Density, NewSoFarGraph, Graph).

rand(N1, N2, R) :-
    random(R1),
    R is R1 mod (N2 - N1 + 1) + N1.

% Color graph
color_graph(N, D, Col, C) :-
    create_graph(N, D, G),
    length(Col, N),
    Col #:: 1..N,
    constrain_color(G, Col),
    max_list(Col, C),
    bb_min(labeling(Col), C, bb_options{strategy:continue}).

% Neighboring edges must not have same color
constrain_color([], _).
constrain_color([A-B|T], Col) :-
    element(A, Col, ColA),
    element(B, Col, ColB),
    ColA #\= ColB,
    constrain_color(T, Col).

% Find the max element of a list
max_list(List, Max) :-
    length(List, Len),
    MaxIndex #:: 1..Len,
    element(MaxIndex, List, Max),
    max_list_helper(List, Max).

max_list_helper([], _).
max_list_helper([H|T], Max) :-
    H #=< Max,
    max_list_helper(T, Max).

