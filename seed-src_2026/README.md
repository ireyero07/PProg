En el F16, cuando dice "Este argumento será compatible con el de log, pudiendo combinarse ambos en cualquier orden"
nosotros hemos hecho que no se pueda combinar el orden, es decir, si fueran compatibles, el orden sería: 
./executable dataFile -l logFile -d
Además, en el F16, al ser determinista, nosotros hacemos que en el attack, siempre gane el player. 

KITCHEN CHAOS

Eres un chef diminuto que ha aparecido misteriosamente en el sotano de un enorme
restaurante. Tu unico objetivo es escapar atravesando la cocina, los pasillos y
la sala VIP antes de que los enemigos acaben contigo.

Por el camino encontraras ingredientes cobrados vida como Lettuce, Tomato, Bread 
o Cheese que podras reclutar para que te acompanen. Cuantos mas ingredientes te
sigan, mas fuerte seras en combate. Pero cuidado, el restaurante esta lleno de
peligros: cucarachas, ratas, lavaplatos furiosos y chefs enemigos que no dudaran
en atacarte.

Recoge objetos, abre puertas con las llaves correctas, usa botiquines para
recuperar vida y lucha junto a tus ingredientes para llegar a la salida.
De todos los chefs diminutos que se turnan en esta aventura tendran que cooperar
para escapar.

EJECUCION:
  ./castle castle.dat                      - modo normal
  ./castle castle.dat -l fichero.log       - guarda log de comandos
  ./castle castle.dat -d                   - modo determinista (sin aleatoriedad)
  ./castle castle.dat -l fichero.log -d    - combinado

COMANDOS DISPONIBLES:
  move <n/s/e/w/u/d>       - mover al jugador en una direccion
  take <objeto>             - coger un objeto del suelo
  drop <objeto>             - soltar un objeto del inventario
  attack <personaje>        - atacar a un enemigo
  chat <personaje>          - hablar con un personaje amigo
  inspect <objeto>          - ver la descripcion de un objeto
  recruit <personaje>       - reclutar un personaje amigo para que te siga
  abandon <personaje>       - dejar de llevar a un personaje contigo
  use <objeto>              - usar un objeto del inventario (por ejemplo una pocion)
  use <objeto> over <personaje> - usar un objeto sobre un follower
  open <enlace> with <objeto>   - abrir una puerta o enlace con un objeto
  exit                      - salir del juego

NOTAS:
  - Solo se pueden coger objetos que sean movibles
  - Algunos objetos necesitan que tengas otro objeto primero para poder cogerlos
  - Los personajes amigos reclutados te siguen y te ayudan en combate
  - El juego termina cuando un jugador muere

=======================================================
                  KITCHEN CHAOS - MAPA
=======================================================
FLOOR 0 - SOTANO
=================
              [Crates 54]
               Lettuce (amigo)
                    |
                    S
                    |
[Entry 51] --N-- [Barrels 52] --E-- [Pipes 53]
 Bread (amigo)    Cockroach(-T-)     Spider(-oO)
                  Silver Key         Bottle of water
                  Fresh Apple              |
                  Crowbar*                 N  <-- CERRADO (necesitas Crowbar)
                  Old Wooden Chest         |
                                    [CK Taqueria 55]
                                     CK King(-M-) JEFE
                                     Iron Storage Chest
                                     Hammer*
                                          |
                                          UP
                                          |
FLOOR 1 - COCINA                   [Corridor 56]
=================                   Ratatta(.=-)
                                     Energy Drink
                                     Oven protection
                                          |
                                          N
                                          |
           [Fridge 58] --E-- [Kitchen 57] --N-- [Chef Bathroom 59]
            Tomato (amigo)    Cheese (amigo)      Raticate(*=-)
                              Rusty Key           Energy Drink
                              Sizzling Tray*      Master Key
                              Frozen Chest        Stone Spice Chest
                                                       |
                                                       E  <-- CERRADO (necesitas Hammer)
                                                       |
                                               [RK Den 510]
                                                Ratatouille King(M) JEFE
                                                    |
                                                    UP
                                                    |
