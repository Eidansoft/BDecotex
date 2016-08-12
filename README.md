# BDecotex
Personal solution for a small PYME management

Install Apache2
Add to configuration apache rewrite module
Add virtual host for the project folder to apache
At virtualhost config add enable rewrite and follow symbolic links (if needed)
Create libs folder inside app and copy uncompressed "src" folder of fastRoute lib.
The path for teh lib must be app/libs/fastRoute/bootstrap.php

