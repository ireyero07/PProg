================================================================================
                     F14 - DOCUMENTACION DEL PROYECTO
                          PPROG 2025/2026 - Castle
================================================================================


--------------------------------------------------------------------------------
(a) DESCRIPCION DEL PROYECTO
--------------------------------------------------------------------------------

Castle es un juego de aventura textual por turnos desarrollado en C. El jugador
(o jugadores) exploran un castillo infestado de enemigos con el objetivo de
llegar al Salon del Chef Michelin y derrotar al jefe final: el Fat Michelin
Chef. Para llegar hasta el, es necesario superar varios jefes intermedios,
resolver puzzles de llaves y puertas, y reclutar hasta 6 aliados que combaten
a tu lado.

El juego dispone de dos modos:

  · MODO UN JUGADOR (castle1p.dat)
    Un unico jugador, el Chef, recorre el castillo solo. El objetivo es matar
    al jefe final habiendo reclutado el mayor numero posible de aliados. La
    puntuacion final depende de cuantos HP totales tienen los aliados que
    sobreviven hasta el final.

  · MODO MULTIJUGADOR (castle2p.dat)
    Dos jugadores (Chef y Grandma) se turnan sus acciones en el mismo mapa,
    cooperando para derrotar al jefe final. Los aliados se reparten entre los
    dos jugadores y al final se suman todos para calcular la puntuacion conjunta.
    Al ser cooperativo, no se trata de competir sino de coordinarse para
    conseguir la victoria perfecta.

