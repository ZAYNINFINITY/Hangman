# Level-by-Level Blueprint (30 Progressive Levels)

This repo currently ships a single-file console Hangman (`hangman.cpp`) plus a basic `README.md`.

Below: **30 in-game levels** (progressive mechanics) and **~510 granular tasks** (**17 per level**), each with a realistic commit message.

---

## Level 1 – Project Bootstrap & Core Refactor

**Feature Enhancements**

- Keep current classic Hangman loop; make behavior deterministic in tests.
- Improve “already guessed” feedback and end-of-game summary.

**Code Architecture / Refactoring**

- Extract `GameState`, `GameConfig`, and pure helper functions.
- Remove `using namespace std;` and reduce global side effects.

**UI/UX Improvements**

- Clearer prompts, consistent casing, and input retry prompts.
- Show guessed letters list every turn.

**Game Mechanics**

- Single-word game with fixed attempts; basic win/lose conditions.

**Tests & Bug Fixes**

- Fix non-letter input handling and newline/whitespace issues.
- Add initial unit test harness skeleton.

**Documentation**

- Add build/run instructions and contribution guidelines.

**Tasks (17)**

1. Refactor main loop into `runGame()` — Commit: `Refactor main loop into runGame()`
2. Introduce `GameState` struct for word/guesses — Commit: `Add GameState struct for core state`
3. Add `GameConfig` for attempts/casing rules — Commit: `Add GameConfig for game settings`
4. Replace `rand()` usage behind `Rng` wrapper — Commit: `Wrap RNG to centralize randomness`
5. Normalize word casing consistently — Commit: `Normalize selected word casing consistently`
6. Extract `isAlphaLetter()` input guard — Commit: `Add alpha-only input validation`
7. Handle multi-character input robustly — Commit: `Handle multi-character guesses gracefully`
8. Print guessed letters each turn — Commit: `Display guessed letters list each turn`
9. Improve duplicate-guess messaging — Commit: `Improve duplicate guess feedback`
10. Make hangman drawing independent of attempts max — Commit: `Decouple hangman drawing from attempts max`
11. Add `formatMaskedWord()` helper — Commit: `Extract masked word formatting helper`
12. Add `--seed` CLI option (optional) — Commit: `Add optional --seed for reproducible games`
13. Add skeleton `tests/` directory — Commit: `Add initial tests directory structure`
14. Add unit tests for `formatMaskedWord()` — Commit: `Add tests for masked word formatting`
15. Fix edge case: empty word list — Commit: `Handle empty word list with clear error`
16. Update README with build/run steps — Commit: `Update README with build and run instructions`
17. Add `docs/` roadmap reference — Commit: `Document planned 30-level campaign roadmap`

---

## Level 2 – External Word Lists & Categories v1

**Feature Enhancements**

- Load words from external files with basic categories.
- Fall back to built-in list if files missing.

**Code Architecture / Refactoring**

- Add `WordRepository` and `FileWordSource`.
- Separate parsing/validation from selection.

**UI/UX Improvements**

- Category selection menu with defaults.
- Better error output when files can’t be read.

**Game Mechanics**

- Level 2 introduces longer words and one selected category.

**Tests & Bug Fixes**

- Validate word list entries (alpha, min length).
- Unit tests for parsing and category selection.

**Documentation**

- Document word list format and locations.

**Tasks (17)**

1. Create `data/words/animals.txt` — Commit: `Add animals word list`
2. Create `data/words/countries.txt` — Commit: `Add countries word list`
3. Create `data/words/movies.txt` — Commit: `Add movies word list`
4. Implement `WordRepository` interface — Commit: `Add WordRepository abstraction`
5. Implement file loader with trimming — Commit: `Add file-based word list loader`
6. Add word validation (alpha + length) — Commit: `Validate words loaded from files`
7. Add category enum + mapping — Commit: `Add category model and mapping`
8. Implement category selection prompt — Commit: `Add category selection prompt`
9. Add default category behavior — Commit: `Add default category when none chosen`
10. Add fallback to built-in words — Commit: `Fallback to built-in words when files missing`
11. Add logging helper for load errors — Commit: `Improve word load error messages`
12. Add tests for word validation rules — Commit: `Add tests for word list validation`
13. Add tests for file parsing (CRLF/LF) — Commit: `Add tests for line ending tolerant parsing`
14. Add tests for category selection flow — Commit: `Add tests for category selection`
15. Add “Level 2” rules summary screen — Commit: `Show Level 2 rules summary`
16. Tune Level 2 word length constraints — Commit: `Adjust Level 2 word length constraints`
17. Document word list format in README — Commit: `Document external word list format`

---

## Level 3 – CMake Build, Source Layout & CI

**Feature Enhancements**

- Standard build using CMake; separate debug/release.

**Code Architecture / Refactoring**

- Move code to `src/` and headers to `include/`.
- Create a small library target for core logic.

**UI/UX Improvements**

- Add version output `--version` and help `--help`.

**Game Mechanics**

- No new mechanics; foundation for later levels.

**Tests & Bug Fixes**

- Add cross-platform build verification in CI.

**Documentation**

- Update README build steps for CMake.

**Tasks (17)**

1. Add top-level `CMakeLists.txt` — Commit: `Add CMake build configuration`
2. Split code into `src/main.cpp` — Commit: `Move entrypoint into src/main.cpp`
3. Add `include/hangman/Game.hpp` — Commit: `Add public Game header`
4. Create `hangman_core` library target — Commit: `Create hangman_core library target`
5. Wire executable to core library — Commit: `Link executable against hangman_core`
6. Add compiler warnings flags — Commit: `Enable warnings for supported compilers`
7. Add `--help` CLI output — Commit: `Add --help CLI usage output`
8. Add `--version` CLI output — Commit: `Add --version output`
9. Add basic argument parsing module — Commit: `Add minimal CLI argument parser`
10. Create `tests` CMake target — Commit: `Add CMake test target`
11. Add lightweight test framework (doctest) — Commit: `Vendor doctest for unit tests`
12. Add CI workflow for Windows/Linux — Commit: `Add GitHub Actions CI for builds`
13. Cache build artifacts in CI — Commit: `Speed up CI with build caching`
14. Add `.gitignore` for build outputs — Commit: `Add .gitignore for build directories`
15. Fix include hygiene and headers — Commit: `Clean up includes and header boundaries`
16. Update README with CMake instructions — Commit: `Update README with CMake build steps`
17. Add CONTRIBUTING quickstart — Commit: `Add CONTRIBUTING.md with workflow`

---

## Level 4 – Difficulty Presets (Easy/Normal/Hard)

**Feature Enhancements**

- Difficulty presets affect attempts, hint budget, and score multipliers.

**Code Architecture / Refactoring**

- Add `Difficulty` model and rule tables.
- Centralize rule lookups via `Ruleset`.

**UI/UX Improvements**

- Difficulty shown during play; confirm selection.

**Game Mechanics**

- Level 4 introduces difficulty selection and fewer attempts on hard.

**Tests & Bug Fixes**

- Validate difficulty parsing and rule constraints.

**Documentation**

- Document difficulty rules and scoring multipliers.

**Tasks (17)**

