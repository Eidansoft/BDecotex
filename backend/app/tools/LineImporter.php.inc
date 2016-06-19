<?php
require_once (dirname(__FILE__).'/BDecotexImporter.php.inc');
require_once '../model/LineDAOImpl.php.inc';

/**
 * Description of LineImporter
 *
 * @author alex
 */
class LineImporter extends BDecotexImporter {
    
    public function __construct() {
        parent::__construct(realpath(dirname(__FILE__)."/../../../originales/Lineas.xml"), new LineDAOImpl());
    }

    protected function processObject($object) {
        $this->dao->create($object->Descripción);
    }

}
