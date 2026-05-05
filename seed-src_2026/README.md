================================================================================
                     F14 - DOCUMENTACIÓN DEL PROYECTO
                          PPROG 2025/2026 - Castle
================================================================================
────────────────────────────────────────────────────────────────────────────────
(a) DESCRIPCIÓN DEL PROYECTO
────────────────────────────────────────────────────────────────────────────────
Castle es un juego de aventura textual por turnos desarrollado en C. El jugador
(o jugadores) exploran un castillo infestado de enemigos con el objetivo de
llegar al Salón del Chef Michelin y derrotar al jefe final: el Fat Michelin
Chef. Para llegar hasta él, es necesario superar varios jefes intermedios,
resolver puzzles de llaves y puertas, y reclutar hasta 6 aliados que combaten
a tu lado.
El juego dispone de dos modos:
  · MODO UN JUGADOR (castle1p.dat)
    Un único jugador, el Chef, recorre el castillo solo. El objetivo es matar
    al jefe final habiendo reclutado el mayor número posible de aliados. La
    puntuación final depende de cuántos aliados sobreviven hasta el final.
  · MODO MULTIJUGADOR (castle2p.dat)
    Dos jugadores (Chef y Grandma) se turnan sus acciones en el mismo mapa,
    cooperando para derrotar al jefe final. Los aliados se reparten entre los
    dos jugadores y al final se suman todos para calcular la puntuación conjunta.
    Al ser cooperativo, no se trata de competir sino de coordinarse para
    conseguir la victoria perfecta.