FLOOR 2 - SALA VIP                         [Dining Room 511]
==================                          Bacon (amigo)
                                            Master Chef Trunk
                                            First Aid Kit*
                                            Bottle of Water
                                                 |          |
                                                 W          S
                                                 |          |
                                          [Bathroom 512] [Backyard 513]
                                           Dishwasher      Master Chef(4^*)
                                           (1o.)               |         |
                                                               E         S  <-- CERRADO (necesitas Small Screwdriver)
                                                               |         |
                                                         [Garden 514] [Michelin Room 515]
                                                          Ham (amigo)  Fat Michelin Chef JEFE FINAL
                                                          Hot Chicken Soup
                                                          Golden Chef Chest
                                                          Small Screwdriver*
=======================================================
LEYENDA:
  *  = objeto que necesita otro objeto para poder cogerse
  --> CERRADO = enlace bloqueado que necesita un objeto para abrirse
  JEFE = enemigo jefe con muchos HP
  (amigo) = personaje que puedes reclutar
OBJETOS CLAVE:
  Silver Key    -> en Barrels  -> permite coger Crowbar
  Crowbar       -> en Barrels  -> abre paso a CK Taqueria
  Rusty Key     -> en Kitchen  -> permite coger Hammer
  Hammer        -> en CK Taqueria -> abre paso a RK Den
  Master Key    -> en Chef Bathroom -> permite coger First Aid Kit y Small Screwdriver
  Small Screwdriver -> en Garden -> abre paso al jefe final
=======================================================

=======================================================
          KITCHEN CHAOS - GUIA COMPLETA