1. Add `Difficulty` enum — Commit: `Add Difficulty enum`
2. Add `Ruleset` struct for per-difficulty rules — Commit: `Introduce Ruleset for difficulty rules`
3. Implement difficulty selection menu — Commit: `Add difficulty selection menu`
4. Persist difficulty choice in state — Commit: `Store selected difficulty in GameState`
5. Vary attempts by difficulty — Commit: `Set attempts based on difficulty`
6. Add score multiplier per difficulty — Commit: `Add score multiplier per difficulty`
7. Display difficulty in HUD — Commit: `Show difficulty in game HUD`
8. Add CLI `--difficulty` option — Commit: `Add --difficulty CLI flag`
9. Validate CLI difficulty values — Commit: `Validate difficulty CLI input`
10. Add tests for ruleset tables — Commit: `Add tests for difficulty rules tables`
11. Add tests for CLI difficulty parsing — Commit: `Add tests for difficulty argument parsing`
12. Add “recommended difficulty” hint — Commit: `Add recommended difficulty hint in menu`
13. Tune hard mode attempt counts — Commit: `Tune hard mode attempts`
14. Prevent invalid attempts (<=0) — Commit: `Guard against invalid attempts configuration`
15. Refactor HUD rendering to function — Commit: `Extract HUD rendering helper`
16. Update README with difficulty docs — Commit: `Document difficulty presets in README`
17. Add `CHANGELOG.md` entry for Level 4 — Commit: `Add changelog entry for difficulty presets`

---

## Level 5 – Scoring v1 (Accuracy + Speed)

**Feature Enhancements**

- Score based on correct letters, mistakes, and completion bonus.
- Optional speed bonus if timer exists later (stub now).

**Code Architecture / Refactoring**

- Add `Scoring` module with pure functions.
- Store score events (for later analytics).

**UI/UX Improvements**

- Show score delta after each guess.

**Game Mechanics**

- Level 5 introduces scoring goals; unlock next level by minimum score.

**Tests & Bug Fixes**

- Unit tests for scoring math and edge cases.

**Documentation**

- Document scoring formula and examples.

**Tasks (17)**

1. Add `ScoreState` to `GameState` — Commit: `Add ScoreState to game state`
2. Implement points for correct guess — Commit: `Add points for correct guesses`
3. Implement penalty for wrong guess — Commit: `Add penalty for incorrect guesses`
4. Add completion bonus scoring — Commit: `Add completion bonus scoring`
5. Add repeated-guess neutral scoring — Commit: `Ensure duplicate guesses do not change score`
6. Track per-turn score delta — Commit: `Track score delta per turn`
7. Render score in HUD — Commit: `Display current score in HUD`
8. Show “+/-X” feedback per guess — Commit: `Show score delta feedback per guess`
9. Add scoring config to `Ruleset` — Commit: `Move scoring constants into Ruleset`
10. Add tests for correct guess scoring — Commit: `Add tests for correct guess scoring`
11. Add tests for wrong guess penalties — Commit: `Add tests for wrong guess penalties`
12. Add tests for completion bonus — Commit: `Add tests for completion bonus calculation`
13. Add score clamp (no negative below floor) — Commit: `Clamp score to non-negative floor`
14. Add minimum-score-to-pass Level 5 — Commit: `Add pass threshold for Level 5`
15. Add end-of-round score breakdown — Commit: `Show score breakdown at round end`
16. Refactor scoring into `Scoring.cpp` — Commit: `Extract scoring to dedicated module`
17. Document scoring in README — Commit: `Document scoring rules and examples`

---

## Level 6 – Local Leaderboards (JSON)

**Feature Enhancements**

- Persist high scores locally with player name and timestamp.
- Separate leaderboards by difficulty and category.

**Code Architecture / Refactoring**

- Add `LeaderboardStore` with JSON serialization.
- Add `Clock` abstraction for timestamps.

**UI/UX Improvements**

- Show top N scores on startup and after game over.

**Game Mechanics**

- Level 6 introduces competitive replay loop (beat your best).

**Tests & Bug Fixes**

- Test serialization roundtrip and file corruption handling.

**Documentation**

- Document leaderboard file location and schema.

**Tasks (17)**

1. Vendor `nlohmann/json` — Commit: `Vendor nlohmann/json for persistence`
2. Add `LeaderboardEntry` model — Commit: `Add LeaderboardEntry model`
3. Add `Leaderboard` container type — Commit: `Add Leaderboard container type`
4. Implement JSON encode/decode — Commit: `Implement leaderboard JSON serialization`
5. Save leaderboard to `data/leaderboard.json` — Commit: `Persist leaderboard to JSON file`
6. Load leaderboard on startup — Commit: `Load leaderboard on startup`
7. Add corruption-safe load fallback — Commit: `Handle corrupted leaderboard file gracefully`
8. Prompt for player name on first run — Commit: `Prompt for player name on first run`
9. Add “Top 10” leaderboard screen — Commit: `Add Top 10 leaderboard screen`
10. Filter leaderboard by difficulty — Commit: `Split leaderboard by difficulty`
11. Filter leaderboard by category — Commit: `Split leaderboard by category`
12. Add unit tests for JSON roundtrip — Commit: `Add tests for leaderboard JSON roundtrip`
13. Add unit tests for corruption fallback — Commit: `Add tests for leaderboard corruption handling`
14. Add deterministic timestamp in tests — Commit: `Inject clock for deterministic timestamps`
15. Sort and truncate entries reliably — Commit: `Sort and truncate leaderboard entries`
16. Add CLI `--reset-leaderboard` — Commit: `Add --reset-leaderboard option`
17. Document leaderboard storage — Commit: `Document leaderboard file schema and location`

---

## Level 7 – Hint System v1 (Reveal + Vowel)

**Feature Enhancements**

- Add limited hints: reveal a letter, reveal a vowel/consonant choice.

**Code Architecture / Refactoring**

- Add `HintEngine` and hint budget in `Ruleset`.

**UI/UX Improvements**

- Add hint prompt (`?` command) and show remaining hints.

**Game Mechanics**

- Level 7 introduces hint-limited play with score penalty.

**Tests & Bug Fixes**

- Ensure hints never reveal already-guessed letters.

**Documentation**

- Document hint types and penalties.

**Tasks (17)**

1. Add hint budget to `Ruleset` — Commit: `Add hint budget to Ruleset`
2. Add hint count to state — Commit: `Track hints remaining in GameState`
3. Implement reveal-letter hint — Commit: `Implement reveal-letter hint`
4. Implement vowel-priority hint — Commit: `Implement vowel-priority hint`
5. Add scoring penalty for hints — Commit: `Apply score penalty for hint usage`
6. Add `?` input command handling — Commit: `Add ? command to request hints`
7. Add hint menu UI — Commit: `Add hint selection menu`
8. Prevent hints when budget is zero — Commit: `Block hint usage when out of hints`
9. Prefer unrevealed letters only — Commit: `Ensure hints reveal only new letters`
10. Render remaining hints in HUD — Commit: `Display hints remaining in HUD`
11. Add tests for reveal-letter hint — Commit: `Add tests for reveal-letter hint`
12. Add tests for vowel hint behavior — Commit: `Add tests for vowel hint selection`
13. Add tests for hint budget decrement — Commit: `Add tests for hint budget tracking`
14. Add edge case handling for 1-letter words — Commit: `Handle hint behavior for very short words`
15. Refactor hint logic into `HintEngine` — Commit: `Extract hint logic to HintEngine`
16. Add Level 7 pass criteria update — Commit: `Update Level 7 pass criteria with hints`
17. Document hints in README — Commit: `Document hint commands and penalties`

