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
            |"null"              |"Linea 1" |"Hombre"   |0     |404      |
            |"Abrigos"           |"null"    |"Hombre"   |0     |404      |
            |"Abrigos"           |"Linea 1" |"null"     |0     |404      |
            |"Abrigos"           |"Linea 1" |"Hombre"   |"null"|404      |

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

    @current
    Esquema del escenario: Al modificar los parametros obligatorios de un modelo, el sistema debe comprobar que el nuevo modelo no exista previamente
        Cuando el usuario crea un modelo de la familia <FAMILIA>, linea <LINEA>, sexo <SEXO> y variante <VAR>
        Y el usuario crea un modelo de la familia <FAMILIA2>, linea <LINEA2>, sexo <SEXO2> y variante <VAR2>
        Y el usuario modifica el campo <CAMPO> al valor <VALOR>
        Entonces el sistema devuelve un codigo http <HTTP COD>

        Ejemplos: Los campos obligatorios no pueden cambiarse a vacio ni a una combinacion de campos de un modelo que ya exista
            |FAMILIA    |LINEA     |SEXO       |VAR   |FAMILIA2         |LINEA2    |SEXO2       |VAR2  |CAMPO         |VALOR       |HTTP COD |
            |"Camisas"  |"Linea 1" |"Mujer"    |"0"   |"Pantalones"     |"Linea 1" |"Mujer"     |"0"   |"xid_family"  |"Camisas"   |409      |
            |"Camisas"  |"Linea 1" |"Mujer"    |"0"   |"Camisas"        |"Linea 2" |"Mujer"     |"0"   |"xid_line"    |"Linea 1"   |409      |
            |"Camisas"  |"Linea 1" |"Mujer"    |"0"   |"Camisas"        |"Linea 1" |"Embarazada"|"0"   |"xid_sex"     |"Mujer"     |409      |
            |"Camisas"  |"Linea 1" |"Mujer"    |"0"   |"Camisas"        |"Linea 1" |"Mujer"     |"1"   |"variant"     |"0"         |409      |
            |"Camisas"  |"Linea 1" |"Mujer"    |"0"   |"Pantalones"     |"Linea 1" |"Mujer"     |"0"   |"xid_family"  |"null"      |404      |
            |"Camisas"  |"Linea 1" |"Mujer"    |"0"   |"Camisas"        |"Linea 2" |"Mujer"     |"0"   |"xid_line"    |"null"      |404      |
            |"Camisas"  |"Linea 1" |"Mujer"    |"0"   |"Camisas"        |"Linea 1" |"Embarazada"|"0"   |"xid_sex"     |"null"      |404      |
            |"Camisas"  |"Linea 1" |"Mujer"    |"0"   |"Camisas"        |"Linea 1" |"Mujer"     |"1"   |"variant"     |"null"      |404      |
            |"Camisas"  |"Linea 1" |"Mujer"    |"0"   |"Pantalones"     |"Linea 1" |"Mujer"     |"0"   |"xid_family"  |"Abrigos"   |200      |
            |"Camisas"  |"Linea 1" |"Mujer"    |"0"   |"Camisas"        |"Linea 2" |"Mujer"     |"0"   |"xid_line"    |"Linea 3"   |200      |
            |"Camisas"  |"Linea 1" |"Mujer"    |"0"   |"Camisas"        |"Linea 1" |"Embarazada"|"0"   |"xid_sex"     |"Hombre"    |200      |
            |"Camisas"  |"Linea 1" |"Mujer"    |"0"   |"Camisas"        |"Linea 1" |"Mujer"     |"1"   |"variant"     |"2"         |200      |
            |"Camisas"  |"Linea 1" |"Mujer"    |"0"   |"Pantalones"     |"Linea 1" |"Mujer"     |"0"   |"xid_family"  |"Pantalones"|200      |
            |"Camisas"  |"Linea 1" |"Mujer"    |"0"   |"Camisas"        |"Linea 2" |"Mujer"     |"0"   |"xid_line"    |"Linea 2"   |200      |
            |"Camisas"  |"Linea 1" |"Mujer"    |"0"   |"Camisas"        |"Linea 1" |"Embarazada"|"0"   |"xid_sex"     |"Embarazada"|200      |
            |"Camisas"  |"Linea 1" |"Mujer"    |"0"   |"Camisas"        |"Linea 1" |"Mujer"     |"1"   |"variant"     |"1"         |200      |

