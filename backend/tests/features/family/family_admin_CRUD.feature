# language: es
@backend @rest @family
Característica: Operaciones CRUD con las familias de productos
    El usuario administrador necesita administrar las familias dadas de alta
    en el sistema, para ello tiene que poder crear, modificar, consultar y
    eliminar las familias en el sistema.

    Antecedentes:
        Dado que la tabla "family" esta vacia

    Esquema del escenario: Crear familias de productos con parametros validos
        Cuando el usuario crea la familia <nombre> con codigo <cod>
        Entonces el sistema devuelve un codigo http <http cod>

        Ejemplos: Tanto el nombre de la familia como el codigo son obligatorios
            |nombre             |cod   |http cod |
            |"familia prueba 1" |"F1"  |200      |
            |"familia prueba 2" |"null"|400      |
            |"null"             |"F1"  |400      |
            |"null"             |"null"|400      |

    Escenario: Al crear una nueva familia el sistema notifica el nuevo id asignado
        Cuando el usuario crea la familia "Prueba de familia" con codigo "F1"
        Entonces el sistema devuelve un codigo http "200"
        Y el sistema incluye en la respuesta los siguientes atributos:
            |ATRIBUTO       |VALOR                        |
            |id_family      |regex(\d+)                   |
            |description    |Prueba de familia            |
            |code           |F1                           |

    Escenario: Evitar codigos duplicados cuando se crea una nueva familia
        Cuando el usuario crea la familia "Prueba de familia a duplicar" con codigo "F1"
        Y el usuario crea la familia "Codigo ya existente" con codigo "F1"
        Entonces el sistema devuelve un codigo http "409"

    Esquema del escenario: Modificar familia de productos con parametros validos
        Cuando el usuario crea la familia <nombre> con codigo <cod>
        Y el usuario modifica la familia al nuevo nombre <nuevo nombre> con codigo <nuevo cod>
        Entonces el sistema devuelve un codigo http <http cod>

        Ejemplos: Tanto el nombre de la familia como el codigo son obligatorios
            |nombre                 |cod   |nuevo nombre            |nuevo cod  |http cod |
            |"cambia nombre"        |"FE1" |"familia mod"           |"FE1"      |200      |
            |"cambia codigo"        |"FE2" |"cambia codigo"         |"FE22"     |200      |
            |"cambia los dos"       |"FE3" |"cambia nombre y cod"   |"FE33"     |200      |
            |"cambia solo nombre"   |"FE4" |"familia mod"           |"null"     |400      |
            |"cambia solo codigo"   |"FE5" |"null"                  |"FE44"     |400      |

    Escenario: Al modificar una familia el sistema notifica el nuevo estado de la familia
        Cuando el usuario crea la familia "Prueba de familia" con codigo "F1"
        Y el usuario modifica la familia al nuevo nombre "Familia editada" con codigo "F2"
        Entonces el sistema devuelve un codigo http "200"
        Y el sistema incluye en la respuesta los siguientes atributos:
            |ATRIBUTO       |VALOR                        |
            |id_family      |regex(\d+)                   |
            |description    |Familia editada              |
            |code           |F2                           |

    Escenario: Evitar codigos duplicados cuando se modifica una familia
        Dado el usuario crea la familia "Prueba de familia a duplicar" con codigo "F1"
        Y el usuario crea la familia "Prueba de familia a modificar" con codigo "F2"
        Cuando el usuario modifica la familia al nuevo nombre "Familia editada" con codigo "F1"
        Entonces el sistema devuelve un codigo http "409"

    Escenario: El usuario puede obtener una lista con todas las familias existentes en el sistema
        Dado que en el sistema existen las familias:
            |NOMBRE         |CODIGO |
            |Familia 1      |1      |
            |Familia 2      |2      |
            |Familia 3      |3      |
            |Familia 4      |4      |
            |Familia 5      |5      |
            |Familia 6      |6      |
        Cuando el usuario solicita el listado de todas las familias
        Entonces el sistema devuelve un codigo http "200"
        Y el sistema incluye el listado con las familias:
            |NOMBRE         |CODIGO |
            |Familia 1      |1      |
            |Familia 2      |2      |
            |Familia 3      |3      |
            |Familia 4      |4      |
            |Familia 5      |5      |
            |Familia 6      |6      |

    Escenario: Eliminar familia de productos existente
        Cuando el usuario crea la familia "Prueba de familia a borrar" con codigo "F1"
        Y el usuario elimina la familia creada
        Entonces el sistema devuelve un codigo http "200"