---

## Level 8 – Timed Rounds (Soft Timer)

**Feature Enhancements**

- Add optional round timer with time-based score modifier.

**Code Architecture / Refactoring**

- Add `Timer` abstraction; keep time measurement out of core logic.

**UI/UX Improvements**

- Display elapsed time; warn when time is low.

**Game Mechanics**

- Level 8 adds “beat the clock” scoring bonus.

**Tests & Bug Fixes**

- Make timer injectable in tests.

**Documentation**

- Document timer rules and scoring effects.

**Tasks (17)**

1. Add `ITimer` interface — Commit: `Add timer interface for round timing`
2. Implement `SystemTimer` — Commit: `Implement SystemTimer using steady_clock`
3. Add elapsed time tracking to state — Commit: `Track elapsed time in GameState`
4. Render timer in HUD — Commit: `Show elapsed time in HUD`
5. Add time warnings at thresholds — Commit: `Add low-time warnings`
6. Add soft time limit per difficulty — Commit: `Add soft time limit by difficulty`
7. Apply time bonus on win — Commit: `Apply time-based win bonus`
8. Apply time penalty when exceeding limit — Commit: `Apply time penalty after soft limit`
9. Add CLI `--no-timer` — Commit: `Add --no-timer option`
10. Add tests with fake timer — Commit: `Add fake timer for deterministic tests`
11. Add tests for time bonus math — Commit: `Add tests for time bonus calculation`
12. Add tests for time penalty math — Commit: `Add tests for time penalty calculation`
13. Refactor scoring to accept time inputs — Commit: `Refactor scoring to accept elapsed time`
14. Add end screen time summary — Commit: `Show time summary on round end`
15. Fix input pauses affecting timer display — Commit: `Fix timer display around user input`
16. Update Level 8 completion requirements — Commit: `Update Level 8 rules for timed rounds`
17. Document timer mode in README — Commit: `Document timed rounds and scoring`

---

## Level 9 – ANSI TUI Polish (Colors + Micro-Animations)

**Feature Enhancements**

- Add colored output (configurable) and micro-animations (typing/flash).

**Code Architecture / Refactoring**

- Add `Renderer` interface with `AnsiRenderer` implementation.

**UI/UX Improvements**

- Clear screen between turns (optional), centered layout, consistent spacing.

**Game Mechanics**

- No new mechanics; presentation upgrade for campaign feel.

**Tests & Bug Fixes**

- Disable ANSI when stdout not a tty (best-effort).

**Documentation**

- Document color toggle and terminal compatibility.

**Tasks (17)**

1. Add `Renderer` interface — Commit: `Introduce Renderer abstraction`
2. Implement `PlainRenderer` fallback — Commit: `Add PlainRenderer for non-ANSI terminals`
3. Implement `AnsiRenderer` colors — Commit: `Add ANSI color renderer`
4. Add config flag `enableColors` — Commit: `Add color toggle to config`
5. Add CLI `--no-color` option — Commit: `Add --no-color option`
6. Add “flash” effect on correct guess — Commit: `Add flash effect on correct guess`
7. Add “wrong-guess emphasis” effect — Commit: `Add wrong-guess emphasis effect`
8. Add optional clear-screen per turn — Commit: `Add optional clear screen between turns`
9. Improve layout spacing and headers — Commit: `Polish HUD layout spacing`
10. Add category/difficulty badges in HUD — Commit: `Add badges for category and difficulty`
11. Gate animations behind config — Commit: `Add config to disable animations`
12. Add tests for renderer selection — Commit: `Add tests for renderer selection logic`
13. Add basic output tests for `PlainRenderer` — Commit: `Add basic output tests for PlainRenderer`
14. Fix hangman drawing alignment — Commit: `Fix hangman ASCII alignment`
15. Improve ANSI support on Windows (best-effort) — Commit: `Improve ANSI support on Windows terminals`
16. Add docs for TUI styling — Commit: `Add docs for TUI styling guidelines`
17. Update README with color options — Commit: `Document terminal UI and color flags`

---

## Level 10 – Accessibility & Input Ergonomics

**Feature Enhancements**

- High-contrast mode, reduced motion mode, and improved key mappings.

**Code Architecture / Refactoring**

- Add `AccessibilityConfig` and propagate to renderer.

**UI/UX Improvements**

- Allow backspace re-entry and show valid command hints.

**Game Mechanics**

- No new mechanics; usability improvements support longer campaign.

**Tests & Bug Fixes**

- Better handling for non-ASCII input and locale quirks.

**Documentation**

- Document accessibility flags and recommended settings.

**Tasks (17)**

1. Add high-contrast palette — Commit: `Add high contrast palette`
2. Add reduced motion mode — Commit: `Add reduced motion setting`
3. Add CLI `--reduced-motion` — Commit: `Add --reduced-motion option`
4. Add CLI `--high-contrast` — Commit: `Add --high-contrast option`
5. Show command cheatsheet in HUD — Commit: `Show command hints in HUD`
6. Add `:quit` and `:restart` commands — Commit: `Add :quit and :restart commands`
7. Add `:help` command screen — Commit: `Add :help command`
8. Improve input reader for whitespace handling — Commit: `Improve input reader for whitespace handling`
9. Reject non-ASCII letters with clear message — Commit: `Reject non-ASCII letters with clear message`
10. Add tests for command parsing — Commit: `Add tests for command parsing`
11. Add tests for input normalization — Commit: `Add tests for input normalization`
12. Prevent multiple guesses from single line — Commit: `Prevent multiple guesses from single line input`
13. Add optional terminal bell feedback — Commit: `Add optional terminal bell feedback`
14. Propagate accessibility settings to renderer — Commit: `Propagate accessibility settings to renderer`
15. Add Level 10 accessibility notes — Commit: `Add Level 10 accessibility release notes`
16. Add `docs/ACCESSIBILITY.md` — Commit: `Add accessibility documentation`
17. Update README accessibility section — Commit: `Document accessibility flags in README`

---

## Level 11 – Localization v1 (UI Strings + Language Selection)

**Feature Enhancements**

- Support multiple UI languages (English baseline + at least one more).

**Code Architecture / Refactoring**

- Add `I18n` string table loader (JSON) with key-based lookup.

**UI/UX Improvements**

- Language selection menu and persisted preference.

**Game Mechanics**

- Level 11 introduces language-specific word lists.

**Tests & Bug Fixes**

- Test missing-key fallbacks.

**Documentation**

- Document how to add translations.

**Tasks (17)**

1. Add `data/i18n/en.json` — Commit: `Add English i18n string table`
2. Add `data/i18n/es.json` — Commit: `Add Spanish i18n string table`
3. Add `I18n` module for key lookup — Commit: `Add I18n string lookup module`
4. Add fallback for missing keys — Commit: `Add fallback for missing i18n keys`
5. Add language selection menu — Commit: `Add language selection menu`
6. Persist language preference — Commit: `Persist language preference`
7. Add CLI `--lang` option — Commit: `Add --lang option`
8. Load word lists per selected language — Commit: `Load word lists per selected language`
9. Add `data/words/es/animals.txt` — Commit: `Add Spanish animals word list`
10. Add `data/words/es/countries.txt` — Commit: `Add Spanish countries word list`
11. Wire localized strings into renderer — Commit: `Wire localized strings into renderer`
12. Add tests for i18n table loading — Commit: `Add tests for i18n table loading`
13. Add tests for fallback behavior — Commit: `Add tests for i18n fallback behavior`
14. Add tests for `--lang` parsing — Commit: `Add tests for language CLI parsing`
15. Add documentation for adding translations — Commit: `Add documentation for adding translations`
16. Update Level 11 rules text — Commit: `Update Level 11 rules for localization`
17. Update README localization section — Commit: `Document localization and language packs`

