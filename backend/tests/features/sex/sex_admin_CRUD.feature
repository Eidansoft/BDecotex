# language: es
@backend @rest @sex
Característica: Operaciones CRUD con con el sexo de los productos
    El usuario administrador necesita administrar la categorizacion de sexos dados de alta
    en el sistema, para ello tiene que poder crear, modificar, consultar y
    eliminar los sexos disponibles en el sistema.

    Antecedentes:
        Dado que la tabla "sex" esta vacia

    Esquema del escenario: Crear nuevo sexo de producto con parametros validos
        Cuando el usuario crea el sexo <nombre> con codigo <cod>
        Entonces el sistema devuelve un codigo http <http cod>

        Ejemplos: Tanto el nombre como el codigo son obligatorios
            |nombre     |cod    |http cod |
            |"Hombre"   |"H"    |200      |
            |"Mujer"    |"null" |404      |
            |"null"     |"E"    |404      |
            |"null"     |"null" |404      |

    Escenario: Al crear un nuevo sexo el sistema notifica el nuevo id asignado
        Cuando el usuario crea el sexo "Embarazada" con codigo "E"
        Entonces el sistema devuelve un codigo http "200"
        Y el sistema incluye en la respuesta los siguientes atributos:
            |ATRIBUTO       |VALOR                        |
            |id_sex         |regex(\d+)                   |
            |name           |Embarazada                   |
            |code           |E                            |

    Escenario: Evitar codigos duplicados cuando se crea un nuevo sexo
        Cuando el usuario crea el sexo "Embarazada" con codigo "E"
        Y el usuario crea el sexo "Codigo duplicado" con codigo "E"
        Entonces el sistema devuelve un codigo http "409"