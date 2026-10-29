# Pong architecture

The current project is a small C++20/raylib prototype: `src/main.cpp` starts
`Game`, and `Game::Run()` owns the window, loop, update and drawing. Keep this
working baseline while separating responsibilities as the game grows.

## Proposed structure

```text
assets/
  audio/                 # sound effects
  fonts/                 # fonts
  music/                 # music tracks
  textures/              # sprites, backgrounds, UI art
docs/
  architecture.md
src/
  app/                   # composition root, window and top-level loop
  core/                  # clock, game state, events, configuration
  gameplay/              # match rules, entities and deterministic simulation
  input/                 # device input mapped to gameplay/UI actions
  mechanics/             # opt-in modifiers and mechanics
  platform/              # raylib-facing window/audio/resource adapters
  render/                # world and presentation rendering
  ui/                    # menus, HUD, settings and accessibility UI
  Game.cpp               # temporary legacy implementation during migration
  Game.h
  main.cpp
tests/
  unit/                  # isolated rules and systems
  integration/           # match-flow and system interaction
```

## Ownership and update flow

`app` constructs the dependencies and runs a fixed-step simulation. `core`
owns match/session state and shared event types, but does not depend on raylib.
`gameplay` owns the ball, paddles, collision and scoring rules. `input` turns
keyboard/gamepad state into player actions. `render` and `ui` read state and
draw it; they do not change match rules. `platform` contains the raylib
boundary, so game rules can be exercised without opening a window.

The loop should gather input, advance simulation in fixed time steps, publish
events such as `PointScored` or `RoundStarted`, then render. Keep the simulation
deterministic and pass time explicitly. This makes replay, rollback, AI,
network play and repeatable tests possible later.

## Adding mechanics

Represent optional mechanics as small gameplay modules with explicit lifecycle
hooks (start, update, end) and configuration. A mechanic should use the match
context and emit/consume typed events rather than reaching into unrelated
systems. Examples include power-ups, spin, curved shots, shields, arena hazards,
and alternate scoring. Keep base Pong rules independent so mechanics can be
enabled per mode and tested in isolation.

## Migration order

1. Move window and loop ownership from `Game` into `app`/`GameSession`.
2. Extract input, update and drawing without changing behavior.
3. Move ball/paddle/scoring rules into `gameplay` and add fixed-step timing.
4. Add event types and mechanic lifecycle once a first mechanic is needed.
5. Add unit tests for rules and integration tests for match flow.

Avoid introducing an entity-component framework or a general plugin system
until the game has concrete needs for them. Small explicit systems fit Pong
better and keep new mechanics easy to understand.