---

## Level 12 – Campaign Skeleton (30-Level Progression State)

**Feature Enhancements**

- Add campaign mode with level unlocks (1–30), progress saved locally.

**Code Architecture / Refactoring**

- Add `CampaignState` and `ProgressStore` (JSON).

**UI/UX Improvements**

- Level select screen showing locked/unlocked levels.

**Game Mechanics**

- Each level defines word constraints, attempts, hint budget, and modifiers.

**Tests & Bug Fixes**

- Ensure progress saves atomically.

**Documentation**

- Document campaign progression and save format.

**Tasks (17)**

1. Add `CampaignLevel` model — Commit: `Add CampaignLevel model`
2. Add `CampaignState` for progression — Commit: `Add CampaignState for progression`
3. Persist campaign progress to JSON — Commit: `Persist campaign progress to JSON`
4. Implement atomic progress save — Commit: `Implement atomic progress save`
5. Add campaign level select screen — Commit: `Add campaign level select screen`
6. Show locked levels in level select — Commit: `Show locked levels in level select`
7. Add continue campaign option — Commit: `Add continue campaign option`
8. Unlock next level after passing — Commit: `Unlock next level after passing`
9. Add per-level rules table — Commit: `Add per-level rules table`
10. Apply campaign rules to `Ruleset` — Commit: `Apply campaign rules to Ruleset`
11. Add tests for campaign unlock logic — Commit: `Add tests for campaign unlock logic`
12. Add tests for progress persistence — Commit: `Add tests for progress persistence`
13. Add `--campaign` mode — Commit: `Add --campaign mode`
14. Add `--level` override — Commit: `Add --level override for campaign`
15. Prevent starting locked levels — Commit: `Prevent starting locked levels`
16. Add campaign completion summary — Commit: `Add campaign completion summary`
17. Document campaign mode — Commit: `Document 30-level campaign mode`

---

## Level 13 – Word Difficulty Scaling (Length + Rarity)

**Feature Enhancements**

- Tag words by difficulty; scale selection by campaign level.

**Code Architecture / Refactoring**

- Add word metadata parsing (`word|difficulty|tags`).

**UI/UX Improvements**

- Show difficulty indicator and expected length range.

**Game Mechanics**

- Level 13 introduces longer words and fewer common letters.

**Tests & Bug Fixes**

- Validate metadata parsing and backward compatibility.

**Documentation**

- Document metadata format for word lists.

**Tasks (17)**

1. Define word metadata schema — Commit: `Define word metadata schema`
2. Parse metadata from word list entries — Commit: `Parse metadata from word list entries`
3. Support plain words without metadata — Commit: `Support plain words without metadata`
4. Add word difficulty tiers (1–5) — Commit: `Add word difficulty tiers`
5. Add rarity-weighted word selection — Commit: `Add rarity-weighted word selection`
6. Scale word difficulty by campaign level — Commit: `Scale word difficulty by campaign level`
7. Display word difficulty tier in HUD — Commit: `Display word difficulty tier in HUD`
8. Add tests for word metadata parsing — Commit: `Add tests for word metadata parsing`
9. Add tests for plain word compatibility — Commit: `Add tests for plain word compatibility`
10. Add tests for weighted selection — Commit: `Add tests for weighted word selection`
11. Add metadata to EN animals list — Commit: `Add metadata to EN animals list`
12. Add metadata to EN countries list — Commit: `Add metadata to EN countries list`
13. Validate difficulty tier bounds — Commit: `Validate difficulty tier bounds`
14. Improve reporting for invalid lines — Commit: `Improve reporting for invalid word list lines`
15. Tune Level 13 constraints — Commit: `Tune Level 13 word difficulty constraints`
16. Wire campaign rules to difficulty tiers — Commit: `Wire campaign rules to difficulty tiers`
17. Document metadata and difficulty tiers — Commit: `Document word metadata and difficulty tiers`

---

## Level 14 – Smart Hint v2 (Frequency-Based Suggestions)

**Feature Enhancements**

- Offer suggested next letters using frequency analysis of remaining candidates.

**Code Architecture / Refactoring**

- Keep a candidate list based on pattern + guessed letters.

**UI/UX Improvements**

- Show top 3 suggested letters (optional) with a toggle.

**Game Mechanics**

- Level 14 introduces “analysis hint” that costs more points.

**Tests & Bug Fixes**

- Test candidate filtering with repeated letters.

**Documentation**

- Explain how frequency hints work.

**Tasks (17)**

1. Add `CandidateFilter` module — Commit: `Add candidate filter for smart hints`
2. Build candidate list for current category — Commit: `Build candidate list for current category`
3. Filter candidates by masked pattern — Commit: `Filter candidates by masked pattern`
4. Exclude candidates containing wrong guesses — Commit: `Exclude candidates containing wrong guesses`
5. Compute letter frequencies from candidates — Commit: `Compute letter frequencies from candidates`
6. Generate top letter suggestions — Commit: `Generate top letter suggestions`
7. Add analysis-based hint type — Commit: `Add analysis-based hint type`
8. Add higher penalty for analysis hint — Commit: `Add higher penalty for analysis hint`
9. Add toggle for suggestion display — Commit: `Add toggle for suggestion display`
10. Show suggested letters in HUD — Commit: `Show suggested letters in HUD`
11. Add tests for candidate filtering — Commit: `Add tests for candidate filtering`
12. Add tests for frequency hint calculation — Commit: `Add tests for frequency hint calculation`
13. Handle empty candidate set gracefully — Commit: `Handle empty candidate set gracefully`
14. Cache candidates per round for performance — Commit: `Cache candidates per round for performance`
15. Tune Level 14 hint penalties — Commit: `Tune Level 14 hint penalties`
16. Update Level 14 rules text — Commit: `Update Level 14 rules text`
17. Document frequency-based hint system — Commit: `Document frequency-based hint system`

---

## Level 15 – Save/Load Mid-Round

**Feature Enhancements**

- Save and resume an in-progress round (campaign or quick play).

**Code Architecture / Refactoring**

- Add `GameSerializer` and stable schema versioning.

**UI/UX Improvements**

- Add `:save` / `:load` commands with confirmations.

**Game Mechanics**

- Level 15 introduces limited save slots (e.g., 3) for challenge integrity.

**Tests & Bug Fixes**

- Test serialization roundtrip and schema migration stubs.

**Documentation**

- Document save locations and schema version policy.

**Tasks (17)**

