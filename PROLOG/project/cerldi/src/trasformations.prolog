:-['./operators.prolog'].
% transformation rules for language ldi
% needs to be completed for all language operators

% base case for input event def
transform_instant_formula(X, Transformed, T):-
  t_entity(X, event, input),
  Transformed = (event(X,T)).

% base case for user event def
transform_instant_formula(X, Transformed, T):-
  t_entity(X, event, user),
  definition_conditions(X, Y),
  transform_instant_formula(Y, Transformed, T).

% and
transform_instant_formula(and(X,Y), Transformed, T):-!,
  transform_instant_formula(X, XTr, T),
  transform_instant_formula(Y, YTr, T),
  Transformed = (
    XTr, YTr
  ).

% or
transform_instant_formula(or(X,Y), Transformed, T):-!,
  transform_instant_formula(X, XTr, T),
  transform_instant_formula(Y, YTr, T),
  Transformed = (
    XTr; YTr
  ).

% start
transform_instant_formula(start(X), Transformed, Ts):-!,
  transform_durative_formula(X, XTr, [[Ts,_]]),
  Transformed = XTr.

% end
transform_instant_formula(end(X), Transformed, Te):-!,
  transform_durative_formula(X, XTr, [[_,Te]]),
  Transformed = XTr.

% tnot
transform_instant_formula(tnot(X), Transformed, T):-!,
  transform_instant_formula(X, XTr, T),
  Transformed = (\+ (XTr)).

% base case for input state def
transform_durative_formula(X, Transformed, T):-
  t_entity(X, state, input),
  Transformed = (event(X,T)).

% base case for user state def
transform_durative_formula(X, Transformed, T):-
  t_entity(X, state, user),
  definition_conditions(X, Y),
  transform_durative_formula(Y, Transformed, T).

% ~>
transform_durative_formula(~>(L,R), Transformed, I):-!,
  transform_instant_formula(L, TrL, Ts),
  transform_instant_formula(R, TrR, Te),
  Transformed = ( 
    findall(Ts, TrL, S),
    findall(Te, TrR, E),
    maximal_intervals(S, E, I)
  ).

% union
transform_durative_formula(union(L, R), Transformed, I):- !,
  transform_durative_formula(L, TrL, IL),
  transform_durative_formula(R, TrR, IR),
  Transformed = (
    findall(IL, TrL, [LIntervals]),
    findall(IR, TrR, [RIntervals]),
    temporal_union(LIntervals, RIntervals, I)
  ).

% intersection
transform_durative_formula(intersection(L, R), Transformed, I):- !,
  transform_durative_formula(L, TrL, IL),
  transform_durative_formula(R, TrR, IR),
  Transformed = (
    findall(IL, TrL, [LIntervals]),
    findall(IR, TrR, [RIntervals]),
    temporal_intersection(LIntervals, RIntervals, I)
  ).

% minus
transform_durative_formula(minus(L, R), Transformed, I) :- !,
  transform_durative_formula(L, TrL, IL),
  transform_durative_formula(R, TrR, IR),
  Transformed = (
    findall(IL, TrL, [LIntervals]),
    findall(IR, TrR, [RIntervals]),
    temporal_minus(LIntervals, RIntervals, I1),
    remove_empty_intervals(I1, I)
  ).


