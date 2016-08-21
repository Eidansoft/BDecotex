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

    Esquema del escenario: Modificar sexo con parametros validos
        Cuando el usuario crea el sexo <NOMBRE> con codigo <COD>
        Y el usuario modifica el sexo al nuevo nombre <NUEVO NOMBRE> con codigo <NUEVO COD>
        Entonces el sistema devuelve un codigo http <HTTP COD>

        Ejemplos: Tanto el nombre como el codigo son obligatorios
            |NOMBRE                 |COD   |NUEVO NOMBRE            |NUEVO COD  |HTTP COD |
            |"cambia nombre"        |"FE1" |"sex mod"               |"FE1"      |200      |
            |"cambia codigo"        |"FE2" |"cambia codigo"         |"FE22"     |200      |
            |"cambia los dos"       |"FE3" |"cambia nombre y cod"   |"FE33"     |200      |
            |"cambia solo nombre"   |"FE4" |"sex mod"               |"null"     |404      |
            |"cambia solo codigo"   |"FE5" |"null"                  |"FE44"     |404      |

    Escenario: Al modificar un sexo el sistema notifica el nuevo estado del sexo
        Cuando el usuario crea el sexo "Embarazada" con codigo "E"
        Y el usuario modifica el sexo al nuevo nombre "Embarazadisimas" con codigo "ESS"
        Entonces el sistema devuelve un codigo http "200"
        Y el sistema incluye en la respuesta los siguientes atributos:
            |ATRIBUTO       |VALOR                        |
            |id_sex         |regex(\d+)                   |
            |name           |Embarazadisimas              |
            |code           |ESS                          |

    Escenario: Evitar codigos duplicados cuando se modifica un sexo
        Dado el usuario crea el sexo "Embarazada" con codigo "E"
        Y el usuario crea el sexo "Sexo a modificar" con codigo "S2"
        Cuando el usuario modifica el sexo al nuevo nombre "Duplicado" con codigo "E"
        Entonces el sistema devuelve un codigo http "409"

    Escenario: El usuario puede obtener una lista con todos los sexos existentes en el sistema
        Dado que en el sistema existen los sexos:
            |NOMBRE         |CODIGO |
            |Hombre         |H      |
            |Mujer          |M      |
            |Embarazada     |E      |
            |Unisex         |U      |
            |No definido    |N      |
        Cuando el usuario solicita el listado de todos los sexos
        Entonces el sistema devuelve un codigo http "200"
        Y el sistema incluye el listado con los sexos:
            |NOMBRE         |CODIGO |
            |Hombre         |H      |
            |Mujer          |M      |
            |Embarazada     |E      |
            |Unisex         |U      |
            |No definido    |N      |

    Escenario: Eliminar sexo existente
        Cuando el usuario crea el sexo "Embarazada" con codigo "E"
        Y el usuario elimina el sexo creado
        Entonces el sistema devuelve un codigo http "200"