1. Add `GameSnapshot` model — Commit: `Add GameSnapshot model`
2. Serialize game snapshot to JSON — Commit: `Serialize game snapshot to JSON`
3. Deserialize game snapshot from JSON — Commit: `Deserialize game snapshot from JSON`
4. Add snapshot schema version field — Commit: `Add snapshot schema version field`
5. Add `:save` command — Commit: `Add :save command`
6. Add `:load` command — Commit: `Add :load command`
7. Add save slot selection UI — Commit: `Add save slot selection UI`
8. Limit saves to three slots — Commit: `Limit saves to three slots`
9. Add confirmation before overwriting save — Commit: `Add confirmation before overwriting save`
10. Guard against incompatible snapshot versions — Commit: `Guard against incompatible snapshot versions`
11. Add tests for snapshot roundtrip — Commit: `Add tests for snapshot roundtrip`
12. Add tests for snapshot version mismatch — Commit: `Add tests for snapshot version mismatch`
13. Handle corrupted save files gracefully — Commit: `Handle corrupted save files gracefully`
14. Allow campaign to resume from last save — Commit: `Allow campaign to resume from last save`
15. Add optional autosave setting — Commit: `Add optional autosave setting`
16. Add Level 15 save slot rules — Commit: `Add Level 15 save slot rules`
17. Document save/load commands and files — Commit: `Document save/load commands and files`

---

## Level 16 – Undo/Redo (Limited)

**Feature Enhancements**

- Allow undo/redo of the last guess with restrictions (e.g., 1 undo per round).

**Code Architecture / Refactoring**

- Add immutable `TurnEvent` log and replay to compute state.

**UI/UX Improvements**

- Add `:undo` / `:redo` commands and show remaining undos.

**Game Mechanics**

- Level 16 introduces strategic undo with score cost.

**Tests & Bug Fixes**

- Ensure undo restores attempts, masked letters, and score.

**Documentation**

- Document limitations and scoring impacts.

**Tasks (17)**

1. Add `TurnEvent` model — Commit: `Add TurnEvent model`
2. Record guesses as turn events — Commit: `Record guesses as turn events`
3. Compute state by replaying events — Commit: `Compute state by replaying events`
4. Add undo budget per difficulty — Commit: `Add undo budget per difficulty`
5. Add `:undo` command — Commit: `Add :undo command`
6. Add `:redo` command — Commit: `Add :redo command`
7. Apply score penalty for undo — Commit: `Apply score penalty for undo`
8. Restore attempts and mask when undoing — Commit: `Restore attempts and mask when undoing`
9. Restore guessed letters on undo — Commit: `Restore guessed letters on undo`
10. Display undos remaining in HUD — Commit: `Display undos remaining in HUD`
11. Add tests for undo state restoration — Commit: `Add tests for undo state restoration`
12. Add tests for redo behavior — Commit: `Add tests for redo behavior`
13. Add tests for undo budget enforcement — Commit: `Add tests for undo budget enforcement`
14. Block undo after round ends — Commit: `Block undo after round ends`
15. Tune Level 16 undo penalty values — Commit: `Tune Level 16 undo penalty values`
16. Add help text for undo and redo — Commit: `Add help text for undo and redo`
17. Document undo/redo rules and limits — Commit: `Document undo/redo rules and limits`

---

## Level 17 – Audio & Feedback (Cross-Platform Best-Effort)

**Feature Enhancements**

- Optional sound cues (terminal bell) and richer feedback patterns.

**Code Architecture / Refactoring**

- Add `Feedback` module behind config.

**UI/UX Improvements**

- Sound toggle in settings; distinct cues for events.

**Game Mechanics**

- No new mechanics; reinforcement improves engagement.

**Tests & Bug Fixes**

- Ensure audio calls are no-ops when disabled.

**Documentation**

- Document supported terminals and sound limitations.

**Tasks (17)**

1. Add feedback configuration options — Commit: `Add feedback configuration options`
2. Add bell feedback for correct guess — Commit: `Add bell feedback for correct guess`
3. Add bell feedback for wrong guess — Commit: `Add bell feedback for wrong guess`
4. Add win/lose feedback cues — Commit: `Add win/lose feedback cues`
5. Add sound enabled toggle — Commit: `Add sound enabled toggle`
6. Add CLI flags for sound toggle — Commit: `Add CLI flags for sound toggle`
7. Add feedback for hint usage — Commit: `Add feedback for hint usage`
8. Add feedback for level up — Commit: `Add feedback for level up`
9. Suppress feedback in reduced motion mode — Commit: `Suppress feedback in reduced motion mode`
10. Add tests for feedback config gating — Commit: `Add tests for feedback config gating`
11. Add tests for sound CLI flags — Commit: `Add tests for sound CLI flags`
12. Add settings screen — Commit: `Add settings screen`
13. Persist settings to JSON — Commit: `Persist settings to JSON`
14. Load settings on startup — Commit: `Load settings on startup`
15. Polish feedback patterns for Level 17 — Commit: `Polish feedback patterns for Level 17`
16. Add documentation for sound feedback — Commit: `Add documentation for sound feedback`
17. Update README with settings options — Commit: `Update README with settings options`

---

## Level 18 – Daily Challenge Mode (Deterministic Word)

**Feature Enhancements**

- Daily challenge chooses a deterministic word per day + language/category.

**Code Architecture / Refactoring**

- Add `DailySeed` generator and `ChallengeResult` storage.

**UI/UX Improvements**

- Daily challenge screen with streak indicator.

**Game Mechanics**

- One attempt per day (configurable) with streak rewards.

**Tests & Bug Fixes**

- Test determinism across machines/timezones (UTC-based).

**Documentation**

- Document determinism rules and streak tracking.

**Tasks (17)**

1. Add daily challenge mode — Commit: `Add daily challenge mode`
2. Generate UTC-based daily seed — Commit: `Generate UTC-based daily seed`
3. Pick deterministic daily category — Commit: `Pick deterministic daily category`
4. Pick deterministic daily word — Commit: `Pick deterministic daily word`
5. Add daily challenge result model — Commit: `Add daily challenge result model`
6. Persist daily challenge results — Commit: `Persist daily challenge results`
7. Add daily streak calculation — Commit: `Add daily streak calculation`
8. Add daily challenge screen — Commit: `Add daily challenge screen`
9. Show last daily result summary — Commit: `Show last daily result summary`
10. Enforce one daily attempt per day — Commit: `Enforce one daily attempt per day`
11. Add tests for daily seed determinism — Commit: `Add tests for daily seed determinism`
12. Add tests for daily word selection — Commit: `Add tests for daily word selection`
13. Add tests for streak calculation — Commit: `Add tests for streak calculation`
14. Add shareable daily result summary — Commit: `Add shareable daily result summary`
15. Integrate daily mode with campaign unlocks — Commit: `Integrate daily mode with campaign unlocks`
16. Document daily challenge mode — Commit: `Document daily challenge mode`
17. Update README with daily challenge info — Commit: `Update README with daily challenge info`

---

## Level 19 – Achievements & Badges

**Feature Enhancements**

- Unlock achievements (streaks, no-hint wins, hard-mode clears).

**Code Architecture / Refactoring**

- Add rules-driven `AchievementEngine`.

**UI/UX Improvements**

- Banner-style unlock notification + achievements screen.

**Game Mechanics**

- Level 19 introduces achievement-based bonus points.

**Tests & Bug Fixes**

- Test achievement triggers and persistence.

**Documentation**

- Document achievement list and how to add new ones.

**Tasks (17)**

