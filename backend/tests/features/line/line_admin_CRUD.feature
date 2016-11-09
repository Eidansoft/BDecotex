# language: es
@backend @rest @line
Característica: Operaciones CRUD con las lineas de productos
    El usuario administrador necesita administrar las lineas dadas de alta
    en el sistema, para ello tiene que poder crear, modificar, consultar y
    eliminar las lineas en el sistema.

    Antecedentes:
        Dado que la tabla "line" esta vacia

    Esquema del escenario: Crear lineas de productos con parametros validos
        Cuando el usuario crea la linea <NOMBRE> con codigo <COD>
        Entonces el sistema devuelve un codigo http <HTTP COD>

        Ejemplos: Tanto el nombre de la linea como el codigo son obligatorios
            |NOMBRE             |COD   |HTTP COD |
            |"linea prueba 1"   |"F1"  |200      |
            |"linea prueba 2"   |"null"|400      |
            |"null"             |"F1"  |400      |
            |"null"             |"null"|400      |

    Escenario: Al crear una nueva linea el sistema notifica el nuevo id asignado
        Cuando el usuario crea la linea "Prueba de linea" con codigo "F1"
        Entonces el sistema devuelve un codigo http "200"
        Y el sistema incluye en la respuesta los siguientes atributos:
            |ATRIBUTO       |VALOR                        |
            |id_line        |regex(\d+)                   |
            |name           |Prueba de linea              |
            |code           |F1                           |

    Escenario: Evitar codigos duplicados cuando se crea una nueva linea
        Cuando el usuario crea la linea "Prueba de linea a duplicar" con codigo "F1"
        Y el usuario crea la linea "Codigo ya existente" con codigo "F1"
        Entonces el sistema devuelve un codigo http "409"

    Esquema del escenario: Modificar linea de productos con parametros validos
        Cuando el usuario crea la linea <NOMBRE> con codigo <COD>
        Y el usuario modifica la linea al nuevo nombre <NUEVO NOMBRE> con codigo <NUEVO COD>
        Entonces el sistema devuelve un codigo http <HTTP COD>

        Ejemplos: Tanto el nombre de la linea como el codigo son obligatorios
            |NOMBRE                 |COD   |NUEVO NOMBRE            |NUEVO COD  |HTTP COD |
            |"cambia nombre"        |"FE1" |"linea mod"             |"FE1"      |200      |
            |"cambia codigo"        |"FE2" |"cambia codigo"         |"FE22"     |200      |
            |"cambia los dos"       |"FE3" |"cambia nombre y cod"   |"FE33"     |200      |
            |"cambia solo nombre"   |"FE4" |"linea mod"             |"null"     |400      |
            |"cambia solo codigo"   |"FE5" |"null"                  |"FE44"     |400      |

    Escenario: Al modificar una linea el sistema notifica el nuevo estado de la linea
        Cuando el usuario crea la linea "Prueba de linea" con codigo "F1"
        Y el usuario modifica la linea al nuevo nombre "Linea editada" con codigo "F2"
        Entonces el sistema devuelve un codigo http "200"
        Y el sistema incluye en la respuesta los siguientes atributos:
            |ATRIBUTO       |VALOR                        |
            |id_line        |regex(\d+)                   |
            |name           |Linea editada                |
            |code           |F2                           |

    Escenario: Evitar codigos duplicados cuando se modifica una linea
        Dado el usuario crea la linea "Prueba de linea a duplicar" con codigo "F1"
        Y el usuario crea la linea "Prueba de linea a modificar" con codigo "F2"
        Cuando el usuario modifica la linea al nuevo nombre "Linea editada" con codigo "F1"
        Entonces el sistema devuelve un codigo http "409"

    Escenario: El usuario puede obtener una lista con todas las lineas existentes en el sistema
        Dado que en el sistema existen las lineas:
            |NOMBRE       |CODIGO |
            |Linea 1      |LLL1   |
            |Linea 2      |LL2    |
            |Linea 3      |LL3    |
            |Linea 4      |L4     |
            |Linea 5      |L5     |
            |Linea 6      |L6     |
        Cuando el usuario solicita el listado de todas las lineas
        Entonces el sistema devuelve un codigo http "200"
        Y el sistema incluye el listado con las lineas:
            |NOMBRE       |CODIGO |
            |Linea 1      |LLL1   |
            |Linea 2      |LL2    |
            |Linea 3      |LL3    |
            |Linea 4      |L4     |
            |Linea 5      |L5     |
            |Linea 6      |L6     |

    Escenario: Eliminar linea de productos existente
        Cuando el usuario crea la linea "Prueba de linea a borrar" con codigo "F1"
        Y el usuario elimina la linea creada
        Entonces el sistema devuelve un codigo http "200"