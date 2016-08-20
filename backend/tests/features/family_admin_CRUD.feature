# language: es
Característica: Operaciones CRUD con las familias de productos
    El usuario administrador necesita administrar las familias dadas de alta
    en el sistema, para ello tiene que poder crear, modificar, consultar y
    eliminar las familias en el sistema.

    Antecedentes:
        Dado que la tabla "family" esta vacia

    Esquema del escenario: Crear familias de productos con parametros validos
        Cuando el usuario crea la familia <nombre> con codigo <cod>
        Entonces el sistema devuelve un codigo http <http cod>

        Ejemplos:
        |nombre             |cod   |http cod |
        |"familia prueba 1" |"F1"  |200      |
        |"familia prueba 2" |"null"|404      |
        |"null"             |"F1"  |404      |
        |"null"             |"null"|404      |

    Esquema del escenario: Modificar familia de productos con parametros validos
        Cuando el usuario crea la familia <nombre> con codigo <cod>
        Y el usuario modifica la familia al nuevo nombre <nuevo nombre> con codigo <nuevo cod>
        Entonces el sistema devuelve un codigo http <http cod>

        Ejemplos:
        |nombre                 |cod   |nuevo nombre            |nuevo cod  |http cod |
        |"cambia nombre"        |"FE1" |"familia mod"           |"FE1"      |200      |
        |"cambia codigo"        |"FE2" |"cambia codigo"         |"FE22"     |200      |
        |"cambia los dos"       |"FE3" |"cambia nombre y cod"   |"FE33"     |200      |
        |"cambia solo nombre"   |"FE4" |"familia mod"           |"null"     |404      |
        |"cambia solo codigo"   |"FE5" |"null"                  |"FE44"     |404      |

    Escenario: Eliminar familia de productos existente
        Cuando el usuario crea la familia "Prueba de familia a borrar" con codigo "F1"
        Y el usuario elimina la familia creada
        Entonces el sistema devuelve un codigo http "200"

    Escenario: Evitar codigos duplicados en las familias
        Cuando el usuario crea la familia "Prueba de familia a duplicar" con codigo "F1"
        Y el usuario crea la familia "Codigo ya existente" con codigo "F1"
        Entonces el sistema devuelve un codigo http "409"


    Escenario: Al crear una nueva familia el sistema notifica el nuevo id asignado
        Cuando el usuario crea la familia "Prueba de familia" con codigo "F1"
        Entonces el sistema devuelve un codigo http "200"
        Y el sistema incluye en la respuesta los siguientes atributos:
            |ATRIBUTO       |VALOR                        |
            |id_family      |                             |
            |description    |Prueba de familia            |
            |code           |F1                           |
