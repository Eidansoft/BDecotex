Feature: Family CRUD feature
	Para gestionar familias
	Como usuario administrador
	necesitamos poder crear, modificar, consultar y eliminar familias

	Scenario: Crear familia de productos
		Given El servidor esta corriendo
		When el usuario crea la familia "familia de prueba" con codigo "001"
		Then el sistema responde un codigo http "200"
                And el sistema responde con la familia enviada
	Scenario: Modificar familia de productos
		Given El servidor esta corriendo
		And existe al menos una familia creada en el sistema
		When el usuario modifica la familia al nuevo nombre "Familia MOD" con codigo "002"
                Then el sistema responde un codigo http "200"
                And el sistema responde con la familia enviada
