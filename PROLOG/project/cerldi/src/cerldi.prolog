% operators of the language
:-['src/operators.prolog'].
% computation of an entity's level
:-['src/levels.prolog'].
% formulae transformation rules
:-['src/trasformations.prolog'].
% definitions preprocessing
:-['src/preprocessing.prolog'].
% implementation of temporal operations
:-['src/temporal_operations.prolog'].
% useful utilies
:-['src/utilities.prolog'].
% read from file, assert and retract events
:-['src/stream.prolog'].


:-dynamic t_entity/3, max_level/1, event/2, state/2, transformed_definition_conditions/3.

% main loop
er(StreamFile, OutputFile, DefinitionsFile, Window, Step):-
    open(StreamFile, read, SF, [alias(inputstream)]),
    open(OutputFile, write, OF,[alias(resultsfile)]),
    consult(DefinitionsFile),
    preprocess_definitions,
    CurrentTime is Step,
    er_loop(CurrentTime, Window, Step),
    close(SF),
    close(OF).

er_loop(Tq, Window, Step):-
    assert_events(inputstream, Tq, EndOfFile),
    format(resultsfile, "Query at T= ~w\n", [Tq]),
    temporal_query,
    findall(_,(t_entity(X, event, user), event(X,T), format(resultsfile, "event(~w, ~w).\n", [X,T])), _),
    findall(_,(t_entity(X, state, user), state(X,T), format(resultsfile, "state(~w, ~w).\n", [X,T])), _),
    continue_er_loop(EndOfFile, Tq, Window, Step).

continue_er_loop(yes, _, _, _).
continue_er_loop(no, Tq, Window, Step):-
    Tq1 is Tq + Step,
    NextWindowStart is Tq1 - Window,
    forget_input_events(NextWindowStart),
    forget_output_entities,
    er_loop(Tq1, Window, Step).


% performs a temporal query at instant Tq, over stream with Alias
temporal_query:-
    findall(_,
        (
            max_level(MaxLevel),
            all_between(1, MaxLevel, Levels),
            member(Level, Levels),
            t_entity(X, _, user),
            level(X, Level),
            process_entity(X)
        ),_).


% processes the entity X
process_entity(X):-
    % we need to make sure that it is a user defined entity of type event
    t_entity(X, event, user),!,
    % we get the transformed conditions YTr, and the variable C corresponding
    % to the instant at which the definition is true
    transformed_definition_conditions(X, YTr, C),
    findall(_,
            (
                YTr, % we execute the transformed conditions
                assert_if_not_exists(event(X,C)) % we assert the result
            ),_).

process_entity(X):-
    % same as above but for states
    t_entity(X, state, user),!,
    transformed_definition_conditions(X, YTr, C),
    findall(_,
            (
                YTr,
                assert_if_not_exists(state(X,C))
            ),_).

forget_output_entities:-   
    findall(_,(t_entity(X,event,user), retractall(event(X,T))),_),
    findall(_,(t_entity(X,state,user), retractall(state(X,T))),_).