1. Add achievement identifiers — Commit: `Add achievement identifiers`
2. Add achievement model — Commit: `Add achievement model`
3. Persist achievements to JSON — Commit: `Persist achievements to JSON`
4. Add achievement evaluation engine — Commit: `Add achievement evaluation engine`
5. Add achievement for no-hint win — Commit: `Add achievement for no-hint win`
6. Add achievement for zero mistakes — Commit: `Add achievement for zero mistakes`
7. Add hard mode streak achievement — Commit: `Add hard mode streak achievement`
8. Add daily streak achievement — Commit: `Add daily streak achievement`
9. Add achievements screen — Commit: `Add achievements screen`
10. Add achievement unlock banner — Commit: `Add achievement unlock banner`
11. Add score bonus for achievements — Commit: `Add score bonus for achievements`
12. Add tests for achievement triggers — Commit: `Add tests for achievement triggers`
13. Add tests for achievement persistence — Commit: `Add tests for achievement persistence`
14. Localize achievement names and descriptions — Commit: `Localize achievement names and descriptions`
15. Add sorting and filtering for achievements — Commit: `Add sorting and filtering for achievements`
16. Tune achievement reward values — Commit: `Tune achievement reward values`
17. Document achievements and extension guide — Commit: `Document achievements and extension guide`

---

## Level 20 – Multiplayer Hotseat (Player vs Player)

**Feature Enhancements**

- Player 1 sets the word (hidden), Player 2 guesses; swap roles.

**Code Architecture / Refactoring**

- Add `GameMode` enum and mode-specific setup flows.

**UI/UX Improvements**

- Best-effort hidden input + clear screen; clear prompts and safety warnings.

**Game Mechanics**

- Level 20 adds rounds, turn-based scoring, and match winner.

**Tests & Bug Fixes**

- Test mode switching and score separation.

**Documentation**

- Document multiplayer rules and fairness notes.

**Tasks (17)**

1. Add `GameMode` enum — Commit: `Add GameMode enum`
2. Add multiplayer mode selection — Commit: `Add multiplayer mode selection`
3. Add secret word setup flow — Commit: `Add secret word setup flow`
4. Validate secret word input — Commit: `Validate secret word input`
5. Clear screen after secret word entry — Commit: `Clear screen after secret word entry`
6. Track scores for both players — Commit: `Track scores for both players`
7. Add round counter and role swapping — Commit: `Add round counter and role swapping`
8. Add multiplayer match win conditions — Commit: `Add multiplayer match win conditions`
9. Add multiplayer round recap — Commit: `Add multiplayer round recap`
10. Add configurable multiplayer rounds — Commit: `Add configurable multiplayer rounds`
11. Add tests for mode transitions — Commit: `Add tests for mode transitions`
12. Add tests for multiplayer scoring — Commit: `Add tests for multiplayer scoring`
13. Add tests for role swapping — Commit: `Add tests for role swapping`
14. Localize multiplayer UI strings — Commit: `Localize multiplayer UI strings`
15. Gate Level 20 behind campaign progress — Commit: `Gate Level 20 behind campaign progress`
16. Tune multiplayer scoring multipliers — Commit: `Tune multiplayer scoring multipliers`
17. Document hotseat multiplayer rules — Commit: `Document hotseat multiplayer rules`

---

## Level 21 – AI Opponent v1 (Race Mode)

**Feature Enhancements**

- AI guesses letters in parallel; player races to finish first.

**Code Architecture / Refactoring**

- Add `AiPlayer` with strategy interface.

**UI/UX Improvements**

- Show AI guesses and progress; optional speed setting.

**Game Mechanics**

- Level 21 adds “race” scoring and AI difficulty presets.

**Tests & Bug Fixes**

- Test AI never guesses invalid/repeated letters.

**Documentation**

- Document AI strategies and tuning.

**Tasks (17)**

1. Add AI strategy interface — Commit: `Add AI strategy interface`
2. Implement frequency-based AI strategy — Commit: `Implement frequency-based AI strategy`
3. Add AI guess cooldown — Commit: `Add AI guess cooldown`
4. Track AI guessed letters — Commit: `Track AI guessed letters`
5. Add race mode vs AI — Commit: `Add race mode vs AI`
6. Show AI progress in HUD — Commit: `Show AI progress in HUD`
7. Show AI guess log — Commit: `Show AI guess log`
8. Add AI difficulty presets — Commit: `Add AI difficulty presets`
9. Make AI use candidate filtering — Commit: `Make AI use candidate filtering`
10. Adjust scoring for AI race mode — Commit: `Adjust scoring for AI race mode`
11. Add tests for AI guess validity — Commit: `Add tests for AI guess validity`
12. Add tests for AI difficulty presets — Commit: `Add tests for AI difficulty presets`
13. Add tests for race win conditions — Commit: `Add tests for race win conditions`
14. Localize AI mode strings — Commit: `Localize AI mode strings`
15. Tune default AI speed values — Commit: `Tune default AI speed values`
16. Unlock AI race mode in campaign — Commit: `Unlock AI race mode in campaign`
17. Document AI race mode — Commit: `Document AI race mode and strategies`

---

## Level 22 – Power-Ups (Limited Use)

**Feature Enhancements**

- Add power-ups: “extra attempt”, “reveal vowel”, “freeze timer”.

**Code Architecture / Refactoring**

- Add `PowerUpEngine` with inventory and cooldowns.

**UI/UX Improvements**

- Power-up inventory display and activation prompts.

**Game Mechanics**

- Level 22 introduces power-up drops on streaks.

**Tests & Bug Fixes**

- Test stacking rules and cooldown enforcement.

**Documentation**

- Document power-ups and balance rules.

**Tasks (17)**

1. Add power-up types — Commit: `Add power-up types`
2. Add power-up inventory to state — Commit: `Add power-up inventory to state`
3. Implement extra attempt power-up — Commit: `Implement extra attempt power-up`
4. Implement reveal vowel power-up — Commit: `Implement reveal vowel power-up`
5. Implement freeze timer power-up — Commit: `Implement freeze timer power-up`
6. Add :power command for power-ups — Commit: `Add :power command for power-ups`
7. Display power-up inventory in HUD — Commit: `Display power-up inventory in HUD`
8. Add power-up drop rules based on streak — Commit: `Add power-up drop rules based on streak`
9. Enforce power-up cooldowns — Commit: `Enforce power-up cooldowns`
10. Adjust scoring for power-up usage — Commit: `Adjust scoring for power-up usage`
11. Add tests for power-up inventory — Commit: `Add tests for power-up inventory`
12. Add tests for cooldown enforcement — Commit: `Add tests for power-up cooldown enforcement`
13. Add tests for freeze timer behavior — Commit: `Add tests for freeze timer behavior`
14. Localize power-up UI strings — Commit: `Localize power-up UI strings`
15. Balance Level 22 power-up drop rates — Commit: `Balance Level 22 power-up drop rates`
16. Update Level 22 rules summary — Commit: `Update Level 22 rules summary`
17. Document power-ups and activation — Commit: `Document power-ups and activation`

---

## Level 23 – Analytics (Local) & Session Summary

**Feature Enhancements**

- Track guess accuracy, average time, hint usage, and per-category stats locally.

**Code Architecture / Refactoring**

- Add `StatsStore` with aggregation functions.

**UI/UX Improvements**

- Add session summary screen and lifetime stats screen.

**Game Mechanics**

- Level 23 introduces performance targets for bonus unlocks.

**Tests & Bug Fixes**

- Test stats aggregation math.

**Documentation**

- Document what’s tracked and how to reset it.