CONDICIÓN DE VICTORIA:
  El juego termina cuando el Fat Michelin Chef es derrotado en su habitación
  (Michelin Chef's Room). Dependiendo del número total de aliados vivos
  (propios en 1p, suma de ambos jugadores en 2p) se obtiene:
    6 aliados  →  VICTORIA PERFECTA  (Bread, Lettuce, Cheese, Tomato, Bacon, Ham)
    3-5 aliados →  Victoria normal
    1-2 aliados →  Victoria ajustada
    0 aliados  →  Victoria al límite
  Si algún jugador muere (HP llega a 0), la partida termina en GAME OVER.
LOS 6 ALIADOS (ingredientes):
  1. Bread   (=)  ·  Entry (inicio)
  2. Lettuce \M/  ·  Crates (1p) / Crates (2p)
  3. Cheese  (:)  ·  Kitchen
  4. Tomato  (^)  ·  Fridge
  5. Bacon   /=/  ·  Dining Room
  6. Ham    (>3   ·  Garden
Cada aliado reclutado aumenta el daño de ataque en 10 puntos. Un jugador con
los 6 aliados inflige 70 de daño por ataque.
────────────────────────────────────────────────────────────────────────────────
(b) MANUAL DE USO
────────────────────────────────────────────────────────────────────────────────
COMPILACIÓN
  Desde el directorio raíz del proyecto:
    make
  Esto genera el ejecutable "castle" en el directorio raíz.
  Para limpiar objetos y ejecutable:
    make clean
EJECUCIÓN
  Forma general:
    ./castle <fichero_de_datos> [opciones]
  Ejemplos:
    # Modo 1 jugador (normal)
    ./castle castle1p.dat
    # Modo multijugador (normal)
    ./castle castle2p.dat
    # Con log de comandos (guarda un registro en fichero)
    ./castle castle1p.dat -l log/partida.txt
    # Modo determinista (sin aleatoriedad, los ataques siempre tienen éxito)
    ./castle castle1p.dat -d
    # Determinista + log
    ./castle castle1p.dat -d -l log/partida.txt
  Nota: el flag -d desactiva las game_rules (eventos aleatorios) y hace que
  los ataques siempre hagan daño fijo (10 × número de atacantes).
COMANDOS DISPONIBLES
  ┌──────────────────────┬───────┬─────────────────────────────────────────┐
  │ Comando completo     │ Corto │ Descripción                             │
  ├──────────────────────┼───────┼─────────────────────────────────────────┤
  │ move <dirección>     │ m     │ Mover al jugador. Direcciones:          │
  │                      │       │ n(norte) s(sur) e(este) w(oeste)        │
  │                      │       │ u(arriba) d(abajo)                      │
  ├──────────────────────┼───────┼─────────────────────────────────────────┤
  │ take <objeto>        │ t     │ Recoger un objeto del suelo.            │
  │                      │       │ Algunos objetos requieren tener una     │
  │                      │       │ llave concreta en el inventario.        │
  ├──────────────────────┼───────┼─────────────────────────────────────────┤
  │ drop <objeto>        │ d     │ Soltar un objeto al suelo.              │
  ├──────────────────────┼───────┼─────────────────────────────────────────┤
  │ attack <personaje>   │ a     │ Atacar a un enemigo. El jugador y todos │
  │                      │       │ sus aliados atacan juntos.              │
  ├──────────────────────┼───────┼─────────────────────────────────────────┤
  │ chat <personaje>     │ c     │ Hablar con un personaje amistoso.       │
  ├──────────────────────┼───────┼─────────────────────────────────────────┤
  │ inspect <objeto>     │ i     │ Inspeccionar un objeto para ver su      │
  │                      │       │ descripción detallada.                  │
  ├──────────────────────┼───────┼─────────────────────────────────────────┤
  │ recruit <personaje>  │ r     │ Reclutar a un aliado para que te siga.  │
  ├──────────────────────┼───────┼─────────────────────────────────────────┤
  │ abandon <personaje>  │ ab    │ Dejar de llevar a un aliado.            │
  ├──────────────────────┼───────┼─────────────────────────────────────────┤
  │ use <obj> over <chr> │ u     │ Usar un objeto sobre un personaje u     │
  │                      │       │ objeto (p.ej. curar a un aliado).       │
  ├──────────────────────┼───────┼─────────────────────────────────────────┤
  │ open <enlace> <dir>  │ o     │ Abrir una puerta o paso bloqueado       │
  │   with <herramienta> │       │ usando la herramienta correcta.         │
  │                      │       │ Ej: open pipes north with crowbar       │
  ├──────────────────────┼───────┼─────────────────────────────────────────┤
  │ exit                 │ e     │ Salir del juego.                        │
  └──────────────────────┴───────┴─────────────────────────────────────────┘
MECÁNICAS Y NOTAS IMPORTANTES
  · ATAQUES Y DAÑO
    Cada ataque inflige 10 × (1 + nº_aliados) de daño al enemigo.
    En modo aleatorio (normal), hay un 50% de probabilidad de que el enemigo
    contraataque al jugador o a un aliado por 10 HP en lugar de recibir daño.
  · PUERTAS BLOQUEADAS
    Hay tres pasos bloqueados que requieren herramientas específicas:
      - Pipes North     → necesita Crowbar       (requiere Silver Key para tomarla)
      - Chef Bathroom E → necesita Hammer        (requiere Rusty Key para tomarlo)
      - Backyard South  → necesita Screwdriver   (requiere Master Key para tomarlo)
  · LLAVES Y COFRES
    Los objetos dentro de cofres sólo se pueden recoger si se tiene la llave
    correcta en el inventario. No hace falta un comando especial: simplemente
    ejecuta "take <objeto>" y el juego verifica si tienes la llave.
  · EVENTOS ALEATORIOS (game_rules)
    En modo normal, cada turno pueden ocurrir eventos aleatorios:
      - Un enemigo en la sala ataca al jugador (10% probabilidad)
      - Un aliado desaparece aleatoriamente (5%)
      - El jugador recibe críticas negativas [-5 a -25 HP] (5%)
      - Un objeto se teletransporta a otra sala (10%)
      - La mochila llena inflige daño pasivo [-1 a -5 HP]
      - En la sala del jefe final, daño de fuego continuo cada turno
  · JEFES (BOSSES)
    Al morir un jefe, sus puertas asociadas se abren automáticamente.
    Los tres jefes intermedios son: Cockroach King, Ratatouille King y, como
    jefe final, el Fat Michelin Chef.
  · MODO MULTIJUGADOR
    Los turnos se alternan entre P1 (Chef) y P2 (Grandma). Ambos comparten
    el mismo mapa. Los aliados sólo pueden seguir a un jugador a la vez.
    Los objetos recogidos son del inventario de cada jugador por separado.
    Al final de la partida, la puntuación se calcula sumando los aliados
    de ambos jugadores.
────────────────────────────────────────────────────────────────────────────────
(c) MAPA DEL JUEGO
────────────────────────────────────────────────────────────────────────────────
  El mapa es idéntico en modo 1 jugador y multijugador (mismas salas y
  conexiones). Las diferencias entre modos están en la posición de algunos
  objetos y en los HP de los enemigos.
  LEYENDA:
    [Sala]         Habitación
    ─── / │        Conexión abierta
    ═══ / ║        Conexión BLOQUEADA (requiere herramienta)
    (*)            Herramienta necesaria indicada junto al paso
    ♦ Nombre       Aliado (aliado) en esa sala
    ✖ Nombre       Enemigo en esa sala
    ★ Nombre       JEFE en esa sala
                         [54 Crates]
                         ♦ Lettuce
                              │ N/S
                              │
   [53 Pipes] ─── E/W ─── [52 Barrels]
   ✖ Spider                 ✖ Cockroach          [51 Entry]
        │                                         ♦ Bread
        │ N  ← BLOQUEADO (crowbar)
        ║ (crowbar necesita Silver Key)
        │
   [55 Cockroach King's Taqueria]
   ★ Cockroach King
        │ Up/Down
        │
   [56 Corridor]
   ✖ Ratatta
        │ N/S
        │
   [58 Fridge] ─── W/E ─── [57 Kitchen] ─── N/S ─── [59 Chef Bathroom]
   ♦ Tomato                  ♦ Cheese                 ✖ Raticate
   ◈ Master Key                                              │ E ← BLOQUEADO (hammer)
                                                             ║ (hammer necesita Rusty Key)
                                                             │
                                                    [510 Ratatouille King's Den]
                                                    ★ Ratatouille King
                                                             │ Up/Down
                                                             │
   [512 Bathroom] ─── W/E ─── [511 Dining Room] ─── S/N ─── [513 Backyard]
   ✖ Dishwasher               ♦ Bacon                       ✖ Master Chef
                                                             │ E/W
                                                        [514 Garden]
                                                        ♦ Ham
                                                             │ S ← BLOQUEADO (screwdriver)
                                                             ║ (screwdriver necesita Master Key)
                                                             │
                                                    [515 Michelin Chef's Room]
                                                    ★★ FAT MICHELIN CHEF (FINAL BOSS)
  OBJETOS CLAVE Y SUS POSICIONES:
    Modo 1 jugador (castle1p.dat):
      Silver Key    → Crates (54)       [libre]
      Rusty Key     → Barrels (52)      [libre]
      Crowbar       → Barrels (52)      [necesita Silver Key en inventario]
      Hammer        → CK Taqueria (55)  [necesita Rusty Key en inventario]
      Oven Protec.  → Corridor (56)     [libre]
      Master Key    → Fridge (58)       [libre]
      Screwdriver   → Garden (514)      [necesita Master Key en inventario]
      First Aid Kit → Dining Room (511) [necesita Master Key en inventario]
      Energy Drink  → Corridor (56)     [libre]
      Fresh Apple   → Barrels (52)      [libre]
    Modo multijugador (castle2p.dat):
      Silver Key    → Barrels (52)      [libre]   ← diferente al 1p
      Rusty Key     → Corridor (56)     [libre]   ← diferente al 1p
      (resto de objetos en la misma posición que en 1p)
  RESUMEN DE PUERTAS BLOQUEADAS (ambos modos):
    Pipes North          (53 → 55)  →  open pipes north with crowbar
    Chef Bathroom East   (59 → 510) →  open chef bathroom east with hammer
    Backyard South       (513 → 515)→  open backyard south with small screwdriver
────────────────────────────────────────────────────────────────────────────────
(d) PRUEBAS DE JUEGO - WALKTHROUGH ÓPTIMO
────────────────────────────────────────────────────────────────────────────────
  Objetivo: derrotar al jefe final reclutando los 6 aliados en el mínimo
  número de movimientos posible, sin comandos innecesarios.
  Daño de ataque: (1 + nº_aliados) × 10 HP por ataque.
  En modo -d (determinista) siempre se hace daño (sin contraataques).
════════════════════════════════════════════════════════════════════════════════
  (d.1) MODO 1 JUGADOR  ─  castle1p.dat
════════════════════════════════════════════════════════════════════════════════
  Inicio: sala Entry (51) · Daño inicial: 10 · HP: 100
  ─── ENTRY (51) ─────────────────────────────────────────────────────────────
  1.  recruit bread
        → Bread se une. Daño: 20.
  ─── BARRELS (52) ────────────────────────────────────────────────────────────
  2.  move north
  3.  attack cockroach
        → Cockroach: 20 HP → 1 ataque (20 dmg). Muerto.
  4.  take rusty key
  5.  take fresh apple
  ─── CRATES (54) ─────────────────────────────────────────────────────────────
  6.  move north
  7.  take silver key
  8.  recruit lettuce
        → Lettuce se une. Daño: 30.
  ─── BARRELS (52) ────────────────────────────────────────────────────────────
  9.  move south
  10. take crowbar
        [La Silver Key en el inventario permite cogerlo del cofre]
  ─── PIPES (53) ──────────────────────────────────────────────────────────────
  11. move east
  12. attack spider
  13. attack spider
        → Spider: 40 HP → 2 ataques (30 dmg/ataque). Muerto.
  14. open pipes north with crowbar
        → Paso norte desbloqueado.
  ─── COCKROACH KING'S TAQUERIA (55) ──────────────────────────────────────────
  15. move north
  16. take hammer
        [La Rusty Key en el inventario permite cogerlo del cofre]
  17. attack cockroach king
  18. attack cockroach king
  19. attack cockroach king
        → Cockroach King: 80 HP → 3 ataques (30 dmg/ataque). Muerto.
        [Jefe muerto: las puertas asociadas se abren automáticamente]
  ─── CORRIDOR (56) ───────────────────────────────────────────────────────────
  20. move up
  21. take oven protection
  22. take energy drink
  23. attack ratatta
  24. attack ratatta
        → Ratatta: 40 HP → 2 ataques (30 dmg/ataque). Muerto.
  ─── KITCHEN (57) ────────────────────────────────────────────────────────────
  25. move north
  26. recruit cheese
        → Cheese se une. Daño: 40.
  27. take sizzling tray
        [La Oven Protection en el inventario permite cogerlo]
  ─── FRIDGE (58) ─────────────────────────────────────────────────────────────
  28. move west
  29. recruit tomato
        → Tomato se une. Daño: 50.
  30. take master key
  ─── KITCHEN (57) → CHEF BATHROOM (59) ──────────────────────────────────────
  31. move east
  32. move north
  33. attack raticate
        → Raticate: 50 HP → 1 ataque (50 dmg). Muerto.
  34. open chef bathroom east with hammer
        → Paso este desbloqueado.
  ─── RATATOUILLE KING'S DEN (510) ────────────────────────────────────────────
  35. move east
  36. attack ratatouille king
  37. attack ratatouille king
  38. attack ratatouille king
        → Ratatouille King: 120 HP → 3 ataques (50 dmg/ataque). Muerto.
        [Jefe muerto: las puertas asociadas se abren automáticamente]
  ─── DINING ROOM (511) ───────────────────────────────────────────────────────
  39. move up
  40. recruit bacon
        → Bacon se une. Daño: 60.
  41. take first aid kit
        [La Master Key en el inventario permite cogerlo del cofre]
  ─── BACKYARD (513) ──────────────────────────────────────────────────────────
  42. move south
  43. attack master chef
  44. attack master chef
        → Master Chef: 70 HP → 2 ataques (60 dmg/ataque). Muerto.
  ─── GARDEN (514) ────────────────────────────────────────────────────────────
  45. move east
  46. recruit ham
        → Ham se une. Daño: 70. *** LOS 6 ALIADOS RECLUTADOS ***
  47. take small screwdriver
        [La Master Key en el inventario permite cogerlo del cofre]
  ─── BACKYARD (513) → MICHELIN CHEF'S ROOM (515) ─────────────────────────────
  48. move west
  49. open backyard south with small screwdriver
        → Paso sur desbloqueado. Acceso al jefe final.
  50. move south
  ─── MICHELIN CHEF'S ROOM (515) ── JEFE FINAL ────────────────────────────────
  51. attack fat michelin chef
  52. attack fat michelin chef
  53. attack fat michelin chef
  54. attack fat michelin chef
  55. attack fat michelin chef
        → Fat Michelin Chef: 350 HP → 5 ataques (70 dmg/ataque). Muerto.
  ════════════════════════════════════════════════════════════
   VICTORIA PERFECTA · 6/6 aliados · 55 comandos en total
   Aliados: Bread · Lettuce · Cheese · Tomato · Bacon · Ham
  ════════════════════════════════════════════════════════════
════════════════════════════════════════════════════════════════════════════════
  (d.2) MODO MULTIJUGADOR  ─  castle2p.dat
════════════════════════════════════════════════════════════════════════════════
  Diferencias respecto al modo 1p:
    · Silver Key: Barrels (52) en vez de Crates (54)
    · Rusty Key:  Corridor (56) en vez de Barrels (52)
    · Cockroach King HP: 70  ·  Ratatouille King HP: 90  ·  Jefe final HP: 200
  Reparto de aliados:
    P1 (Chef)   →  Bread · Cheese · Tomato · Bacon    (4 aliados)
    P2 (Grandma)→  Lettuce · Ham                      (2 aliados)
    TOTAL       →  6 aliados = VICTORIA PERFECTA
  Los turnos se alternan: primero actúa P1 y luego P2 en cada ronda.
  Inicio: ambos en Entry (51).
  ─── ENTRY (51) ─────────────────────────────────────────────────────────────
  T1  P1: recruit bread
            → Bread sigue a P1. P1 daño: 20.
  T1  P2: move north
            → P2 en Barrels (52).
  ─── BARRELS (52) ────────────────────────────────────────────────────────────
  T2  P1: move north
            → P1 en Barrels (52). Ambos en (52).
  T2  P2: take silver key
            [Silver Key está en Barrels en modo 2p]
  T3  P1: attack cockroach
            → Cockroach: 20 HP. P1+Bread = 20 dmg. Muerto.
  T3  P2: take crowbar
            [Tiene Silver Key → puede cogerlo del cofre]
  T4  P1: take fresh apple
  T4  P2: move north
            → P2 en Crates (54).
  ─── CRATES (54) ─────────────────────────────────────────────────────────────
  T5  P1: move north
            → P1 en Crates (54). Ambos en (54).
  T5  P2: recruit lettuce
            → Lettuce sigue a P2. P2 daño: 20.
  ─── BARRELS (52) → PIPES (53) ───────────────────────────────────────────────
  T6  P1: move south
  T6  P2: move south
            → Ambos en Barrels (52).
  T7  P1: move east
  T7  P2: move east
            → Ambos en Pipes (53).
  ─── PIPES (53) ──────────────────────────────────────────────────────────────
  T8  P1: attack spider
            → Spider: 40 HP. P1+Bread = 20 dmg → 20 HP restantes.
  T8  P2: attack spider
            → P2+Lettuce = 20 dmg → Spider muerto.
  T9  P1: take bottle of water
            [No hay nada crítico que hacer, recoge item menor]
  T9  P2: open pipes north with crowbar
            → Paso norte desbloqueado.
  ─── COCKROACH KING'S TAQUERIA (55) ──────────────────────────────────────────
  T10 P1: move north
  T10 P2: move north
            → Ambos en (55).
  T11 P1: attack cockroach king
            → CK: 70 HP. P1+Bread = 20 dmg → 50 HP.
  T11 P2: attack cockroach king
            → P2+Lettuce = 20 dmg → 30 HP.
  T12 P1: attack cockroach king
            → 20 dmg → 10 HP.
  T12 P2: attack cockroach king
            → 20 dmg → Muerto.
            [Jefe muerto: puertas se abren]
  ─── CORRIDOR (56) ───────────────────────────────────────────────────────────
  T13 P1: move up
  T13 P2: move up
            → Ambos en (56).
  T14 P1: take oven protection
  T14 P2: take rusty key
            [Rusty Key está en Corridor en modo 2p]
  T15 P1: attack ratatta
            → Ratatta: 40 HP. P1+Bread = 20 dmg → 20 HP.
  T15 P2: attack ratatta
            → P2+Lettuce = 20 dmg → Muerto.
  T16 P1: take energy drink
  T16 P2: move down
            → P2 baja a CK Taqueria (55) a buscar el hammer.
  ─── P2 RECOGE HAMMER / P1 AVANZA ────────────────────────────────────────────
  T17 P1: move north
            → P1 en Kitchen (57).
  T17 P2: take hammer
            [P2 tiene Rusty Key → puede cogerlo del cofre en (55)]
  T18 P1: recruit cheese
            → Cheese sigue a P1. P1 daño: 30.
  T18 P2: move up
            → P2 en Corridor (56).
  T19 P1: move west
            → P1 en Fridge (58).
  T19 P2: move north
            → P2 en Kitchen (57).
  ─── FRIDGE (58) / KITCHEN (57) ──────────────────────────────────────────────
  T20 P1: recruit tomato
            → Tomato sigue a P1. P1 daño: 40.
  T20 P2: move north
            → P2 en Chef Bathroom (59).
  T21 P1: take master key
  T21 P2: attack raticate
            → Raticate: 50 HP. P2+Lettuce = 20 dmg → 30 HP.
  ─── CHEF BATHROOM (59) ──────────────────────────────────────────────────────
  T22 P1: move east
            → P1 en Kitchen (57).
  T22 P2: attack raticate
            → 20 dmg → 10 HP.
  T23 P1: move north
            → P1 en Chef Bathroom (59).
  T23 P2: attack raticate
            → 20 dmg → Muerto.
  T24 P1: [P1 llega a (59)]
            attack raticate → Raticate ya muerto. P1 no hace nada útil aquí.
            (o simplemente move east si el raticate ya está muerto)
  T24 P2: open chef bathroom east with hammer
            → Paso este desbloqueado.
  T25 P1: move east
  T25 P2: move east
            → Ambos en Ratatouille King's Den (510).
  ─── RATATOUILLE KING'S DEN (510) ────────────────────────────────────────────
  T26 P1: attack ratatouille king
            → RK: 90 HP. P1+Bread+Cheese+Tomato = 40 dmg → 50 HP.
  T26 P2: attack ratatouille king
            → P2+Lettuce = 20 dmg → 30 HP.
  T27 P1: attack ratatouille king
            → 40 dmg → Ratatouille King muerto.
            [Jefe muerto: puertas se abren]
  T27 P2: take venomous bottle
  ─── DINING ROOM (511) ───────────────────────────────────────────────────────
  T28 P1: move up
  T28 P2: move up
            → Ambos en (511).
  T29 P1: recruit bacon
            → Bacon sigue a P1. P1 daño: 50.
  T29 P2: move south
            → P2 en Backyard (513).
  T30 P1: take first aid kit
            [Tiene Master Key → puede cogerlo]
  T30 P2: attack master chef
            → MC: 70 HP. P2+Lettuce = 20 dmg → 50 HP.
  ─── BACKYARD (513) ──────────────────────────────────────────────────────────
  T31 P1: move south
            → P1 en Backyard (513).
  T31 P2: attack master chef
            → 20 dmg → 30 HP.
  T32 P1: attack master chef
            → P1+Bread+Cheese+Tomato+Bacon = 50 dmg → Master Chef muerto.
  T32 P2: move east
            → P2 en Garden (514).
  ─── GARDEN (514) ────────────────────────────────────────────────────────────
  T33 P1: move east
            → P1 en Garden (514). Ambos en (514).
  T33 P2: recruit ham
            → Ham sigue a P2. P2 daño: 30. *** LOS 6 ALIADOS RECLUTADOS ***
  T34 P1: take small screwdriver
            [Tiene Master Key → puede cogerlo del cofre]
  T34 P2: take hot chicken soup
  ─── BACKYARD (513) → MICHELIN CHEF'S ROOM (515) ─────────────────────────────
  T35 P1: move west
  T35 P2: move west
            → Ambos en Backyard (513).
  T36 P1: open backyard south with small screwdriver
            → Paso sur desbloqueado. Acceso al jefe final.
  T36 P2: move south
            → P2 en Michelin Chef's Room (515).
  ─── MICHELIN CHEF'S ROOM (515) ── JEFE FINAL ────────────────────────────────
  T37 P1: move south
            → P1 en (515). Ambos frente al jefe final.
  T37 P2: attack fat michelin chef
            → FMC: 200 HP. P2+Lettuce+Ham = 30 dmg → 170 HP.
  T38 P1: attack fat michelin chef
            → P1+Bread+Cheese+Tomato+Bacon = 50 dmg → 120 HP.
  T38 P2: attack fat michelin chef
            → 30 dmg → 90 HP.
  T39 P1: attack fat michelin chef
            → 50 dmg → 40 HP.
  T39 P2: attack fat michelin chef
            → 30 dmg → 10 HP.
  T40 P1: attack fat michelin chef
            → 50 dmg → Fat Michelin Chef MUERTO.
  ════════════════════════════════════════════════════════════
   VICTORIA PERFECTA · 6/6 aliados · 40 turnos (80 acciones)
   P1: Bread · Cheese · Tomato · Bacon      (4 aliados)
   P2: Lettuce · Ham                        (2 aliados)
   Total: 6 aliados = puntuación perfecta
  ════════════════════════════════════════════════════════════
────────────────────────────────────────────────────────────────────────────────
  FIN DE LA DOCUMENTACIÓN F14
────────────────────────────────────────────────────────────────────────────────