# language: es
@backend @rest @model
Característica: Operaciones CRUD con los modelos de productos
    El usuario administrador necesita administrar los modelos dados de alta
    en el sistema, para ello tiene que poder crear, modificar, consultar y
    eliminar los modelos en el sistema.

    Antecedentes:
        Dado que la tabla "model" esta vacia
        Y que el sistema contiene los sexos:
            |SEXO           |COD       |
            |Mujer          |M         |
            |Hombre         |H         |
            |Embarazada     |E         |
            |Unisex         |U         |
        Y que el sistema contiene las lineas:
            |LINEA          |COD       |
            |Linea 1        |1         |
            |Linea 2        |2         |
            |Linea 3        |3         |
        Y que el sistema contiene las familias:
            |FAMILIA        |COD       |
            |Abrigos        |1         |
            |Camisas        |2         |
            |Casacas        |3         |
            |Pantalones     |4         |
            |Zapatos        |5         |

    Esquema del escenario: Crear modelos de productos con parametros validos
        Cuando el usuario crea un modelo de la familia <FAMILIA>, linea <LINEA>, sexo <SEXO> y variante <VAR>
        Entonces el sistema devuelve un codigo http <HTTP COD>

        Ejemplos: Los atributos del modelo, familia, linea, sexo y variante son obligatorios
            |FAMILIA             |LINEA     |SEXO       |VAR   |HTTP COD |
            |"Abrigos"           |"Linea 1" |"Hombre"   |0     |200      |
            |"null"              |"Linea 1" |"Hombre"   |0     |400      |
            |"Abrigos"           |"null"    |"Hombre"   |0     |400      |
            |"Abrigos"           |"Linea 1" |"null"     |0     |400      |
            |"Abrigos"           |"Linea 1" |"Hombre"   |"null"|400      |

    Escenario: Al crear un nuevo modelo el sistema notifica el nuevo id asignado
        Cuando el usuario crea un modelo de la familia "Camisas", linea "Linea 2", sexo "Mujer" y variante "0"
        Entonces el sistema devuelve un codigo http "200"
        Y el sistema incluye en la respuesta los siguientes atributos:
            |ATRIBUTO       |VALOR                        |
            |id_model       |regex(\d+)                   |
            |xid_family     |regex(\d+)                   |
            |xid_line       |regex(\d+)                   |
            |xid_sex        |regex(\d+)                   |
            |variant        |0                            |

    Escenario: Evitar codigos duplicados cuando se crea un nuevo modelo
        Cuando el usuario crea un modelo de la familia "Pantalones", linea "Linea 3", sexo "Unisex" y variante "2"
        Y el usuario crea un modelo de la familia "Pantalones", linea "Linea 3", sexo "Unisex" y variante "2"
        Entonces el sistema devuelve un codigo http "409"

    Esquema del escenario: Evitar codigos duplicados cuando se crea un nuevo modelo
        Dado el usuario crea un modelo de la familia <FAMILIA>, linea <LINEA>, sexo <SEXO> y variante <VAR>
        Cuando el usuario crea un modelo de la familia <FAMILIA2>, linea <LINEA2>, sexo <SEXO2> y variante <VAR2>
        Entonces el sistema devuelve un codigo http <HTTP COD>

        Ejemplos: La combinacion de campos obligatorios no puede existir previamente
            |FAMILIA    |LINEA     |SEXO       |VAR   |FAMILIA2    |LINEA2    |SEXO2      |VAR2  |HTTP COD |
            |"Camisas"  |"Linea 1" |"Mujer"    |"0"   |"Camisas"   |"Linea 1" |"Mujer"    |"0"   |409      |
            |"Camisas"  |"Linea 1" |"Mujer"    |"0"   |"Pantalones"|"Linea 1" |"Mujer"    |"0"   |200      |
            |"Camisas"  |"Linea 1" |"Mujer"    |"0"   |"Camisas"   |"Linea 2" |"Mujer"    |"0"   |200      |
            |"Camisas"  |"Linea 1" |"Mujer"    |"0"   |"Camisas"   |"Linea 1" |"Hombre"   |"0"   |200      |
            |"Camisas"  |"Linea 1" |"Mujer"    |"0"   |"Camisas"   |"Linea 1" |"Mujer"    |"2"   |200      |

    Escenario: Es posible modificar los atributos obligatorios de un modelo pero no se permiten codigos duplicados, por lo que el sistema comprobara que la combinacion de atributos identificadores no exista previamente. Este test comprueba la duplicidad de familia
        Cuando el usuario crea un modelo de la familia "Camisas", linea "Linea 1", sexo "Mujer" y variante "0"
        Y el usuario crea un modelo de la familia "Pantalones", linea "Linea 1", sexo "Mujer" y variante "0"
        Y el usuario modifica el modelo previamente creado a familia "Camisas", linea "Linea 1", sexo "Mujer" y variante "0"
        Entonces el sistema devuelve un codigo http "409"

    Escenario: Es posible modificar los atributos obligatorios de un modelo pero no se permiten codigos duplicados, por lo que el sistema comprobara que la combinacion de atributos identificadores no exista previamente. Este test comprueba la duplicidad de linea
        Cuando el usuario crea un modelo de la familia "Camisas", linea "Linea 1", sexo "Mujer" y variante "0"
        Y el usuario crea un modelo de la familia "Camisas", linea "Linea 2", sexo "Mujer" y variante "0"
        Y el usuario modifica el modelo previamente creado a familia "Camisas", linea "Linea 1", sexo "Mujer" y variante "0"
        Entonces el sistema devuelve un codigo http "409"

    Escenario: Es posible modificar los atributos obligatorios de un modelo pero no se permiten codigos duplicados, por lo que el sistema comprobara que la combinacion de atributos identificadores no exista previamente. Este test comprueba la duplicidad de sexo
        Cuando el usuario crea un modelo de la familia "Camisas", linea "Linea 1", sexo "Mujer" y variante "0"
        Y el usuario crea un modelo de la familia "Camisas", linea "Linea 1", sexo "Hombre" y variante "0"
        Y el usuario modifica el modelo previamente creado a familia "Camisas", linea "Linea 1", sexo "Mujer" y variante "0"
        Entonces el sistema devuelve un codigo http "409"

    Escenario: Es posible modificar los atributos obligatorios de un modelo pero no se permiten codigos duplicados, por lo que el sistema comprobara que la combinacion de atributos identificadores no exista previamente. Este test comprueba la duplicidad de variante
        Cuando el usuario crea un modelo de la familia "Camisas", linea "Linea 1", sexo "Mujer" y variante "0"
        Y el usuario crea un modelo de la familia "Camisas", linea "Linea 1", sexo "Mujer" y variante "1"
        Y el usuario modifica el modelo previamente creado a familia "Camisas", linea "Linea 1", sexo "Mujer" y variante "0"
        Entonces el sistema devuelve un codigo http "409"

    Escenario: Al hacer un modelo hijo de otro, si el modelo padre no existe en el sistema, se devolvera un error
        Cuando el usuario crea un modelo de la familia "Pantalones", linea "Linea 3", sexo "Unisex" y variante "2"
        Y el usuario modifica los siguientes campos:
            |ATRIBUTO               |VALOR                        |
            |FAMILY                 |Pantalones                   |
            |LINE                   |Linea 3                      |
            |SEX                    |Unisex                       |
            |variant                |2                            |
            |xid_model_parent       |123                          |
        Entonces el sistema devuelve un codigo http "404"

    Escenario: Al hacer un modelo hijo de otro, el sistema comprueba que el modelo padre exista
        Dado el usuario crea un modelo de la familia "Pantalones", linea "Linea 3", sexo "Unisex" y variante "2"
        Cuando el usuario crea un modelo de la familia "Pantalones", linea "Linea 3", sexo "Hombre" y variante "2"
        Y el usuario modifica los siguientes campos:
            |ATRIBUTO               |VALOR                        |
            |FAMILY                 |Pantalones                   |
            |LINE                   |Linea 3                      |
            |SEX                    |Hombre                       |
            |variant                |2                            |
            |xid_model_parent       |1                            |
        Entonces el sistema devuelve un codigo http "200"

    Escenario: El usuario puede obtener una lista con todos los modelos existentes en el sistema
        Dado que en el sistema existen los modelos:
            |FAMILIA         |LINEA     |SEXO        |VAR   |DESCRIPCION                              |
            |Pantalones      |Linea 1   |Mujer       |0     |P1M0 tiene minimo 25 caracteres          |
            |Camisas         |Linea 2   |Mujer       |0     |C2M0 tiene minimo 25 caracteres          |
            |Abrigos         |Linea 2   |Mujer       |0     |A2M0 tiene minimo 25 caracteres          |
            |Camisas         |Linea 1   |Mujer       |0     |C1M0 tiene minimo 25 caracteres          |
            |Camisas         |Linea 2   |Hombre      |0     |C2H0 tiene minimo 25 caracteres          |
            |Camisas         |Linea 1   |Hombre      |0     |C1H0 tiene minimo 25 caracteres          |
            |Pantalones      |Linea 2   |Hombre      |0     |P2H0 tiene minimo 25 caracteres          |
            |Pantalones      |Linea 2   |Hombre      |1     |P2H1 tiene minimo 25 caracteres          |
        Cuando el usuario solicita el listado de todos los modelos
        Entonces el sistema devuelve un codigo http "200"
        Y el sistema devuelve una lista de elementos con los siguientes atributos:
            |ATRIBUTO               |VALOR                                  |
            |id_model               |regex(\d+)                             |
            |code                   |regex(....)                            |
            |description            |regex(.... tiene minimo 25 caracteres) |

    Escenario: Eliminar modelo de productos existente
        Dado el usuario crea un modelo con los siguientes campos:
            |ATRIBUTO               |VALOR                        |
            |FAMILY                 |Pantalones                   |
            |LINE                   |Linea 3                      |
            |SEX                    |Unisex                       |
            |variant                |2                            |
        Y el usuario crea un modelo con los siguientes campos:
            |ATRIBUTO               |VALOR                        |
            |FAMILY                 |Camisas                      |
            |LINE                   |Linea 2                      |
            |SEX                    |Mujer                        |
            |variant                |0                            |
        Cuando el usuario elimina el modelo creado
        Entonces el sistema devuelve un codigo http "200"

    Escenario: Es posible obtener los datos de un modelo por identificandolo por su ID
        Dado el usuario crea un modelo con los siguientes campos:
            |ATRIBUTO               |VALOR                        |
            |FAMILY                 |Pantalones                   |
            |LINE                   |Linea 3                      |
            |SEX                    |Unisex                       |
            |variant                |2                            |
            |description            |Pantalones de multiples usos |
            |front                  |Parte delantera              |
            |back                   |Parte trasera                |
            |neck                   |Cuello                       |
            |arm                    |El brazo                     |
            |observations           |Las observaciones            |
            |model_number_parent    |modelo de referencia         |
            |xid_model_parent       |1                            |
            |creation_date          |12345678                     |
            |client                 |Nombre del cliente           |
            |old_ref                |Anterior referencia          |
        Cuando el usuario solicita el modelo identificandolo por el id
        Entonces el sistema devuelve un codigo http "200"
        Y el sistema incluye en la respuesta los siguientes atributos:
            |ATRIBUTO               |VALOR                        |
            |id_model               |regex(\d+)                   |
            |xid_family             |regex(\d+)                   |
            |xid_line               |regex(\d+)                   |
            |xid_sex                |regex(\d+)                   |
            |variant                |2                            |
            |description            |Pantalones de multiples usos |
            |front                  |Parte delantera              |
            |back                   |Parte trasera                |
            |neck                   |Cuello                       |
            |arm                    |El brazo                     |
            |observations           |Las observaciones            |
            |model_number_parent    |modelo de referencia         |
            |xid_model_parent       |1                            |
            |creation_date          |regex(\d+)                   |
            |client                 |Nombre del cliente           |
            |old_ref                |Anterior referencia          |

    Escenario: Es posible modificar cualquiera de los atributos de un modelo
        Cuando el usuario crea un modelo de la familia "Pantalones", linea "Linea 3", sexo "Unisex" y variante "2"
        Y el usuario modifica los siguientes campos:
            |ATRIBUTO               |VALOR                        |
            |FAMILY                 |Pantalones                   |
            |LINE                   |Linea 3                      |
            |SEX                    |Unisex                       |
            |variant                |2                            |
            |description            |Pantalones de multiples usos |
            |front                  |Parte delantera              |
            |back                   |Parte trasera                |
            |neck                   |Cuello                       |
            |arm                    |Brazo                        |
            |observations           |Las observaciones            |
            |model_number_parent    |modelo ref                   |
            |xid_model_parent       |1                            |
            |creation_date          |12345678                     |
            |client                 |Nombre del cliente           |
            |old_ref                |Anterior referencia          |
        Entonces el sistema devuelve un codigo http "200"
        Y el sistema incluye en la respuesta los siguientes atributos:
            |ATRIBUTO               |VALOR                        |
            |id_model               |regex(\d+)                   |
            |xid_family             |regex(\d+)                   |
            |xid_line               |regex(\d+)                   |
            |xid_sex                |regex(\d+)                   |
            |variant                |2                            |
            |description            |Pantalones de multiples usos |
            |front                  |Parte delantera              |
            |back                   |Parte trasera                |
            |neck                   |Cuello                       |
            |arm                    |Brazo                        |
            |observations           |Las observaciones            |
            |model_number_parent    |modelo ref                   |
            |xid_model_parent       |1                            |
            |creation_date          |regex(\d+)                   |
            |client                 |Nombre del cliente           |
            |old_ref                |Anterior referencia          |