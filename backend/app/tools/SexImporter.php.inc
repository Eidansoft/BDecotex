<?php
require_once (dirname(__FILE__).'/BDecotexImporter.php.inc');
require_once '../model/SexDAOImpl.php.inc';

/**
 * Description of SexImporter
 *
 * @author alex
 */
class SexImporter extends BDecotexImporter {
    
    public function __construct() {
        parent::__construct(realpath(dirname(__FILE__)."/../../../originales/Sexo.xml"), new SexDAOImpl());
    }

    protected function processObject($object) {
        $this->dao->create($object->Sexo, $object->Código);
    }

}
