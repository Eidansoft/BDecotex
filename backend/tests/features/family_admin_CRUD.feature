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