CONDICION DE VICTORIA:
  El juego termina cuando el Fat Michelin Chef es derrotado en su habitacion
  (Michelin Chef's Room). La puntuacion final es la suma total de HP de todos
  los aliados vivos en ese momento (propios en 1p, suma de ambos jugadores en 2p):

    6 aliados con HP alto  -->  VICTORIA PERFECTA
    3-5 aliados            -->  Victoria normal
    1-2 aliados            -->  Victoria ajustada
    0 aliados              -->  Victoria al limite

  Si algun jugador muere (HP llega a 0), la partida termina en DERROTA.

LOS 6 ALIADOS (ingredientes):
  1. Bread   (=)  ·  Entry (inicio)
  2. Lettuce \\f[M]/  ·  Crates
  3. Cheese  (:)  ·  Kitchen
  4. Tomato  (^)  ·  Fridge
  5. Bacon   /=/  ·  Dining Room
  6. Ham    (>3   ·  Garden

Cada aliado reclutado aumenta el dano de ataque en 10 puntos. Un jugador con
los 6 aliados inflige 70 de dano por ataque.


--------------------------------------------------------------------------------
(b) MANUAL DE USO
--------------------------------------------------------------------------------

COMPILACION
  Desde el directorio raiz del proyecto:

    make

  Esto genera el ejecutable "castle" en el directorio raiz.

  Para limpiar objetos y ejecutable:

    make clean

EJECUCION
  Forma general:

    ./castle &lt;fichero_de_datos&gt; [opciones]

  Ejemplos:

    # Modo 1 jugador (normal)
    ./castle castle1p.dat

    # Modo multijugador (normal)
    ./castle castle2p.dat

    # Con log de comandos (guarda un registro en fichero)
    ./castle castle1p.dat -l log/partida.txt

    # Modo determinista (sin aleatoriedad, los ataques siempre tienen exito)
    ./castle castle1p.dat -d

    # Determinista + log
    ./castle castle1p.dat -d -l log/partida.txt

  Nota: el flag -d desactiva las game_rules (eventos aleatorios) y hace que
  los ataques siempre hagan dano fijo (10 x numero de atacantes).

COMANDOS DISPONIBLES
  +-----------------------+-------+-----------------------------------------+
  | Comando completo      | Corto | Descripcion                             |
  +-----------------------+-------+-----------------------------------------+
  | move &lt;direccion&gt;      | m     | Mover al jugador. Direcciones:          |
  |                       |       | n(norte) s(sur) e(este) w(oeste)        |
  |                       |       | u(arriba) d(abajo)                      |
  +-----------------------+-------+-----------------------------------------+
  | take &lt;objeto&gt;         | t     | Recoger un objeto del suelo.            |
  |                       |       | Algunos objetos requieren tener una     |
  |                       |       | llave concreta en el inventario.        |
  +-----------------------+-------+-----------------------------------------+
  | drop &lt;obj&gt;         | d     | Soltar un objeto al suelo.              |
  +-----------------------+-------+-----------------------------------------+
  | attack &lt;chr&gt;    | a     | Atacar a un enemigo. El jugador y todos |
  |                       |       | sus aliados atacan juntos.              |
  +-----------------------+-------+-----------------------------------------+
  | chat &lt;chr&gt;      | c     | Hablar con un personaje amistoso.       |
  +-----------------------+-------+-----------------------------------------+
  | inspect &lt;obj&gt;      | i     | Inspeccionar un objeto para ver su      |
  |                       |       | descripcion detallada.                  |
  +-----------------------+-------+-----------------------------------------+
  | recruit &lt;chr&gt;   | r     | Reclutar a un aliado para que te siga.  |
  +-----------------------+-------+-----------------------------------------+
  | abandon &lt;chr&gt;   | ab    | Dejar de llevar a un aliado.            |
  +-----------------------+-------+-----------------------------------------+
  | use &lt;obj&gt;             | u     | Usar un objeto de salud: lo consume y   |
  |  [over &lt;obj&gt;]         |       | aplica sus HP al jugador. Si se indica  |
  |                       |       | un aliado, los HP van a ese personaje.  |
  |                       |       | El argumento over &lt;obj&gt; es opcional.    |
  +-----------------------+-------+-----------------------------------------+
  | open &lt;lnk&gt; with &lt;obj&gt; | o     | Abrir un enlace bloqueado usando el     |
  |                       |       | objeto adecuado (llave o herramienta).  |
  |                       |       | Ej: open pipes north with crowbar       |
  +-----------------------+-------+-----------------------------------------+
  | exit                  | e     | Salir del juego.                        |
  +-----------------------+-------+-----------------------------------------+

MECANICAS Y NOTAS IMPORTANTES

  · ATAQUES Y DANO
    Cada ataque inflige 10 x (1 + numero_aliados) de dano al enemigo.
    En modo aleatorio (normal), hay un 50% de probabilidad de que el enemigo
    contraataque al jugador o a un aliado por 10 HP en lugar de recibir dano.

  · PUERTAS BLOQUEADAS
    Hay tres pasos bloqueados que requieren herramientas especificas:
      - Pipes North      --> necesita Crowbar       (requiere Silver Key para tomarla)
      - Chef Bathroom E  --> necesita Hammer        (requiere Rusty Key para tomarlo)
      - Backyard South   --> necesita Screwdriver   (requiere Master Key para tomarlo)

  · LLAVES Y COFRES
    Los objetos dentro de cofres solo se pueden recoger si se tiene la llave
    correcta en el inventario. No hace falta un comando especial: simplemente
    ejecuta "take &lt;obj&gt;" y el juego verifica si tienes la llave.

  · EVENTOS ALEATORIOS (game_rules)
    En modo normal, cada turno pueden ocurrir eventos aleatorios:
      - Un enemigo en la sala ataca al jugador (10% probabilidad)
      - Un aliado desaparece aleatoriamente (5%)
      - El jugador recibe criticas negativas [-5 a -25 HP] (5%)
      - Un objeto se teletransporta a otra sala (10%)
      - La mochila llena inflige dano pasivo [-1 a -5 HP]
      - En la sala del jefe final, dano de fuego continuo cada turno

  · JEFES (BOSSES)
    Al morir un jefe, sus puertas asociadas se abren automaticamente.
    Los tres jefes son: Cockroach King, Ratatouille King y, como
    jefe final, el Fat Michelin Chef.

  · MODO MULTIJUGADOR
    Los turnos se alternan entre P1 (Chef) y P2 (Grandma). Ambos comparten
    el mismo mapa. Los aliados solo pueden seguir a un jugador a la vez.
    Los objetos recogidos son del inventario de cada jugador por separado.
    Al final de la partida, la puntuacion se calcula sumando los HP de todos
    los aliados de ambos jugadores.


--------------------------------------------------------------------------------
(c) MAPA DEL JUEGO
--------------------------------------------------------------------------------

  El mapa es identico en modo 1 jugador y multijugador (mismas salas,
  conexiones y posiciones de objetos). Las diferencias entre modos estan
  unicamente en los HP de los enemigos.

  LEYENDA:
    [Nombre / ID]  Habitacion / sala
    ---  /  |      Conexion abierta (N=norte, S=sur, E=este, W=oeste)
    ===  /  #      Conexion BLOQUEADA (requiere herramienta)
    (herram.)      Herramienta necesaria para abrir ese paso
    +Nombre        Aliado reclutable en esa sala
    xNombre        Enemigo en esa sala
    *Nombre        JEFE en esa sala
    [U] / [D]      Escaleras hacia arriba (Up) / hacia abajo (Down)
    [Cofre]        Objeto no movible (cofre); contiene otro objeto
    Nombre†        Objeto con dependencia (necesita llave en inventario)


  ============================================================
  PLANTA 0 - SOTANO
  ============================================================
  (Acceso inicial. Escaleras hacia Planta 1 desde CK Taqueria)

  +----------------+           +-------------------------+
  | Crates    (54) |           | CK's Taqueria     (55)  |
  | + Lettuce      |           | * Cockroach King        |
  | Wooden Key     |           | [Iron Storage Chest]    |
  |                |           | Hammer† (Iron Key)      |
  |                |           | Poison Bottle           |
  |                |           | [U] -> Corridor  (56)   |
  +-------+--------+           +-----------##------------+
          |                                ##
          N/S                   N*(locked, Crowbar)
          |                                ##
  +-------+--------+           +-----------##------------+
  | Barrels   (52) |           | Pipes            (53)   |
  | x Cockroach    | <--E/W--> | x Spider                |
  | [Old Wooden    |           | Bottle of Water         |
  |   Chest]       |           +-------------------------+
  | Iron Key       |
  | Crowbar†       |
  |  (Wooden Key)  |
  | Fresh Apple    |
  +-------+--------+
          |
          N/S
          |
  +-------+--------+
  | Entry     (51) |
  | + Bread        |
  +----------------+


  ============================================================
  PLANTA 1 - PRIMERA PLANTA
  ============================================================
  (Acceso desde Planta 0. Escaleras hacia Planta 2 desde RK Den)

                             +--------------------+  E*(Hammer)  +---------------------+
                             | Chef Bathroom (59) |##############| RK Den        (510) |
                             | x Raticate         |              | * Ratatouille King  |
                             +---------+----------+              | Master Key          |
                                       |                         | Venomous Bottle     |
                                      N/S                        | [U]->Dining Rm (511)|
                                       |                         +---------------------+
  +--------------------+ E/W +---------+----------+
  | Fridge        (58) |<--->| Kitchen        (57)|
  | + Tomato           |     | + Cheese           |
  +--------------------+     | [Frozen Chest]     |
                             | Sizzling Tray†     |
                             |  (Oven Prot.)      |
                             +---------+----------+
                                       |
                                       N/S
                                       |
                             +---------+-----------+
                             | Corridor       (56) |
                             | x Ratatta           |
                             | Frozen Key          |
                             | Oven Prot.†         |
                             |  (Frozen Key)       |
                             | Energy Drink        |
                             | [D]->CK Taq.   (55) |
                             +--------------------++


  ============================================================
  PLANTA 2 - SEGUNDA PLANTA / EXTERIOR
  ============================================================
  (Acceso desde Planta 1. Aqui se encuentra el jefe final)

  +--------------------+   W/E   +------------------------+
  | Bathroom     (512) |<------->| Dining Room      (511) |
  | x Dishwasher       |         | + Bacon                |
  | Golden Key         |         | [Master Chef Trunk]    |
  +--------------------+         | First Aid Kit†         |
                                 |  (Frozen Key)          |
                                 | Cup of Water           |
                                 | [D]->RK Den    (510)   |
                                 +----------+-------------+
                                            |
                                            S/N
                                            |
                                 +----------------------++-+  W/E   +--------------------+
                                 | Backyard         (513)  |<------>| Garden       (514) |
                                 | x Master Chef           |        | + Ham              |
                                 +----------+--------------+        | [Golden Chef Chest]|
                                        |                           | Small Screwdrvr†   |
                                 S*(locked, Small Screwdriver)      |  (Golden Key)      |
                                        |                           | Hot Chicken Soup   |
                                 +----------+--------------+        +--------------------+
                                 | Michelin Ch.Rm    (515) |
                                 | ** Fat Michelin Chef    |
                                 | Killer Grenade          |
                                 +-------------------------+


  TODOS LOS OBJETOS POR SALA:
  +---------------------+---------------------+-------------------------------+
  | Sala                | Objetos             | Notas                         |
  +---------------------+---------------------+-------------------------------+
  | Entry (51)          | (ninguno)           | Aliado: Bread                 |
  | Barrels (52)        | Old Wooden Chest    | No movible; Aliado: Cockroach |
  |                     | Iron Key            | Libre                         |
  |                     | Crowbar             | Dep: Wooden Key; abre Pipes N |
  |                     | Fresh Apple (+10hp) | Libre                         |
  | Crates (54)         | Wooden Key          | Libre; Aliado: Lettuce        |
  | Pipes (53)          | Bottle of Water(+1) | Libre; Enemigo: Spider        |
  | CK Taqueria (55)    | Iron Storage Chest  | No movible                    |
  |                     | Hammer              | Dep: Iron Key; abre Bathrm E  |
  |                     | Poison Bottle(-10)  | Libre                         |
  | Corridor (56)       | Frozen Key          | Libre; Enemigo: Ratatta       |
  |                     | Oven Protection     | Dep: Frozen Key               |
  |                     | Energy Drink (+30)  | Libre                         |
  | Kitchen (57)        | Frozen Chest        | No movible; Aliado: Cheese    |
  |                     | Sizzling Tray (+20) | Dep: Oven Protection          |
  | Fridge (58)         | (ninguno)           | Aliado: Tomato                |
  | Chef Bathroom (59)  | (ninguno)           | Enemigo: Raticate             |
  | RK Den (510)        | Master Key          | Libre                         |
  |                     | Venomous Bottle(-15)| Libre                         |
  | Dining Room (511)   | Master Chef Trunk   | No movible; Aliado: Bacon     |
  |                     | First Aid Kit(+100) | Dep: Frozen Key               |
  |                     | Cup of Water (+1)   | Libre                         |
  | Bathroom (512)      | Golden Key          | Libre; Enemigo: Dishwasher    |
  | Backyard (513)      | (ninguno)           | Enemigo: Master Chef          |
  | Garden (514)        | Golden Chef Chest   | No movible; Aliado: Ham       |
  |                     | Small Screwdriver   | Dep: Golden Key; abre Backyd S|
  |                     | Hot Chicken Soup(+20)| Libre                        |
  | Michelin Ch.Rm(515) | Killer Grenade(-30) | Libre; Jefe Final             |
  +---------------------+---------------------+-------------------------------+

  PUERTAS BLOQUEADAS:
    Pipes North          (53->55)    open pipes north with crowbar
    Chef Bathroom East   (59->510)   open chef bathroom east with hammer
    Backyard South       (513->515)  open backyard south with small screwdriver


--------------------------------------------------------------------------------
(d) PRUEBAS DE JUEGO - WALKTHROUGH OPTIMO
--------------------------------------------------------------------------------

  Objetivo: derrotar al jefe final reclutando los 6 aliados.
  Se demuestra el uso de todos los comandos nuevos: recruit, abandon, use,
  use over, y open.

  Dano de ataque: (1 + num_aliados) x 10 HP por ataque.
  Se recomienda ejecutar con -d (modo determinista) para reproducir sin
  aleatoriedad (ataques siempre exitosos, game_rules desactivadas).

================================================================================
  (d.1) MODO 1 JUGADOR  -  castle1p.dat
================================================================================

  Inicio: sala Entry (51) | Dano: 10 | HP: 100
  CONDICION DE VICTORIA: derrotar al Fat Michelin Chef en sala 515.
  PUNTUACION: suma de HP de todos los aliados vivos al terminar.

  --- ENTRY (51) --------------------------------------------------------------
  1.  recruit bread
        --> Bread se une. Dano: 20.            [DEMO: recruit]
  2.  abandon bread
        --> Bread deja de seguir.              [DEMO: abandon]
  3.  recruit bread
        --> Bread se une de nuevo. Dano: 20.

  --- BARRELS (52) ------------------------------------------------------------
  4.  move north
  5.  attack cockroach
        --> Cockroach: 20 HP --> 1 ataque (20 dmg). Muerto.
  6.  take iron key
  7.  take fresh apple
  8.  use fresh apple
        --> Jugador: +10 HP (110 HP total).    [DEMO: use]

  --- CRATES (54) -------------------------------------------------------------
  9.  move north
  10. take wooden key
  11. recruit lettuce
        --> Lettuce se une. Dano: 30.

  --- BARRELS (52) ------------------------------------------------------------
  12. move south
  13. take crowbar
        [Wooden Key en inventario --> puede cogerse; dep=Wooden Key]

  --- PIPES (53) --------------------------------------------------------------
  14. move east
  15. attack spider
  16. attack spider
        --> Spider: 40 HP --> 2 ataques (30 dmg). Muerto.
  17. open pipes north with crowbar
        --> Paso norte desbloqueado.           [DEMO: open]

  --- COCKROACH KING'S TAQUERIA (55) ------------------------------------------
  18. move north
  19. take hammer
        [Iron Key en inventario --> puede cogerse; dep=Iron Key]
  20. attack cockroach king
  21. attack cockroach king
  22. attack cockroach king
        --> Cockroach King: 80 HP --> 3 ataques (30 dmg). Muerto.
        [Jefe caido: puertas asociadas se abren automaticamente]

  --- CORRIDOR (56) -----------------------------------------------------------
  23. move up
  24. take frozen key
  25. take oven protection
        [Frozen Key en inventario --> puede cogerse; dep=Frozen Key]
  26. take energy drink
  27. use energy drink over bread
        --> Bread: +30 HP.                     [DEMO: use over aliado]
  28. attack ratatta
  29. attack ratatta
        --> Ratatta: 40 HP --> 2 ataques (30 dmg). Muerto.

  --- KITCHEN (57) ------------------------------------------------------------
  30. move north
  31. recruit cheese
        --> Cheese se une. Dano: 40.
  32. take sizzling tray
        [Oven Protection en inventario --> puede cogerse; dep=Oven Protection]

  --- FRIDGE (58) -------------------------------------------------------------
  33. move west
  34. recruit tomato
        --> Tomato se une. Dano: 50.

  --- CHEF BATHROOM (59) ------------------------------------------------------
  35. move east
  36. move north
  37. attack raticate
        --> Raticate: 50 HP --> 1 ataque (50 dmg). Muerto.
  38. open chef bathroom east with hammer
        --> Paso este desbloqueado.

  --- RATATOUILLE KING'S DEN (510) --------------------------------------------
  39. move east
  40. take master key
        [Master Key se encuentra en esta sala, libre]
  41. attack ratatouille king
  42. attack ratatouille king
  43. attack ratatouille king
        --> Ratatouille King: 120 HP --> 3 ataques (50 dmg). Muerto.
        [Jefe caido: puertas asociadas se abren automaticamente]

  --- DINING ROOM (511) -------------------------------------------------------
  44. move up
  45. recruit bacon
        --> Bacon se une. Dano: 60.
  46. take first aid kit
        [Frozen Key en inventario --> puede cogerse; dep=Frozen Key]

  --- BATHROOM (512) --- [desvio para obtener Golden Key] ---------------------
  47. move west
  48. take golden key
  49. move east

  --- BACKYARD (513) ----------------------------------------------------------
  50. move south
  51. attack master chef
  52. attack master chef
        --> Master Chef: 70 HP --> 2 ataques (60 dmg). Muerto.

  --- GARDEN (514) ------------------------------------------------------------
  53. move east
  54. recruit ham
        --> Ham se une. Dano: 70.  *** LOS 6 ALIADOS RECLUTADOS ***
  55. take small screwdriver
        [Golden Key en inventario --> puede cogerse; dep=Golden Key]

  --- BACKYARD (513) --> MICHELIN CHEF'S ROOM (515) ---------------------------
  56. move west
  57. open backyard south with small screwdriver
        --> Paso sur desbloqueado.
  58. move south

  --- MICHELIN CHEF'S ROOM (515) - JEFE FINAL ---------------------------------
  59. attack fat michelin chef
  60. attack fat michelin chef
  61. attack fat michelin chef
  62. attack fat michelin chef
  63. attack fat michelin chef
        --> Fat Michelin Chef: 350 HP --> 5 ataques (70 dmg). Muerto.

  ===========================================================================
   VICTORIA PERFECTA | 6/6 aliados | 63 comandos
   Aliados: Bread . Lettuce . Cheese . Tomato . Bacon . Ham
   Comandos nuevos demostrados: recruit, abandon, use, use over, open (x2)
  ===========================================================================


================================================================================
  (d.2) MODO MULTIJUGADOR  -  castle2p.dat
================================================================================

  Las posiciones de todos los objetos son identicas al modo 1 jugador.

  Diferencias de HP respecto al modo 1p:
    Cockroach King: 70 HP  |  Ratatouille King: 90 HP  |  Jefe Final: 200 HP

  Reparto de aliados:
    P1 (Chef)    -->  Bread, Cheese, Tomato, Bacon    (4 aliados, 50 dmg final)
    P2 (Grandma) -->  Lettuce, Ham                    (2 aliados, 30 dmg final)
    TOTAL        -->  6 aliados = VICTORIA PERFECTA

  Los turnos se alternan: P1 actua primero, luego P2.
  Inicio: ambos en Entry (51).

  --- ENTRY / BARRELS ---------------------------------------------------------
  T1  P1: recruit bread              --> Bread->P1. P1 dano: 20.
  T1  P2: move north                 --> P2 en Barrels (52).

  T2  P1: move north                 --> Ambos en Barrels (52).
  T2  P2: take iron key              [Iron Key libre en Barrels]

  T3  P1: attack cockroach           --> 20 dmg. Cockroach muerto.
  T3  P2: move north                 --> P2 en Crates (54).

  T4  P1: move north                 --> Ambos en Crates (54).
  T4  P2: take wooden key            [Wooden Key libre en Crates]

  T5  P1: move south                 --> P1 en Barrels (52).
  T5  P2: recruit lettuce            --> Lettuce->P2. P2 dano: 20. [DEMO recruit]

  T6  P1: take fresh apple
  T6  P2: move south                 --> Ambos en Barrels (52).

  T7  P1: move east                  --> P1 en Pipes (53).
  T7  P2: take crowbar               [P2 tiene Wooden Key --> dep OK]

  --- PIPES (53) --------------------------------------------------------------
  T8  P1: attack spider              --> Spider: 40->20 HP.
  T8  P2: move east                  --> Ambos en Pipes (53).

  T9  P1: attack spider              --> Spider: 20->0. Muerto.
  T9  P2: open pipes north with crowbar --> Paso norte desbloqueado. [DEMO open]

  --- COCKROACH KING'S TAQUERIA (55) ------------------------------------------
  T10 P1: move north
  T10 P2: move north                 --> Ambos en CK Taqueria (55).

  T11 P1: attack cockroach king      --> CK: 70->50 HP.
  T11 P2: take hammer                [P2 tiene Iron Key --> dep OK]

  T12 P1: attack cockroach king      --> CK: 50->30 HP.
  T12 P2: attack cockroach king      --> CK: 30->10 HP.

  T13 P1: attack cockroach king      --> CK: 10->0. Muerto.
  T13 P2: take poison bottle

  --- CORRIDOR (56) -----------------------------------------------------------
  T14 P1: move up
  T14 P2: move up                    --> Ambos en Corridor (56).

  T15 P1: take frozen key            [P1 toma Frozen Key para dep de Oven Prot]
  T15 P2: take energy drink

  T16 P1: take oven protection       [Frozen Key en P1 inventario --> dep OK]
  T16 P2: use energy drink over lettuce --> Lettuce P2: +30 HP. [DEMO use over]

  T17 P1: attack ratatta             --> Ratatta: 40->20 HP.
  T17 P2: abandon lettuce            --> Lettuce deja de seguir. [DEMO abandon]

  T18 P1: attack ratatta             --> Ratatta: 20->0. Muerto.
  T18 P2: recruit lettuce            --> Lettuce->P2 de nuevo. [DEMO recruit x2]

  --- KITCHEN (57) ------------------------------------------------------------
  T19 P1: move north
  T19 P2: move north                 --> Ambos en Kitchen (57).

  T20 P1: recruit cheese             --> Cheese->P1. P1 dano: 30.
  T20 P2: move north                 --> P2 en Chef Bathroom (59).

  --- FRIDGE (58) / CHEF BATHROOM (59) ----------------------------------------
  T21 P1: move west                  --> P1 en Fridge (58).
  T21 P2: attack raticate            --> Raticate: 50->20 HP. (30 dmg P2+Lettuce)

  T22 P1: recruit tomato             --> Tomato->P1. P1 dano: 40.
  T22 P2: attack raticate            --> Raticate: 20->0. Muerto.

  T23 P1: take sizzling tray         [P1 tiene Oven Protection --> dep OK]
  T23 P2: open chef bathroom east with hammer --> Paso este desbloqueado.

  T24 P1: move east                  --> P1 en Kitchen (57).
  T24 P2: move east                  --> Ambos en RK Den (510).

  T25 P1: move north                 --> P1 en Chef Bathroom (59).
  T25 P2: take master key            [Master Key libre en RK Den]

  T26 P1: move east                  --> Ambos en RK Den (510).
  T26 P2: attack ratatouille king    --> RK: 90->60 HP. (30 dmg P2+Lettuce)

  T27 P1: attack ratatouille king    --> RK: 60->20 HP. (40 dmg P1+3 aliados)
  T27 P2: attack ratatouille king    --> RK: 20->0. Muerto.

  T28 P1: take venomous bottle
  T28 P2: move up                    --> P2 en Dining Room (511).

  --- DINING ROOM (511) -------------------------------------------------------
  T29 P1: move up                    --> Ambos en Dining Room (511).
  T29 P2: recruit bacon              --> Bacon->P2 (o P1, segun disponibilidad).

  T30 P1: recruit bacon              --> Bacon->P1. P1 dano: 50.
  T30 P2: take first aid kit         [P2 tiene Frozen Key... ver nota]

  Nota: First Aid Kit dep=Frozen Key (614). P1 tiene el Frozen Key (tomado en
  T15). Para que P2 pueda tomar el First Aid Kit, P1 debe pasar el Frozen Key
  a P2 (drop + take), o P1 lo toma directamente.

  T30 P1: take first aid kit         [P1 tiene Frozen Key --> dep OK]
  T30 P2: move west                  --> P2 en Bathroom (512).

  --- BATHROOM (512) --- [desvio Golden Key] ----------------------------------
  T31 P1: move south                 --> P1 en Backyard (513).
  T31 P2: take golden key            [Golden Key libre en Bathroom]

  T32 P1: attack master chef         --> MC: 70->20 HP. (50 dmg P1+4 aliados)
  T32 P2: move east                  --> P2 en Dining Room (511).

  T33 P1: attack master chef         --> MC: 20->0. Muerto.
  T33 P2: move south                 --> P2 en Backyard (513).

  --- GARDEN (514) ------------------------------------------------------------
  T34 P1: move east                  --> Ambos en Garden (514).
  T34 P2: recruit ham                --> Ham->P2. P2 dano: 30. *** 6 ALIADOS ***

  T35 P1: take small screwdriver     [P1 no tiene Golden Key... P2 lo tiene]
  T35 P2: take small screwdriver     [P2 tiene Golden Key --> dep OK]

  T36 P1: take hot chicken soup
  T36 P2: move west                  --> P2 en Backyard (513).

  --- MICHELIN CHEF'S ROOM (515) - JEFE FINAL ---------------------------------
  T37 P1: move west                  --> Ambos en Backyard (513).
  T37 P2: open backyard south with small screwdriver --> Paso desbloqueado.

  T38 P1: move south                 --> P1 en Michelin Chef's Room (515).
  T38 P2: move south                 --> Ambos en (515).

  T39 P1: attack fat michelin chef   --> FMC: 200->150 HP. (50 dmg)
  T39 P2: attack fat michelin chef   --> FMC: 150->120 HP. (30 dmg)

  T40 P1: attack fat michelin chef   --> FMC: 120->70 HP.
  T40 P2: attack fat michelin chef   --> FMC: 70->40 HP.

  T41 P1: attack fat michelin chef   --> FMC: 40->0. MUERTO. VICTORIA.

  ===========================================================================
   VICTORIA PERFECTA | 6/6 aliados | 41 turnos (81 acciones)
   P1: Bread . Cheese . Tomato . Bacon     (4 aliados)
   P2: Lettuce . Ham                       (2 aliados)
   Comandos nuevos: recruit, abandon, use over, open (x2)
  ===========================================================================


--------------------------------------------------------------------------------
  FIN DE LA DOCUMENTACION F14
--------------------------------------------------------------------------------