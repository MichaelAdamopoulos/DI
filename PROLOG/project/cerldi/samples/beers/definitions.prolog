% input event declarations
input_event_declaration(turns_on).
input_event_declaration(turns_off).
input_event_declaration(picks).
input_event_declaration(drops).
input_event_declaration(drinks).
input_event_declaration(leaves).

event_def picks_and_drops :=
    picks and drops.

event_def picks_and_not_drops :=
    picks and tnot drops.

event_def picks_and_drops_or_drinks :=
    picks and drops or drinks.

event_def starts_drinking :=
    start(drinking_period).

event_def stops_drinking :=
    end(drinking_period).

state_def powered_on :=
    turns_on ~> turns_off.

state_def drinking_period :=
    drinks ~> leaves.

state_def powered_on_or_drinking_period :=
    powered_on union drinking_period.

state_def powered_on_and_drinking_period :=
    powered_on intersection drinking_period.

state_def drinking_period_minus_powered_on :=
    drinking_period minus powered_on.



