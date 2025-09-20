% this file should include predicates
% for: 
%   - maximal_interval (~>) (already included)
%   - temporal union (union) (already included)
%   - temporal intersection (intersection)
%   - temporal difference (minus)


% maximal intervals
maximal_intervals([],_,[]).
maximal_intervals([S|STail], E, I):-
    maximal_intervals(S, STail, E, I).

maximal_intervals(Ts, _, [], [[Ts, inf]]).
maximal_intervals(Ts, S, [E|ETail], I) :-
    E =< Ts,!, maximal_intervals(Ts, S, ETail, I).
maximal_intervals(Ts, S, [E|ETail], I):-
    Ts < E, member(E, S),!, maximal_intervals(Ts, S, ETail, I).
maximal_intervals(Ts, S, [Te|ETail], [[Ts,Te]|I]):-
    Ts < Te, advance(S,Te,S1), maximal_intervals(S1, ETail, I).

advance([], _, []).
advance([X|T], Tc, [X|T]):- X >= Tc.
advance([X|T], Tc, L):- X < Tc, advance(T,Tc,L).

% temporal union
temporal_union(A,B,L):-
    merge_ilse(A,B,R),
    compute_union_intervals(R,0,0,_,L).

merge_ilse(A,B,R):-
    flatten_ilist(A, Af),
    flatten_ilist(B, Bf),
    merge_ilse2(Af,Bf, R).

flatten_ilist([],[]).
flatten_ilist([[A,B]|R],[(A,1,0),(B,0,1)|R1]):-
    flatten_ilist(R,R1).

merge_ilse2([],[],[]).
merge_ilse2([],[B|BR],[B|BR]).
merge_ilse2([A|AR],[],[A|AR]).

merge_ilse2([(T,Sa,Ea)|Atail], [(T,Sb,Eb)|BTail], [(T,S,E)|R]):-
   S is Sa + Sb,
   E is Ea + Eb,
   merge_ilse2(Atail, BTail, R).

merge_ilse2([(Ta,Sa,Ea)|Atail], [(Tb,Sb,Eb)|BTail], [(Ta,Sa,Ea)|R]):-
   Ta < Tb,
   merge_ilse2(Atail, [(Tb,Sb,Eb)|BTail], R).

merge_ilse2([(Ta,Sa,Ea)|Atail], [(Tb,Sb,Eb)|BTail], [(Tb,Sb,Eb)|R]):-
   Ta > Tb,
   merge_ilse2([(Ta,Sa,Ea)|Atail], BTail, R).

compute_union_intervals([],_,_,_,[]).
compute_union_intervals([(TS,SC,EC)|R], 0, E, _, IL):-
    SC > 0,
    EN is E+EC,
    compute_union_intervals(R, SC, EN, TS, IL).

compute_union_intervals([(TE,SC,EC)|R],S,E,TS,[[TS,TE]|IL]):-
    S \= 0,
    SN is S+SC,
    EN is E+EC,
    SN=EN,
    compute_union_intervals(R,0,0,_,IL).

compute_union_intervals([(_,SC,EC)|R],S,E,TS,IL):-
    S \= 0,
    SN is S+SC,
    EN is E+EC,
    SN\=EN,
    compute_union_intervals(R,SN,EN,TS,IL).

% intersection intervals
temporal_intersection([], _, []).
temporal_intersection(_, [], []).
temporal_intersection([[A1, A2] | ATail], [[B1, B2] | BTail], Result) :-
  Start is max(A1, B1),
  End is min(A2, B2),
  (
    Start < End ->
      Result = [[Start, End] | Rest]
    ;
      Result = Rest
  ),
  (
    A2 =< B2 ->
      temporal_intersection(ATail, [[B1, B2] | BTail], Rest)
    ;
      temporal_intersection([[A1, A2] | ATail], BTail, Rest)
  ).

% minus intervals
temporal_minus([], _, []).
temporal_minus([A|ATail], B, Result) :-
    minus_interval(A, B, Subtracted),
    temporal_minus(ATail, B, Rest),
    append(Subtracted, Rest, Result).

% One case for each possible overlap for intervals

minus_interval(Interval, [], [Interval]).
minus_interval([A1, A2], [[B1, B2] | BTail], Result) :-
    (A2 =< B1 ; A1 >= B2), !,
    minus_interval([A1, A2], BTail, Result).

minus_interval([A1, A2], [[_, B2] | BTail], Result) :-
    B2 =< A1, !,
    minus_interval([A1, A2], BTail, Result).

minus_interval([A1, A2], [[B1, B2] | BTail], Result) :-
    B1 =< A1, B2 >= A2, !,
    minus_interval([], BTail, Result).

minus_interval([A1, A2], [[B1, B2] | BTail], Result) :-
    B1 =< A1, B2 < A2, !,
    NewA1 is B2,
    minus_interval([NewA1, A2], BTail, Result).

minus_interval([A1, A2], [[B1, B2] | BTail], Result) :-
    B1 > A1, B2 >= A2, !,
    Sub = [[A1, B1]],
    minus_interval([], BTail, Rest),
    append(Sub, Rest, Result).

minus_interval([A1, A2], [[B1, B2] | BTail], Result) :-
    B1 > A1, B2 < A2, !,
    Sub = [[A1, B1]],
    NewA1 is B2,
    minus_interval([NewA1, A2], BTail, Rest),
    append(Sub, Rest, Result).

remove_empty_intervals([], []).
remove_empty_intervals([[]|Tail], Result) :-
    remove_empty_intervals(Tail, Result).
remove_empty_intervals([H|Tail], [H|Result]) :-
    H \= [],
    remove_empty_intervals(Tail, Result).

