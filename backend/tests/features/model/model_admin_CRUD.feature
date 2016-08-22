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
  #          |"null"              |"Linea 1" |"Hombre"   |0     |404      |
  #          |"Abrigos"           |"null"    |"Hombre"   |0     |404      |
  #          |"Abrigos"           |"Linea 1" |"null"     |0     |404      |
  #          |"Abrigos"           |"Linea 1" |"Hombre"   |"null"|404      |

