# BDecotex
Personal solution for a small PYME management

Install Apache2
Add to configuration apache rewrite module
Add virtual host with config add enable overwrite for the project folder to apache, example
	<Directory "/var/www/html">
        AllowOverride All
		Allow from All
    </Directory>

Create libs folder inside app and copy necessary libs:
	- Copy uncompressed "src" folder of fastRoute lib. The path for the fastRoute lib must be app/libs/fastRoute/bootstrap.php
	- Copy unconpressed folder src/Valitron for valitron lib. The path for the valitron lib must be app/libs/valitron/Validator.php
	- Also you need to copy lang/es.php file into Valitron folder. The path for the language file of valitron lib must be app/libs/valitron/es.php

Create the database "bdecotex" at mysql
Import at the database the tables:
	- family
	- line
	- sex
	- model
	- message
Configure DB connection at BDecotex/backend/app/config.php.inc file
To refill tables with data, you can execute "php test.php" at BDecotex/backend/app/tools/


