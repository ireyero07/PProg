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