=======================================================
OBJETIVO: Llegar al Michelin chef's Room y derrotar al
Fat Michelin Chef para escapar del restaurante.
Los dos jugadores se turnan. Cada linea es el turno
de un jugador (J1 = Chef, J2 = Grandma).
=======================================================
PARTE 1 - SOTANO
=======================================================
-- Entry (51) --
J1: chat Bread          (Bread dice algo)
J2: inspect Bread       (inspeccionamos al personaje)
J1: recruit Bread       (Bread ahora nos sigue)
J2: move north          (vamos a Barrels)
-- Barrels (52) --
J1: move north          (J1 llega a Barrels)
J2: attack Cockroach    (J2 ataca la cucaracha)
J1: attack Cockroach    (J1 remata si sigue viva)
J2: take Silver Key     (cogemos la llave de plata)
J1: take Fresh Apple    (cogemos la manzana)
J2: take Crowbar        (cogemos la palanca, necesita Silver Key)
J1: inspect Silver Key  (inspeccionamos la llave)
J2: move north          (J2 va a Crates a por Lettuce)
-- Crates (54) --
J1: move north          (J1 llega a Crates)
J2: chat Lettuce        (hablamos con Lettuce)
J1: recruit Lettuce     (Lettuce se une al equipo)
J2: move south          (volvemos a Barrels)
J1: move south
J2: move east           (vamos a Pipes)
-- Pipes (53) --
J1: move east           (J1 llega a Pipes)
J2: inspect Bottle of water
J1: attack Spider       (atacamos la arana, Bread y Lettuce ayudan)
J2: attack Spider
J1: open Pipes North with Crowbar   (abrimos el paso al norte)
J2: move north          (vamos a CK Taqueria)
-- CK Taqueria (55) --
J1: move north
J2: attack Cockroach King   (jefe! con followers hacemos mas dano)
J1: attack Cockroach King
J2: attack Cockroach King
J1: attack Cockroach King   (seguimos hasta matarle)
J2: use Fresh Apple         (recuperamos vida)
J1: move up                 (subimos al Corridor)
-- Corridor (56) --
J2: move up
J1: attack Ratatta
J2: take Energy Drink
J1: take Oven protection
J2: move north              (vamos a Kitchen)
=======================================================
PARTE 2 - COCINA
=======================================================
-- Kitchen (57) --
J1: move north
J2: chat Cheese
J1: recruit Cheese          (Cheese se une)
J2: take Rusty Key
J1: take Sizzling Tray      (necesita Oven protection)
J2: use Sizzling Tray       (recuperamos vida)
J1: move west               (vamos a Fridge)
-- Fridge (58) --
J2: move west
J1: chat Tomato
J2: recruit Tomato          (Tomato se une)
J1: move east               (volvemos a Kitchen)
J2: move east
-- Kitchen de nuevo --
J1: move south              (bajamos a Corridor)
J2: move south
J1: move down               (bajamos a CK Taqueria)
J2: move down
J1: take Hammer             (necesita Rusty Key)
J2: move up                 (subimos de nuevo)
J1: move up
J2: move north              (a Kitchen)
J1: move north
J2: move north              (a Chef Bathroom)
-- Chef Bathroom (59) --
J1: move north
J2: attack Raticate         (con todos los followers)
J1: attack Raticate
J2: take Master Key
J1: take Energy Drink
J2: use Energy Drink        (recuperamos vida)
J1: open Chef Bathroom East with Hammer   (abrimos paso al este)
J2: move east               (vamos a RK Den)
-- RK Den (510) --
J1: move east
J2: attack Ratatouille King  (jefe con muchos HP)
J1: attack Ratatouille King
J2: attack Ratatouille King
J1: attack Ratatouille King
J2: abandon Bread            (abandonamos a Bread para demostrar el comando)
J1: recruit Bread            (lo volvemos a reclutar)
J2: move up                  (subimos al Dining Room)
=======================================================
PARTE 3 - SALA VIP
=======================================================
-- Dining Room (511) --
J1: move up
J2: chat Bacon
J1: recruit Bacon            (Bacon se une)
J2: take First Aid Kit       (necesita Master Key)
J1: inspect First Aid Kit
J2: move west                (vamos al Bathroom)
-- Bathroom (512) --
J1: move west
J2: attack Dishwasher
J1: attack Dishwasher
J2: move east                (volvemos al Dining Room)
J1: move east
J2: move south               (vamos al Backyard)
-- Backyard (513) --
J1: move south
J2: attack Master Chef
J1: attack Master Chef
J2: use First Aid Kit        (recuperamos vida antes del jefe final)
J1: move east                (vamos al Garden)
-- Garden (514) --
J2: move east
J1: chat Ham
J2: recruit Ham              (Ham se une, ahora tenemos 5 followers)
J1: take Hot Chicken Soup
J2: take Small Screwdriver   (necesita Master Key)
J1: use Hot Chicken Soup     (recuperamos vida)
J2: move west                (volvemos al Backyard)
J1: move west
-- Backyard de nuevo --
J2: open Backyard South with Small Screwdriver   (abrimos paso al jefe final)
J1: move south               (vamos al Michelin Room)
-- Michelin chef's Room (515) --
J2: move south
J1: attack Fat Michelin Chef  (jefe final, hp=200, necesitamos todos los followers)
J2: attack Fat Michelin Chef
J1: attack Fat Michelin Chef
J2: attack Fat Michelin Chef
J1: attack Fat Michelin Chef
J2: attack Fat Michelin Chef
J1: attack Fat Michelin Chef
J2: attack Fat Michelin Chef
... seguimos atacando hasta matarle ...
J1: exit                      (escapamos del restaurante!)
=======================================================
FUNCIONALIDADES DEMOSTRADAS EN ESTA GUIA:
  move     -> todas las direcciones (n,s,e,w,up)
  take     -> con y sin dependencia de otro objeto
  drop     -> (no necesario en este camino pero disponible)
  attack   -> contra enemigos normales y jefes
  chat     -> con todos los personajes amigos
  inspect  -> varios objetos
  recruit  -> Bread, Lettuce, Cheese, Tomato, Bacon, Ham
  abandon  -> Bread en RK Den
  use      -> Fresh Apple, Sizzling Tray, Energy Drink, First Aid Kit, Hot Chicken Soup
  open     -> Pipes North, Chef Bathroom East, Backyard South
=======================================================