<?php
require_once (dirname(__FILE__).'/BDecotexImporter.php.inc');
require_once '../model/FamilyDAOImpl.php.inc';

/**
 * Description of FamilyImporter
 *
 * @author alex
 */
class FamilyImporter extends BDecotexImporter {
    
    public function __construct() {
        parent::__construct(realpath(dirname(__FILE__)."/../../../originales/Familias.xml"), new FamilyDAOImpl());
    }

    protected function processObject($object) {
        $this->dao->create($object->Desc,
                           $object->Cod);
    }

}