**Tasks (17)**

1. Add stats event model — Commit: `Add stats event model`
2. Log per-turn stats events — Commit: `Log per-turn stats events`
3. Aggregate guess accuracy metrics — Commit: `Aggregate guess accuracy metrics`
4. Aggregate round timing metrics — Commit: `Aggregate round timing metrics`
5. Aggregate hint usage metrics — Commit: `Aggregate hint usage metrics`
6. Aggregate performance by category — Commit: `Aggregate performance by category`
7. Persist stats to JSON store — Commit: `Persist stats to JSON store`
8. Add lifetime stats screen — Commit: `Add lifetime stats screen`
9. Add session summary screen — Commit: `Add session summary screen`
10. Add --reset-stats option — Commit: `Add --reset-stats option`
11. Add tests for accuracy aggregation — Commit: `Add tests for accuracy aggregation`
12. Add tests for time aggregation — Commit: `Add tests for time aggregation`
13. Add tests for hint aggregation — Commit: `Add tests for hint aggregation`
14. Localize stats UI strings — Commit: `Localize stats UI strings`
15. Add Level 23 performance targets — Commit: `Add Level 23 performance targets`
16. Add stats export to text — Commit: `Add stats export to text`
17. Document local analytics and reset options — Commit: `Document local analytics and reset options`

---

## Level 24 – Advanced Word Categories (Tags + Themed Events)

**Feature Enhancements**

- Add tags (e.g., “space”, “sports”) and themed playlists.

**Code Architecture / Refactoring**

- Add `TagIndex` for fast filtering.

**UI/UX Improvements**

- Filter UI for tags and “surprise me”.

**Game Mechanics**

- Level 24 introduces rotating themed events (weekly playlist).

**Tests & Bug Fixes**

- Test tag parsing and filtering.

**Documentation**

- Document tagging and playlist format.

**Tasks (17)**

1. Parse tags from word metadata — Commit: `Parse tags from word metadata`
2. Build tag index for fast filtering — Commit: `Build tag index for fast filtering`
3. Add tag filter UI — Commit: `Add tag filter UI`
4. Add surprise-me tag selection — Commit: `Add surprise-me tag selection`
5. Add themed playlist format — Commit: `Add themed playlist format`
6. Select weekly themed playlist — Commit: `Select weekly themed playlist`
7. Show weekly theme in UI — Commit: `Show weekly theme in UI`
8. Select words from themed playlists — Commit: `Select words from themed playlists`
9. Add tests for tag parsing — Commit: `Add tests for tag parsing`
10. Add tests for tag filtering — Commit: `Add tests for tag filtering`
11. Add tests for playlist selection — Commit: `Add tests for playlist selection`
12. Localize theme UI strings — Commit: `Localize theme UI strings`
13. Add themed word packs — Commit: `Add themed word packs`
14. Validate tag characters and length — Commit: `Validate tag characters and length`
15. Tune Level 24 theme bonus rules — Commit: `Tune Level 24 theme bonus rules`
16. Update Level 24 rules summary — Commit: `Update Level 24 rules summary`
17. Document tags and themed playlists — Commit: `Document tags and themed playlists`

---

## Level 25 – Challenge Modifiers (Fog, Noisy Input, Double Letters)

**Feature Enhancements**

- Add optional modifiers per level that change gameplay rules.

**Code Architecture / Refactoring**

- Add modifier pipeline applied to input/scoring/rendering.

**UI/UX Improvements**

- Show active modifiers with tooltips/help text.

**Game Mechanics**

- Level 25 introduces Fog of War and Double Trouble rounds.

**Tests & Bug Fixes**

- Test modifier composition and edge cases.

**Documentation**

- Document modifiers and how they affect fairness.

**Tasks (17)**

1. Add challenge modifier types — Commit: `Add challenge modifier types`
2. Add modifiers to campaign level config — Commit: `Add modifiers to campaign level config`
3. Implement fog of war modifier — Commit: `Implement fog of war modifier`
4. Implement noisy input modifier — Commit: `Implement noisy input modifier`
5. Implement double trouble modifier — Commit: `Implement double trouble modifier`
6. Apply modifiers in game loop — Commit: `Apply modifiers in game loop`
7. Adjust scoring for active modifiers — Commit: `Adjust scoring for active modifiers`
8. Show active modifiers in HUD — Commit: `Show active modifiers in HUD`
9. Add modifiers help screen — Commit: `Add modifiers help screen`
10. Add tests for fog modifier behavior — Commit: `Add tests for fog modifier behavior`
11. Add tests for double trouble guessing — Commit: `Add tests for double trouble guessing`
12. Add tests for modifier composition — Commit: `Add tests for modifier composition`
13. Localize modifier descriptions — Commit: `Localize modifier descriptions`
14. Tune Level 25 modifier balance — Commit: `Tune Level 25 modifier balance`
15. Show modifiers preview in level select — Commit: `Show modifiers preview in level select`
16. Update Level 25 rules summary — Commit: `Update Level 25 rules summary`
17. Document challenge modifiers — Commit: `Document challenge modifiers`

---

## Level 26 – Word Packs & Modding (Local Packs)

**Feature Enhancements**

- Load optional word pack bundles from `data/packs/` with validation.

**Code Architecture / Refactoring**

- Add pack manifest (`pack.json`) and pack loader.

**UI/UX Improvements**

- Pack selection UI and pack health checks.

**Game Mechanics**

- Level 26 introduces community packs and pack-based campaigns.

**Tests & Bug Fixes**

- Validate manifest schema and prevent path traversal.

**Documentation**

- Provide pack authoring guide.

**Tasks (17)**

1. Define word pack manifest schema — Commit: `Define word pack manifest schema`
2. Add pack loader module — Commit: `Add pack loader module`
3. Validate word pack manifest and files — Commit: `Validate word pack manifest and files`
4. Harden pack loader against path traversal — Commit: `Harden pack loader against path traversal`
5. Add core pack manifest — Commit: `Add core pack manifest`
6. Add word pack selection UI — Commit: `Add word pack selection UI`
7. Add pack health check output — Commit: `Add pack health check output`
8. Allow packs to contribute categories and tags — Commit: `Allow packs to contribute categories and tags`
9. Use pack words in candidate filtering — Commit: `Use pack words in candidate filtering`
10. Add tests for pack manifest parsing — Commit: `Add tests for pack manifest parsing`
11. Add tests for pack validation failures — Commit: `Add tests for pack validation failures`
12. Add tests for pack path traversal guard — Commit: `Add tests for pack path traversal guard`
13. Localize pack UI strings — Commit: `Localize pack UI strings`
14. Add sample community word pack — Commit: `Add sample community word pack`
15. Update Level 26 rules for pack selection — Commit: `Update Level 26 rules for pack selection`
16. Add word pack authoring guide — Commit: `Add word pack authoring guide`
17. Document word packs and modding — Commit: `Document word packs and modding`

---

## Level 27 – Hardcore Mode (Rule Overlays)

**Feature Enhancements**

- Add Hardcore mode: stricter penalties, limited hints/undos, harsher scoring.

**Code Architecture / Refactoring**

- Add `ModeRules` overlays applied on top of difficulty.

**UI/UX Improvements**

- Prominent warnings and confirmations before starting.

**Game Mechanics**

- Level 27 is Hardcore unlock with separate leaderboard channel.

**Tests & Bug Fixes**

- Test overlays don’t break existing rules.

**Documentation**

- Document Hardcore rules.

**Tasks (17)**

1. Add ModeRules overlay — Commit: `Add ModeRules overlay`
2. Add hardcore mode selection — Commit: `Add hardcore mode selection`
3. Reduce hint and undo budgets in hardcore — Commit: `Reduce hint and undo budgets in hardcore`
4. Increase wrong guess penalties in hardcore — Commit: `Increase wrong guess penalties in hardcore`
5. Add hardcore leaderboard partition — Commit: `Add hardcore leaderboard partition`
6. Add hardcore completion badge — Commit: `Add hardcore completion badge`
7. Add hardcore confirmation prompt — Commit: `Add hardcore confirmation prompt`
8. Show hardcore indicator in HUD — Commit: `Show hardcore indicator in HUD`
9. Add tests for ModeRules overlays — Commit: `Add tests for ModeRules overlays`
10. Add tests for hardcore scoring penalties — Commit: `Add tests for hardcore scoring penalties`
11. Add tests for hardcore hint/undo budgets — Commit: `Add tests for hardcore hint/undo budgets`
12. Localize hardcore mode strings — Commit: `Localize hardcore mode strings`
13. Tune Level 27 hardcore thresholds — Commit: `Tune Level 27 hardcore thresholds`
14. Add Level 27 rules summary — Commit: `Add Level 27 rules summary`
15. Unlock hardcore mode at Level 27 — Commit: `Unlock hardcore mode at Level 27`
16. Document hardcore mode rules — Commit: `Document hardcore mode rules`
17. Update README with hardcore mode — Commit: `Update README with hardcore mode`

---

## Level 28 – QA Hardening (Fuzz/Properties + Sanitizers)

**Feature Enhancements**

- Improve stability and correctness with broader automated checks.

**Code Architecture / Refactoring**

- Make core logic more pure and testable; reduce direct I/O.

**UI/UX Improvements**

- Better error messages and recovery flows.

**Game Mechanics**

- No new mechanics; reliability for final stretch.

**Tests & Bug Fixes**

- Add property tests and sanitizer build targets.

**Documentation**

- Document QA workflows.

**Tasks (17)**

1. Reduce I/O in core logic for testability — Commit: `Reduce I/O in core logic for testability`
2. Add randomized tests for word selection invariants — Commit: `Add randomized tests for word selection invariants`
3. Add property tests for scoring bounds — Commit: `Add property tests for scoring bounds`
4. Add tests for invalid input handling — Commit: `Add tests for invalid input handling`
5. Add tests for corrupted saves — Commit: `Add tests for corrupted saves`
6. Add sanitizer options in CMake — Commit: `Add sanitizer options in CMake`
7. Add CI sanitizer job — Commit: `Add CI sanitizer job`
8. Add clang-format configuration — Commit: `Add clang-format configuration`
9. Add CI formatting check — Commit: `Add CI formatting check`
10. Fix warnings under strict build flags — Commit: `Fix warnings under strict build flags`
11. Add --self-test mode — Commit: `Add --self-test mode`
12. Improve error messages for missing data — Commit: `Improve error messages for missing data`
13. Add tests for campaign rule table validity — Commit: `Add tests for campaign rule table validity`
14. Add tests for leaderboard sorting stability — Commit: `Add tests for leaderboard sorting stability`
15. Add QA and CI documentation — Commit: `Add QA and CI documentation`
16. Add Level 28 QA hardening notes — Commit: `Add Level 28 QA hardening notes`
17. Update README with QA workflows — Commit: `Update README with QA workflows`

---

## Level 29 – Season Mode (Rotating Rules + Limited-Time Rewards)

**Feature Enhancements**

- Add season definitions that rotate rulesets weekly/monthly with unique rewards.

**Code Architecture / Refactoring**

- Add `SeasonConfig` loader (JSON) and rule overlays.

**UI/UX Improvements**

- Season banner, reward preview, and season points display.

**Game Mechanics**

- Level 29 adds season points and season-only achievements.

**Tests & Bug Fixes**

- Test season config parsing and fallback.

**Documentation**

- Document season format and safety considerations.

**Tasks (17)**

1. Add SeasonConfig model — Commit: `Add SeasonConfig model`
2. Add default season configuration — Commit: `Add default season configuration`
3. Load season configuration from JSON — Commit: `Load season configuration from JSON`
4. Apply season rule overlays — Commit: `Apply season rule overlays`
5. Track season points — Commit: `Track season points`
6. Persist season progress — Commit: `Persist season progress`
7. Show season banner in main menu — Commit: `Show season banner in main menu`
8. Add season reward preview screen — Commit: `Add season reward preview screen`
9. Add season-only achievements — Commit: `Add season-only achievements`
10. Add tests for season config parsing — Commit: `Add tests for season config parsing`
11. Add tests for season rule overlays — Commit: `Add tests for season rule overlays`
12. Localize season UI strings — Commit: `Localize season UI strings`
13. Fallback gracefully when season config missing — Commit: `Fallback gracefully when season config missing`
14. Tune Level 29 season point rules — Commit: `Tune Level 29 season point rules`
15. Add Level 29 rules summary — Commit: `Add Level 29 rules summary`
16. Document season mode and config format — Commit: `Document season mode and config format`
17. Update README with season mode — Commit: `Update README with season mode`

---

## Level 30 – Full Polish (Balance, Performance, Packaging)

**Feature Enhancements**

- Final balancing pass across all levels and modes; improve startup speed.

**Code Architecture / Refactoring**

- Consolidate configuration; remove duplication; tighten interfaces.

**UI/UX Improvements**

- Smooth transitions, consistent style, and cohesive theme.

**Game Mechanics**

- Final boss level: strict rules, rare words, limited resources, big rewards.

**Tests & Bug Fixes**

- Add end-to-end test scenarios and regression suite.

**Documentation**

- Finalize README, add screenshots (terminal captures), and release notes.

**Tasks (17)**

1. Profile and optimize word pack loading — Commit: `Profile and optimize word pack loading`
2. Cache parsed word lists for faster startup — Commit: `Cache parsed word lists for faster startup`
3. Refactor config loading into one module — Commit: `Refactor config loading into one module`
4. Deduplicate rule constants across levels — Commit: `Deduplicate rule constants across levels`
5. Balance scoring and difficulty across all levels — Commit: `Balance scoring and difficulty across all levels`
6. Add Level 30 boss modifiers — Commit: `Add Level 30 boss modifiers`
7. Add end-to-end scenario tests — Commit: `Add end-to-end scenario tests`
8. Add regression tests for reported bugs — Commit: `Add regression tests for reported bugs`
9. Polish --help output and command docs — Commit: `Polish --help output and command docs`
10. Add CPack packaging configuration — Commit: `Add CPack packaging configuration`
11. Add release build presets — Commit: `Add release build presets`
12. Upload CI build artifacts — Commit: `Upload CI build artifacts`
13. Add docs for capturing terminal screenshots — Commit: `Add docs for capturing terminal screenshots`
14. Finalize README feature list — Commit: `Finalize README feature list`
15. Add player guide for all 30 levels — Commit: `Add player guide for all 30 levels`
16. Document architecture and module overview — Commit: `Document architecture and module overview`
17. Add Level 30 release notes and changelog — Commit: `Add Level 30 release notes and changelog`
